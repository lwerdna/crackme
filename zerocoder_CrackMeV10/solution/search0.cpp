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
    // bytes known of the checksum
    crackme[0x295] = 0x2B;
    crackme[0x29B] = 0xD6;
    crackme[0x299] = 0xDE;
    crackme[0x297] = 0x70;

    BYTE backup[681];
    memcpy(backup, crackme, 681);

    WORD t0;
    CHAR a, b, c;

    // will brute bytes [294], [296], [298], [29A]
    for(DWORD i=0; i<256; ++i)
        for(DWORD j=0; j<256; ++j)
            for(DWORD k=0; k<256; ++k)
                for(DWORD l=0; l<256; ++l)
                {

                    crackme[0x294] = i;
                    crackme[0x296] = j;
                    crackme[0x298] = k;
                    crackme[0x29A] = l;

                    // must produce ascii
                    t0 = ROUND1_EQU0;
                    t0 += 0xA4A9;
                    a = t0 & 0xFF;
                    b = (t0 >> 8) & 0xFF;
                    if(a < 'A' || a > 'z' || (a > 'Z' && a < 'a'))
                        continue;
                    if(b < 'A' || b > 'z' || (b > 'Z' && b < 'a'))
                        continue;


                    // must produce ascii also
                    c = crackme[0x299] ^ crackme[0x29A] ^ crackme[0x29B] ^ crackme[0x29C] ^ 0x0A ^ 0xAB;
                    if(a < 'A' || a > 'z' || (a > 'Z' && a < 'a'))
                        continue;


                    t0 = ROUND2_EQU0;
                    if((t0 >> 8) != 0xCD)
                        continue;
                    t0 = ROUND2_EQU1;
                    if(t0 != 0xF419)
                        continue;
                    t0 = ROUND2_EQU2;
                    if((t0 >> 8) != 0xF4)
                        continue;



                    printf("Could be: \"%c%c__. \" (serial may start with %c)\n", a, b, c);
                }


}
