// 2009 andrewl

// random MQ sbox experiment

// how "collideable" is a randomly generated 16->16 bit MQ sbox?

/*
this s-box covered 0.863342 of output space
0.136658 (4478 Y's) have 0 X's
0.271301 (8890 Y's) have 1 X's
0.265869 (8712 Y's) have 2 X's
0.182526 (5981 Y's) have 3 X's
0.090698 (2972 Y's) have 4 X's
0.036682 (1202 Y's) have 5 X's
0.011871 (389 Y's) have 6 X's
0.003418 (112 Y's) have 7 X's
0.000824 (27 Y's) have 8 X's
0.000092 (3 Y's) have 9 X's
0.000061 (2 Y's) have 10 X's
the average Y value has 2.000000 X's
0.592041 (19400 total) of outputs are collidable (>=2 X's)
*/

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
UINT lookup[136]; // 16*17/2

WORD evaluate(WORD x)
{
    WORD result=0;
    INT cursor=0;

    for(INT i=0; i<16; ++i)
        for(INT j=i; j<16; ++j)
        {
            if( (x & (1<<i)) && (x & (1<<j))    )
                result ^= lookup[cursor];

            cursor++;
        }

    return result;
}

VOID GenerateRandomSBox()
{
    for(INT i=0; i<136; ++i)
    {
        UINT64 t;
        GetRandom(&t);
        t &= 0xFFFF;    // can be a member of equations [0..15] (16 equations)
        lookup[i] = t;
    }
}

INT main(INT ac, PCHAR *av)
{
    PBYTE output_map = (PBYTE)malloc(65536); // 2^15 (a byte for all possible outputs y)

    InitRandom();

    for(INT i=0; i<10000; ++i)
    {
        GenerateRandomSBox();

        memset(output_map, 0, 65536);

        for(INT x=0; x<65536; ++x) // for each of 2^16 inputs
        {
            WORD y = evaluate(x);

            if(y >= 65536) { printf("WTF!!! f(%08X)=%08X\n",x,y); while(1); }
            
            output_map[y]++;
        }

        // count outputs hit
        INT hits=0;
        for(INT j=0; j<65536; ++j)
            if(output_map[j])
                hits++;

        printf("this s-box covered %f of output space\n", (float)hits/65536);
/*
        for(INT j=0; j<65536; ++j)
            printf("%d\n", output_map[j]);
*/

        // arr[i] contains the number of outputs for which there are i inputs
        INT collisions[128];
        memset(collisions,0,128*sizeof(INT));
        for(INT j=0; j<65536; ++j)
        {
            if(output_map[j] > 128) { printf("WTF!!! f(X)=%08X has %d X's\n", j, output_map[j]); while(1); }

            collisions[output_map[j]]++;
        }

        for(INT j=0; j<128; ++j)
            if(collisions[j])
            {
                printf("%f (%d Y's) have %d X's\n", (float)collisions[j]/65536, collisions[j], j);
            }

        float avg_collisions_per_Y=0;

        for(INT j=0; j<128; ++j)
            if(collisions[j])
            {
                avg_collisions_per_Y += (((float)collisions[j]/65536) * j);
            }
        printf("the average Y value has %f X's\n", avg_collisions_per_Y);

        // 

        printf("%f (%d total) of outputs are collidable (>=2 X's)\n", (float)(65536 - collisions[0] - collisions[1])/65536, 65536 - collisions[0] - collisions[1]);

        printf("--\n");
    }

}
