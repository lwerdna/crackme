#define INFO "Keygen to Numernia's \"Keygenme Tvaa\" by andrewl - Sept 25th, 2009"

#include <windows.h>
#include <stdio.h>

DWORD __declspec(naked) FieldMul(DWORD a, DWORD b)
{
  __asm
  {
    loc_00401010: mov     edx,dword ptr [esp+4]
    loc_00401014: push    ebx
    loc_00401015: mov     ebx,dword ptr [esp+0Ch]
    loc_00401019: push    esi
    loc_0040101A: xor     eax,eax
    loc_0040101C: mov     esi,13h
    loc_00401021: test    bl,1
    loc_00401024: je      loc_00401028
    loc_00401026: xor     eax,edx
    loc_00401028: mov     ecx,edx
    loc_0040102A: add     edx,edx
    loc_0040102C: and     ecx,40000h
    loc_00401032: test    ecx,ecx
    loc_00401034: je      loc_0040103C
    loc_00401036: xor     edx,80027h
    loc_0040103C: shr     ebx,1
    loc_0040103E: dec     esi
    loc_0040103F: jne     loc_00401021
    loc_00401041: pop     esi
    loc_00401042: pop     ebx
    loc_00401043: ret
  };
}

DWORD __declspec(naked) FieldAdd(DWORD a, DWORD b)
{
  __asm
  {
    loc_00401000: mov     eax,dword ptr [esp+4]
    loc_00401004: mov     ecx,dword ptr [esp+8]
    loc_00401008: xor     eax,ecx
    loc_0040100A: ret
  };
}

DWORD FieldBruteInverse(DWORD a)
{
    for(DWORD i=0; i<0xFFFFFF; ++i)
        if(FieldMul(a, i) == 1)
            return i;

    return 0;
}

VOID BlockCipher(DWORD b[4], DWORD key[4])
{
    DWORD temp;

    for(INT i=0; i<4; ++i)
    {
        b[i] &= 0x7FFFF;
        key[i] &= 0x7FFFF;
    }

    DWORD consts[4] = {0x29C3B, 0x68723, 0x2A198, 0x45B82};

    for(INT round=0; round<8; ++round)
    {
        for(INT i=0; i<4; ++i)
        {
            b[i] = FieldAdd(b[i], key[i]);
            b[i] = FieldMul(b[i], consts[i]);
        }

        switch(round)
        {
            case 0:
                b[round] = FieldAdd(b[round], 0x2A198);
                break;
            case 1:
                b[round] = FieldMul(b[round], 0x987);
                break;
            case 2:
                b[round] = FieldMul(b[round], 0xA96);
                break;
            case 3:
                b[round] = FieldAdd(b[round], 0x29C3B);
                break;
            case 4:
                temp = 0x7d2f9;

                for(INT i=3; i>=0; --i)
                {
                    temp = FieldAdd(temp, i + 0x164);
                    b[i] = FieldAdd(b[i], temp);
                }
                break;
            case 5:
                temp = 0xfbf2;

                for(INT i=0; i<4; ++i)
                {
                    temp = FieldAdd(temp, i + 0x97);
                    b[i] = FieldAdd(b[i], temp);
                }
                break;
            case 6:
                temp = 0x2e102;

                for(INT i=0; i<4; ++i)
                {
                    temp = FieldMul(temp, i + 0xE2);
                    b[i] = FieldMul(b[i], temp);
                }
                break;
            case 7:
                temp = 0x70e8d;

                for(INT i=0; i<8; ++i)
                {
                    temp = FieldMul(temp, i+0x41);
                    b[i%4] = FieldAdd(b[i%4], temp);
                }
        }
    }
}

VOID BlockCipher_Trace(DWORD b[4], DWORD key[4])
{
    #define FIELDADDTRACE(INDEX,VALUE) { \
        printf("b[%d] = FieldAdd(b[%d],0x%08X);\n",(INDEX),(INDEX),(VALUE)); \
        b[INDEX] = FieldAdd(b[(INDEX)],(VALUE)); \
    }

    #define FIELDMULTRACE(INDEX,VALUE) { \
        printf("b[%d] = FieldMul(b[%d],0x%08X);\n",(INDEX),(INDEX),(VALUE)); \
        b[INDEX] = FieldMul(b[(INDEX)],(VALUE)); \
    }

    DWORD temp;

    for(INT i=0; i<4; ++i)
    {
        b[i] &= 0x7FFFF;
        key[i] &= 0x7FFFF;
    }

    DWORD consts[4] = {0x29C3B, 0x68723, 0x2A198, 0x45B82};

    for(INT round=0; round<8; ++round)
    {
        for(INT i=0; i<4; ++i)
        {
            FIELDADDTRACE(i, key[i]);
            FIELDMULTRACE(i, consts[i]);
        }

        switch(round)
        {
            case 0:
                FIELDADDTRACE(round, 0x2A198);
                break;
            case 1:
                FIELDMULTRACE(round, 0x987);
                break;
            case 2:
                FIELDMULTRACE(round, 0xA96);
                break;
            case 3:
                FIELDADDTRACE(round, 0x29C3B);
                break;
            case 4:
                temp = 0x7d2f9;

                for(INT i=3; i>=0; --i)
                {
                    temp = FieldAdd(temp, i + 0x164);
                    FIELDADDTRACE(i, temp);
                }
                break;
            case 5:
                temp = 0xfbf2;

                for(INT i=0; i<4; ++i)
                {
                    temp = FieldAdd(temp, i + 0x97);
                    FIELDADDTRACE(i, temp);
                }
                break;
            case 6:
                temp = 0x2e102;

                for(INT i=0; i<4; ++i)
                {
                    temp = FieldMul(temp, i + 0xE2);
                    FIELDMULTRACE(i, temp);
                }
                break;
            case 7:
                temp = 0x70e8d;

                for(INT i=0; i<8; ++i)
                {
                    temp = FieldMul(temp, i+0x41);
                    FIELDADDTRACE(i%4, temp);
                }
        }
    }
}

VOID BlockCipher_Unrolled(DWORD b[4])
{
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[0] = FieldAdd(b[0], 0x0002A198);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[1] = FieldMul(b[1], 0x00000987);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[2] = FieldMul(b[2], 0x00000A96);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[3] = FieldAdd(b[3], 0x00029C3B);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[3] = FieldAdd(b[3], 0x0007D39E);
    b[2] = FieldAdd(b[2], 0x0007D2F8);
    b[1] = FieldAdd(b[1], 0x0007D39D);
    b[0] = FieldAdd(b[0], 0x0007D2F9);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[0] = FieldAdd(b[0], 0x0000FB65);
    b[1] = FieldAdd(b[1], 0x0000FBFD);
    b[2] = FieldAdd(b[2], 0x0000FB64);
    b[3] = FieldAdd(b[3], 0x0000FBFE);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[0] = FieldMul(b[0], 0x0001251A);
    b[1] = FieldMul(b[1], 0x00040453);
    b[2] = FieldMul(b[2], 0x0003A972);
    b[3] = FieldMul(b[3], 0x0006C2A2);
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldMul(b[0], 0x00029C3B);
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[1] = FieldMul(b[1], 0x00068723);
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[2] = FieldMul(b[2], 0x0002A198);
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[3] = FieldMul(b[3], 0x00045B82);
    b[0] = FieldAdd(b[0], 0x0004AA65);
    b[1] = FieldAdd(b[1], 0x0003C9F6);
    b[2] = FieldAdd(b[2], 0x00062400);
    b[3] = FieldAdd(b[3], 0x000196DE);
    b[0] = FieldAdd(b[0], 0x00027B82);
    b[1] = FieldAdd(b[1], 0x0003FBB2);
    b[2] = FieldAdd(b[2], 0x00050D04);
    b[3] = FieldAdd(b[3], 0x00032C43);
}

VOID BlockCipher_Inverse(DWORD b[4])
{
    b[3] = FieldAdd(b[3], 0x00032C43);
    b[2] = FieldAdd(b[2], 0x00050D04);
    b[1] = FieldAdd(b[1], 0x0003FBB2);
    b[0] = FieldAdd(b[0], 0x00027B82);
    b[3] = FieldAdd(b[3], 0x000196DE);
    b[2] = FieldAdd(b[2], 0x00062400);
    b[1] = FieldAdd(b[1], 0x0003C9F6);
    b[0] = FieldAdd(b[0], 0x0004AA65);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x0006C2A2));
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0003A972));
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00040453));
    b[0] = FieldMul(b[0], FieldBruteInverse(0x0001251A));
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[3] = FieldAdd(b[3], 0x0000FBFE);
    b[2] = FieldAdd(b[2], 0x0000FB64);
    b[1] = FieldAdd(b[1], 0x0000FBFD);
    b[0] = FieldAdd(b[0], 0x0000FB65);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldAdd(b[0], 0x0007D2F9);
    b[1] = FieldAdd(b[1], 0x0007D39D);
    b[2] = FieldAdd(b[2], 0x0007D2F8);
    b[3] = FieldAdd(b[3], 0x0007D39E);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[3] = FieldAdd(b[3], 0x00029C3B);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x00000A96));
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00000987));
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
    b[0] = FieldAdd(b[0], 0x0002A198);
    b[3] = FieldMul(b[3], FieldBruteInverse(0x00045B82));
    b[3] = FieldAdd(b[3], 0x00061C8E);
    b[2] = FieldMul(b[2], FieldBruteInverse(0x0002A198));
    b[2] = FieldAdd(b[2], 0x000303D6);
    b[1] = FieldMul(b[1], FieldBruteInverse(0x00068723));
    b[1] = FieldAdd(b[1], 0x0006F387);
    b[0] = FieldMul(b[0], FieldBruteInverse(0x00029C3B));
    b[0] = FieldAdd(b[0], 0x0003917F);
}

UINT crc_table[256] = 
{
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
        0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
        0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
        0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
        0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
        0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
        0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
        0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
        0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
        0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
        0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
        0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
        0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
        0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
        0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
        0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
        0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
        0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
        0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
        0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
        0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
        0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
        0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
        0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
        0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
        0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
        0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
        0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
        0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
        0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
        0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
        0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
        0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
        0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
        0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
        0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
        0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
        0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
        0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
        0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
        0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
        0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

UINT __declspec(naked) CalcCRC(PCHAR input)
{
  __asm
  {
    loc_004015C0: mov     edx,dword ptr [esp+4]
    loc_004015C4: or      eax,0FFFFFFFFh
    loc_004015C7: movsx   ecx,byte ptr [edx]
    loc_004015CA: test    ecx,ecx
    loc_004015CC: je      loc_004015EB
    loc_004015CE: inc     edx
    loc_004015CF: xor     ecx,eax
    loc_004015D1: and     ecx,0FFh
    loc_004015D7: shr     eax,8
    loc_004015DA: mov     ecx, crc_table[ecx*4]
    loc_004015E1: xor     eax,ecx
    loc_004015E3: movsx   ecx,byte ptr [edx]
    loc_004015E6: inc     edx
    loc_004015E7: test    ecx,ecx
    loc_004015E9: jne     loc_004015CF
    loc_004015EB: not     eax
    loc_004015ED: ret
  };
}

UINT ExpMod(UINT b, UINT e, UINT m)
{
    UINT64 answer = 1;
    UINT64 runner = b;

    while(e)
    {
        if(e & 1)
            answer = (answer * runner) % m;

        e >>= 1;

        runner = (runner * runner) % m;
    }

    return answer;
}

INT main(INT ac, PCHAR *av)
{
    printf(INFO "\n\n");

    CHAR serial[128];

    PCHAR alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx";

    PCHAR name = "andrewl";
    if(ac>1)
        name = av[1];

    DWORD dw[4];

    // make dw[0]
    DWORD crc = CalcCRC(name);

    printf("crc: %08X\n", crc);
    crc &= 0x7FFFF;

    for(dw[0]=1; dw[0]<0x7FFFF; ++dw[0])
        if(ExpMod(dw[0],0x2665,0x7FFFF) == crc)
            break;
        
    printf("dw0: %08X\n", dw[0]);

    // make dw[1]
    dw[1] = GetTickCount() % 0x7FFFF;
    
    while(1)
    {
        if(((dw[1]*99) % 0x7FFBB) % 9 == 0)
            break;
            
        dw[1]++;
        if(dw[1] > 0x7FFFF)
            dw[1] = 0;
    }

    printf("dw1: %08X\n", dw[1]);

    // make dw[2]
    dw[2] = GetTickCount() & 0x7FFFF;
    dw[3] = dw[2] ^ (*(PDWORD)name & 0x7FFFF);

    printf("dw2: %08X\n", dw[2]);
    printf("dw3: %08X\n", dw[3]);

    // encrypt
    BlockCipher_Inverse(dw);
    printf("BlockCipher_Inverse() returns: %08X %08X %08X %08X\n", dw[0], dw[1], dw[2], dw[3]);

    // encode serial
    PBYTE pb = (PBYTE)dw;

    for(INT i=0; i<16; ++i)
    {
        // find 
        UINT base = 1;

        for(; ; base++)
        {
            UINT trial = ExpMod(base, 0x49EFA9, 0x9401D7);

            BOOL b2 = (trial % 2) ? 0 : 1;
            BOOL b3 = (trial % 3) ? 0 : 1;
            BOOL b5 = (trial % 5) ? 0 : 1;
            BOOL b7 = (trial % 7) ? 0 : 1;
            BOOL b11 = (trial % 11) ? 0 : 1;
            BOOL b13 = (trial % 13) ? 0 : 1;
            BOOL b17 = (trial % 17) ? 0 : 1;
            BOOL b19 = (trial % 19) ? 0 : 1;

            // required factors
            if((pb[i] & 1) && !b2)
                continue;
            if((pb[i] & 2) && !b3)
                continue;
            if((pb[i] & 4) && !b5)
                continue;
            if((pb[i] & 8) && !b7)
                continue;
            if((pb[i] & 16) && !b11) 
                continue;
            if((pb[i] & 32) && !b13)
                continue;
            if((pb[i] & 64) && !b17)
                continue;
            if((pb[i] & 128) && !b19)
                continue;

            // required non-factors
            if(!(pb[i] & 1) && b2)
                continue;
            if(!(pb[i] & 2) && b3)
                continue;
            if(!(pb[i] & 4) && b5)
                continue;
            if(!(pb[i] & 8) && b7)
                continue;
            if(!(pb[i] & 16) && b11) 
                continue;
            if(!(pb[i] & 32) && b13)
                continue;
            if(!(pb[i] & 64) && b17)
                continue;
            if(!(pb[i] & 128) && b19)
                continue;
       
            break;
        }

        printf("%08X should decode to %02X\n", base, pb[i]);

        serial[4*i+3] = alphabet[base % 60];
        base /= 60;
        serial[4*i+2] = alphabet[base % 60];
        base /= 60;
        serial[4*i+1] = alphabet[base % 60];
        base /= 60;
        serial[4*i] = alphabet[base];
    }   

    serial[64] = 0;

    printf("------------------------------------------------\n");
    printf("  name: %s\n", name);
    printf("serial: %s\n", serial);
    printf("------------------------------------------------\n");

    printf("\nctrl+c to quit\n");
    while(1);

    return 0;
}
