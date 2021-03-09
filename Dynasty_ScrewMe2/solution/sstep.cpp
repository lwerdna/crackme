// os level includes
#include <windows.h>
#define STATUS_SUCCESS 0

// crt
#include <stdio.h>

// stl
#include <map>

// my junk
#include "funconversions.h"
#include "funconsolehelpers.h"

// globals
typedef NTSTATUS (NTAPI * PFN_NTSYSTEMDEBUGCONTROL)(INT,PVOID,ULONG,PVOID,ULONG,PULONG);
PFN_NTSYSTEMDEBUGCONTROL pfn_NtSystemDebugControl=0;

BOOL g_verbose=0;

#define VERBOSE(...) { if(g_verbose) printf(__VA_ARGS__); }

#define ARGHELPSTR  "\n" \
                    "Branch Tracer - andrewl\n" \
                    "Build Date: %s\n" \
                    "\n" \
                    "syntax:\n" \
                    "%s <exe_file> <start_addr> [P:<passes>] [-V] [S:<start>] [E:<end>]\n" \
                    "\n" \
                    "    switch type      description\n" \
                    "---------- --------- --------------------------------------------------\n" \
                    "  exe_file (string)  path of trace target\n" \
                    "start_addr (numeric) address that trace should start\n" \
                    "    passes (numeric) number of times start_addr hit before trace starts\n" \
                    "                     default: 1\n" \
                    " start,end (numeric) address window that should be printed\n" \
                    "                     default: print all addresses\n" \
                    "        -v (n/a)     be verbose\n" \
                    "\n" \
                    "notes:\n" \
                    "-----------------------------------------------------------------------\n" \
                    "- all numeric arguments in hex\n" \
                    "- currently specific to Intel Core CPU's, other options soon\n" \
                    "\n" \
                    "description:\n" \
                    "-----------------------------------------------------------------------\n" \
                    "branch traces execution in address range. optionally waits for some   " "\n" \
                    "given passes at start of range before activating trace. only thread   " "\n" \
                    "that first activated trace is traced. tries to limit trace target to  " "\n" \
                    "one core. optionally will print only addresses in a certain range,    " "\n" \
                    "though all addresses are actually being stepped." "\n" \
                    "\n" \
                    "though not as pretty, the most efficient thing to do is only print out\n" \
                    "addresses where branches were taken. with just a length disassembler,\n" \
                    "block structure and non-taken branches follow.\n" \
                    "\n"

//
//
int GainPrivileges(void)
{
    BOOL bRet=0;

	HANDLE hToken;
	BOOL bEnablePRivilege = TRUE;
	LUID luid;
	TOKEN_PRIVILEGES tp;

	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken))
        ERRCLEANUP("OpenProcessToken()");

	if(!LookupPrivilegeValueA(NULL,"SeDebugPrivilege",&luid))
        ERRCLEANUP("LookupPrivilegeValueA()");
	
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),FALSE,FALSE))
        ERRCLEANUP("AdjustTokenPrivileges()");

	CloseHandle(hToken);

    bRet=1;

    cleanup:

    return bRet;
}

//
// SET/RESET MSR's
//

#define SysDbgReadMsr 16
#define SysDbgWriteMsr 17

#define MSR_LASTBRANCH_TOS 0x1C9
#define MSR_DEBUGCTLA 0x1D9
#define MSR_LASTBRANCH_0 0x40

#define LBR 0x01 // last branch record
#define BTF 0x02


typedef struct _SysDbgMsr{
    ULONG Address;
    ULONGLONG Data;
} SysDbgMsr, *PSysDbgMsr;

BOOL SetMsr(ULONG address, ULONGLONG data)
{
    SysDbgMsr msr;
    msr.Address = address;
    msr.Data = data;

    NTSTATUS status = pfn_NtSystemDebugControl(SysDbgWriteMsr, (PVOID)&msr, sizeof(msr), 0, 0, 0);

    if(status == STATUS_SUCCESS)
        return 1;

    cleanup:
    return 0;
}

BOOL ReadMsr(ULONG address, ULONGLONG *pdata)
{
    SysDbgMsr msr;
    msr.Address=address;

    NTSTATUS status = pfn_NtSystemDebugControl(SysDbgReadMsr, (PVOID)&msr, sizeof(msr), 0, 0, 0);

    if(status == STATUS_SUCCESS) {
        *pdata = msr.Data;
        return 1;
    }

    cleanup:
    return 0;
}

BOOL GetLastBranch(ULONGLONG *branch)
{
    BOOL bRet=0;

    // get top of stack
    ULONGLONG tos;
    if(!ReadMsr(MSR_LASTBRANCH_TOS, &tos))
        ERRCLEANUP("ReadMsr()");
    VERBOSE("tos: %d\n", tos);

    // seek stack
    ULONGLONG record;
    if(!ReadMsr(MSR_LASTBRANCH_0+tos, &record))
        ERRCLEANUP("ReadMsr()");

    *branch = record;

    // this appears to never happen, despite the docs!
    // we only have the "from" address, which is ok, 'cause our EH is called at the "to" address
    // kind of just leaving here to find if there's a computer where it actually happens
    if((ULONG)(record>>32))
        printf("Crazy Processor! Email me!!!: %08X\n", (ULONG)(record>>32));

    bRet=1;

    cleanup:

    return bRet;
}

int main(int argc, char * argv[])
{
    int                 iFuncRet=-1;
    BOOL                bRet;

    // arg stuff
    //
    BOOL bArgsOk=0;

    // process creation stuff
    //
    STARTUPINFO si={0};
    PROCESS_INFORMATION pi={0};

    // debugger stuff
    //
    DEBUG_EVENT         de;

    BOOL                bBreakDebugLoop=0;

    PCHAR               pathToTarget;
    ULONGLONG           nPasses=1;
    ULONGLONG           ullStart=-1, ullEnd=-1, ullNumInstr=-1;
    ULONGLONG           windowStart=0, windowEnd=-1;

    BOOL                bShowAddresses=1;
    BOOL                bShowOperands=1;
    BOOL                bUsermodeCodeOnly=0;

    UCHAR               preCCByte=0;
    CONTEXT             context={0};

    DWORD               dwRet=0;

    #define STATE_INIT 1                // program just started
    #define STATE_BP_START_INSERTED 2   // CREATE_PROCESS_DEBUG_EVENT received, initial BP inserted
    #define STATE_BP_START_DELAYING 3   // start BP hit, but are counting down passes
    #define STATE_TRACE_ACTIVE 4        // start BP hit, trace active for activeThreadId
    INT state = STATE_INIT;

    // have this here just to watch that trace should only happen for this ThreadId... of course the TF is set
    // on per-thread basis (BTF,LBR global per core) 
    //
    DWORD activeThreadId;

    // this maps threadid->THREADINFO
    //
    typedef struct _THREADINFO
    {
        HANDLE hThread;     // handle to thread
        INT order;          // number of thread

    } THREADINFO, *PTHREADINFO;

    std::map<DWORD,THREADINFO> tInfo;

    UINT currThreadOrder=0;

    // parse args
    //
    if(argc > 2)
    {
        pathToTarget=argv[1];

        if(!hexStrToUint64(argv[2], &ullStart))
            ERRCLEANUP("parsing start address: %s", argv[2])
    }

    for(int i=3; i<argc; ++i)
    {
        if(!strncmp(argv[i],"P:",2))
        {
            if(!hexStrToUint64(&argv[i][2], &nPasses))
                ERRCLEANUP("parsing passes argument: %s", argv[i])
        }
        else if(!strncmp(argv[i],"-V",2))
        {
            g_verbose=1;
        }
        else if(!strncmp(argv[i],"S:",2))
        {
            if(!hexStrToUint64(&argv[i][2], &windowStart))
                ERRCLEANUP("parsing window start argument: %s", argv[i])
        }
        else if(!strncmp(argv[i],"E:",2))
        {
            if(!hexStrToUint64(&argv[i][2], &windowEnd))
                ERRCLEANUP("parsing window end argument: %s", argv[i])
        }
        else
        {
            ERRCLEANUP("unrecognised option: %s", argv[i]);
        }
    }

    if(argc<3)
        bArgsOk=0;
    else if(ullStart==-1)
        ERRCLEANUP("must specify S:\n")
    else
        bArgsOk=1;

    if(!bArgsOk)
    {
        printf(ARGHELPSTR, __TIMESTAMP__, argv[0]); 
        goto cleanup;
    }

    VERBOSE("Parsed args:\n");
    VERBOSE("-----------------------------------------------------------------------\n");
    VERBOSE("       start: %08I64X\n", ullStart);
    VERBOSE("      passes: %08I64X\n", nPasses);
    VERBOSE("window start: %08I64X\n", windowStart);
    VERBOSE("  window end: %08I64X\n", windowEnd);
    VERBOSE("     verbose: 1\n");

    //
    if(!GainPrivileges())
        ERRCLEANUP("GainPrivileges()");

    // get NTDLL address/function
    //
    {
        HMODULE hNtdll = LoadLibrary("ntdll");
        if(!hNtdll)
            ERRCLEANUP("LoadLibrary()");
        pfn_NtSystemDebugControl = (PFN_NTSYSTEMDEBUGCONTROL)GetProcAddress(hNtdll, "NtSystemDebugControl");
        if(!pfn_NtSystemDebugControl)
            ERRCLEANUP("GetProcAddress()");
    }

    // make us (and child process target) execute only on first processor
    //
    VERBOSE("trying to get on first core...\n");
    SetProcessAffinityMask(GetCurrentProcess(), 1);
    Sleep(500);

    // LAUNCH PROG
    //
    si.cb=sizeof(STARTUPINFO);

    if(!CreateProcess(argv[1],0,0,0,0,DEBUG_PROCESS|DEBUG_ONLY_THIS_PROCESS,0,0,&si,&pi))
        ERRCLEANUP("creating process");

    // store initial thread
    tInfo[pi.dwThreadId].order=currThreadOrder++;
    tInfo[pi.dwThreadId].hThread=pi.hThread;

    // 
    while(!bBreakDebugLoop && WaitForDebugEvent(&de, INFINITE))
    {
        DWORD       dwContinueStatus=DBG_CONTINUE;

        switch(de.dwDebugEventCode)
        {
            case CREATE_PROCESS_DEBUG_EVENT:
            {
                VERBOSE("CREATE_PROCESS_DEBUG_EVENT\n");
                VERBOSE("initial thread id:%08X handle:%08X\n", de.dwThreadId, de.u.CreateProcessInfo.hThread);
                VERBOSE("inserting breakpoint\n");

                if(!ReadProcessMemory(pi.hProcess, (void *)ullStart, &preCCByte, 1, &dwRet) || dwRet!=1)
                    { ERRCLEANUP("breakpointing read\n"); }

                if(!WriteProcessMemory(pi.hProcess, (void *)ullStart, "\xCC", 1, &dwRet))
                    { ERRCLEANUP("breakpointing write\n"); }

                state = STATE_BP_START_INSERTED;

                break;
            }

            case EXCEPTION_DEBUG_EVENT:
                if(de.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_SINGLE_STEP)
                {
                    VERBOSE("EXCEPTION_SINGLE_STEP\n");
                    VERBOSE("thread id:%08X\n", de.dwThreadId);

                    if(tInfo.find(de.dwThreadId) == tInfo.end())
                        ERRCLEANUP("do not recognise BP'd threadid");

                    VERBOSE("thread handle:%08X\n", tInfo[de.dwThreadId].hThread);
                    VERBOSE("thread order:%08X\n", tInfo[de.dwThreadId].order);

                    if(state == STATE_TRACE_ACTIVE)
                    {
                        // superfluous check: TF *should* be set on per-thread basis, and only
                        // on the first thread that hit the BP on the final pass
                        if(de.dwThreadId == activeThreadId)
                        {
                            // get context
                            memset(&context, 0, sizeof(context));
                            context.ContextFlags=CONTEXT_CONTROL|CONTEXT_INTEGER;

                            if(!GetThreadContext(tInfo[de.dwThreadId].hThread, &context))
                                ERRCLEANUP("GetThreadContext()");

                            // show current branch
                            ULONGLONG last_branch;
                            if(!GetLastBranch(&last_branch))
                                ERRCLEANUP("GetLastBranch()");

                            if(last_branch >= windowStart && last_branch <= windowEnd)
                            {
                                printf("%08X", (ULONG)last_branch);
                                VERBOSE(" -> %08X\n", context.Eip);
                                printf("\n");
                            }

                            // set tracking flags
                            context.EFlags|=0x100;
                            if(!SetThreadContext(tInfo[de.dwThreadId].hThread, &context))
                                ERRCLEANUP("SetThreadContext()");

                            SetMsr(MSR_DEBUGCTLA, LBR|BTF); 
                        }
                        else
                        {
                            VERBOSE("ignoring thread id %d\n", de.dwThreadId);
                        }
                    }
                    else if(state == STATE_BP_START_DELAYING)
                    {
                        // we just single-step'd over the BP'd instruction, restore BP
                        // 
                        if(!WriteProcessMemory(pi.hProcess, (void *)ullStart, "\xCC", 1, &dwRet))
                            { ERRCLEANUP("re-inserting breakpoint\n"); }

                        VERBOSE("re-inserted breakpoint to wait for more passes\n");
                    }
                    else
                        ERRCLEANUP("unknown state when handling EXCEPTION_SINGLE_STEP\n");
                }
                else if(de.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT)
                {
                    VERBOSE("EXCEPTION_BREAKPOINT\n");
                    VERBOSE("thread id:%08X\n", de.dwThreadId);

                    if(tInfo.find(de.dwThreadId) == tInfo.end())
                        ERRCLEANUP("do not recognise BP'd threadid");

                    VERBOSE("thread handle:%08X\n", tInfo[de.dwThreadId].hThread);
                    VERBOSE("thread order:%08X\n", tInfo[de.dwThreadId].order);

                    memset(&context, 0, sizeof(context));
                    context.ContextFlags=CONTEXT_CONTROL;
                    if(!GetThreadContext(tInfo[de.dwThreadId].hThread, &context))
                        ERRCLEANUP("GetThreadContext()");

                    if(context.Eip==(ullStart+1))
                    {
                        if(nPasses == 1)
                        {
                            VERBOSE("reached bp, activating\n");

                            // restore byte replaced by CC
                            if(!WriteProcessMemory(pi.hProcess, (void *)ullStart, &preCCByte, 1, &dwRet) || dwRet!=1)
                                ERRCLEANUP("single stepping\n");

                            // set trap flag
                            context.EFlags|=0x100;

                            // rewind EIP back to where inserted CC was
                            context.Eip-=1;

                            // activate tracing
                            if(!SetThreadContext(tInfo[de.dwThreadId].hThread, &context))
                                ERRCLEANUP("setting context\n");

                            SetMsr(MSR_DEBUGCTLA, LBR|BTF);

                            // 
                            activeThreadId = de.dwThreadId;

                            VERBOSE("set active thread id: %08X\n", activeThreadId);

                            state = STATE_TRACE_ACTIVE;
                        }
                        else
                        {
                            nPasses--;

                            VERBOSE("skipping this breakpoint (%d passes remaining)\n", nPasses);

                            // restore byte replaced by CC
                            if(!WriteProcessMemory(pi.hProcess, (void *)ullStart, &preCCByte, 1, &dwRet) || dwRet!=1)
                                ERRCLEANUP("single stepping\n");

                            // set trap flag
                            context.EFlags|=0x100;

                            // rewind EIP back to where inserted CC was
                            context.Eip-=1;

                            // set trap flag, but ***DEACTIVATE*** BTF,LBR
                            if(!SetThreadContext(tInfo[de.dwThreadId].hThread, &context))
                                ERRCLEANUP("setting context\n");

                            SetMsr(MSR_DEBUGCTLA, 0);

                            //
                            state = STATE_BP_START_DELAYING;
                        }
                    }
                    else
                    {
                        VERBOSE("ignoring breakpoint exception at %08X\n", context.Eip);
                    }

                }
                else
                {
                    VERBOSE("ignoring exception %08X\n", de.u.Exception.ExceptionRecord.ExceptionCode);
                }

                break;

            case CREATE_THREAD_DEBUG_EVENT:
                VERBOSE("CREATE_THREAD_DEBUG_EVENT\n");
                VERBOSE("order:%d id:%08X handle:%08X\n", currThreadOrder, de.dwThreadId, de.u.CreateThread.hThread);
                tInfo[de.dwThreadId].order=currThreadOrder++;
                tInfo[de.dwThreadId].hThread=de.u.CreateThread.hThread;

                break;

            case EXIT_THREAD_DEBUG_EVENT:
                VERBOSE("EXIT_THREAD_DEBUG_EVENT\n");
                VERBOSE("exit code:%08X\n", de.u.ExitThread.dwExitCode);
                break;

            case LOAD_DLL_DEBUG_EVENT:
                VERBOSE("LOAD_DLL_DEBUG_EVENT\n");
                break;

            case OUTPUT_DEBUG_STRING_EVENT:
                VERBOSE("OUTPUT_DEBUG_STRING_EVENT\n");
                break;

            case UNLOAD_DLL_DEBUG_EVENT:
                VERBOSE("UNLOAD_DLL_DEBUG_EVENT\n");
                break;

            case EXIT_PROCESS_DEBUG_EVENT:
                VERBOSE("EXIT_PROCESS_DEBUG_EVENT\n");
                bBreakDebugLoop=1;
                break;
        }

        if(!ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus))
            ERRCLEANUP("ContinueDebugEvent()\n");
    }

    iFuncRet=0;

    cleanup:

    if(pi.hProcess)
        CloseHandle(pi.hProcess);
    if(pi.hThread)
        CloseHandle(pi.hThread);

    return iFuncRet;
}

