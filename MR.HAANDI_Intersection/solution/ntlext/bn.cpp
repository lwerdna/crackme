// reads some NTL data types, written to fight "Intersection" by Mr.Haandi
// 2010 andrewl

#include <windows.h>
#include <dbgeng.h>

// miracl stuff
extern "C"
{
#include "c:\code\lib\miracl5.3.3\include\miracl.h"
}
#pragma comment(lib, "c:\\code\\lib\\miracl5.3.3\\ms32.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

// globals
miracl * mip;

PDEBUG_CONTROL4 control=0;
PDEBUG_CLIENT4 client=0;
PDEBUG_DATA_SPACES3 dataspaces = 0;

//
//
void DllMain()
{
}

//
//
// DEBUG INTERFACE STUFF
//
// 

BOOL GetInterfaces(PDEBUG_CLIENT4 pclient)
{
    BOOL bRet=0;

    client = pclient;
    if(!client)
        if(DebugCreate(__uuidof(IDebugClient4), (PVOID *)&client) != S_OK)
            goto cleanup;

    if(client->QueryInterface(__uuidof(IDebugControl3), (PVOID *)&control) != S_OK)
        goto cleanup;

    if(client->QueryInterface(__uuidof(IDebugDataSpaces3), (PVOID *)&dataspaces) != S_OK)
        goto cleanup;

    bRet=1;
    cleanup:
    return bRet;
}

VOID ReleaseInterfaces()
{
    if(dataspaces)
    {
        dataspaces->Release();
        dataspaces=0;
    }

    if(control)
    {
        control->Release();
        control=0;
    }

    if(client)
    {
        client->Release();
        client=0;
    }
}

//
//
// DEBUG CALLBACK NOTIFICATIONS
//
// 

extern "C" HRESULT __stdcall DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
    HRESULT hFuncRet=E_FAIL;

    if(!GetInterfaces(0))
        goto cleanup;

    control->Output(DEBUG_OUTPUT_NORMAL,"extension: initializing...\n");

    *Version = DEBUG_EXTENSION_VERSION(1, 0);
    *Flags = 0;

    // init miracl
    mip = mirsys(100, 16);
    mip->IOBASE = 16;

    hFuncRet = S_OK;

    cleanup:
    ReleaseInterfaces();
    return hFuncRet;
}

extern "C" VOID __stdcall DebugExtensionUninitialize(void)
{
    if(!GetInterfaces(0))
        goto cleanup;

    control->Output(DEBUG_OUTPUT_NORMAL,"extension: uninitializing...\n");

    cleanup:
    ReleaseInterfaces();
}

extern "C" VOID WINAPI DebugExtensionNotify(ULONG Notify, ULONG64 Argument)
{
    if(!GetInterfaces(0))
        goto cleanup;

    switch(Notify)
    {
        case DEBUG_NOTIFY_SESSION_ACTIVE:
            //control->Output(DEBUG_OUTPUT_NORMAL,"extension: got DEBUG_NOTIFY_SESSION_ACTIVE\n");
            break;

        case DEBUG_NOTIFY_SESSION_INACTIVE:
            //control->Output(DEBUG_OUTPUT_NORMAL,"extension: got DEBUG_NOTIFY_SESSION_INACTIVE\n");
            break;

        case DEBUG_NOTIFY_SESSION_ACCESSIBLE:
            //control->Output(DEBUG_OUTPUT_NORMAL,"extension: got DEBUG_NOTIFY_SESSION_ACCESSIBLE\n");
            break;

        case DEBUG_NOTIFY_SESSION_INACCESSIBLE:
            //control->Output(DEBUG_OUTPUT_NORMAL,"extension: got DEBUG_NOTIFY_SESSION_INACCESSIBLE\n");
            break;
    }

    cleanup:
    ReleaseInterfaces();
}

//
//
// REAL BIGNUM WORK NOW
//
//
VOID __stdcall DisplayZZ(UINT64 addr)
{
    // see representation details in include\NTL\c_lip.h

    // read number of coefficients for this number
    DWORD dwRet;
    ULONG nCoeffs;
    dataspaces->ReadVirtual(addr,&nCoeffs,4,&dwRet);
    if(nCoeffs>64)
        { control->Output(DEBUG_OUTPUT_NORMAL, "DisplayZZ: >64 coeffs, abandoning\n"); return; }

    // allocate, read the coeff's themselves
    PDWORD coeffs=new DWORD[nCoeffs];
    dataspaces->ReadVirtual(addr+4,coeffs,nCoeffs*4,&dwRet);

    // sign is sign bit on 0'th coeff
    if(coeffs[0]&0x80000000)
        control->Output(DEBUG_OUTPUT_NORMAL, "-");
    else
        control->Output(DEBUG_OUTPUT_NORMAL, "+");

    // evaluate coeff0 * (2^30)^0 + coeff1 * (2^30)^1 + ... + coeffN-1 * (2^30)^(N-1)
    big answer = mirvar(0);
    for(int i=nCoeffs-1; i>=0; --i)
    {
        premult(answer, 0x40000000, answer);
        big coeff = mirvar(0);
        convert((INT)(coeffs[i]&0x7FFFFFFF), coeff);
        add(answer, coeff, answer);
        mirkill(coeff);
    }

    // print it out
    CHAR buff[512];
    mip->IOBASE=10;
    cotstr(answer,buff);
    control->Output(DEBUG_OUTPUT_NORMAL, "%010s",buff);
    mip->IOBASE=16;

    // cleanup
    mirkill(answer);
    delete [] coeffs;
}

HRESULT __stdcall DisplayPoly(UINT64 addr)
{
    HRESULT hRes = E_FAIL;
    DWORD dwRet;

    UINT64 ui64_start = addr;

    // get number of terms
    ULONG nTerms;
    dataspaces->ReadVirtual((UINT64)ui64_start-8,&nTerms,4,&dwRet);
    if(nTerms > 64)
    {
        control->Output(DEBUG_OUTPUT_ERROR, "DisplayPoly: >64 terms, abandoning\n"); 
        goto quit_error; 
    }

    // print each term
    for(INT i=nTerms-1; i>=0; --i)
    {
        UINT addrZZ;
        dataspaces->ReadVirtual((UINT64)ui64_start+4*i, &addrZZ, 4, &dwRet);

        DisplayZZ(addrZZ);

        control->Output(DEBUG_OUTPUT_NORMAL, "*x^%d ",i);
    }

    // cleanup crap
    hRes=S_OK;
    quit_error:
    return hRes;
}

HRESULT __stdcall point(PDEBUG_CLIENT4 Client, PCSTR arg)
{
    HRESULT hRes = E_FAIL;

    // get interfaces
    //
    if(!GetInterfaces(0))
        goto quit_error;

    DWORD dwRet;

    // get arg
    DEBUG_VALUE pdv;
    memset(&pdv,0,sizeof(pdv));
    if(S_OK!=control->Evaluate(arg,DEBUG_VALUE_INT64,&pdv,0))
    {
        control->Output(DEBUG_OUTPUT_ERROR, "error evaluating expression\n");
        goto quit_error;
    }
    UINT64 ui64_start = pdv.I64;

    // get sub vectors
    ULONG subvects[4];
    dataspaces->ReadVirtual(ui64_start,subvects,4*4,&dwRet);

    for(INT i=0; i<4; ++i)
    {
        DisplayPoly(subvects[i]);
        control->Output(DEBUG_OUTPUT_NORMAL, "\n");
    }

    control->Output(DEBUG_OUTPUT_NORMAL, "\n");

    hRes = S_OK;
    quit_error:
    ReleaseInterfaces();
    return hRes;
}

HRESULT __stdcall poly(PDEBUG_CLIENT4 Client, PCSTR arg)
{
    HRESULT hRes = E_FAIL;
    DWORD dwRet;

    // get interfaces
    //
    if(!GetInterfaces(0))
        goto quit_error;

    // get arg
    DEBUG_VALUE pdv;
    memset(&pdv,0,sizeof(pdv));

    if(S_OK!=control->Evaluate(arg,DEBUG_VALUE_INT64,&pdv,0))
    { 
        control->Output(DEBUG_OUTPUT_ERROR, "error evaluating expression\n"); 
        goto quit_error; 
    }
    UINT64 ui64_start = pdv.I64;

    // get number of terms
    ULONG nTerms;
    dataspaces->ReadVirtual((UINT64)ui64_start-8,&nTerms,4,&dwRet);
    if(nTerms>64)
    {
        control->Output(DEBUG_OUTPUT_ERROR, "poly(): >64 terms, abandoning\n"); 
        goto quit_error; 
    }
    //control->Output(DEBUG_OUTPUT_NORMAL, "detected %d terms for poly @%08X\n",nTerms,ui64_start);

    DisplayPoly(ui64_start);
    control->Output(DEBUG_OUTPUT_NORMAL, "\n");

    // cleanup crap
    hRes=S_OK;
    quit_error:
    ReleaseInterfaces();
    return hRes;
}

HRESULT __stdcall polygp(PDEBUG_CLIENT4 Client, PCSTR arg)
{
    HRESULT hRes = E_FAIL;
    DWORD dwRet;

    // get interfaces
    //
    if(!GetInterfaces(0))
        goto quit_error;

    // get arg
    DEBUG_VALUE pdv;
    memset(&pdv,0,sizeof(pdv));

    if(S_OK!=control->Evaluate(arg,DEBUG_VALUE_INT64,&pdv,0))
    { 
        control->Output(DEBUG_OUTPUT_ERROR, "error evaluating expression\n"); 
        goto quit_error; 
    }
    UINT64 ui64_start = pdv.I64;

    // get number of terms
    ULONG nTerms;
    dataspaces->ReadVirtual((UINT64)ui64_start-8,&nTerms,4,&dwRet);
    if(nTerms>64)
    {
        control->Output(DEBUG_OUTPUT_ERROR, "poly(): >64 terms, abandoning\n"); 
        goto quit_error; 
    }
    //control->Output(DEBUG_OUTPUT_NORMAL, "detected %d terms for poly @%08X\n",nTerms,ui64_start);

    control->Output(DEBUG_OUTPUT_NORMAL, "(");
    DisplayPoly(ui64_start);
    control->Output(DEBUG_OUTPUT_NORMAL, ") * Mod(1,p), \\");
    control->Output(DEBUG_OUTPUT_NORMAL, "\n");

    // cleanup crap
    hRes=S_OK;
    quit_error:
    ReleaseInterfaces();
    return hRes;
}

HRESULT __stdcall zz(PDEBUG_CLIENT4 Client, PCSTR arg)
{
    HRESULT hRes = E_FAIL;
    DWORD dwRet;

    // get interfaces
    //
    if(!GetInterfaces(0))
        goto quit_error;

    // get arg
    DEBUG_VALUE pdv;
    memset(&pdv,0,sizeof(pdv));

    if(S_OK!=control->Evaluate(arg,DEBUG_VALUE_INT64,&pdv,0))
    { 
        control->Output(DEBUG_OUTPUT_ERROR, "error evaluating expression\n"); 
        goto quit_error; 
    }

    DisplayZZ(pdv.I64);

    // cleanup crap
    hRes=S_OK;
    quit_error:
    ReleaseInterfaces();
    return hRes;
}

