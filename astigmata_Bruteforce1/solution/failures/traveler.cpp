// 2008 andrewl

#include <windows.h>

#include <stdio.h>

#include "state.h"
#include "known_solutions.h"

STATE solutions[1024];
DWORD nSolutions;

BOOL does_sol_exist(STATE t)
{
    for(int i=0; i<nSolutions; ++i)
        if(!memcmp(&t, solutions+i, sizeof(t)))
            return 1;

    return 0;
}

unsigned __int64 hexStrToUint64(const char * hex_string)
{
    unsigned __int64 result = 0;
    int len = 0, i = 0;
    unsigned char value;

    if(hex_string[0] == '0' && hex_string[1] == 'x')
        hex_string += 2;

    // find strlen
    len=-1;
    while(hex_string[++len]!='\0');

    if(len > 16)
        return -1;

    for(i=0; i<len; i++) {
        char temp = hex_string[i];

        if((temp >= 0x30) && (temp <= 0x39)) // [0-9]
            value = temp - 0x30;
        else if(temp >= 0x41 && temp <= 0x46) // [A-F]
            value = temp - 0x37;
        else if(temp >= 0x61 && temp <= 0x66) // [A-Fa-f]
            value = temp - 0x57;
        else
            return -1;

        result <<= 4;
        result |= value;
    }

    return result;
}

void iterate(PSTATE t, DWORD i)
{
    while(i--)
    {
        DWORD shamt = t->eax & 0x1F;

        if(shamt)
        {
            DWORD left = 0, right, ceffect;

            right = t->eax >> shamt;

            shamt = 32 - shamt;
            ceffect = t->CF << shamt;

            if(++shamt < 32)
                left = t->eax << shamt;
            
            t->eax = left | ceffect | right;          
        }

        t->eax += t->ebx;
        t->eax += 0x11223344;

        t->CF = 0;
        if(t->eax < 0x11223344)
            t->CF = 1;

        t->eax ^= t->ebx;
        t->ebx ^= t->eax;
        t->eax ^= t->ebx;
    }
}

DWORD search(DWORD init)
{
    DWORD retVal = 0;

    DWORD i=0;

    STATE t={0};
    STATE t1={0};
    STATE t2={0};

    // INITIAL STATE
    t.CF = 0;
    t.eax = init;
    t.ebx = 0;

    // TIMER
    SYSTEMTIME time0;
    GetLocalTime(&time0);

    while(1)
    {
        DWORD shamt = t.eax & 0x1F;

        if(shamt)
        {
            DWORD left = 0, right, ceffect;

            right = t.eax >> shamt;

            shamt = 32 - shamt;
            ceffect = t.CF << shamt;

            if(++shamt < 32)
                left = t.eax << shamt;
            
            t.eax = left | ceffect | right;          
        }

        t.eax += t.ebx;
        t.eax += 0x11223344;

        t.CF = 0;
        if(t.eax < 0x11223344)
            t.CF = 1;

        t.eax ^= t.ebx;
        t.ebx ^= t.eax;
        t.eax ^= t.ebx;

        // MARK 100 MILLION
        if(++i == 100000000)
        {
            //printf("100e6 marker (eax,ebx,CF) = (%08X,%08X,%d)\n", t.eax, t.ebx, t.CF);
            t2 = t1;
            t1 = t;
            i=0;

            // also test if we've used up too much time (and are probably looping)
            SYSTEMTIME time1;
            GetLocalTime(&time1);

            DWORD sec0 = time0.wHour * 3600 + time0.wMinute * 60 + time0.wSecond;
            DWORD sec1 = time1.wHour * 3600 + time1.wMinute * 60 + time1.wSecond;

            if(sec1 - sec0 > 20)
            {
                printf("timeout\n");
                goto cleanup;
            }

        }

        // HIT SOLUTION, BACKTRACE
        if((t.eax ^ t.ebx) == 0x0D5446474)
        {
            // we are i iterations from the t1 state
            // we are 100000000+i iterations from the t2 state
            // we want the state 100000000 iterations ago
            if(!t2.eax && !t2.ebx)
            {
                printf("solution found too soon, no history to backtrace it!\n");
                goto cleanup;
            }

            STATE z = t2;
            iterate(&z, i);

            // if it exists, return
            if(does_sol_exist(z))
                goto cleanup;

            // a new one? then add it and continue the search
            solutions[nSolutions++] = z;
            printf("solution (eax,ebx,CF)={0x%08X, 0x%08X, %d},\n", z.eax, z.ebx, z.CF);

            // reset timer then, since we're on the trail of new solutions
            GetLocalTime(&time0);

            // is the entire thing done? can I return to life now?
            if(z.ebx == 0)
            {
                printf("holy fucking shit yo!\n");
                retVal = 1;
                goto cleanup;
            }
        }
    }

    cleanup:

    return retVal;
}

void main(int argc, char * argv[])
{
    DWORD init = 0xDEADBEEF;

    if(argc > 1)
        init = (DWORD) hexStrToUint64(argv[1]);

    for(int i=0; i<N_KNOWN_SOLUTIONS; ++i)
        solutions[nSolutions++] = known_solutions[i];

    while(1)
    {
        printf("search(0x%08X)\n", init);
        if(search(init))
            break;

        init = (init * 0xDEADBEEF) % -1; 
    }
}
