
// OS
#include <windows.h>

// cstdlib
#include <stdio.h>

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



void reverse_rcr(DWORD reg_eax, DWORD cf)
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

    for(int i=0; i<33; ++i)
    {
        BYTE cf_new;
        DWORD eax_new = rcl(reg_eax, bytes[i], cf, &cf_new);

        if( (eax_new & 0xFF) == bytes[i])
            printf( "%08X cf=%d (byte 0x%02X positioned at bit %d)\n", eax_new, cf_new, bytes[i], i+7);
    }
}


void main(int argc, char * argv[])
{
    if(argc < 3)
        return;

    DWORD r_eax = hexStrToUint64(argv[1]);
    DWORD cf = hexStrToUint64(argv[2]);

    printf("finding rcr inverse of %08X with cf=%d:\n\n", r_eax, cf);

    reverse_rcr(r_eax, cf);
}

// 2008 andrewl

