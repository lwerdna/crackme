#define INFO "keygen to death's electric-camel - nov12_2009 andrewl/crackmes.de"

// build with MSVC6 SP5:
// cl keygen.cpp /Ic:\cryptopp41 /O1 /EHsc /c
// link keygen.obj c:\cryptopp41\release\cryptlib.lib /NODEFAULTLIB:libcmt


#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "cryptlib.h"
#include "misc.h"
#include "tiger.h"
#include "blowfish.h"
#include "sha.h"
#include "base64.h"

#pragma comment(lib,"c:\\cryptopp41\\release\\cryptlib.lib")

using namespace std;
using namespace CryptoPP;

void __declspec(naked) sub_00401D70(PBYTE p)
{
  __asm
  {
    loc_00401D70: sub     esp,44h
    loc_00401D73: push    ebx
    loc_00401D74: push    ebp
    loc_00401D75: push    esi
    loc_00401D76: mov     esi,dword ptr [esp+54h]
    loc_00401D7A: mov     bl,1
    loc_00401D7C: push    edi
    loc_00401D7D: mov     byte ptr [esp+1Ch],bl
    loc_00401D81: mov     byte ptr [esp+24h],bl
    loc_00401D85: mov     byte ptr [esp+36h],bl
    loc_00401D89: mov     byte ptr [esp+42h],bl
    loc_00401D8D: mov     byte ptr [esp+43h],bl
    loc_00401D91: mov     byte ptr [esp+4Ch],bl
    loc_00401D95: mov     edi,esi
    loc_00401D97: lea     ebx,[esp+14h]
    loc_00401D9B: mov     al,3
    loc_00401D9D: mov     cl,5
    loc_00401D9F: mov     edx,6
    loc_00401DA4: sub     edi,ebx
    loc_00401DA6: mov     byte ptr [esp+25h],al
    loc_00401DAA: mov     byte ptr [esp+27h],al
    loc_00401DAE: mov     byte ptr [esp+28h],cl
    loc_00401DB2: mov     byte ptr [esp+31h],al
    loc_00401DB6: mov     byte ptr [esp+32h],cl
    loc_00401DBA: mov     byte ptr [esp+34h],cl
    loc_00401DBE: mov     byte ptr [esp+35h],al
    loc_00401DC2: mov     byte ptr [esp+38h],al
    loc_00401DC6: mov     byte ptr [esp+39h],al
    loc_00401DCA: mov     byte ptr [esp+3Ch],cl
    loc_00401DCE: mov     byte ptr [esp+3Dh],cl
    loc_00401DD2: mov     byte ptr [esp+46h],al
    loc_00401DD6: mov     byte ptr [esp+47h],cl
    loc_00401DDA: mov     byte ptr [esp+48h],al
    loc_00401DDE: mov     byte ptr [esp+4Fh],al
    loc_00401DE2: mov     byte ptr [esp+1Dh],2
    loc_00401DE7: mov     byte ptr [esp+1Eh],4
    loc_00401DEC: mov     byte ptr [esp+1Fh],8
    loc_00401DF1: mov     byte ptr [esp+20h],10h
    loc_00401DF6: mov     byte ptr [esp+21h],20h
    loc_00401DFB: mov     byte ptr [esp+22h],40h
    loc_00401E00: mov     byte ptr [esp+23h],80h
    loc_00401E05: mov     byte ptr [esp+26h],7
    loc_00401E0A: mov     byte ptr [esp+29h],4
    loc_00401E0F: mov     byte ptr [esp+2Ah],2
    loc_00401E14: mov     byte ptr [esp+2Bh],dl
    loc_00401E18: mov     byte ptr [esp+2Ch],dl
    loc_00401E1C: mov     byte ptr [esp+2Dh],0
    loc_00401E21: mov     byte ptr [esp+2Eh],7
    loc_00401E26: mov     byte ptr [esp+2Fh],4
    loc_00401E2B: mov     byte ptr [esp+30h],2
    loc_00401E30: mov     byte ptr [esp+33h],0
    loc_00401E35: mov     byte ptr [esp+37h],dl
    loc_00401E39: mov     byte ptr [esp+3Ah],2
    loc_00401E3E: mov     byte ptr [esp+3Bh],7
    loc_00401E43: mov     byte ptr [esp+3Eh],0
    loc_00401E48: mov     byte ptr [esp+3Fh],4
    loc_00401E4D: mov     byte ptr [esp+40h],dl
    loc_00401E51: mov     byte ptr [esp+41h],2
    loc_00401E56: mov     byte ptr [esp+44h],0
    loc_00401E5B: mov     byte ptr [esp+45h],0
    loc_00401E60: mov     byte ptr [esp+49h],4
    loc_00401E65: mov     byte ptr [esp+4Ah],4
    loc_00401E6A: mov     byte ptr [esp+4Bh],0
    loc_00401E6F: mov     byte ptr [esp+4Dh],dl
    loc_00401E73: mov     byte ptr [esp+4Eh],dl
    loc_00401E77: mov     byte ptr [esp+50h],4
    loc_00401E7C: mov     byte ptr [esp+51h],7
    loc_00401E81: mov     byte ptr [esp+52h],7
    loc_00401E86: mov     byte ptr [esp+53h],4
    loc_00401E8B: lea     eax,[esp+14h]
    loc_00401E8F: lea     ecx,[esp+25h]
    loc_00401E93: mov     dword ptr [esp+10h],edi
    loc_00401E97: mov     dword ptr [esp+58h],edx
    loc_00401E9B: mov     byte ptr [eax],0
    loc_00401E9E: lea     edi,[esp+1Dh]
    loc_00401EA2: mov     ebp,4
    loc_00401EA7: movsx   ebx,byte ptr [ecx-1]
    loc_00401EAB: mov     dl,byte ptr [esi]
    loc_00401EAD: test    byte ptr [esp+ebx+1Ch],dl
    loc_00401EB1: je      loc_00401EB8
    loc_00401EB3: mov     bl,byte ptr [edi-1]
    loc_00401EB6: or      byte ptr [eax],bl
    loc_00401EB8: movsx   ebx,byte ptr [ecx]
    loc_00401EBB: test    byte ptr [esp+ebx+1Ch],dl
    loc_00401EBF: je      loc_00401EC9
    loc_00401EC1: mov     dl,byte ptr [edi]
    loc_00401EC3: mov     bl,byte ptr [eax]
    loc_00401EC5: or      bl,dl
    loc_00401EC7: mov     byte ptr [eax],bl
    loc_00401EC9: inc     esi
    loc_00401ECA: add     ecx,2
    loc_00401ECD: add     edi,2
    loc_00401ED0: dec     ebp
    loc_00401ED1: jne     loc_00401EA7
    loc_00401ED3: mov     edi,dword ptr [esp+10h]
    loc_00401ED7: mov     dl,byte ptr [eax]
    loc_00401ED9: mov     byte ptr [edi+eax],dl
    loc_00401EDC: mov     edx,dword ptr [esp+58h]
    loc_00401EE0: inc     eax
    loc_00401EE1: dec     edx
    loc_00401EE2: mov     dword ptr [esp+58h],edx
    loc_00401EE6: jne     loc_00401E9B
    loc_00401EE8: pop     edi
    loc_00401EE9: pop     esi
    loc_00401EEA: pop     ebp
    loc_00401EEB: pop     ebx
    loc_00401EEC: add     esp,44h
    loc_00401EEF: ret
  };
}

VOID main(INT ac, PCHAR *av)
{
    printf("\n" INFO "\n\n");

    INT i;

    // need 48 characters
    CHAR systemid[256];
    printf("enter 48-character \"Unique system code\" given by crackme:\n");
    scanf("%s", systemid); // wow you can overFL)w! me!
    printf("systemid: %s\n", systemid);

    PCHAR partA = "icouldberandom";

    Tiger hash;
    BYTE tiger_hash[Tiger::DIGESTSIZE];
    hash.CalculateDigest(tiger_hash, (PBYTE)partA, strlen(partA));
    printf("tiger(partA): ");
    for(i=0; i<Tiger::DIGESTSIZE; ++i)
        printf("%02X", tiger_hash[i]);
    printf("\n");

    sub_00401D70(tiger_hash);
    printf("xform1(tiger(partA)): ");
    for(i=0; i<Tiger::DIGESTSIZE; ++i)
        printf("%02X", tiger_hash[i]);
    printf("\n");

    printf("privateKey: ");
    BYTE privateKey[10];
    memcpy(privateKey, "\x00\x00\x00\x00\x07\x92\xA1\x95\x22\x23", 10);
    for(i=0; i<10; ++i)
        printf("%02X", privateKey[i]);
    printf("\n");

    printf("sha1(systemid): ");
    SHA1 hash2;
    BYTE sha1_hash[SHA1::DIGESTSIZE];
    hash2.CalculateDigest(sha1_hash, (PBYTE)systemid, strlen(systemid));
    for(i=0; i<SHA1::DIGESTSIZE; ++i)
        printf("%02X", sha1_hash[i]);
    printf("\n");

    printf("xor_action(privateKey): ");
    for(i=0; i<10; ++i)
        privateKey[i]^=(sha1_hash[i]+sha1_hash[i+10]);
    privateKey[8]^=0x67;
    privateKey[9]^=0x4F;
    for(i=0; i<10; ++i)
        printf("%02X", privateKey[i]);
    printf("\n");

    printf("blowfish_decrypt(xor_action(privateKey), xform1(tiger(partA))): ");
    Blowfish fish(tiger_hash, 6, (CipherDir)1);
    fish.ProcessBlock(privateKey, privateKey);
    for(i=0; i<10; ++i)
        printf("%02X", privateKey[i]);
    printf("\n");

    printf("base64(blowfish_decrypt(xor_action(privateKey), xform1(tiger(partA)))): ");
    CHAR encoded[128];
    memset(encoded, 0, 128);
    Base64Encoder encode;
    encode.Put(privateKey, 10);
    encode.MessageEnd(-1);
    encode.Get((PUCHAR)encoded, 128);
    printf("%s\n", encoded);

    printf("\n--------------------------------------------------------------------\n");
    printf("    systemid: %s\n", systemid);
    printf("serial partA: %s\n", partA);
    printf("serial partB: %s\n", encoded);
    printf("--------------------------------------------------------------------\n");

    printf("ctrL+C to quit!\n");
    while(1);
}
