// 2008 andrewl

// OS
#include <windows.h>

// cstdlib
#include <stdio.h>

// custom types
#include "state.h"
#include "known_solutions.h"

// globals
DWORD g_depth_cutoff;

// functions
DWORD rcl(DWORD x, BYTE n, BYTE cf, PBYTE p_new_cf)
{
    BYTE new_cf;

    __asm
    {
        pushf;
        mov cl, [cf];
        rcr cl, 1;
        mov cl, [n];
        mov eax, [x];
        rcl eax, cl;
        rcl cl, 1;
        and cl, 0x01;
        mov [new_cf], cl;
        mov [x], eax;
        popf;
    }

    if(p_new_cf)
        *p_new_cf = new_cf;

    return x;
}

DWORD rcr(DWORD x, BYTE n, BYTE cf, PBYTE p_new_cf)
{
    BYTE new_cf;

    __asm
    {
        pushf;
        mov cl, [cf];
        rcr cl, 1;
        mov cl, [n];
        mov eax, [x];
        rcr eax, cl;
        rcl cl, 1;
        and cl, 0x01;
        mov [new_cf], cl;
        mov [x], eax;
        popf;
    }

    if(p_new_cf)
        *p_new_cf = new_cf;

    return x;
}

unsigned __int64 hexStrToUint64(const char * hex_string)
{
    unsigned __int64 result = 0;
    int len=0, i=0;
    unsigned char value;

    if(hex_string[0]=='0' && hex_string[1]=='x')
        hex_string += 2;

    // find strlen
    len=-1;
    while(hex_string[++len]!='\0');

    if(len > 8)
        return -1;

    for(i=0; i<len; i++) {
        char temp = hex_string[i];

        if((temp>=0x30) && (temp <=0x39)) // [0-9]
            value = temp - 0x30;
        else if(temp>=0x41 && temp<=0x46) // [A-F]
            value = temp - 0x37;
        else if(temp>=0x61 && temp<=0x66) // [A-Fa-f]
            value = temp - 0x57;
        else
            return -1;

        result = result | (unsigned long)(value << ((len-i-1) * 4));
    }

    return result;
}

void search(DWORD r_eax, DWORD r_ebx, DWORD cf, UINT depth_curr, BOOL bPrint)
{

    if(bPrint)
    {
        for(int i=0; i<depth_curr; ++i)
            printf(" ");

        printf("EAX=%08X EBX=%08X cf=%d ENTERED SEARCH (AFTER cm's EXCH)\n", r_eax, r_ebx, cf);
    }

    if(depth_curr == g_depth_cutoff)
    {
        if(r_ebx == 0)
            printf("\n\n\n******holy fucking shit!******\n\n\n");
        //printf("additional solution: (eax,ebx,cf) = (%08X,%08X,%d)\n", r_eax, r_ebx, cf);
        return;
    }

    // undo the xchg
    r_eax ^= r_ebx;
    r_ebx ^= r_eax;
    r_eax ^= r_ebx;

    if( ((r_eax < 0x11223344) && (cf != 1)) ||
        ((r_eax >= 0x11223344) && (cf != 0))    )   // carry flag must have been set on last add of 0x11223344
            return;

    if(bPrint)
    {
        for(int i=0; i<depth_curr; ++i)
            printf(" ");

        printf("EAX=%08X EBX=%08X cf=%d AFTER cm's ADD\n", r_eax, r_ebx, cf);
    }

    // undo the add 0x11223344
    r_eax += 0xEEDDCCBC;
    // undo the add r_ebx
    r_eax += (0xFFFFFFFF - r_ebx + 1);

    if(bPrint)
    {
        for(int i=0; i<depth_curr; ++i)
            printf(" ");

        printf("EAX=%08X EBX=%08X cf=%d AFTER cm's RCR\n", r_eax, r_ebx, cf);
    }


    // undo the RCR of the low byte
    // form [al][ah][reg_eax hi word][cf][al][ah][reg_eax hi word]
    BYTE bitbuff_NC[8];
    *(PDWORD)(bitbuff_NC) = r_eax;
    *(PDWORD)(bitbuff_NC+4) = (r_eax << 1) | 0;
    ULONGLONG ull_NC = *(PULONGLONG)bitbuff_NC;

    BYTE bitbuff_CY[8];
    *(PDWORD)(bitbuff_CY) = r_eax;
    *(PDWORD)(bitbuff_CY+4) = (r_eax << 1) | 1;
    ULONGLONG ull_CY = *(PULONGLONG)bitbuff_CY;

    for(int i=0; i<33; ++i)
    {
        BYTE b_NC = ull_NC & 0xFF;
        BYTE b_CY = ull_CY & 0xFF;

        DWORD new_eax;
        BYTE new_cf;

        // try carry flag was set after rcl
        new_eax = rcl(r_eax, b_CY, 1, &new_cf);
        if( (new_eax & 0xFF) == b_CY)
        {
            //DWORD verifier = rcr(new_eax, new_eax & 0xFF, new_cf, 0);

            search(new_eax, r_ebx, new_cf, depth_curr+1, bPrint);
        }

        // try carry flag not set
        new_eax = rcl(r_eax, b_NC, 0, &new_cf);
        if( (new_eax & 0xFF) == b_NC)
        {
            //DWORD verifier = rcr(new_eax, new_eax & 0xFF, new_cf, 0);

            search(new_eax, r_ebx, new_cf, depth_curr+1, bPrint);
        }

        ull_NC >>= 1;
        ull_CY >>= 1;
    }

    return;
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

void main(int argc, char * argv[])
{

    g_depth_cutoff = 100;

    for(int i=0; i<N_KNOWN_SOLUTIONS; ++i)
    {
        STATE t = known_solutions[i];

        printf("searching backwards from solution state:\n");
        printf("(eax,ebx,CF)=(%08X,%08X,%d)\n", t.eax, t.ebx, t.CF);
        printf("assumed at depth %d:\n", g_depth_cutoff);

        // go forward depth iterations
        iterate(&t, g_depth_cutoff);

        // now come back
        search(t.eax, t.ebx, t.CF, 0, 0);
    }
}
