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
        mov [x], eax;
        xor cl, cl;
        rcl cl, 1;
        mov [new_cf], cl;
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
        mov [x], eax;
        xor cl, cl;
        rcl cl, 1;
        mov [new_cf], cl;
        popf;
    }

    if(p_new_cf)
        *p_new_cf = new_cf;

    return x;
}

void main()
{
    DWORD cf = 0;

    DWORD branch_count[32] = {0};

    for(DWORD reg_eax = 0; reg_eax < 0xFFFFFFFF; ++reg_eax)
    {
        BYTE bitbuff[8];
        *(PDWORD)(bitbuff) = reg_eax;
        *(PDWORD)(bitbuff+4) = (reg_eax << 1) | cf;
        ULONGLONG b = *(PULONGLONG)bitbuff;

        BYTE bytes[33];
        for(int i=0; i<33; ++i)
        {
            bytes[i] = b & 0xFF;
            b >>= 1;
        }

        DWORD num_branches = 0;

        for(int i=0; i<33; ++i)
            if( ( rcl(reg_eax, bytes[i], cf, 0) & 0xFF ) == bytes[i])
                num_branches++;

        if(num_branches >= 25)
            printf("%08X has %d RCR inverses with cf=%d\n", reg_eax, num_branches, cf);

        branch_count[num_branches]++;
    }

    // report results
    for(int i=0; i<32; ++i)
        printf("numbers with %d branches: %d (%f%%)\n", i, branch_count[i], 100 * ((float)branch_count[i]/0xFFFFFFFF));
}
