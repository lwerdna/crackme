#include <windows.h>
#include "common.h"
/*************************************************************
 *
 * RANDOMIZING FUNCTIONS/VARIABLES
 *
 *************************************************************/

HCRYPTPROV hCryptProv=0;


BOOL InitRandom()
{
    BOOL bRet=0;

    if(!hCryptProv)
    {
        if(!CryptAcquireContext(&hCryptProv,0,MS_DEF_PROV,PROV_RSA_FULL,0))
            if(!CryptAcquireContext(&hCryptProv,0,MS_DEF_PROV,PROV_RSA_FULL,CRYPT_NEWKEYSET))
                ERRCLEANUP("CryptAcquireContext()");
    }

    bRet=1;
    cleanup:
    return bRet;
}

BOOL GetRandom(UINT64 *val)
{
    BOOL bRet=0;

    if(!CryptGenRandom(hCryptProv,8,(PBYTE)val)) 
        ERRCLEANUP("CryptGetRandom()");

    bRet=1;
    cleanup:
    return bRet;
}

BOOL ReleaseRandom()
{
    if(hCryptProv) 
        CryptReleaseContext(hCryptProv, 0);
            
    return 1;
}
