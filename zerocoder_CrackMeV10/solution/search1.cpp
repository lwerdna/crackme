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

VOID main(INT ac, PCHAR *av)
{
    UINT len = 10;
    if(ac>1)
        len = atoi(av[1]);
    printf("assuming pw len %d\n", len);
    crackme[0x29D] = len;

    CHAR startchar=' ';
    if(ac>2)
        startchar = av[2][0];
    printf("starting with char '%c'\n", startchar);

    // bytes known of the checksum
    crackme[0x295] = 0x2B;
    crackme[0x29B] = 0xD6;
    crackme[0x299] = 0xDE;
    crackme[0x297] = 0x70;

    crackme[0x1BF] = 'T';
    crackme[0x1C0] = 'r';
    crackme[0x1C1] = 'u';
    crackme[0x1C2] = 'e';
    crackme[0x1C3] = '.';
    crackme[0x1C4] = ' ';

    BYTE backup[681];
    memcpy(backup, crackme, 681);

    WORD t0;
    CHAR a, b;

    for(CHAR h=startchar; h<'~'; ++h)
    {
        printf("trying first char '%c'\n", h);
        crackme[0x29E] = h;

        // will brute bytes [294], [296], [298], [29A]
        for(DWORD i=0; i<256; ++i)
        {
            crackme[0x294] = i;

            for(DWORD j=0; j<256; ++j)
            {
                crackme[0x296] = j;

                for(DWORD k=0; k<256; ++k)
                {
                    crackme[0x298] = k;

                    for(DWORD l=0; l<256; ++l)
                    {
                        crackme[0x29A] = l;

                        // round1 must produce "True. "
                        t0 = ROUND1_EQU0;
                        t0 += 0xA4A9;
                        if(t0 != 'rT')
                            continue;

                        // relies on password... can only use upper half
                        // this must produce AB5E to add to BA17 to get 6575 'ue'
                        // thus the xor half must be AB
                        t0 = ROUND1_EQU1;
                        if((t0 >> 8) != 0xAB)
                            continue;

                        t0 = ROUND1_EQU2;
                        t0 += 0x2C15;
                        if(t0 != ' .')
                            continue;

                        // stage2
                        t0 = ROUND2_EQU0;
                        if(t0 != 0xCDAB)
                            continue;
                        t0 = ROUND2_EQU1;
                        if(t0 != 0xF419)
                            continue;
                        t0 = ROUND2_EQU2;
                        if(t0 != 0xF434)
                            continue;

                        printf("Could be: %02X 2B %02X 70 %02X DE %02X D6\n", i,j,k,l);
                    }
                }
            }
        }
    }
}
