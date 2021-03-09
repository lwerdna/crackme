#define INFO "Keygen for Cyclops's Angler - 3/9/2009 andrewl"

#include <windows.h>
#include <shellapi.h>

// printf thunk so no stdlib needed
//
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

   WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, lstrlen(buffer), &dwRet, 0);
}

// for CRC-32-IEEE 802.3 poly: 0xEDB88320
//
UINT crc_table[256] = {
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

// this is _allrem
void __declspec(naked) func_00401860()
{
  __asm
  {
    loc_00401860: push    ebx
    loc_00401861: mov     eax,dword ptr [esp+14h]
    loc_00401865: or      eax,eax
    loc_00401867: jne     loc_00401881
    loc_00401869: mov     ecx,dword ptr [esp+10h]
    loc_0040186D: mov     eax,dword ptr [esp+0Ch]
    loc_00401871: xor     edx,edx
    loc_00401873: div     ecx
    loc_00401875: mov     eax,dword ptr [esp+8]
    loc_00401879: div     ecx
    loc_0040187B: mov     eax,edx
    loc_0040187D: xor     edx,edx
    loc_0040187F: jmp     loc_004018D1
    loc_00401881: mov     ecx,eax
    loc_00401883: mov     ebx,dword ptr [esp+10h]
    loc_00401887: mov     edx,dword ptr [esp+0Ch]
    loc_0040188B: mov     eax,dword ptr [esp+8]
    loc_0040188F: shr     ecx,1
    loc_00401891: rcr     ebx,1
    loc_00401893: shr     edx,1
    loc_00401895: rcr     eax,1
    loc_00401897: or      ecx,ecx
    loc_00401899: jne     loc_0040188F
    loc_0040189B: div     ebx
    loc_0040189D: mov     ecx,eax
    loc_0040189F: mul     dword ptr [esp+14h]
    loc_004018A3: xchg    eax,ecx
    loc_004018A4: mul     dword ptr [esp+10h]
    loc_004018A8: add     edx,ecx
    loc_004018AA: jb      loc_004018BA
    loc_004018AC: cmp     edx,dword ptr [esp+0Ch]
    loc_004018B0: ja      loc_004018BA
    loc_004018B2: jb      loc_004018C2
    loc_004018B4: cmp     eax,dword ptr [esp+8]
    loc_004018B8: jbe     loc_004018C2
    loc_004018BA: sub     eax,dword ptr [esp+10h]
    loc_004018BE: sbb     edx,dword ptr [esp+14h]
    loc_004018C2: sub     eax,dword ptr [esp+8]
    loc_004018C6: sbb     edx,dword ptr [esp+0Ch]
    loc_004018CA: neg     edx
    loc_004018CC: neg     eax
    loc_004018CE: sbb     edx,0
    loc_004018D1: pop     ebx
    loc_004018D2: ret     10h
  };
}

// this is _allmul
void __declspec(naked) func_004018E0()
{
  __asm
  {
    loc_004018E0: mov     eax,dword ptr [esp+8]
    loc_004018E4: mov     ecx,dword ptr [esp+10h]
    loc_004018E8: or      ecx,eax
    loc_004018EA: mov     ecx,dword ptr [esp+0Ch]
    loc_004018EE: jne     loc_004018F9
    loc_004018F0: mov     eax,dword ptr [esp+4]
    loc_004018F4: mul     ecx
    loc_004018F6: ret     10h
    loc_004018F9: push    ebx
    loc_004018FA: mul     ecx
    loc_004018FC: mov     ebx,eax
    loc_004018FE: mov     eax,dword ptr [esp+8]
    loc_00401902: mul     dword ptr [esp+14h]
    loc_00401906: add     ebx,eax
    loc_00401908: mov     eax,dword ptr [esp+8]
    loc_0040190C: mul     ecx
    loc_0040190E: add     edx,ebx
    loc_00401910: pop     ebx
    loc_00401911: ret     10h
  };
}

// cyclops's expmod
void __declspec(naked) func_00401630()
{
  __asm
  {
    loc_00401630: sub     esp,10h
    loc_00401633: mov     eax,dword ptr [esp+18h]
    loc_00401637: push    ebp
    loc_00401638: push    esi
    loc_00401639: mov     esi,dword ptr [esp+1Ch]
    loc_0040163D: push    edi
    loc_0040163E: xor     edi,edi
    loc_00401640: cmp     eax,edi
    loc_00401642: mov     ebp,1
    loc_00401647: mov     dword ptr [esp+10h],edi
    loc_0040164B: je      loc_004016AD
    loc_0040164D: push    ebx
    loc_0040164E: mov     ebx,dword ptr [esp+2Ch]
    loc_00401652: mov     dword ptr [esp+1Ch],edi
    loc_00401656: test    byte ptr [esp+28h],1
    loc_0040165B: je      loc_0040167D
    loc_0040165D: mov     eax,dword ptr [esp+14h]
    loc_00401661: push    eax
    loc_00401662: push    ebp
    loc_00401663: push    edi
    loc_00401664: push    esi
    loc_00401665: call    func_004018E0
    loc_0040166A: mov     ecx,dword ptr [esp+1Ch]
    loc_0040166E: push    ecx
    loc_0040166F: push    ebx
    loc_00401670: push    edx
    loc_00401671: push    eax
    loc_00401672: call    func_00401860
    loc_00401677: mov     ebp,eax
    loc_00401679: mov     dword ptr [esp+14h],edx
    loc_0040167D: push    edi
    loc_0040167E: push    esi
    loc_0040167F: push    edi
    loc_00401680: push    esi
    loc_00401681: call    func_004018E0
    loc_00401686: mov     ecx,dword ptr [esp+1Ch]
    loc_0040168A: push    ecx
    loc_0040168B: push    ebx
    loc_0040168C: push    edx
    loc_0040168D: push    eax
    loc_0040168E: call    func_00401860
    loc_00401693: mov     esi,eax
    loc_00401695: mov     eax,dword ptr [esp+28h]
    loc_00401699: shr     eax,1
    loc_0040169B: mov     edi,edx
    loc_0040169D: mov     dword ptr [esp+28h],eax
    loc_004016A1: jne     loc_00401656
    loc_004016A3: pop     ebx
    loc_004016A4: pop     edi
    loc_004016A5: mov     eax,ebp
    loc_004016A7: pop     esi
    loc_004016A8: pop     ebp
    loc_004016A9: add     esp,10h
    loc_004016AC: ret
    loc_004016AD: pop     edi
    loc_004016AE: mov     eax,ebp
    loc_004016B0: pop     esi
    loc_004016B1: pop     ebp
    loc_004016B2: add     esp,10h
    loc_004016B5: ret
  };
}

// cyclops's primality test
UINT __declspec(naked) CyclopsIsPrime(UINT i)
{
  __asm
  {
    loc_004016C0: sub     esp,44h
    loc_004016C3: push    ebx
    loc_004016C4: push    ebp
    loc_004016C5: push    esi
    loc_004016C6: mov     esi,dword ptr [esp+54h]
    loc_004016CA: xor     ebp,ebp
    loc_004016CC: push    edi
    loc_004016CD: lea     ebx,[esi-1]
    loc_004016D0: mov     dword ptr [esp+18h],2
    loc_004016D8: mov     ecx,ebx
    loc_004016DA: mov     dword ptr [esp+1Ch],3
    loc_004016E2: test    bl,1
    loc_004016E5: mov     dword ptr [esp+20h],5
    loc_004016ED: mov     dword ptr [esp+24h],7
    loc_004016F5: mov     dword ptr [esp+28h],0Bh
    loc_004016FD: mov     dword ptr [esp+2Ch],0Dh
    loc_00401705: mov     dword ptr [esp+30h],11h
    loc_0040170D: mov     dword ptr [esp+34h],13h
    loc_00401715: mov     dword ptr [esp+38h],17h
    loc_0040171D: mov     dword ptr [esp+3Ch],1Dh
    loc_00401725: mov     dword ptr [esp+40h],1Fh
    loc_0040172D: mov     dword ptr [esp+44h],25h
    loc_00401735: mov     dword ptr [esp+48h],29h
    loc_0040173D: mov     dword ptr [esp+4Ch],2Bh
    loc_00401745: mov     dword ptr [esp+50h],2Fh
    loc_0040174D: mov     dword ptr [esp+10h],ecx
    loc_00401751: jne     loc_0040175F
    loc_00401753: shr     ecx,1
    loc_00401755: inc     ebp
    loc_00401756: test    cl,1
    loc_00401759: je      loc_00401753
    loc_0040175B: mov     dword ptr [esp+10h],ecx
    loc_0040175F: lea     eax,[esp+18h]
    loc_00401763: mov     dword ptr [esp+14h],0
    loc_0040176B: mov     dword ptr [esp+58h],eax
    loc_0040176F: jmp     loc_00401775
    loc_00401771: mov     ecx,dword ptr [esp+10h]
    loc_00401775: mov     edx,dword ptr [esp+58h]
    loc_00401779: mov     eax,dword ptr [edx]
    loc_0040177B: cmp     esi,eax
    loc_0040177D: je      loc_004017CE
    loc_0040177F: push    esi
    loc_00401780: push    ecx
    loc_00401781: push    eax
    loc_00401782: call    func_00401630
    loc_00401787: add     esp,0Ch
    loc_0040178A: cmp     eax,1
    loc_0040178D: je      loc_004017B5
    loc_0040178F: cmp     eax,ebx
    loc_00401791: je      loc_004017B5
    loc_00401793: mov     edi,1
    loc_00401798: cmp     ebp,edi
    loc_0040179A: jb      loc_004017B1
    loc_0040179C: push    esi
    loc_0040179D: push    2
    loc_0040179F: push    eax
    loc_004017A0: call    func_00401630
    loc_004017A5: add     esp,0Ch
    loc_004017A8: cmp     eax,ebx
    loc_004017AA: je      loc_004017B5
    loc_004017AC: inc     edi
    loc_004017AD: cmp     edi,ebp
    loc_004017AF: jbe     loc_0040179C
    loc_004017B1: cmp     eax,ebx
    loc_004017B3: jne     loc_004017DB
    loc_004017B5: mov     eax,dword ptr [esp+14h]
    loc_004017B9: mov     edx,dword ptr [esp+58h]
    loc_004017BD: inc     eax
    loc_004017BE: add     edx,4
    loc_004017C1: cmp     eax,0Fh
    loc_004017C4: mov     dword ptr [esp+14h],eax
    loc_004017C8: mov     dword ptr [esp+58h],edx
    loc_004017CC: jb      loc_00401771
    loc_004017CE: pop     edi
    loc_004017CF: pop     esi
    loc_004017D0: pop     ebp
    loc_004017D1: mov     eax,1
    loc_004017D6: pop     ebx
    loc_004017D7: add     esp,44h
    loc_004017DA: ret
    loc_004017DB: pop     edi
    loc_004017DC: pop     esi
    loc_004017DD: pop     ebp
    loc_004017DE: xor     eax,eax
    loc_004017E0: pop     ebx
    loc_004017E1: add     esp,44h
    loc_004017E4: ret
  };
}

void FindPartition(UINT N, PUINT a, PUINT b)
{
    for(UINT i=3; ; ++i)
    {
        if(!CyclopsIsPrime(i) || !CyclopsIsPrime(N-i))
            continue;
            
        *a=i;
        *b=(N-i);
        return;
    }
}

VOID main()
{
    printf("\n" INFO "\n\n");

    INT ac;
    LPWSTR *avw=CommandLineToArgvW(GetCommandLineW(),&ac);

    CHAR user[256];
    lstrcpy(user,"Cyclops");
    if(ac>1)
        WideCharToMultiByte(CP_ACP,0,avw[1],-1,user,256,0,0);
    
    //
    // generate CRCs
    // 
    UINT crcA=CalcCRC(user);
    UINT crcB=CalcCRC(user+1);
    UINT crcC=CalcCRC(user+2);
    UINT crcD=CalcCRC(user+3);
    printf("CRC for %s: %08X\n",user,crcA);
    printf("CRC for %s: %08X\n",user+1,crcB);
    printf("CRC for %s: %08X\n",user+2,crcC);
    printf("CRC for %s: %08X\n",user+3,crcD);

    //
    // turn them into even numbers for Goldbach action
    //
    crcA -= 0x13373;
    crcB -= 0x13373;
    crcC -= 0x13373;
    crcD -= 0x13373;

    if(crcA % 2) crcA++;
    if(crcB % 2) crcB++;
    if(crcC % 2) crcC++;
    if(crcD % 2) crcD++;

    printf("\nEven targets: %08X %08X %08X %08X\n",crcA,crcB,crcC,crcD);

    //
    // find the Goldbach partition of each of them - these are the components of the serial
    //
    UINT partA, partB, partC, partD, partE, partF, partG, partH;

    printf("\nFinding partition for %08X... ", crcA);
    FindPartition(crcA, &partA, &partE);
    printf("%08X + %08X\n", partA, partE);

    printf("Finding partition for %08X... ", crcB);
    FindPartition(crcB, &partB, &partF);
    printf("%08X + %08X\n", partB, partF);

    printf("Finding partition for %08X... ", crcC);
    FindPartition(crcC, &partC, &partG);
    printf("%08X + %08X\n", partC, partG);

    printf("Finding partition for %08X... ", crcD);
    FindPartition(crcD, &partD, &partH);
    printf("%08X + %08X\n", partD, partH);

    //
    // done! print name/serial
    //
    printf("\n");
    printf("  user: %s\n", user);
    printf("serial: %X-%X-%X-%X-%X-%X-%X-%X\n\n", partA, partB, partC, partD, partE, partF, partG, partH);

    printf("\nctrl+c to quit");
    while(1);
}
