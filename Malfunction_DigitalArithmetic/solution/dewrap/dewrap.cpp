// de-wraper for malfunction's crackme #5 "Digital Arithmetic"
// 2/2009 andrewl

#include <windows.h>

#define VBASE 0x401000
#define ROFFSET 0x200
#define RSIZE 0x3600
#define ROFFSETEND (ROFFSET+RSIZE)

#define OFF2VA(X) (VBASE+(X)-ROFFSET)
#define VA2OFF(X) (ROFFSET+(X)-VBASE)

extern "C" void printf(char * fmtstr, ...)
{
    DWORD   dwRet;
    CHAR    buffer[256];

    __asm
    {
                mov     ecx, 0x08
                lea     edi, fmtstr
                add     edi, 0x20
        more:   push    [edi]
                sub     edi, 4
                dec     ecx
                jnz     more
    }

    wsprintf(buffer, fmtstr);

    __asm add esp, 0x20

    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwRet, 0);
}

VOID entrypoint()
{
    INT ac;
    LPWSTR *av=CommandLineToArgvW(GetCommandLineW(),&ac);
    if(ac<2) return;

    HANDLE hFile = CreateFileW(av[1],GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    UINT fSize = GetFileSize(hFile,0);
    HANDLE hMap = CreateFileMapping(hFile,0,PAGE_READWRITE,0,fSize,0);
    PUCHAR p = (PUCHAR) MapViewOfFile(hMap,FILE_MAP_WRITE|FILE_MAP_READ,0,0,0);
    if(!hFile || !hMap || !p) return;

    for(INT i=ROFFSET; i<ROFFSETEND; ++i)
    {
        if( p[i] == 0x60 && // pusha opcode
            p[i+1] == 0xBE && // mov esi, ...
            p[i+6] == 0xB9 && // mov ecx, ...
            p[i+11] == 0x8B && // mov edx, ...
            p[i+17] == 0xBF && // mov edi, ...
            p[i+22] == 0xBB // mov ebx, ...
            )
        {
            // locate protection
            printf("found wrapped function @%X\n", OFF2VA(i));

            DWORD end = *(PDWORD)(p+i+2);
            DWORD len = *(PDWORD)(p+i+7);
            DWORD start = end-len+1;
            DWORD key = *(PDWORD)(p+VA2OFF(*(PDWORD)(p+i+13)));
            DWORD xor_end = *(PDWORD)(p+i+18);
            DWORD xor_len = *(PDWORD)(p+i+23);
            DWORD xor_start = xor_end-xor_len+1;
            printf("  [%X,%X] len:%X key:%X xor:[%X,%X]\n", start, end, len, key, xor_start, xor_end);
 
            // k emulate obf
            for(INT j=end; j>=start; --j)
            {
                for(DWORD k=xor_end; k>=xor_start; --k)
                {
                    key ^= p[VA2OFF(k)];
                    key -= p[VA2OFF(k)];
                    //printf("key %X\n", key);
                }

                //printf("modding %X:%X with key %X ", j, *(PDWORD)(p+VA2OFF(j)), key);
                *(PDWORD)(p+VA2OFF(j)) -= key;
                *(PDWORD)(p+VA2OFF(j)) ^= key;
                //printf("== %X\n", *(PDWORD)(p+VA2OFF(j)));
            }
        }
    }

    // fix calls to wrapped code
    // all "real" subroutines are exactly 0x8A from start of wraping stub
    DWORD wrapped_locs[12] = {  0x401718,0x4019A8,0x401CE7,0x401E5B,
                                0x401F96,0x40269B,0x402A66,0x402BAE,
                                0x402CE1,0x402F28,0x40305B,0x4031E7     };

    for(UINT i=0; i<12; ++i)
    {
        for(INT j=ROFFSET; j<ROFFSETEND; ++j)
        {
            if(p[j] == 0xE8)
            {
                INT rel = *(PINT)(p+j+1);

                if((INT)OFF2VA(j)+5+rel == wrapped_locs[i])
                {
                    printf("wrapped @%X is called @%X\n", wrapped_locs[i], OFF2VA(j));

                    *(PINT)(p+j+1) = (wrapped_locs[i]+0x8A)-(OFF2VA(j)+5);
                }
            }
        }
    }

    // for some reason, some calls are aiming two instructions into some subroutines
    // .. fix this

    for(INT j=ROFFSET; j<ROFFSETEND; ++j)
    {
        if(p[j]==0x55 && p[j+1]==0x89 && p[j+2]==0xE5) // push ebp; mov ebp, esp
        {
            // search for calls targetting immediately past this prologue
            //
            for(INT k=ROFFSET; k<ROFFSETEND; ++k)
            {
                if(p[k] == 0xE8)
                {
                    INT rel = *(PINT)(p+k+1);

                    if((INT)OFF2VA(k)+5+rel == OFF2VA(j+3))
                    {
                        printf("fixing call at @%X\n", OFF2VA(k));
                        *(PINT)(p+k+1) = OFF2VA(j)-(OFF2VA(k)+5);
                    }
                }
            }
        }
    }


}
