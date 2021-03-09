// keygen to Ra$cal's Ra$cal crackme N3 with vm
// 2008 andrewl

#define _CRT_SECURE_NO_DEPRECATE 1

#include <windows.h>

#include <stdio.h>
#include <conio.h>

ULONG bswap(ULONG i)
{
    __asm
    {
        mov eax, [i]
        bswap eax
        mov [i], eax
    }

    return i;
}

ULONG computeTarget(PCHAR name, ULONG compute0, ULONG compute2)
{
    UINT target = 0;

    for(int i=0; i<strlen(name); ++i)
    {
        UINT temp = (i%2==0) ? (compute2-i) : (compute0+i);

        temp ^= name[i];
        temp ^= 0x4F620AEC;
        target ^= temp;

        __asm
        {
            mov eax, [target]
            mov ecx, [i]
            rol eax, cl
            mov [target], eax
        }

         //printf("pass %d - target: %08X\n", i, target);
    }

    return target;
}

void main(int argc, char * argv[])
{
    ULONG   t;

    ULONG   dword0 = 0xDEADBEEF; //GetTickCount();
    ULONG   dword1 = 0xCAFEBABE;
    ULONG   dword2 = 0xBADC0D32; //GetTickCount();

    ULONG   compute0, compute1, compute2;
    ULONG   computeA, computeB, computeC;

    ULONG   target;

    CHAR    strUser[128];
    CHAR    strUser2[128];

    if(argc < 2)
    {
        printf("you can supply username as argument\n");
        strcpy(strUser, "Ra$cal");
    }
    else
    {
        strcpy(strUser, argv[1]);
        printf("strUser: %s\n", strUser);
    }

    //
    printf("  dword0: %08X\n", dword0);
    printf("  dword2: %08X\n", dword2);

    // get value of computer name
    ULONG   dwCpu=0;
    char    strCpu[64];
    DWORD   dwRet = 64;
    GetComputerName(strCpu, &dwRet);

    printf("strCpu: %s\n", strCpu);
    printf("   len: %d\n", dwRet);

    for(int i=0; i<dwRet; ++i)
    {
        dwCpu ^= (strCpu[i] ^ i);

        //printf("pass %d: dwCpu after xor: %08X\n", i, dwCpu);

        __asm
        {
            mov eax, [dwCpu]
            rol eax, 3
            mov [dwCpu], eax
        }

        //printf("pass %d: dwCpu after rol: %08X\n", i, dwCpu);
    }

    printf("   dwCpu: %08Xh (%dd)\n", dwCpu, dwCpu);

    // get sum of name characters
    UINT    userSum=0;

    for(int i=0; i<strlen(strUser); ++i)
        userSum += strUser[i];

    // expand user buffer
    strcpy(strUser2, strUser);

    if(strlen(strUser)<=8)
        strcat(strUser2, strUser);

    printf(" strUser2: %s\n", strUser2);

    compute0 = dword0 ^ bswap(dwCpu) ^ dwCpu;   // saved at 12FA74
    printf("compute0: %08X\n", compute0);

    compute2 = dword2 ^ bswap(dwCpu) ^ dwCpu;   // saved at 12FA68
    printf("compute2: %08X\n", compute2);
 

    target = computeTarget(strUser2, compute0, compute2);

    printf(" target: %08X\n", target);

    UINT    r = target;
    
    r ^= bswap(dwCpu) ^ dwCpu;
    r ^= bswap(compute0) ^ compute0;
    r ^= bswap(compute2) ^ compute2;

    printf("\n\n");
    printf("user: \n");
    printf("        %s\n", strUser);
    printf("key: \n");
    printf("        %d-%08X%08X%08X-\n", userSum, dword0, r, dword2);
    _getch();

    /* if you wanted to see rest of the verification

    compute1 = dword1 ^ bswap(compute2) ^ compute2;     // saved at 12fa5c
    printf("compute1: %08X\n", compute1);

    computeA = compute1 ^ bswap(compute0) ^ compute0;   // saved at 12fa50
    printf("computeA: %08X\n", computeA);

    computeB = computeA ^ bswap(dwCpuName) ^ dwCpuName; // saved at 12fa44
    printf("computeB: %08X\n", computeB);
    */


}
