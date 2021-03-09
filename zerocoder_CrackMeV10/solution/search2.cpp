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

BOOL g_restart = 0;

DWORD WINAPI RestartThread(LPVOID parameter)
{
    while(1)
    {
        Sleep(60000);
        g_restart = 1;
    }
}

VOID main(INT ac, PCHAR *av)
{
    WORD correctA[4] = {0x2B67, 0xD6CB, 0xDE4C, 0x70CF};
    WORD correctB[4] = {0x2BE7, 0xD64B, 0xDECC, 0x70CF};

    UINT pwlen = 10;
    UINT which = 'A';
    PWORD correct = correctA;

    if(ac > 1)
        pwlen = atoi(av[1]);
    if(ac > 2)
    {
        if(av[1][0] == 'A')
        {
            which = 'A';
            correct = correctA;
        }
        else if(av[1][0] == 'B')
        {
            which = 'B';
            correct = correctB;
        }
    }

    printf("using password length: %d\n", pwlen);
    printf("using correct set: %c\n", which);

    srand(GetTickCount());

    WORD t0, t1, t2, t3, t4;
 
    CHAR currpw[11] = "iiiiiiiiii";

    memset(crackme+0x29D, 0, 12);
    crackme[0x29D] = pwlen;
    memcpy(crackme+0x29E, currpw, pwlen);
    crackme[0x29E+pwlen] = 0x0d;
    UINT diff = -1;

    CreateThread(0, 0, RestartThread, 0, 0, 0);

    do
    {
        if(g_restart)
        {
            g_restart = 0;
            diff = -1;
            memcpy(currpw, "iiiiiiiiii\x00", 11);
            memset(crackme+0x29D, 0, 12);
            crackme[0x29D] = pwlen;
            memcpy(crackme+0x29E, currpw, pwlen);
            crackme[0x29E + pwlen] = 0x0d;
        }

        // make random change
        crackme[0x29E + 1 + rand() % (pwlen-1)] = ' ' + rand() % ('~' - ' ');

        if(rand()%2)
            crackme[0x29E + 1 + rand() % (pwlen-1)] = ' ' + rand() % ('~' - ' ');

        if(rand()%2)
            crackme[0x29E + 1 + rand() % (pwlen-1)] = ' ' + rand() % ('~' - ' ');

        t0 = ROUND0_EQU0;
        *(PWORD)(crackme + 0x294) = t0;
        t1 = ROUND0_EQU1;
        *(PWORD)(crackme + 0x29A) = t1;
        t2 = ROUND0_EQU2;
        *(PWORD)(crackme + 0x298) = t2;
        t3 = ROUND0_EQU3;
        *(PWORD)(crackme + 0x296) = t3;

        t4 = ROUND1_EQU1; // this must produce AB5E to add to BA17 to get 6575 'eu'

        UINT diff2 = abs(t0 - correct[0]) + abs(t1 - correct[1]) + abs(t2 - correct[2]) + abs(t3 - correct[3]) + abs(t4 - 0xAB5E);

        if(diff2 < diff)
        {
            diff = diff2;
            memcpy(currpw, crackme+0x29E, pwlen);
            
            CHAR buff[11];
            memcpy(buff, currpw, pwlen);
            buff[pwlen] = 0;
            printf("pass \"%s\" has output {%04X %04X %04X %04X %04X} (diff: %d)\n", buff, t0, t1, t2, t3, t4, diff);
        }
        else
        {
            memcpy(crackme+0x29E, currpw, pwlen);
        }

   } while(diff);

   printf("found! \"%s\"\n", currpw);
}
