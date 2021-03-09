char *info = "Keygen to BUBLic's \"Xor 2 Zero KeygenMe\" by andrewl Jan 14th, 2009";

//
// code seems funny in places, remember crackme requirement: only AND/XOR can be used to alter equations

#include <windows.h>

#include <stdio.h>
#include <conio.h>

extern "C"
{
#include "md5.h"
}

#undef EXAMPLE
//#define EXAMPLE 1

// EQUATION TYPE IS JUST A BYTE FOR EVERY BIT - LAST BIT FOR AUGMENT
// while kind of wasteful on space, makes addressing stuff much easier
//
#ifdef EXAMPLE
#define EQU_BITS 9
typedef UCHAR EQU[EQU_BITS];
#define EQUATIONS_N 5
#else
#define EQU_BITS 129
typedef UCHAR EQU[EQU_BITS];
#define EQUATIONS_N 100
#endif

// EQUATION OPERATIONS - THESE MAY ONLY USE AND/XOR FOR ACTUAL OPS ON THE BITS
//
void EQU_NOT(EQU c, EQU a);
void EQU_AND(EQU c, EQU a, EQU b);
void EQU_XOR(EQU c, EQU a, EQU b);
void EQU_XCHG(EQU a, EQU b);

// EQUATION TESTS
//
BOOL EQU_ISNONZERO(EQU a);
BOOL EQU_ISEQUAL(EQU a, EQU b);

// FUNCTION DEFINITIONS
//
void EQU_NOT(EQU c, EQU a)
{
    for(UINT i=0; i<EQU_BITS; ++i)
        c[i] = a[i] ^ 1;
}

void EQU_AND(EQU c, EQU a, EQU b)
{
    for(UINT i=0; i<EQU_BITS; ++i)
        c[i] = a[i] & b[i];
}

void EQU_XOR(EQU c, EQU a, EQU b)
{
    for(UINT i=0; i<EQU_BITS; ++i)
        c[i] = a[i] ^ b[i];
}

void EQU_XCHG(EQU a, EQU b)
{
    if(EQU_ISEQUAL(a, b))
        return;

    EQU_XOR(a, a, b);
    EQU_XOR(b, a, b);
    EQU_XOR(a, a, b);
}

// EQUATION TESTS
//
BOOL EQU_ISNONZERO(EQU a)
{
    for(UINT i=0; i<EQU_BITS; ++i)
        if(a[i])
            return 1;

    return 0;
}

BOOL EQU_ISEQUAL(EQU a, EQU b)
{
    EQU c;
    EQU_XOR(c, a, b);

    return !EQU_ISNONZERO(c);
}

// MISCELLANEOUS EQUATION FUNCTION
//
void EQU_PRINT(EQU a)
{

    // convert the bytes representing bits to real bytes
    UCHAR bytes[EQU_BITS/8];
    memset(bytes, 0, EQU_BITS/8);

    for(UINT i=0; i<EQU_BITS-1; ++i)
        bytes[i/8] |= (a[i]<<7) >> (i%8);

    // now print the bytes out
    for(UINT i=0; i<EQU_BITS/8; ++i)
        printf("%02X ", bytes[i]);

    // print out augmented bit
    printf("%02X\n", a[EQU_BITS-1]);
}

void EQU_FROMMD5(EQU a, PUCHAR digest)
{
    // each bits in digest becomes a byte in the EQU a
    for(UINT i=0; i<EQU_BITS-1; ++i)
    {
        a[i] = 0;
        if(digest[i/8] & (0x80 >> (i%8)))
            a[i] = 1;
    }

    // augmented bit, we want solution to be 0
    //
    // from crackme:
    //.text:0040117C                 test    cl, 1
    //.text:0040117F                 mov     [eax+8], ecx
    //.text:00401182                 jnz     short badboy    ;
    a[EQU_BITS-1] = 0;
}

// EQUATIONS BUILDER
//
EQU g_equations[EQUATIONS_N]={0};

void build_equations(PCHAR name)
{
    #ifdef EXAMPLE
    /*
    UCHAR equ0[] = {0, 1, 1, 1, 0, 1, 0, 0, 1};
    UCHAR equ1[] = {0, 0, 0, 1, 1, 0, 1, 1, 1};
    UCHAR equ2[] = {1, 0, 1, 1, 0, 0, 0, 1, 1};
    UCHAR equ3[] = {1, 0, 1, 0, 1, 1, 0, 1, 1};
    UCHAR equ4[] = {0, 1, 1, 1, 0, 1, 0, 1, 1};
    */

    UCHAR equ0[] = {1, 0, 1, 1, 0, 1, 0, 0, 1};
    UCHAR equ1[] = {0, 1, 0, 0, 1, 0, 1, 1, 1};
    UCHAR equ2[] = {1, 1, 0, 1, 1, 0, 0, 0, 1};
    UCHAR equ3[] = {1, 0, 1, 0, 1, 0, 1, 0, 1};
    UCHAR equ4[] = {0, 1, 1, 1, 1, 1, 1, 0, 1};

    for(UINT i=0; i<EQU_BITS; ++i)
    {
        g_equations[0][i] = equ0[i];
        g_equations[1][i] = equ1[i];
        g_equations[2][i] = equ2[i];
        g_equations[3][i] = equ3[i];
        g_equations[4][i] = equ4[i];
    }
    #else
    UCHAR digest[16]={0};
    MD5_CTX ctx={0};
    UINT len = strlen(name);

    MD5Init(&ctx);
    MD5Update(&ctx, (PUCHAR)name, len);
    MD5Final(digest, &ctx);
    EQU_FROMMD5(g_equations[0], digest);

    for(UINT i=1; i<100; ++i)
    {
        // BUBlic's MD5 implementation does this anomoly
        ctx.state[0] = 0;
        ctx.count[0] = len * 0x08;

        MD5Final(digest, &ctx);
        EQU_FROMMD5(g_equations[i], digest);
    }
    #endif
}

void main(INT ac, PCHAR *av)
{
    printf("\n%s\n\n", info);

    printf("[*] parsing args..\n");
    PCHAR name;
    if(ac<2)
    {
        name = "BUBlic";
        printf("no name argument, defaulting...\n");
    }
    else
        name = av[1];
    printf("\n");

    build_equations(name);
    printf("[*] Equations:\n");
    for(UINT i=0; i<EQUATIONS_N; ++i)
        EQU_PRINT(g_equations[i]);

    // GAUSS-JORDAN ELIMINATE THIS
    // 

    // for each coefficient in the g_equations
    INT last_ech=-1;
    UINT coeff=0;
    for(; coeff<EQU_BITS; ++coeff)
    {
        // hunt first equation with nonzero coeff
        // starting with coeff'th equation (due to echelon shape)
        UINT j;
        for(j=last_ech+1; j<EQUATIONS_N; ++j)
            if(g_equations[j][coeff])
                break;

        // not found? next coeff then
        if(j>=EQUATIONS_N)
            continue;

        // place into echelon position
        last_ech++;
        EQU_XCHG(g_equations[j], g_equations[last_ech]);

        // for any remaining row with <coeff> bit set, xor with echelon dude
        for(UINT k=0; k<EQUATIONS_N; ++k)
        {
            if(k==last_ech)
                continue;

            if(g_equations[k][coeff])
                EQU_XOR(g_equations[k], g_equations[k], g_equations[last_ech]);
        }
    }
    printf("\n");

    printf("[*] Equations after Gauss-Jordan:\n");
    for(UINT i=0; i<EQUATIONS_N; ++i)
        EQU_PRINT(g_equations[i]);
    printf("\n");

    // BACK SOLVE
    //
    printf("[*] Backsolving..\n");
    EQU answer;
    memset(answer, 0xFF, EQU_BITS);

    for(INT i=EQUATIONS_N-1; i>=0; --i)
    {
        UCHAR curr_xor=0;

        printf("equation:%d ", i);

        // find pivot
        UINT j;
        for(j=0; j<EQU_BITS-1; ++j)
        {
            if(g_equations[i][j])
            {
                printf("pivot:%d\n", j);

                if(answer[j] != 0xFF)
                    printf("backsolve error!\n");

                answer[j] = 0;

                // xor with coeff's to the right
                for(UINT k=j+1; k<EQU_BITS-1; ++k)
                    if(g_equations[i][k])
                    {
                        if(answer[k] == 0xFF)
                        {
                            answer[k] = 1;
                            answer[j] ^= 1;

                            printf("v%d:1\n", k);
                        }
                        else
                        {
                            answer[j] ^= answer[k];
                        }
                    }

                // finally xor with augment bit
                answer[j] ^= g_equations[i][EQU_BITS-1];

                printf("v%d:%d\n", j, answer[j]);

                goto done_pivot;
            }
        }
                
        printf("pivot error!\n");

        done_pivot:
        __asm nop;
    }
    printf("\n");

    printf("[*] Answer vector:\n");
    #ifdef EXAMPLE 
    for(UINT i=0; i<8; ++i)
        printf("%d ", answer[i]);
    printf("\n");
    #else
    for(UINT i=0; i<128; ++i)
        printf("%d ", answer[i]);
    printf("\n");
    //EQU_PRINT(answer);
    printf("\n");

    printf("[*] Name: %s\n", name);

    // k now form answer in serial-number form
    UCHAR serial[16];
    memset(serial, 0, 16);

    for(UINT i=0; i<128; ++i)
        serial[i/8] |= answer[i]<<7 >> (i%8);

    printf("[*] Serial: %08X-%08X-%08X-%08X\n", *(PDWORD)serial, *(PDWORD)(serial+4), *(PDWORD)(serial+8), *(PDWORD)(serial+12));
    #endif

    getch();
}
