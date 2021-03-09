// 2008 andrewl

// OS
#include <windows.h>

// cstdlib
#include <stdio.h>

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

#define DEPTH_CUTOFF 1000

BOOL search(DWORD r_eax, DWORD r_ebx, DWORD cf, UINT depth_curr, BOOL bPrint)
{

    if(bPrint)
    {
        for(int i=0; i<depth_curr; ++i)
            printf(" ");

        printf("EAX=%08X EBX=%08X cf=%d ENTERED SEARCH (AFTER cm's EXCH)\n", r_eax, r_ebx, cf);
    }

    if(depth_curr == DEPTH_CUTOFF)
    {
        printf("reached cutoff with (eax,ebx) = (%08X,%08X)\n", r_eax, r_ebx);
        return 1;
    }

    // undo the xchg
    r_eax ^= r_ebx;
    r_ebx ^= r_eax;
    r_eax ^= r_ebx;

    if( ((r_eax < 0x11223344) && (cf != 1)) ||
        ((r_eax >= 0x11223344) && (cf != 0))    )   // carry flag must have been set on last add of 0x11223344
            return 0;

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
    BYTE bitbuff[8];
    *(PDWORD)(bitbuff) = r_eax;
    *(PDWORD)(bitbuff+4) = (r_eax << 1) | cf;
    ULONGLONG ull = *(PULONGLONG)bitbuff;

    for(int i=0; i<33; ++i)
    {
        BYTE b = ull & 0xFF;
        DWORD new_eax;
        BYTE new_cf;

        new_eax = rcl(r_eax, b, cf, &new_cf);

        if( (new_eax & 0xFF) == b)
            if(search(new_eax, r_ebx, new_cf, depth_curr+1, bPrint))
                return 1;

        ull >>= 1;
    }

    return 0;
}

void main(void)
{
    printf("hi\n");
    //search(0xFFFF5EEC, 0xFA0ABFEC, 0, 0, 1);
    //return;

    for(DWORD r_eax = 0x90000000; r_eax > 0; r_eax--)
    {
        // we need two DWORDs that XOR to 0x5F5E100
        DWORD r_ebx = r_eax ^ 0xD5446474;

        //r_eax = 0xFFFFFFFE;
        //r_ebx = 0xFA0A1EFE;

        if(search(  r_eax,
                    r_ebx,
                    0,      // carry flag
                    0,      // initial depth
                    0       // print ?
                    ))
        {
            printf("search returned 1 using (eax,ebx) = (%08X,%08X)\n", r_eax, r_ebx);
            return;
        }

        if(!(r_eax % 0x00100000))
            printf("On %08X\n", r_eax);
    }

    return;
}
