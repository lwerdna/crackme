#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "crackme.h"

WORD Equation(PBYTE adders, PBYTE xors, UINT len)
{
    WORD answer=len;
    for(UINT i=0;i<len;++i)
    {
        *((PBYTE)&answer)+=adders[i];
        answer^=*(PWORD)(xors+i);
    }
    return answer;
}

#define ROUND0_EQU0 (Equation(crackme+0x29C,crackme+0x121,0x0B))
#define ROUND0_EQU1 (Equation(crackme+0x29C,crackme+0x113,0x0C))
#define ROUND0_EQU2 (Equation(crackme+0x29A,crackme+0x100,0x0D))
#define ROUND0_EQU3 (Equation(crackme+0x29F,crackme+0x150,0x07))

#define ROUND1_EQU0 (Equation(crackme+0x296,crackme+0x294,0x06))
#define ROUND1_EQU1 (Equation(crackme+0x29C,crackme+0x298,0x06))
#define ROUND1_EQU2 (Equation(crackme+0x294,crackme+0x296,0x06))

#define ROUND2_EQU0 (Equation(crackme+0x1BF,crackme+0x294,0x06))
#define ROUND2_EQU1 (Equation(crackme+0x294,crackme+0x296,0x06))
#define ROUND2_EQU2 (Equation(crackme+0x1BF,crackme+0x296,0x06))

CHAR curr_seed[11];
CHAR curr_offspring[11];
INT i,j,k,w,x,y;

VOID produce_init(CHAR * seed)
{
    strcpy(curr_seed, seed);
    i=1;
    j=i+1;
    k=j+1;
    w=' ';
    x=' ';
    y=' ';
}

BOOL produce_offspring()
{
    BOOL iter_done = 0;

    strcpy(curr_offspring, curr_seed);
    
    goto inside;

    for(i=1; i<8; ++i)
    for(j=i+1; j<9; ++j)
    for(k=j+1; k<10; ++k)
    for(w=' '; w<='~'; ++w)
    for(x=' '; x<='~'; ++x)
    for(y=' '; y<='~'; ++y)
    {
        inside:

        if(iter_done)
            goto outside;

        curr_offspring[i] = w;
        curr_offspring[j] = x;
        curr_offspring[k] = y;

        iter_done = 1;
    }

    outside:

    if(i==8)
        return 0;

    return 1;
}

VOID main(INT ac, PCHAR *av)
{
    WORD t0, t1, t2, t3, t4;
 
    CHAR curr_best[11] = "iiiiiiiiii";

    crackme[0x29D] = 0x0A;
    crackme[0x2A8] = 0x0D;
    
    UINT diff = -1;

    UINT count=0;

    while(1)
    {
        printf("a new g-g-generation! (seed: %s with score %d)\n", curr_best, diff);

        produce_init(curr_best);

        while(produce_offspring())
        {
            
            count++;
            /*
            if(count % 10000 == 0)
                printf("%s\n", curr_offspring);
            */

            memcpy(crackme+0x29E, curr_offspring, 10);

            t0 = ROUND0_EQU0;
            *(PWORD)(crackme + 0x294) = t0;
            t1 = ROUND0_EQU1;
            *(PWORD)(crackme + 0x29A) = t1;
            t2 = ROUND0_EQU2;
            *(PWORD)(crackme + 0x298) = t2;
            t3 = ROUND0_EQU3;
            *(PWORD)(crackme + 0x296) = t3;

            t4 = ROUND1_EQU1; // this must produce AB5E to add to BA17 to get 6575 'eu'

            UINT diff2 = abs(t0 - 0x2B67) + abs(t1 - 0xD6CB) + abs(t2 - 0xDE4C) + abs(t3 - 0x70CF) + abs(t4 - 0xAB5E);

            //if(count % 100000 == 0)
                //printf("%s had difference %d\n", curr_offspring, diff2);

            if(diff2 < diff)
            {
                diff = diff2;
                strcpy(curr_best, curr_offspring);
                printf("pass \"%s\" has output {%04X %04X %04X %04X %04X} (diff: %d)\n", curr_best, t0, t1, t2, t3, t4, diff);
            }
        }
    }
}
