// deobfuscator for "jmp around" crackme

#include <windows.h>
#include <stdio.h>

#include <vector>
#include <map>
using namespace std;

#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "BeaEngine.h"

//-------------------------------------------------------------
// NODE STRUCT
//-------------------------------------------------------------

struct _NODE;

typedef struct _NODE
{
    // virtual addresses (where found, where placed)
    DWORD VA_orig;
    DWORD VA_new;

    // references to other nodes (sequential execution, relative)
    _NODE *seq;
    _NODE *rel;

    // the instruction itself
    BYTE instrBytes[16];

} NODE, *PNODE;

//-------------------------------------------------------------
// NODE HELPER PROCESSING FUNCTIONS
//-------------------------------------------------------------

void UpdateRels(PNODE root, PNODE from, PNODE to)
{
    PNODE curr = root;

    while(curr)
    {
        if(curr->rel == from)
            curr->rel = to;

        curr = curr->seq;
    }
}

PNODE FindNodeWithOriginalVA(PNODE root, DWORD VA)
{
    PNODE curr = root;

    while(curr)
    {
        if(curr->VA_orig == VA)
            return curr;

        curr = curr->seq;
    }

    return 0;
}

//-------------------------------------------------------------
// NODE PRINTING FUNCTIONS
//-------------------------------------------------------------

VOID PrintNode(PNODE curr, bool bUseNewAddr)
{
    DISASM dasm;
    memset(&dasm,0,sizeof(DISASM));

    dasm.VirtualAddr = curr->VA_orig;
    if(bUseNewAddr)
    {
        dasm.VirtualAddr = curr->VA_new;
    }

    dasm.EIP = (UINT64) &(curr->instrBytes);
    Disasm(&dasm);

    printf("% 8X% 8X% 8X% 8X %s\n", curr, curr->VA_orig, curr->VA_new, curr->rel, dasm.CompleteInstr);
}

VOID PrintList(PNODE root, bool bUseNewAddr)
{
    PNODE curr=root;

    printf("% 8s% 8s% 8s% 8s %s\n", "ID", "VA_orig", "VA_new", "->rel", "instruction");
    printf("% 8s% 8s% 8s% 8s %s\n", "--", "-------", "------", "-----", "-----------");

    for(INT i=0; curr; ++i)
    {
        PrintNode(curr, bUseNewAddr);
        curr = curr->seq;
    }
}

//-------------------------------------------------------------
// MAIN, THE REAL WORK
//-------------------------------------------------------------

INT main(INT ac, PCHAR *av)
{
    map<DWORD,INT> dsts; // jmp destinations

    HANDLE hFile=CreateFile("Jump Around.exe",GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    HANDLE hMap=CreateFileMapping(hFile,0,PAGE_READONLY,0,0,0);
    PBYTE pFile=(PBYTE)MapViewOfFile(hMap,FILE_MAP_READ,0,0,0);

    DISASM dasm;
    memset(&dasm,0,sizeof(dasm));
    UINT len;

    // --------------------------------------------------------
    // PASS: disassemble, jmp target becomes seq
    // --------------------------------------------------------

    printf("phase1:\n");

    map<DWORD,int> seen;
    vector<DWORD> queue;
    queue.push_back((DWORD)(pFile + 0xFC8)); // VA: 4019c8

    NODE *root = new NODE;
    memset(root, 0, sizeof(NODE));
    root->instrBytes[0] = 0x90;

    NODE *curr = root;

    while(queue.size())
    {
        dasm.EIP = queue[0];
        queue.erase(queue.begin());

        if(seen.find(dasm.EIP) != seen.end())
        {
            printf("skipping %08X (already seen it)\n", dasm.EIP);
            continue;
        }
        seen[dasm.EIP] = 1;

        sequential:
        dasm.VirtualAddr = 0x4019C8+(dasm.EIP-((INT)pFile+0xFC8));
        len = Disasm(&dasm);
        if(len==UNKNOWN_OPCODE)
            { printf("unknown opcode at %08X\n", dasm.VirtualAddr); while(1); }

        curr->seq = new NODE;
        memset(curr->seq, 0, sizeof(NODE));
        curr = curr->seq;
        memcpy(curr->instrBytes, (PVOID)dasm.EIP, len);
        curr->VA_orig = dasm.VirtualAddr;

        if(dasm.Instruction.BranchType == JmpType)
        {
            // record jmp destination
            if(dasm.Instruction.AddrValue<0x4019C8 || dasm.Instruction.AddrValue>=0x00402EEF)
                { printf("instruction jumps out of bounds at %08X\n", dasm.VirtualAddr); while(1); }

            dasm.EIP = (DWORD)(pFile + 0xFC8 + (dasm.Instruction.AddrValue - 0x4019c8));
            goto sequential;
        }

        else
        {
            // don't continue after ret
            if(dasm.Instruction.BranchType == RetType)
                continue;

            // handle jcc
            if(dasm.Instruction.AddrValue && dasm.Instruction.BranchType != CallType)
            {
                queue.push_back((DWORD)(pFile + 0xFC8 + (dasm.Instruction.AddrValue - 0x4019c8)));
                printf("%08I64X: queuing %08I64X as jcc destination\n",dasm.VirtualAddr,dasm.Instruction.AddrValue);                
            }

            // handle normal fall-thru execution (of normal instructions and jcc's)
            printf("%08I64X: %s\n", dasm.VirtualAddr, dasm.CompleteInstr);
            dasm.EIP += len;
            goto sequential;
        }
    }

    PrintList(root, 0);

    // --------------------------------------------------------
    // PASS: populate rel member
    // --------------------------------------------------------

    printf("phase2:\n");

    curr = root; 

    while(1)
    {
        if(!curr->seq)
            break;

        dasm.EIP = (UINT64)curr->instrBytes;
        dasm.VirtualAddr = curr->VA_orig;
        Disasm(&dasm);

        if(dasm.Instruction.BranchType != CallType && dasm.Instruction.BranchType != RetType && dasm.Instruction.AddrValue)
        {
            // find the node that originally resides at this address
            PNODE p = FindNodeWithOriginalVA(root, dasm.Instruction.AddrValue);
            if(!p)
                { printf("%08X references %08X for which there is no node!\n", curr->VA_orig, dasm.Instruction.AddrValue); while(1); }

            curr->rel = p;
        }
            
        curr = curr->seq;
    }

    PrintList(root, 0);

    // --------------------------------------------------------
    // PASS: jmps treated as NOP's, removed
    // --------------------------------------------------------

    printf("phase3:\n");

    curr = root; 

    while(1)
    {
        NODE *n = curr->seq;    // jmp
        if(!n)
            break;
        NODE *nn = n->seq;      // node after jmp
        if(!nn)
            break;

        dasm.EIP = (UINT64)n->instrBytes;
        Disasm(&dasm);

        if(dasm.Instruction.BranchType == JmpType)
        {
            UpdateRels(root, n, nn);

            curr->seq = nn;
            // and curr remains the same (possibly consume >1 jmp)
        }
        else
        {
            curr = n;
        }
    }

    PrintList(root, 0);

    // --------------------------------------------------------
    // PASS: remove inc/dec junk
    // --------------------------------------------------------

    printf("phase4:\n");

    curr = root; 

    while(1)
    {
        NODE *n = curr->seq;
        if(!n)
            break;
        NODE *nn = n->seq;
        if(!nn)
            break;
        NODE *nnn = nn->seq;
        if(!nnn)
            break;

        dasm.EIP = (UINT64)n->instrBytes;
        Disasm(&dasm);

        if(!strcmp(dasm.CompleteInstr, "inc eax"))
        {
            dasm.EIP = (UINT64)nn->instrBytes;
            Disasm(&dasm);

            if(!strcmp(dasm.CompleteInstr, "dec eax"))
            {
                UpdateRels(root, n, nnn);
                UpdateRels(root, nn, nnn);

                curr->seq = nnn;
                // curr remains the same
            }
            else
                curr = curr->seq;
        }
        else
            curr = curr->seq;
    }

    PrintList(root, 0);

    // --------------------------------------------------------
    // PASS: assign new VA's
    // --------------------------------------------------------

    printf("phase5:\n");

    UINT offs = 0;
    curr = root; 

    while(curr)
    {
        dasm.EIP = (UINT64)curr->instrBytes;
        len = Disasm(&dasm);

        curr->VA_new = 0x4019c8 + offs;
        offs += len;

        curr = curr->seq;
    }

    PrintList(root, 1);

    // --------------------------------------------------------
    // PASS: adjust calls
    // --------------------------------------------------------

    printf("phase6:\n");

    curr = root; 

    while(curr)
    {
        dasm.EIP = (UINT64)curr->instrBytes;
        len = Disasm(&dasm);

        if(dasm.Instruction.BranchType == CallType)
        {
            int adjamt = (int)curr->VA_orig - curr->VA_new;

            *(int *)(curr->instrBytes + 1) += adjamt;
        }

        curr = curr->seq;
    }

    PrintList(root, 1);

    // --------------------------------------------------------
    // PASS: adjust jcc
    // --------------------------------------------------------

    printf("phase7:\n");

    curr = root; 

    while(curr)
    {


        if(curr->rel)
        {
            dasm.EIP = (UINT64)curr->instrBytes;
            dasm.VirtualAddr = curr->VA_new;
            len = Disasm(&dasm);
            if(len != 6)
                { printf("expected 0F JCC XX XX XX XX at instruction (ORIGINAL VA: %08X)\n", curr->VA_orig); while(1); }

            int delta = (int)curr->rel->VA_new - (curr->VA_new + 6); 
            *(int *)(curr->instrBytes + 2) = delta;

            len = Disasm(&dasm);
            if(dasm.Instruction.AddrValue != curr->rel->VA_new)
                { printf("fuck!\n"); while(1); }
        }

        curr = curr->seq;
    }

    PrintList(root, 1);

    // --------------------------------------------------------
    // WRITE OUT TO FILE
    // --------------------------------------------------------
    
    DWORD dwRet;

    HANDLE hFile2=CreateFile("Jump Around_deobf.exe",FILE_WRITE_DATA|FILE_APPEND_DATA,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

    WriteFile(hFile2, pFile, 829952, &dwRet, 0);
    SetFilePointer(hFile2, 0xFC8, 0, FILE_BEGIN);
    
    offs = 0;
    curr = root; 

    while(curr)
    {
        dasm.EIP = (UINT64)curr->instrBytes;
        dasm.VirtualAddr = curr->VA_new;
        len = Disasm(&dasm);

        WriteFile(hFile2, curr->instrBytes, len, &dwRet, 0);

        curr = curr->seq;
    }

    UnmapViewOfFile(pFile);
    CloseHandle(hMap);
    CloseHandle(hFile);

    CloseHandle(hFile2);
}
