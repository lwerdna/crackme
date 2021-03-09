// 2008 andrewl

#define INITIAL_CF_VALUE 1

// OS
#include <windows.h>

// cstdlib
#include <stdio.h>

DWORD g_depth_cutoff = 50;
DWORD g_depth_current = 0;

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

BOOL search(DWORD r_eax, DWORD r_ebx, DWORD cf, UINT depth_curr, BOOL bPrint)
{

    if(bPrint)
    {
        for(int i=0; i<depth_curr; ++i)
            printf(" ");

        printf("EAX=%08X EBX=%08X cf=%d ENTERED SEARCH (AFTER cm's EXCH)\n", r_eax, r_ebx, cf);
    }

    if(depth_curr == g_depth_cutoff)
    {
        printf("reached cutoff with (eax,ebx,cf) = (%08X,%08X,%d)\n", r_eax, r_ebx, cf);
        return 1;
    }

    g_depth_current = depth_curr;

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

            if(search(new_eax, r_ebx, new_cf, depth_curr+1, bPrint))
                return 1;
        }

        // try carry flag not set
        new_eax = rcl(r_eax, b_NC, 0, &new_cf);
        if( (new_eax & 0xFF) == b_NC)
        {
            //DWORD verifier = rcr(new_eax, new_eax & 0xFF, new_cf, 0);

            if(search(new_eax, r_ebx, new_cf, depth_curr+1, bPrint))
                return 1;
        }

        ull_NC >>= 1;
        ull_CY >>= 1;
    }

    return 0;
}



DWORD WINAPI progress_thread(LPVOID p_r_eax)
{
    while(1)
    {
        Sleep(10000);
        printf("On %08X (depth: %08X)\n", *(PDWORD)p_r_eax, g_depth_current);
    }
}



void main(int argc, char * argv[])
{
    printf("hi\n");

    BOOL bPrint = 0;

    if(argc < 3)
    {
        printf("usage: %s <start> <end> [-depth:<depth>] [-cf:<cf>] [-v]\n", argv[0]);
        return;
    }

    DWORD start = hexStrToUint64(argv[1]);
    DWORD end = hexStrToUint64(argv[2]);
    DWORD assume_cf = INITIAL_CF_VALUE;

    for(int i=3; i<argc; ++i)
    {
        if(!strcmp(argv[i], "-v"))
            bPrint = 1;

        if(!strncmp(argv[i], "-cf:", 4))
            assume_cf = atoi(argv[i] + 4);

        if(!strncmp(argv[i], "-d:", 3))
            g_depth_cutoff = hexStrToUint64(argv[i] + 3);
    }

    printf("verbose mode %s\n", bPrint ? "yes" : "off");
    printf("cutoff depth set to %d\n", g_depth_cutoff);
    printf("assuming CF=%d when solution is reached\n", assume_cf);
    printf("searching [%08X, %08X)\n", start, end);


    DWORD r_eax = start;
    DWORD r_ebx;

    HANDLE hThread = CreateThread(0, 0, progress_thread, &r_eax, 0, 0);
    if(!hThread)
        printf("couldn't install progress notification!\n");

    for(; r_eax != end; r_eax--)
    {
        // we need two DWORDs that XOR to 0x5F5E100
        r_ebx = r_eax ^ 0xD5446474;

        if(search(  r_eax,
                    r_ebx,
                    assume_cf,      // carry flag (its final setting)
                    0,      // initial depth
                    bPrint  // print ?
                    ))
        {
            printf("search returned 1 using (eax,ebx) = (%08X,%08X)\n", r_eax, r_ebx);
            return;
        }
    }

    printf("Exiting the loop, (eax,ebx) = (%08X,%08X)\n", r_eax, r_ebx);

    if(hThread)
        CloseHandle(hThread);

    return;
}
