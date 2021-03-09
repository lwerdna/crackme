// 2010 andrewl

// more random MQ sbox experiments...

// picture:
//                 +--+  
// x00..x15 --+--> |s1| ----------> y00..y14 (16 inputs -> 15 outputs) 
//            |    +--+  
//            |            +--+
//            +----------> |s2|
//                         |  | --> y15..y29 (16 inputs -> 15 outputs)
// x16..x31 -------------> |  | 
//                         +--+ 

// the question is: for a 32 input -> 30 output s-box like s2 above, are collisions
// any harder/easier to find for x16..x31 when x00..x15 are held constant?

// answer is no! the results are the same as a single 16->15 sbox


#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "advapi32.lib")

// error crap
#define ERRCLEANUP(FMT,...) { ReportError((FMT,__VA_ARGS__)); goto cleanup; }

void ReportError(char * fmtstr, ...)
{
	CHAR msg_caller[256];
    CHAR msg_gle[256];
    va_list v1;
    va_start(v1,fmtstr);
    vsprintf(msg_caller,fmtstr,v1);
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,0,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),msg_gle,256,0);
    printf("ERROR: %s\nGetLastError() reports: %s",msg_caller,msg_gle);
    va_end(v1);
}

// wincrypt crap
HCRYPTPROV hCryptProv=0;

BOOL InitRandom()
{
    BOOL bRet=0;

    if(!CryptAcquireContext(&hCryptProv,0,MS_DEF_PROV,PROV_RSA_FULL,0))
        if(!CryptAcquireContext(&hCryptProv,0,MS_DEF_PROV,PROV_RSA_FULL,CRYPT_NEWKEYSET))
            ERRCLEANUP("CryptAcquireContext()");

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

// real work 
UINT lookup[528]; // 32*33/2

UINT64 evaluate(UINT64 x)
{
    WORD result=0;
    INT cursor=0;

    for(INT i=0; i<32; ++i)
        for(INT j=i; j<32; ++j)
        {
            if( (x & (1<<i)) && (x & (1<<j))    )
                result ^= lookup[cursor];

            cursor++;
        }

    return result;
}

VOID GenerateRandomEqus()
{
    for(INT i=0; i<528; ++i)
    {
        UINT64 equsAffected;
        if(!GetRandom(&equsAffected))
            ERRCLEANUP("GetRandom()");

        equsAffected &= 0x7FFF;

        lookup[i] = equsAffected;
    }

    cleanup:
    return;
}

INT main(INT ac, PCHAR *av)
{
    PBYTE output_map = (PBYTE)malloc(32768); // 2^15 (a byte for all possible outputs y)

    InitRandom();

    for(INT i=0; i<10000; ++i)
    {
        GenerateRandomEqus();

        memset(output_map, 0, 32768);

        // choose random value for x00..x15
        //
        UINT64 x00_x15;
        if(!GetRandom(&x00_x15))
            ERRCLEANUP("GetRandom()");

        x00_x15 &= 0xFFFF;

        // for every value of x16..x31
        //
        for(INT x16_x31=0; x16_x31<0x10000; ++x16_x31) // for each of 2^16 inputs
        {
            // form the full input
            //
            UINT64 x00_x31 = (x00_x15 << 16) | x16_x31;

            UINT64 y = evaluate(x00_x31);

            if(y >= 32768) { printf("WTF!!! f(%08X)=%016I64X\n",x00_x31,y); while(1); }
            
            output_map[y]++;
        }

        // count outputs hit
        INT hits=0;
        for(INT j=0; j<32768; ++j)
            if(output_map[j])
                hits++;

        printf("this s-box covered %f of output space\n", (float)hits/32768);
/*
        for(INT j=0; j<32768; ++j)
            printf("%d\n", output_map[j]);
*/

        // arr[i] contains the number of outputs for which there are i inputs
        INT collisions[128];
        memset(collisions,0,128*sizeof(INT));
        for(INT j=0; j<32768; ++j)
        {
            if(output_map[j] > 128) { printf("WTF!!! f(X)=%08X has %d X's\n", j, output_map[j]); while(1); }

            collisions[output_map[j]]++;
        }

        for(INT j=0; j<128; ++j)
            if(collisions[j])
            {
                printf("%f (%d Y's) have %d X's\n", (float)collisions[j]/32768, collisions[j], j);
            }

        float avg_collisions_per_Y=0;

        for(INT j=0; j<128; ++j)
            if(collisions[j])
            {
                avg_collisions_per_Y += (((float)collisions[j]/32768) * j);
            }
        printf("the average Y value has %f X's\n", avg_collisions_per_Y);

        // 

        printf("%f (%d total) of outputs are collidable (>=2 X's)\n", (float)(32768 - collisions[0] - collisions[1])/32768, 32768 - collisions[0] - collisions[1]);

        printf("--\n");
    }

    cleanup:
    return 0;
}

