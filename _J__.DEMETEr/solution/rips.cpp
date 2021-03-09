// 2008 andrewl

#include <string.h>

unsigned char hashdata1[] =
{
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
    0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, // ........
    0x07, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, // ........
    0x0D, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, // ........
    0x13, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, // ........
    0x1D, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, // ........
    0x25, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, // %...)...
    0x2B, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, // +.../...
    0x35, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00, // 5...;...
    0x3D, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, // =...C...
    0x47, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, // G...I...
    0x4F, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, // O...S...
    0x59, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x00, // Y...a...
    0x65, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, // e...g...
    0x6B, 0x00, 0x00, 0x00, 0x6D, 0x00, 0x00, 0x00, // k...m...
    0x71, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, // q.......
    0x83, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, // ........
    0x8B, 0x00, 0x00, 0x00, 0x95, 0x00, 0x00, 0x00, // ........
    0x97, 0x00, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, // ........
    0xA3, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00, // ........
    0xAD, 0x00, 0x00, 0x00, 0xB3, 0x00, 0x00, 0x00, // ........
    0xB5, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, // ........
    0xC1, 0x00, 0x00, 0x00, 0xC5, 0x00, 0x00, 0x00, // ........
    0xC7, 0x00, 0x00, 0x00, 0xD3, 0x00, 0x00, 0x00, // ........
    0xDF, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x00, // ........
    0xE5, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, // ........
    0xEF, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, // ........
    0xFB, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, // ........
    0x07, 0x01, 0x00, 0x00                          // ....    
};

unsigned char * phashdata1=hashdata1;

void __declspec(naked) func_004081B0()
{
  __asm
  {
    loc_004081B0: push    ebp
    loc_004081B1: mov     ebp,esp
    loc_004081B3: push    edi
    loc_004081B4: push    esi
    loc_004081B5: push    ebx
    loc_004081B6: sub     esp,594h
    loc_004081BC: mov     edx,dword ptr [ebp+8]
    loc_004081BF: mov     ecx,dword ptr [ebp+8]
    loc_004081C2: mov     esi,dword ptr [ebp+8]
    loc_004081C5: mov     ebx,dword ptr [edx+8]
    loc_004081C8: mov     edi,dword ptr [ecx+0Ch]
    loc_004081CB: mov     edx,dword ptr [ebp+8]
    loc_004081CE: mov     ecx,dword ptr [ebp+8]
    loc_004081D1: mov     dword ptr [ebp-10h],ebx
    loc_004081D4: mov     eax,dword ptr [esi+10h]
    loc_004081D7: mov     ebx,dword ptr [edx+14h]
    loc_004081DA: mov     dword ptr [ebp-14h],edi
    loc_004081DD: mov     esi,dword ptr [ebp+8]
    loc_004081E0: mov     edi,dword ptr [ecx+18h]
    loc_004081E3: mov     dword ptr [ebp-18h],eax
    loc_004081E6: mov     edx,dword ptr [ebp+8]
    loc_004081E9: mov     ecx,dword ptr [ebp+8]
    loc_004081EC: mov     dword ptr [ebp-1Ch],ebx
    loc_004081EF: mov     eax,dword ptr [esi+1Ch]
    loc_004081F2: mov     ebx,dword ptr [edx+20h]
    loc_004081F5: mov     dword ptr [ebp-20h],edi
    loc_004081F8: mov     edi,dword ptr [ecx+24h]
    loc_004081FB: mov     edx,dword ptr [ebp-18h]
    loc_004081FE: mov     dword ptr [ebp-28h],ebx
    loc_00408201: mov     ebx,dword ptr [ebp-10h]
    loc_00408204: mov     ecx,dword ptr [ebp-28h]
    loc_00408207: mov     dword ptr [ebp-24h],eax
    loc_0040820A: mov     eax,dword ptr [ebp-1Ch]
    loc_0040820D: mov     esi,dword ptr [ebp+8]
    loc_00408210: mov     dword ptr [ebp-2Ch],edi
    loc_00408213: mov     edi,dword ptr [ebp-20h]
    loc_00408216: and     ecx,ebx
    loc_00408218: add     esi,28h
    loc_0040821B: xor     edi,eax
    loc_0040821D: and     edi,edx
    loc_0040821F: mov     dword ptr [ebp-30h],esi
    loc_00408222: xor     edi,ecx
    loc_00408224: mov     dword ptr [ebp-34h],edi
    loc_00408227: mov     esi,dword ptr [ebp-14h]
    loc_0040822A: mov     eax,dword ptr [ebp-24h]
    loc_0040822D: rol     dword ptr [ebp-2Ch],15h
    loc_00408231: mov     edx,dword ptr [ebp-20h]
    loc_00408234: and     eax,esi
    loc_00408236: xor     dword ptr [ebp-34h],eax
    loc_00408239: mov     ecx,dword ptr [ebp+8]
    loc_0040823C: mov     ebx,dword ptr [ebp-2Ch]
    loc_0040823F: xor     dword ptr [ebp-34h],edx
    loc_00408242: mov     edi,dword ptr [ecx+28h]
    loc_00408245: mov     eax,dword ptr [ebp-18h]
    loc_00408248: rol     dword ptr [ebp-34h],19h
    loc_0040824C: mov     edx,dword ptr [ebp-14h]
    loc_0040824F: mov     dword ptr [ebp-520h],edi
    loc_00408255: mov     ecx,dword ptr [ebp-24h]
    loc_00408258: mov     esi,dword ptr [ebp-34h]
    loc_0040825B: rol     dword ptr [ebp-28h],15h
    loc_0040825F: add     esi,ebx
    loc_00408261: add     esi,edi
    loc_00408263: mov     dword ptr [ebp-3A4h],esi
    loc_00408269: mov     edi,dword ptr [ebp-1Ch]
    loc_0040826C: mov     ebx,dword ptr [ebp-3A4h]
    loc_00408272: mov     esi,dword ptr [ebp-10h]
    loc_00408275: xor     edi,eax
    loc_00408277: mov     eax,dword ptr [ebp-20h]
    loc_0040827A: and     ecx,ebx
    loc_0040827C: and     edi,edx
    loc_0040827E: xor     edi,ecx
    loc_00408280: mov     dword ptr [ebp-40h],edi
    loc_00408283: and     eax,esi
    loc_00408285: mov     edx,dword ptr [ebp-1Ch]
    loc_00408288: xor     dword ptr [ebp-40h],eax
    loc_0040828B: mov     ecx,dword ptr [ebp-30h]
    loc_0040828E: mov     ebx,dword ptr [ebp-28h]
    loc_00408291: xor     dword ptr [ebp-40h],edx
    loc_00408294: mov     edi,dword ptr [ecx+4]
    loc_00408297: rol     dword ptr [ebp-40h],19h
    loc_0040829B: mov     esi,dword ptr [ebp-40h]
    loc_0040829E: mov     dword ptr [ebp-524h],edi
    loc_004082A4: mov     eax,dword ptr [ebp-14h]
    loc_004082A7: add     esi,ebx
    loc_004082A9: rol     dword ptr [ebp-24h],15h
    loc_004082AD: add     esi,edi
    loc_004082AF: mov     edi,dword ptr [ebp-18h]
    loc_004082B2: mov     dword ptr [ebp-3A8h],esi
    loc_004082B8: mov     edx,dword ptr [ebp-10h]
    loc_004082BB: mov     ebx,dword ptr [ebp-3A8h]
    loc_004082C1: mov     ecx,dword ptr [ebp-20h]
    loc_004082C4: xor     edi,eax
    loc_004082C6: mov     esi,dword ptr [ebp-3A4h]
    loc_004082CC: mov     eax,dword ptr [ebp-1Ch]
    loc_004082CF: and     edi,edx
    loc_004082D1: and     ecx,ebx
    loc_004082D3: xor     edi,ecx
    loc_004082D5: mov     edx,dword ptr [ebp-18h]
    loc_004082D8: and     eax,esi
    loc_004082DA: mov     dword ptr [ebp-4Ch],edi
    loc_004082DD: mov     ecx,dword ptr [ebp-30h]
    loc_004082E0: mov     ebx,dword ptr [ebp-24h]
    loc_004082E3: xor     dword ptr [ebp-4Ch],eax
    loc_004082E6: mov     edi,dword ptr [ecx+8]
    loc_004082E9: mov     eax,dword ptr [ebp-10h]
    loc_004082EC: xor     dword ptr [ebp-4Ch],edx
    loc_004082EF: mov     ecx,dword ptr [ebp-1Ch]
    loc_004082F2: mov     dword ptr [ebp-528h],edi
    loc_004082F8: mov     edx,dword ptr [ebp-3A4h]
    loc_004082FE: rol     dword ptr [ebp-4Ch],19h
    loc_00408302: mov     esi,dword ptr [ebp-4Ch]
    loc_00408305: add     esi,ebx
    loc_00408307: add     esi,edi
    loc_00408309: mov     edi,dword ptr [ebp-14h]
    loc_0040830C: mov     dword ptr [ebp-3ACh],esi
    loc_00408312: mov     ebx,dword ptr [ebp-3ACh]
    loc_00408318: mov     esi,dword ptr [ebp-3A8h]
    loc_0040831E: xor     edi,eax
    loc_00408320: mov     eax,dword ptr [ebp-18h]
    loc_00408323: and     ecx,ebx
    loc_00408325: and     edi,edx
    loc_00408327: xor     edi,ecx
    loc_00408329: mov     edx,dword ptr [ebp-14h]
    loc_0040832C: mov     dword ptr [ebp-58h],edi
    loc_0040832F: and     eax,esi
    loc_00408331: xor     dword ptr [ebp-58h],eax
    loc_00408334: xor     dword ptr [ebp-58h],edx
    loc_00408337: mov     ecx,dword ptr [ebp-30h]
    loc_0040833A: mov     eax,dword ptr [ebp-3A4h]
    loc_00408340: rol     dword ptr [ebp-58h],19h
    loc_00408344: mov     edi,dword ptr [ecx+0Ch]
    loc_00408347: mov     edx,dword ptr [ebp-3A8h]
    loc_0040834D: rol     dword ptr [ebp-20h],15h
    loc_00408351: mov     esi,dword ptr [ebp-58h]
    loc_00408354: mov     dword ptr [ebp-52Ch],edi
    loc_0040835A: mov     ecx,dword ptr [ebp-18h]
    loc_0040835D: mov     ebx,dword ptr [ebp-20h]
    loc_00408360: rol     dword ptr [ebp-1Ch],15h
    loc_00408364: add     esi,ebx
    loc_00408366: add     esi,edi
    loc_00408368: mov     dword ptr [ebp-3B0h],esi
    loc_0040836E: mov     edi,dword ptr [ebp-10h]
    loc_00408371: mov     ebx,dword ptr [ebp-3B0h]
    loc_00408377: mov     esi,dword ptr [ebp-3ACh]
    loc_0040837D: xor     edi,eax
    loc_0040837F: mov     eax,dword ptr [ebp-14h]
    loc_00408382: and     ecx,ebx
    loc_00408384: and     edi,edx
    loc_00408386: xor     edi,ecx
    loc_00408388: mov     dword ptr [ebp-64h],edi
    loc_0040838B: and     eax,esi
    loc_0040838D: mov     edx,dword ptr [ebp-10h]
    loc_00408390: xor     dword ptr [ebp-64h],eax
    loc_00408393: mov     ecx,dword ptr [ebp-30h]
    loc_00408396: mov     ebx,dword ptr [ebp-1Ch]
    loc_00408399: xor     dword ptr [ebp-64h],edx
    loc_0040839C: mov     edi,dword ptr [ecx+10h]
    loc_0040839F: rol     dword ptr [ebp-64h],19h
    loc_004083A3: mov     dword ptr [ebp-530h],edi
    loc_004083A9: mov     esi,dword ptr [ebp-64h]
    loc_004083AC: add     esi,ebx
    loc_004083AE: add     esi,edi
    loc_004083B0: mov     dword ptr [ebp-3B4h],esi
    loc_004083B6: mov     eax,dword ptr [ebp-3A8h]
    loc_004083BC: mov     edi,dword ptr [ebp-3A4h]
    loc_004083C2: rol     dword ptr [ebp-18h],15h
    loc_004083C6: mov     edx,dword ptr [ebp-3ACh]
    loc_004083CC: mov     ebx,dword ptr [ebp-3B4h]
    loc_004083D2: mov     ecx,dword ptr [ebp-14h]
    loc_004083D5: xor     edi,eax
    loc_004083D7: mov     esi,dword ptr [ebp-3B0h]
    loc_004083DD: mov     eax,dword ptr [ebp-10h]
    loc_004083E0: and     edi,edx
    loc_004083E2: and     ecx,ebx
    loc_004083E4: xor     edi,ecx
    loc_004083E6: mov     edx,dword ptr [ebp-3A4h]
    loc_004083EC: and     eax,esi
    loc_004083EE: mov     dword ptr [ebp-70h],edi
    loc_004083F1: mov     ecx,dword ptr [ebp-30h]
    loc_004083F4: mov     ebx,dword ptr [ebp-18h]
    loc_004083F7: xor     dword ptr [ebp-70h],eax
    loc_004083FA: mov     edi,dword ptr [ecx+14h]
    loc_004083FD: mov     eax,dword ptr [ebp-3ACh]
    loc_00408403: xor     dword ptr [ebp-70h],edx
    loc_00408406: mov     ecx,dword ptr [ebp-10h]
    loc_00408409: mov     dword ptr [ebp-534h],edi
    loc_0040840F: mov     edx,dword ptr [ebp-3B0h]
    loc_00408415: rol     dword ptr [ebp-70h],19h
    loc_00408419: mov     esi,dword ptr [ebp-70h]
    loc_0040841C: add     esi,ebx
    loc_0040841E: add     esi,edi
    loc_00408420: mov     edi,dword ptr [ebp-3A8h]
    loc_00408426: mov     dword ptr [ebp-3B8h],esi
    loc_0040842C: mov     ebx,dword ptr [ebp-3B8h]
    loc_00408432: mov     esi,dword ptr [ebp-3B4h]
    loc_00408438: xor     edi,eax
    loc_0040843A: mov     eax,dword ptr [ebp-3A4h]
    loc_00408440: and     ecx,ebx
    loc_00408442: and     edi,edx
    loc_00408444: xor     edi,ecx
    loc_00408446: mov     edx,dword ptr [ebp-3A8h]
    loc_0040844C: mov     dword ptr [ebp-7Ch],edi
    loc_0040844F: and     eax,esi
    loc_00408451: xor     dword ptr [ebp-7Ch],eax
    loc_00408454: xor     dword ptr [ebp-7Ch],edx
    loc_00408457: mov     ecx,dword ptr [ebp-30h]
    loc_0040845A: mov     eax,dword ptr [ebp-3B0h]
    loc_00408460: rol     dword ptr [ebp-7Ch],19h
    loc_00408464: mov     edi,dword ptr [ecx+18h]
    loc_00408467: mov     edx,dword ptr [ebp-3B4h]
    loc_0040846D: rol     dword ptr [ebp-14h],15h
    loc_00408471: mov     esi,dword ptr [ebp-7Ch]
    loc_00408474: mov     dword ptr [ebp-538h],edi
    loc_0040847A: mov     ecx,dword ptr [ebp-3A4h]
    loc_00408480: mov     ebx,dword ptr [ebp-14h]
    loc_00408483: rol     dword ptr [ebp-10h],15h
    loc_00408487: add     esi,ebx
    loc_00408489: add     esi,edi
    loc_0040848B: mov     dword ptr [ebp-3BCh],esi
    loc_00408491: mov     edi,dword ptr [ebp-3ACh]
    loc_00408497: mov     ebx,dword ptr [ebp-3BCh]
    loc_0040849D: mov     esi,dword ptr [ebp-3B8h]
    loc_004084A3: xor     edi,eax
    loc_004084A5: mov     eax,dword ptr [ebp-3A8h]
    loc_004084AB: and     ecx,ebx
    loc_004084AD: and     edi,edx
    loc_004084AF: xor     edi,ecx
    loc_004084B1: mov     dword ptr [ebp-88h],edi
    loc_004084B7: and     eax,esi
    loc_004084B9: mov     edx,dword ptr [ebp-3ACh]
    loc_004084BF: xor     dword ptr [ebp-88h],eax
    loc_004084C5: mov     ecx,dword ptr [ebp-30h]
    loc_004084C8: mov     ebx,dword ptr [ebp-10h]
    loc_004084CB: xor     dword ptr [ebp-88h],edx
    loc_004084D1: mov     edi,dword ptr [ecx+1Ch]
    loc_004084D4: rol     dword ptr [ebp-88h],19h
    loc_004084DB: mov     dword ptr [ebp-53Ch],edi
    loc_004084E1: mov     esi,dword ptr [ebp-88h]
    loc_004084E7: add     esi,ebx
    loc_004084E9: add     esi,edi
    loc_004084EB: mov     dword ptr [ebp-3C0h],esi
    loc_004084F1: mov     eax,dword ptr [ebp-3B4h]
    loc_004084F7: mov     edi,dword ptr [ebp-3B0h]
    loc_004084FD: rol     dword ptr [ebp-3A4h],15h
    loc_00408504: mov     edx,dword ptr [ebp-3B8h]
    loc_0040850A: mov     ebx,dword ptr [ebp-3C0h]
    loc_00408510: mov     ecx,dword ptr [ebp-3A8h]
    loc_00408516: xor     edi,eax
    loc_00408518: mov     esi,dword ptr [ebp-3BCh]
    loc_0040851E: mov     eax,dword ptr [ebp-3ACh]
    loc_00408524: and     edi,edx
    loc_00408526: and     ecx,ebx
    loc_00408528: xor     edi,ecx
    loc_0040852A: mov     edx,dword ptr [ebp-3B0h]
    loc_00408530: and     eax,esi
    loc_00408532: mov     dword ptr [ebp-94h],edi
    loc_00408538: mov     ecx,dword ptr [ebp-30h]
    loc_0040853B: mov     ebx,dword ptr [ebp-3A4h]
    loc_00408541: xor     dword ptr [ebp-94h],eax
    loc_00408547: mov     edi,dword ptr [ecx+20h]
    loc_0040854A: mov     eax,dword ptr [ebp-3B8h]
    loc_00408550: xor     dword ptr [ebp-94h],edx
    loc_00408556: mov     ecx,dword ptr [ebp-3ACh]
    loc_0040855C: mov     dword ptr [ebp-540h],edi
    loc_00408562: mov     edx,dword ptr [ebp-3BCh]
    loc_00408568: rol     dword ptr [ebp-94h],19h
    loc_0040856F: mov     esi,dword ptr [ebp-94h]
    loc_00408575: add     esi,ebx
    loc_00408577: add     esi,edi
    loc_00408579: mov     edi,dword ptr [ebp-3B4h]
    loc_0040857F: mov     dword ptr [ebp-3C4h],esi
    loc_00408585: mov     ebx,dword ptr [ebp-3C4h]
    loc_0040858B: mov     esi,dword ptr [ebp-3C0h]
    loc_00408591: xor     edi,eax
    loc_00408593: mov     eax,dword ptr [ebp-3B0h]
    loc_00408599: and     ecx,ebx
    loc_0040859B: and     edi,edx
    loc_0040859D: xor     edi,ecx
    loc_0040859F: mov     edx,dword ptr [ebp-3B4h]
    loc_004085A5: mov     dword ptr [ebp-0A0h],edi
    loc_004085AB: and     eax,esi
    loc_004085AD: xor     dword ptr [ebp-0A0h],eax
    loc_004085B3: xor     dword ptr [ebp-0A0h],edx
    loc_004085B9: mov     ecx,dword ptr [ebp-30h]
    loc_004085BC: mov     eax,dword ptr [ebp-3BCh]
    loc_004085C2: rol     dword ptr [ebp-0A0h],19h
    loc_004085C9: mov     edi,dword ptr [ecx+24h]
    loc_004085CC: mov     edx,dword ptr [ebp-3C0h]
    loc_004085D2: rol     dword ptr [ebp-3A8h],15h
    loc_004085D9: mov     esi,dword ptr [ebp-0A0h]
    loc_004085DF: mov     dword ptr [ebp-544h],edi
    loc_004085E5: mov     ecx,dword ptr [ebp-3B0h]
    loc_004085EB: mov     ebx,dword ptr [ebp-3A8h]
    loc_004085F1: rol     dword ptr [ebp-3ACh],15h
    loc_004085F8: add     esi,ebx
    loc_004085FA: add     esi,edi
    loc_004085FC: mov     dword ptr [ebp-3C8h],esi
    loc_00408602: mov     edi,dword ptr [ebp-3B8h]
    loc_00408608: mov     ebx,dword ptr [ebp-3C8h]
    loc_0040860E: mov     esi,dword ptr [ebp-3C4h]
    loc_00408614: xor     edi,eax
    loc_00408616: mov     eax,dword ptr [ebp-3B4h]
    loc_0040861C: and     ecx,ebx
    loc_0040861E: and     edi,edx
    loc_00408620: xor     edi,ecx
    loc_00408622: mov     dword ptr [ebp-0ACh],edi
    loc_00408628: and     eax,esi
    loc_0040862A: mov     edx,dword ptr [ebp-3B8h]
    loc_00408630: xor     dword ptr [ebp-0ACh],eax
    loc_00408636: mov     ecx,dword ptr [ebp-30h]
    loc_00408639: mov     ebx,dword ptr [ebp-3ACh]
    loc_0040863F: xor     dword ptr [ebp-0ACh],edx
    loc_00408645: mov     edi,dword ptr [ecx+28h]
    loc_00408648: rol     dword ptr [ebp-0ACh],19h
    loc_0040864F: mov     dword ptr [ebp-548h],edi
    loc_00408655: mov     esi,dword ptr [ebp-0ACh]
    loc_0040865B: add     esi,ebx
    loc_0040865D: add     esi,edi
    loc_0040865F: mov     dword ptr [ebp-3CCh],esi
    loc_00408665: mov     eax,dword ptr [ebp-3C0h]
    loc_0040866B: mov     edi,dword ptr [ebp-3BCh]
    loc_00408671: rol     dword ptr [ebp-3B0h],15h
    loc_00408678: mov     edx,dword ptr [ebp-3C4h]
    loc_0040867E: mov     ebx,dword ptr [ebp-3CCh]
    loc_00408684: mov     ecx,dword ptr [ebp-3B4h]
    loc_0040868A: xor     edi,eax
    loc_0040868C: mov     esi,dword ptr [ebp-3C8h]
    loc_00408692: mov     eax,dword ptr [ebp-3B8h]
    loc_00408698: and     edi,edx
    loc_0040869A: and     ecx,ebx
    loc_0040869C: xor     edi,ecx
    loc_0040869E: mov     edx,dword ptr [ebp-3BCh]
    loc_004086A4: and     eax,esi
    loc_004086A6: mov     dword ptr [ebp-0B8h],edi
    loc_004086AC: mov     ecx,dword ptr [ebp-30h]
    loc_004086AF: mov     ebx,dword ptr [ebp-3B0h]
    loc_004086B5: xor     dword ptr [ebp-0B8h],eax
    loc_004086BB: mov     edi,dword ptr [ecx+2Ch]
    loc_004086BE: mov     eax,dword ptr [ebp-3C4h]
    loc_004086C4: xor     dword ptr [ebp-0B8h],edx
    loc_004086CA: mov     ecx,dword ptr [ebp-3B8h]
    loc_004086D0: mov     dword ptr [ebp-54Ch],edi
    loc_004086D6: mov     edx,dword ptr [ebp-3C8h]
    loc_004086DC: rol     dword ptr [ebp-0B8h],19h
    loc_004086E3: mov     esi,dword ptr [ebp-0B8h]
    loc_004086E9: add     esi,ebx
    loc_004086EB: add     esi,edi
    loc_004086ED: mov     edi,dword ptr [ebp-3C0h]
    loc_004086F3: mov     dword ptr [ebp-3D0h],esi
    loc_004086F9: mov     ebx,dword ptr [ebp-3D0h]
    loc_004086FF: mov     esi,dword ptr [ebp-3CCh]
    loc_00408705: xor     edi,eax
    loc_00408707: mov     eax,dword ptr [ebp-3BCh]
    loc_0040870D: and     ecx,ebx
    loc_0040870F: and     edi,edx
    loc_00408711: xor     edi,ecx
    loc_00408713: mov     edx,dword ptr [ebp-3C0h]
    loc_00408719: mov     dword ptr [ebp-0C4h],edi
    loc_0040871F: and     eax,esi
    loc_00408721: xor     dword ptr [ebp-0C4h],eax
    loc_00408727: xor     dword ptr [ebp-0C4h],edx
    loc_0040872D: mov     ecx,dword ptr [ebp-30h]
    loc_00408730: mov     eax,dword ptr [ebp-3C8h]
    loc_00408736: rol     dword ptr [ebp-0C4h],19h
    loc_0040873D: mov     edi,dword ptr [ecx+30h]
    loc_00408740: mov     edx,dword ptr [ebp-3CCh]
    loc_00408746: rol     dword ptr [ebp-3B4h],15h
    loc_0040874D: mov     esi,dword ptr [ebp-0C4h]
    loc_00408753: mov     dword ptr [ebp-550h],edi
    loc_00408759: mov     ecx,dword ptr [ebp-3BCh]
    loc_0040875F: mov     ebx,dword ptr [ebp-3B4h]
    loc_00408765: rol     dword ptr [ebp-3B8h],15h
    loc_0040876C: add     esi,ebx
    loc_0040876E: add     esi,edi
    loc_00408770: mov     dword ptr [ebp-3D4h],esi
    loc_00408776: mov     edi,dword ptr [ebp-3C4h]
    loc_0040877C: mov     ebx,dword ptr [ebp-3D4h]
    loc_00408782: mov     esi,dword ptr [ebp-3D0h]
    loc_00408788: xor     edi,eax
    loc_0040878A: mov     eax,dword ptr [ebp-3C0h]
    loc_00408790: and     ecx,ebx
    loc_00408792: and     edi,edx
    loc_00408794: xor     edi,ecx
    loc_00408796: mov     dword ptr [ebp-0D0h],edi
    loc_0040879C: and     eax,esi
    loc_0040879E: mov     edx,dword ptr [ebp-3C4h]
    loc_004087A4: xor     dword ptr [ebp-0D0h],eax
    loc_004087AA: mov     ecx,dword ptr [ebp-30h]
    loc_004087AD: mov     ebx,dword ptr [ebp-3B8h]
    loc_004087B3: xor     dword ptr [ebp-0D0h],edx
    loc_004087B9: mov     edi,dword ptr [ecx+34h]
    loc_004087BC: rol     dword ptr [ebp-0D0h],19h
    loc_004087C3: mov     dword ptr [ebp-554h],edi
    loc_004087C9: mov     esi,dword ptr [ebp-0D0h]
    loc_004087CF: add     esi,ebx
    loc_004087D1: add     esi,edi
    loc_004087D3: mov     dword ptr [ebp-3D8h],esi
    loc_004087D9: mov     eax,dword ptr [ebp-3CCh]
    loc_004087DF: mov     edi,dword ptr [ebp-3C8h]
    loc_004087E5: rol     dword ptr [ebp-3BCh],15h
    loc_004087EC: mov     edx,dword ptr [ebp-3D0h]
    loc_004087F2: mov     ebx,dword ptr [ebp-3D8h]
    loc_004087F8: mov     ecx,dword ptr [ebp-3C0h]
    loc_004087FE: xor     edi,eax
    loc_00408800: mov     esi,dword ptr [ebp-3D4h]
    loc_00408806: mov     eax,dword ptr [ebp-3C4h]
    loc_0040880C: and     edi,edx
    loc_0040880E: and     ecx,ebx
    loc_00408810: xor     edi,ecx
    loc_00408812: mov     edx,dword ptr [ebp-3C8h]
    loc_00408818: and     eax,esi
    loc_0040881A: mov     dword ptr [ebp-0DCh],edi
    loc_00408820: mov     ecx,dword ptr [ebp-30h]
    loc_00408823: mov     ebx,dword ptr [ebp-3BCh]
    loc_00408829: xor     dword ptr [ebp-0DCh],eax
    loc_0040882F: mov     edi,dword ptr [ecx+38h]
    loc_00408832: mov     eax,dword ptr [ebp-3D0h]
    loc_00408838: xor     dword ptr [ebp-0DCh],edx
    loc_0040883E: mov     ecx,dword ptr [ebp-3C4h]
    loc_00408844: mov     dword ptr [ebp-558h],edi
    loc_0040884A: mov     edx,dword ptr [ebp-3D4h]
    loc_00408850: rol     dword ptr [ebp-0DCh],19h
    loc_00408857: mov     esi,dword ptr [ebp-0DCh]
    loc_0040885D: add     esi,ebx
    loc_0040885F: add     esi,edi
    loc_00408861: mov     edi,dword ptr [ebp-3CCh]
    loc_00408867: mov     dword ptr [ebp-3DCh],esi
    loc_0040886D: mov     ebx,dword ptr [ebp-3DCh]
    loc_00408873: mov     esi,dword ptr [ebp-3D8h]
    loc_00408879: xor     edi,eax
    loc_0040887B: mov     eax,dword ptr [ebp-3C8h]
    loc_00408881: and     ecx,ebx
    loc_00408883: and     edi,edx
    loc_00408885: xor     edi,ecx
    loc_00408887: mov     edx,dword ptr [ebp-3CCh]
    loc_0040888D: mov     dword ptr [ebp-0E8h],edi
    loc_00408893: and     eax,esi
    loc_00408895: xor     dword ptr [ebp-0E8h],eax
    loc_0040889B: xor     dword ptr [ebp-0E8h],edx
    loc_004088A1: mov     ecx,dword ptr [ebp-30h]
    loc_004088A4: mov     eax,dword ptr [ebp-3D4h]
    loc_004088AA: rol     dword ptr [ebp-0E8h],19h
    loc_004088B1: mov     edi,dword ptr [ecx+3Ch]
    loc_004088B4: mov     edx,dword ptr [ebp-3D8h]
    loc_004088BA: rol     dword ptr [ebp-3C0h],15h
    loc_004088C1: mov     esi,dword ptr [ebp-0E8h]
    loc_004088C7: mov     dword ptr [ebp-55Ch],edi
    loc_004088CD: mov     ecx,dword ptr [ebp-3C8h]
    loc_004088D3: mov     ebx,dword ptr [ebp-3C0h]
    loc_004088D9: rol     dword ptr [ebp-3C4h],15h
    loc_004088E0: add     esi,ebx
    loc_004088E2: add     esi,edi
    loc_004088E4: mov     dword ptr [ebp-3E0h],esi
    loc_004088EA: mov     edi,dword ptr [ebp-3D0h]
    loc_004088F0: mov     ebx,dword ptr [ebp-3E0h]
    loc_004088F6: mov     esi,dword ptr [ebp-3DCh]
    loc_004088FC: xor     edi,eax
    loc_004088FE: mov     eax,dword ptr [ebp-3CCh]
    loc_00408904: and     ecx,ebx
    loc_00408906: and     edi,edx
    loc_00408908: xor     edi,ecx
    loc_0040890A: mov     dword ptr [ebp-0F4h],edi
    loc_00408910: and     eax,esi
    loc_00408912: mov     edx,dword ptr [ebp-3D0h]
    loc_00408918: xor     dword ptr [ebp-0F4h],eax
    loc_0040891E: mov     ecx,dword ptr [ebp-30h]
    loc_00408921: mov     ebx,dword ptr [ebp-3C4h]
    loc_00408927: xor     dword ptr [ebp-0F4h],edx
    loc_0040892D: mov     edi,dword ptr [ecx+40h]
    loc_00408930: rol     dword ptr [ebp-0F4h],19h
    loc_00408937: mov     dword ptr [ebp-560h],edi
    loc_0040893D: mov     esi,dword ptr [ebp-0F4h]
    loc_00408943: add     esi,ebx
    loc_00408945: add     esi,edi
    loc_00408947: mov     dword ptr [ebp-3E4h],esi
    loc_0040894D: mov     eax,dword ptr [ebp-3D8h]
    loc_00408953: mov     edi,dword ptr [ebp-3D4h]
    loc_00408959: rol     dword ptr [ebp-3C8h],15h
    loc_00408960: mov     edx,dword ptr [ebp-3DCh]
    loc_00408966: mov     ebx,dword ptr [ebp-3E4h]
    loc_0040896C: mov     ecx,dword ptr [ebp-3CCh]
    loc_00408972: xor     edi,eax
    loc_00408974: mov     esi,dword ptr [ebp-3E0h]
    loc_0040897A: mov     eax,dword ptr [ebp-3D0h]
    loc_00408980: and     edi,edx
    loc_00408982: and     ecx,ebx
    loc_00408984: xor     edi,ecx
    loc_00408986: mov     edx,dword ptr [ebp-3D4h]
    loc_0040898C: and     eax,esi
    loc_0040898E: mov     dword ptr [ebp-100h],edi
    loc_00408994: mov     ecx,dword ptr [ebp-30h]
    loc_00408997: mov     ebx,dword ptr [ebp-3C8h]
    loc_0040899D: xor     dword ptr [ebp-100h],eax
    loc_004089A3: mov     edi,dword ptr [ecx+44h]
    loc_004089A6: mov     eax,dword ptr [ebp-3DCh]
    loc_004089AC: xor     dword ptr [ebp-100h],edx
    loc_004089B2: mov     ecx,dword ptr [ebp-3D0h]
    loc_004089B8: mov     dword ptr [ebp-564h],edi
    loc_004089BE: mov     edx,dword ptr [ebp-3E0h]
    loc_004089C4: rol     dword ptr [ebp-100h],19h
    loc_004089CB: mov     esi,dword ptr [ebp-100h]
    loc_004089D1: add     esi,ebx
    loc_004089D3: add     esi,edi
    loc_004089D5: mov     edi,dword ptr [ebp-3D8h]
    loc_004089DB: mov     dword ptr [ebp-3E8h],esi
    loc_004089E1: mov     ebx,dword ptr [ebp-3E8h]
    loc_004089E7: mov     esi,dword ptr [ebp-3E4h]
    loc_004089ED: xor     edi,eax
    loc_004089EF: mov     eax,dword ptr [ebp-3D4h]
    loc_004089F5: and     ecx,ebx
    loc_004089F7: and     edi,edx
    loc_004089F9: xor     edi,ecx
    loc_004089FB: mov     edx,dword ptr [ebp-3D8h]
    loc_00408A01: mov     dword ptr [ebp-10Ch],edi
    loc_00408A07: and     eax,esi
    loc_00408A09: xor     dword ptr [ebp-10Ch],eax
    loc_00408A0F: xor     dword ptr [ebp-10Ch],edx
    loc_00408A15: mov     ecx,dword ptr [ebp-30h]
    loc_00408A18: mov     eax,dword ptr [ebp-3E0h]
    loc_00408A1E: rol     dword ptr [ebp-10Ch],19h
    loc_00408A25: mov     edi,dword ptr [ecx+48h]
    loc_00408A28: mov     edx,dword ptr [ebp-3E4h]
    loc_00408A2E: rol     dword ptr [ebp-3CCh],15h
    loc_00408A35: mov     esi,dword ptr [ebp-10Ch]
    loc_00408A3B: mov     dword ptr [ebp-568h],edi
    loc_00408A41: mov     ecx,dword ptr [ebp-3D4h]
    loc_00408A47: mov     ebx,dword ptr [ebp-3CCh]
    loc_00408A4D: rol     dword ptr [ebp-3D0h],15h
    loc_00408A54: add     esi,ebx
    loc_00408A56: add     esi,edi
    loc_00408A58: mov     dword ptr [ebp-3ECh],esi
    loc_00408A5E: mov     edi,dword ptr [ebp-3DCh]
    loc_00408A64: mov     ebx,dword ptr [ebp-3ECh]
    loc_00408A6A: mov     esi,dword ptr [ebp-3E8h]
    loc_00408A70: xor     edi,eax
    loc_00408A72: mov     eax,dword ptr [ebp-3D8h]
    loc_00408A78: and     ecx,ebx
    loc_00408A7A: and     edi,edx
    loc_00408A7C: xor     edi,ecx
    loc_00408A7E: mov     dword ptr [ebp-118h],edi
    loc_00408A84: and     eax,esi
    loc_00408A86: mov     edx,dword ptr [ebp-3DCh]
    loc_00408A8C: xor     dword ptr [ebp-118h],eax
    loc_00408A92: mov     ecx,dword ptr [ebp-30h]
    loc_00408A95: mov     ebx,dword ptr [ebp-3D0h]
    loc_00408A9B: xor     dword ptr [ebp-118h],edx
    loc_00408AA1: mov     edi,dword ptr [ecx+4Ch]
    loc_00408AA4: rol     dword ptr [ebp-118h],19h
    loc_00408AAB: mov     dword ptr [ebp-56Ch],edi
    loc_00408AB1: mov     esi,dword ptr [ebp-118h]
    loc_00408AB7: add     esi,ebx
    loc_00408AB9: add     esi,edi
    loc_00408ABB: mov     dword ptr [ebp-3F0h],esi
    loc_00408AC1: mov     eax,dword ptr [ebp-3E4h]
    loc_00408AC7: mov     edi,dword ptr [ebp-3E0h]
    loc_00408ACD: rol     dword ptr [ebp-3D4h],15h
    loc_00408AD4: mov     edx,dword ptr [ebp-3E8h]
    loc_00408ADA: mov     ebx,dword ptr [ebp-3F0h]
    loc_00408AE0: mov     ecx,dword ptr [ebp-3D8h]
    loc_00408AE6: xor     edi,eax
    loc_00408AE8: mov     esi,dword ptr [ebp-3ECh]
    loc_00408AEE: mov     eax,dword ptr [ebp-3DCh]
    loc_00408AF4: and     edi,edx
    loc_00408AF6: and     ecx,ebx
    loc_00408AF8: xor     edi,ecx
    loc_00408AFA: mov     edx,dword ptr [ebp-3E0h]
    loc_00408B00: and     eax,esi
    loc_00408B02: mov     dword ptr [ebp-124h],edi
    loc_00408B08: mov     ecx,dword ptr [ebp-30h]
    loc_00408B0B: mov     ebx,dword ptr [ebp-3D4h]
    loc_00408B11: xor     dword ptr [ebp-124h],eax
    loc_00408B17: mov     edi,dword ptr [ecx+50h]
    loc_00408B1A: mov     eax,dword ptr [ebp-3E8h]
    loc_00408B20: xor     dword ptr [ebp-124h],edx
    loc_00408B26: mov     ecx,dword ptr [ebp-3DCh]
    loc_00408B2C: mov     dword ptr [ebp-570h],edi
    loc_00408B32: mov     edx,dword ptr [ebp-3ECh]
    loc_00408B38: rol     dword ptr [ebp-124h],19h
    loc_00408B3F: mov     esi,dword ptr [ebp-124h]
    loc_00408B45: add     esi,ebx
    loc_00408B47: add     esi,edi
    loc_00408B49: mov     edi,dword ptr [ebp-3E4h]
    loc_00408B4F: mov     dword ptr [ebp-3F4h],esi
    loc_00408B55: mov     ebx,dword ptr [ebp-3F4h]
    loc_00408B5B: mov     esi,dword ptr [ebp-3F0h]
    loc_00408B61: xor     edi,eax
    loc_00408B63: mov     eax,dword ptr [ebp-3E0h]
    loc_00408B69: and     ecx,ebx
    loc_00408B6B: and     edi,edx
    loc_00408B6D: xor     edi,ecx
    loc_00408B6F: mov     edx,dword ptr [ebp-3E4h]
    loc_00408B75: mov     dword ptr [ebp-130h],edi
    loc_00408B7B: and     eax,esi
    loc_00408B7D: xor     dword ptr [ebp-130h],eax
    loc_00408B83: xor     dword ptr [ebp-130h],edx
    loc_00408B89: mov     ecx,dword ptr [ebp-30h]
    loc_00408B8C: mov     eax,dword ptr [ebp-3ECh]
    loc_00408B92: rol     dword ptr [ebp-130h],19h
    loc_00408B99: mov     edi,dword ptr [ecx+54h]
    loc_00408B9C: mov     edx,dword ptr [ebp-3F0h]
    loc_00408BA2: rol     dword ptr [ebp-3D8h],15h
    loc_00408BA9: mov     esi,dword ptr [ebp-130h]
    loc_00408BAF: mov     dword ptr [ebp-574h],edi
    loc_00408BB5: mov     ecx,dword ptr [ebp-3E0h]
    loc_00408BBB: mov     ebx,dword ptr [ebp-3D8h]
    loc_00408BC1: rol     dword ptr [ebp-3DCh],15h
    loc_00408BC8: add     esi,ebx
    loc_00408BCA: add     esi,edi
    loc_00408BCC: mov     dword ptr [ebp-3F8h],esi
    loc_00408BD2: mov     edi,dword ptr [ebp-3E8h]
    loc_00408BD8: mov     ebx,dword ptr [ebp-3F8h]
    loc_00408BDE: mov     esi,dword ptr [ebp-3F4h]
    loc_00408BE4: xor     edi,eax
    loc_00408BE6: mov     eax,dword ptr [ebp-3E4h]
    loc_00408BEC: and     ecx,ebx
    loc_00408BEE: and     edi,edx
    loc_00408BF0: xor     edi,ecx
    loc_00408BF2: mov     dword ptr [ebp-13Ch],edi
    loc_00408BF8: and     eax,esi
    loc_00408BFA: mov     edx,dword ptr [ebp-3E8h]
    loc_00408C00: xor     dword ptr [ebp-13Ch],eax
    loc_00408C06: mov     ecx,dword ptr [ebp-30h]
    loc_00408C09: mov     ebx,dword ptr [ebp-3DCh]
    loc_00408C0F: xor     dword ptr [ebp-13Ch],edx
    loc_00408C15: mov     edi,dword ptr [ecx+58h]
    loc_00408C18: rol     dword ptr [ebp-13Ch],19h
    loc_00408C1F: mov     dword ptr [ebp-578h],edi
    loc_00408C25: mov     esi,dword ptr [ebp-13Ch]
    loc_00408C2B: add     esi,ebx
    loc_00408C2D: add     esi,edi
    loc_00408C2F: mov     dword ptr [ebp-3FCh],esi
    loc_00408C35: mov     eax,dword ptr [ebp-3F0h]
    loc_00408C3B: mov     edi,dword ptr [ebp-3ECh]
    loc_00408C41: rol     dword ptr [ebp-3E0h],15h
    loc_00408C48: mov     edx,dword ptr [ebp-3F4h]
    loc_00408C4E: mov     ebx,dword ptr [ebp-3FCh]
    loc_00408C54: mov     ecx,dword ptr [ebp-3E4h]
    loc_00408C5A: xor     edi,eax
    loc_00408C5C: mov     esi,dword ptr [ebp-3F8h]
    loc_00408C62: mov     eax,dword ptr [ebp-3E8h]
    loc_00408C68: and     edi,edx
    loc_00408C6A: and     ecx,ebx
    loc_00408C6C: xor     edi,ecx
    loc_00408C6E: mov     ecx,dword ptr [ebp-30h]
    loc_00408C71: and     eax,esi
    loc_00408C73: mov     dword ptr [ebp-148h],edi
    loc_00408C79: mov     edi,dword ptr [ebp-3ECh]
    loc_00408C7F: mov     edx,dword ptr [ebp-3E0h]
    loc_00408C85: xor     dword ptr [ebp-148h],eax
    loc_00408C8B: mov     ebx,dword ptr [ecx+5Ch]
    loc_00408C8E: mov     eax,dword ptr [ebp-3F4h]
    loc_00408C94: xor     dword ptr [ebp-148h],edi
    loc_00408C9A: mov     ecx,dword ptr [ebp-3E8h]
    loc_00408CA0: mov     dword ptr [ebp-57Ch],ebx
    loc_00408CA6: mov     edi,dword ptr [ebp-3F8h]
    loc_00408CAC: rol     dword ptr [ebp-148h],19h
    loc_00408CB3: mov     esi,dword ptr [ebp-148h]
    loc_00408CB9: add     esi,edx
    loc_00408CBB: add     esi,ebx
    loc_00408CBD: mov     ebx,dword ptr [ebp-3F0h]
    loc_00408CC3: mov     dword ptr [ebp-400h],esi
    loc_00408CC9: mov     edx,dword ptr [ebp-400h]
    loc_00408CCF: mov     esi,dword ptr [ebp-3FCh]
    loc_00408CD5: xor     ebx,eax
    loc_00408CD7: mov     eax,dword ptr [ebp-3ECh]
    loc_00408CDD: and     ecx,edx
    loc_00408CDF: and     ebx,edi
    loc_00408CE1: xor     ebx,ecx
    loc_00408CE3: mov     edi,dword ptr [ebp-3F0h]
    loc_00408CE9: mov     dword ptr [ebp-154h],ebx
    loc_00408CEF: and     eax,esi
    loc_00408CF1: xor     dword ptr [ebp-154h],eax
    loc_00408CF7: xor     dword ptr [ebp-154h],edi
    loc_00408CFD: mov     ecx,dword ptr [ebp-30h]
    loc_00408D00: mov     eax,dword ptr [ebp-3F8h]
    loc_00408D06: rol     dword ptr [ebp-154h],19h
    loc_00408D0D: mov     ebx,dword ptr [ecx+60h]
    loc_00408D10: mov     edi,dword ptr [ebp-3FCh]
    loc_00408D16: rol     dword ptr [ebp-3E4h],15h
    loc_00408D1D: mov     esi,dword ptr [ebp-154h]
    loc_00408D23: mov     dword ptr [ebp-580h],ebx
    loc_00408D29: mov     ecx,dword ptr [ebp-3ECh]
    loc_00408D2F: mov     edx,dword ptr [ebp-3E4h]
    loc_00408D35: rol     dword ptr [ebp-3E8h],15h
    loc_00408D3C: add     esi,edx
    loc_00408D3E: add     esi,ebx
    loc_00408D40: mov     dword ptr [ebp-404h],esi
    loc_00408D46: mov     ebx,dword ptr [ebp-3F4h]
    loc_00408D4C: mov     edx,dword ptr [ebp-404h]
    loc_00408D52: mov     esi,dword ptr [ebp-400h]
    loc_00408D58: xor     ebx,eax
    loc_00408D5A: mov     eax,dword ptr [ebp-3F0h]
    loc_00408D60: and     ecx,edx
    loc_00408D62: and     ebx,edi
    loc_00408D64: xor     ebx,ecx
    loc_00408D66: mov     dword ptr [ebp-160h],ebx
    loc_00408D6C: and     eax,esi
    loc_00408D6E: mov     edi,dword ptr [ebp-3F4h]
    loc_00408D74: xor     dword ptr [ebp-160h],eax
    loc_00408D7A: mov     ecx,dword ptr [ebp-30h]
    loc_00408D7D: mov     edx,dword ptr [ebp-3E8h]
    loc_00408D83: xor     dword ptr [ebp-160h],edi
    loc_00408D89: mov     ebx,dword ptr [ecx+64h]
    loc_00408D8C: rol     dword ptr [ebp-160h],19h
    loc_00408D93: mov     dword ptr [ebp-584h],ebx
    loc_00408D99: mov     eax,dword ptr [ebp-160h]
    loc_00408D9F: add     eax,edx
    loc_00408DA1: add     eax,ebx
    loc_00408DA3: mov     dword ptr [ebp-408h],eax
    loc_00408DA9: mov     esi,dword ptr [ebp-3FCh]
    loc_00408DAF: mov     ebx,dword ptr [ebp-3F8h]
    loc_00408DB5: rol     dword ptr [ebp-3ECh],15h
    loc_00408DBC: mov     edi,dword ptr [ebp-400h]
    loc_00408DC2: mov     ecx,dword ptr [ebp-3F0h]
    loc_00408DC8: mov     edx,dword ptr [ebp-408h]
    loc_00408DCE: xor     ebx,esi
    loc_00408DD0: mov     eax,dword ptr [ebp-404h]
    loc_00408DD6: mov     esi,dword ptr [ebp-3F4h]
    loc_00408DDC: and     ebx,edi
    loc_00408DDE: and     ecx,edx
    loc_00408DE0: xor     ebx,ecx
    loc_00408DE2: mov     edi,dword ptr [ebp-3F8h]
    loc_00408DE8: and     esi,eax
    loc_00408DEA: mov     dword ptr [ebp-16Ch],ebx
    loc_00408DF0: mov     ecx,dword ptr [ebp-30h]
    loc_00408DF3: mov     ebx,dword ptr [ebp-3ECh]
    loc_00408DF9: xor     dword ptr [ebp-16Ch],esi
    loc_00408DFF: mov     edx,dword ptr [ecx+68h]
    loc_00408E02: mov     eax,dword ptr [ebp-400h]
    loc_00408E08: xor     dword ptr [ebp-16Ch],edi
    loc_00408E0E: mov     esi,dword ptr [ebp-404h]
    loc_00408E14: mov     dword ptr [ebp-588h],edx
    loc_00408E1A: mov     ecx,dword ptr [ebp-408h]
    loc_00408E20: rol     dword ptr [ebp-16Ch],19h
    loc_00408E27: mov     edi,dword ptr [ebp-16Ch]
    loc_00408E2D: add     edi,ebx
    loc_00408E2F: rol     dword ptr [ebp-3F0h],15h
    loc_00408E36: add     edi,edx
    loc_00408E38: mov     edx,dword ptr [ebp-3FCh]
    loc_00408E3E: mov     dword ptr [ebp-40Ch],edi
    loc_00408E44: mov     ebx,dword ptr [ebp-3F4h]
    loc_00408E4A: xor     edx,eax
    loc_00408E4C: mov     eax,dword ptr [ebp-3F8h]
    loc_00408E52: and     ebx,edi
    loc_00408E54: and     edx,esi
    loc_00408E56: mov     edi,dword ptr [ebp-3FCh]
    loc_00408E5C: xor     edx,ebx
    loc_00408E5E: mov     esi,dword ptr [ebp-3F0h]
    loc_00408E64: and     eax,ecx
    loc_00408E66: mov     ebx,dword ptr [ebp-30h]
    loc_00408E69: xor     edx,eax
    loc_00408E6B: xor     edx,edi
    loc_00408E6D: rol     edx,19h
    loc_00408E70: lea     edi,[edx+esi]
    loc_00408E73: mov     edx,dword ptr [ebx+6Ch]
    loc_00408E76: add     edi,edx
    loc_00408E78: mov     dword ptr [ebp-58Ch],edx
    loc_00408E7E: mov     ecx,dword ptr [ebp-404h]
    loc_00408E84: mov     dword ptr [ebp-410h],edi
    loc_00408E8A: mov     edx,dword ptr [ebp-400h]
    loc_00408E90: mov     eax,dword ptr [ebp-408h]
    loc_00408E96: rol     dword ptr [ebp-3F4h],15h
    loc_00408E9D: mov     esi,dword ptr [ebp-3F8h]
    loc_00408EA3: xor     edx,ecx
    loc_00408EA5: rol     dword ptr [ebp-3F8h],15h
    loc_00408EAC: and     edx,eax
    loc_00408EAE: mov     ebx,dword ptr [ebp-40Ch]
    loc_00408EB4: mov     ecx,dword ptr [ebp-3FCh]
    loc_00408EBA: and     esi,edi
    loc_00408EBC: mov     eax,dword ptr [ebp-400h]
    loc_00408EC2: xor     edx,esi
    loc_00408EC4: mov     edi,dword ptr [ebp-3F4h]
    loc_00408ECA: and     ecx,ebx
    loc_00408ECC: mov     esi,dword ptr [ebp-30h]
    loc_00408ECF: xor     edx,ecx
    loc_00408ED1: xor     edx,eax
    loc_00408ED3: rol     edx,19h
    loc_00408ED6: mov     ebx,dword ptr [ebp-408h]
    loc_00408EDC: lea     eax,[edx+edi]
    loc_00408EDF: mov     edx,dword ptr [esi+70h]
    loc_00408EE2: mov     ecx,dword ptr [ebp-40Ch]
    loc_00408EE8: mov     edi,dword ptr [ebp-3FCh]
    loc_00408EEE: mov     dword ptr [ebp-590h],edx
    loc_00408EF4: add     eax,edx
    loc_00408EF6: mov     edx,dword ptr [ebp-404h]
    loc_00408EFC: mov     dword ptr [ebp-414h],eax
    loc_00408F02: mov     esi,dword ptr [ebp-410h]
    loc_00408F08: and     edi,eax
    loc_00408F0A: xor     edx,ebx
    loc_00408F0C: mov     ebx,dword ptr [ebp-400h]
    loc_00408F12: mov     eax,dword ptr [ebp-404h]
    loc_00408F18: and     edx,ecx
    loc_00408F1A: and     ebx,esi
    loc_00408F1C: xor     edx,edi
    loc_00408F1E: mov     ecx,dword ptr [ebp-3F8h]
    loc_00408F24: xor     edx,ebx
    loc_00408F26: mov     edi,dword ptr [ebp-30h]
    loc_00408F29: xor     edx,eax
    loc_00408F2B: mov     esi,dword ptr [ebp-40Ch]
    loc_00408F31: rol     edx,19h
    loc_00408F34: lea     eax,[edx+ecx]
    loc_00408F37: mov     edx,dword ptr [edi+74h]
    loc_00408F3A: mov     ebx,dword ptr [ebp-410h]
    loc_00408F40: mov     ecx,dword ptr [ebp-400h]
    loc_00408F46: add     eax,edx
    loc_00408F48: mov     dword ptr [ebp-594h],edx
    loc_00408F4E: mov     edx,dword ptr [ebp-408h]
    loc_00408F54: mov     dword ptr [ebp-418h],eax
    loc_00408F5A: mov     edi,dword ptr [ebp-414h]
    loc_00408F60: xor     edx,esi
    loc_00408F62: mov     esi,dword ptr [ebp-404h]
    loc_00408F68: and     edx,ebx
    loc_00408F6A: and     ecx,eax
    loc_00408F6C: xor     edx,ecx
    loc_00408F6E: mov     eax,dword ptr [ebp-408h]
    loc_00408F74: and     esi,edi
    loc_00408F76: rol     dword ptr [ebp-3FCh],15h
    loc_00408F7D: xor     edx,esi
    loc_00408F7F: mov     ecx,dword ptr [ebp-30h]
    loc_00408F82: rol     dword ptr [ebp-400h],15h
    loc_00408F89: xor     edx,eax
    loc_00408F8B: mov     ebx,dword ptr [ebp-3FCh]
    loc_00408F91: mov     esi,dword ptr [ecx+78h]
    loc_00408F94: rol     edx,19h
    loc_00408F97: mov     edi,dword ptr [ebp-410h]
    loc_00408F9D: lea     eax,[edx+ebx]
    loc_00408FA0: mov     ebx,dword ptr [ebp-414h]
    loc_00408FA6: add     eax,esi
    loc_00408FA8: mov     dword ptr [ebp-598h],esi
    loc_00408FAE: mov     esi,dword ptr [ebp-40Ch]
    loc_00408FB4: mov     edx,dword ptr [ebp-404h]
    loc_00408FBA: mov     dword ptr [ebp-41Ch],eax
    loc_00408FC0: mov     ecx,dword ptr [ebp-418h]
    loc_00408FC6: xor     esi,edi
    loc_00408FC8: rol     dword ptr [ebp-404h],15h
    loc_00408FCF: and     edx,eax
    loc_00408FD1: mov     edi,dword ptr [ebp-408h]
    loc_00408FD7: and     esi,ebx
    loc_00408FD9: mov     eax,dword ptr [ebp-40Ch]
    loc_00408FDF: xor     esi,edx
    loc_00408FE1: mov     edx,dword ptr [ebp-30h]
    loc_00408FE4: and     edi,ecx
    loc_00408FE6: mov     ebx,dword ptr [ebp-400h]
    loc_00408FEC: xor     esi,edi
    loc_00408FEE: mov     ecx,dword ptr [edx+7Ch]
    loc_00408FF1: xor     esi,eax
    loc_00408FF3: rol     esi,19h
    loc_00408FF6: mov     edi,dword ptr [ebp-414h]
    loc_00408FFC: lea     eax,[esi+ebx]
    loc_00408FFF: mov     dword ptr [ebp-59Ch],ecx
    loc_00409005: add     eax,ecx
    loc_00409007: mov     esi,dword ptr [ebp-418h]
    loc_0040900D: mov     dword ptr [ebp-420h],eax
    loc_00409013: mov     ebx,dword ptr [ebp-41Ch]
    loc_00409019: mov     ecx,eax
    loc_0040901B: mov     edx,dword ptr [ebp-410h]
    loc_00409021: not     ecx
    loc_00409023: and     ecx,edi
    loc_00409025: and     ebx,esi
    loc_00409027: mov     edi,dword ptr [ebp-408h]
    loc_0040902D: xor     ecx,ebx
    loc_0040902F: xor     ecx,edx
    loc_00409031: mov     ebx,dword ptr [ebp-40Ch]
    loc_00409037: mov     esi,dword ptr [ebp-418h]
    loc_0040903D: xor     ecx,edi
    loc_0040903F: mov     edi,dword ptr [ebp-414h]
    loc_00409045: mov     edx,dword ptr [ebp-41Ch]
    loc_0040904B: and     ecx,ebx
    loc_0040904D: xor     edi,esi
    loc_0040904F: mov     ebx,dword ptr [ebp-418h]
    loc_00409055: and     edi,edx
    loc_00409057: mov     esi,dword ptr [ebp-408h]
    loc_0040905D: xor     ecx,edi
    loc_0040905F: mov     edi,eax
    loc_00409061: mov     eax,dword ptr [ebp-404h]
    loc_00409067: and     edi,ebx
    loc_00409069: xor     ecx,edi
    loc_0040906B: mov     edx,dword ptr [ebp-534h]
    loc_00409071: xor     ecx,esi
    loc_00409073: rol     ecx,19h
    loc_00409076: lea     ebx,[ecx+eax]
    loc_00409079: lea     eax,[ebx+edx+452821E6h]
    loc_00409080: mov     dword ptr [ebp-424h],eax
    loc_00409086: mov     edi,dword ptr [ebp-418h]
    loc_0040908C: mov     ecx,dword ptr [ebp-41Ch]
    loc_00409092: mov     esi,dword ptr [ebp-420h]
    loc_00409098: mov     ebx,eax
    loc_0040909A: mov     edx,dword ptr [ebp-414h]
    loc_004090A0: not     ebx
    loc_004090A2: and     ebx,edi
    loc_004090A4: mov     edi,dword ptr [ebp-40Ch]
    loc_004090AA: rol     dword ptr [ebp-408h],15h
    loc_004090B1: and     esi,ecx
    loc_004090B3: xor     ebx,esi
    loc_004090B5: xor     ebx,edx
    loc_004090B7: mov     esi,dword ptr [ebp-410h]
    loc_004090BD: mov     ecx,dword ptr [ebp-41Ch]
    loc_004090C3: xor     ebx,edi
    loc_004090C5: mov     edi,dword ptr [ebp-418h]
    loc_004090CB: mov     edx,dword ptr [ebp-420h]
    loc_004090D1: and     ebx,esi
    loc_004090D3: xor     edi,ecx
    loc_004090D5: mov     esi,dword ptr [ebp-41Ch]
    loc_004090DB: and     edi,edx
    loc_004090DD: mov     ecx,eax
    loc_004090DF: xor     ebx,edi
    loc_004090E1: mov     edi,dword ptr [ebp-40Ch]
    loc_004090E7: and     ecx,esi
    loc_004090E9: mov     eax,dword ptr [ebp-408h]
    loc_004090EF: rol     dword ptr [ebp-40Ch],15h
    loc_004090F6: xor     ebx,ecx
    loc_004090F8: mov     edx,dword ptr [ebp-558h]
    loc_004090FE: xor     ebx,edi
    loc_00409100: mov     ecx,dword ptr [ebp-420h]
    loc_00409106: rol     ebx,19h
    loc_00409109: lea     esi,[ebx+eax]
    loc_0040910C: mov     edi,dword ptr [ebp-424h]
    loc_00409112: lea     eax,[esi+edx+38D01377h]
    loc_00409119: mov     dword ptr [ebp-428h],eax
    loc_0040911F: mov     ebx,dword ptr [ebp-41Ch]
    loc_00409125: mov     esi,eax
    loc_00409127: mov     edx,dword ptr [ebp-418h]
    loc_0040912D: not     esi
    loc_0040912F: and     edi,ecx
    loc_00409131: mov     ecx,dword ptr [ebp-420h]
    loc_00409137: and     esi,ebx
    loc_00409139: mov     ebx,dword ptr [ebp-410h]
    loc_0040913F: xor     esi,edi
    loc_00409141: xor     esi,edx
    loc_00409143: mov     edi,dword ptr [ebp-414h]
    loc_00409149: xor     esi,ebx
    loc_0040914B: mov     ebx,dword ptr [ebp-41Ch]
    loc_00409151: mov     edx,dword ptr [ebp-424h]
    loc_00409157: and     esi,edi
    loc_00409159: mov     edi,eax
    loc_0040915B: mov     eax,dword ptr [ebp-420h]
    loc_00409161: xor     ebx,ecx
    loc_00409163: and     ebx,edx
    loc_00409165: mov     ecx,dword ptr [ebp-410h]
    loc_0040916B: and     edi,eax
    loc_0040916D: xor     esi,ebx
    loc_0040916F: mov     ebx,dword ptr [ebp-40Ch]
    loc_00409175: xor     esi,edi
    loc_00409177: mov     edx,dword ptr [ebp-588h]
    loc_0040917D: xor     esi,ecx
    loc_0040917F: rol     esi,19h
    loc_00409182: mov     ecx,dword ptr [ebp-424h]
    loc_00409188: lea     edi,[esi+ebx]
    loc_0040918B: lea     eax,[edi+edx-41AB9931h]
    loc_00409192: mov     esi,dword ptr [ebp-420h]
    loc_00409198: mov     ebx,dword ptr [ebp-428h]
    loc_0040919E: mov     dword ptr [ebp-42Ch],eax
    loc_004091A4: mov     edi,eax
    loc_004091A6: mov     edx,dword ptr [ebp-41Ch]
    loc_004091AC: not     edi
    loc_004091AE: mov     eax,dword ptr [ebp-414h]
    loc_004091B4: and     ebx,ecx
    loc_004091B6: and     edi,esi
    loc_004091B8: mov     esi,dword ptr [ebp-418h]
    loc_004091BE: xor     edi,ebx
    loc_004091C0: mov     ecx,dword ptr [ebp-424h]
    loc_004091C6: xor     edi,edx
    loc_004091C8: mov     edx,dword ptr [ebp-420h]
    loc_004091CE: mov     ebx,dword ptr [ebp-428h]
    loc_004091D4: xor     edi,eax
    loc_004091D6: and     edi,esi
    loc_004091D8: mov     eax,dword ptr [ebp-424h]
    loc_004091DE: xor     edx,ecx
    loc_004091E0: mov     esi,dword ptr [ebp-42Ch]
    loc_004091E6: and     edx,ebx
    loc_004091E8: mov     ecx,dword ptr [ebp-414h]
    loc_004091EE: xor     edi,edx
    loc_004091F0: rol     dword ptr [ebp-410h],15h
    loc_004091F7: and     esi,eax
    loc_004091F9: mov     ebx,dword ptr [ebp-410h]
    loc_004091FF: rol     dword ptr [ebp-414h],15h
    loc_00409206: xor     edi,esi
    loc_00409208: mov     edx,dword ptr [ebp-568h]
    loc_0040920E: xor     edi,ecx
    loc_00409210: mov     esi,dword ptr [ebp-424h]
    loc_00409216: rol     edi,19h
    loc_00409219: mov     ecx,dword ptr [ebp-428h]
    loc_0040921F: lea     eax,[edi+ebx]
    loc_00409222: mov     ebx,dword ptr [ebp-42Ch]
    loc_00409228: lea     edi,[eax+edx+34E90C6Ch]
    loc_0040922F: mov     edx,dword ptr [ebp-420h]
    loc_00409235: mov     dword ptr [ebp-430h],edi
    loc_0040923B: not     edi
    loc_0040923D: and     ebx,ecx
    loc_0040923F: and     edi,esi
    loc_00409241: mov     esi,dword ptr [ebp-418h]
    loc_00409247: xor     edi,ebx
    loc_00409249: mov     ecx,dword ptr [ebp-41Ch]
    loc_0040924F: xor     edi,edx
    loc_00409251: mov     eax,dword ptr [ebp-428h]
    loc_00409257: mov     edx,dword ptr [ebp-424h]
    loc_0040925D: xor     edi,esi
    loc_0040925F: mov     ebx,dword ptr [ebp-42Ch]
    loc_00409265: and     edi,ecx
    loc_00409267: mov     esi,dword ptr [ebp-428h]
    loc_0040926D: xor     edx,eax
    loc_0040926F: mov     dword ptr [ebp-18Ch],edi
    loc_00409275: and     edx,ebx
    loc_00409277: mov     edi,dword ptr [ebp-430h]
    loc_0040927D: xor     dword ptr [ebp-18Ch],edx
    loc_00409283: mov     ecx,dword ptr [ebp-418h]
    loc_00409289: and     edi,esi
    loc_0040928B: xor     dword ptr [ebp-18Ch],edi
    loc_00409291: mov     eax,dword ptr [ebp-414h]
    loc_00409297: mov     edx,dword ptr [ebp-54Ch]
    loc_0040929D: xor     dword ptr [ebp-18Ch],ecx
    loc_004092A3: mov     esi,dword ptr [ebp-428h]
    loc_004092A9: mov     ecx,dword ptr [ebp-42Ch]
    loc_004092AF: rol     dword ptr [ebp-18Ch],19h
    loc_004092B6: mov     ebx,dword ptr [ebp-18Ch]
    loc_004092BC: add     ebx,eax
    loc_004092BE: mov     eax,dword ptr [ebp-430h]
    loc_004092C4: lea     edi,[ebx+edx-3F53D649h]
    loc_004092CB: mov     dword ptr [ebp-434h],edi
    loc_004092D1: not     edi
    loc_004092D3: and     edi,esi
    loc_004092D5: mov     dword ptr [ebp-19Ch],edi
    loc_004092DB: and     eax,ecx
    loc_004092DD: xor     dword ptr [ebp-19Ch],eax
    loc_004092E3: mov     ebx,dword ptr [ebp-424h]
    loc_004092E9: mov     edx,dword ptr [ebp-41Ch]
    loc_004092EF: xor     dword ptr [ebp-19Ch],ebx
    loc_004092F5: mov     edi,dword ptr [ebp-42Ch]
    loc_004092FB: mov     eax,dword ptr [ebp-428h]
    loc_00409301: xor     dword ptr [ebp-19Ch],edx
    loc_00409307: mov     esi,dword ptr [ebp-420h]
    loc_0040930D: mov     ecx,dword ptr [ebp-430h]
    loc_00409313: and     dword ptr [ebp-19Ch],esi
    loc_00409319: xor     eax,edi
    loc_0040931B: mov     ebx,dword ptr [ebp-42Ch]
    loc_00409321: and     eax,ecx
    loc_00409323: mov     edx,dword ptr [ebp-434h]
    loc_00409329: mov     esi,dword ptr [ebp-41Ch]
    loc_0040932F: xor     dword ptr [ebp-19Ch],eax
    loc_00409335: and     edx,ebx
    loc_00409337: rol     dword ptr [ebp-418h],15h
    loc_0040933E: mov     ecx,dword ptr [ebp-590h]
    loc_00409344: mov     ebx,dword ptr [ebp-430h]
    loc_0040934A: xor     dword ptr [ebp-19Ch],edx
    loc_00409350: mov     edi,dword ptr [ebp-418h]
    loc_00409356: mov     edx,dword ptr [ebp-42Ch]
    loc_0040935C: xor     dword ptr [ebp-19Ch],esi
    loc_00409362: mov     esi,dword ptr [ebp-434h]
    loc_00409368: rol     dword ptr [ebp-19Ch],19h
    loc_0040936F: and     esi,ebx
    loc_00409371: mov     ebx,dword ptr [ebp-424h]
    loc_00409377: mov     eax,dword ptr [ebp-19Ch]
    loc_0040937D: add     eax,edi
    loc_0040937F: lea     edi,[eax+ecx-3683AF23h]
    loc_00409386: mov     dword ptr [ebp-438h],edi
    loc_0040938C: mov     ecx,dword ptr [ebp-428h]
    loc_00409392: not     edi
    loc_00409394: and     edi,edx
    loc_00409396: mov     edx,dword ptr [ebp-420h]
    loc_0040939C: xor     edi,esi
    loc_0040939E: xor     edi,ecx
    loc_004093A0: xor     edi,edx
    loc_004093A2: and     edi,ebx
    loc_004093A4: mov     dword ptr [ebp-1ACh],edi
    loc_004093AA: mov     eax,dword ptr [ebp-430h]
    loc_004093B0: mov     ecx,dword ptr [ebp-42Ch]
    loc_004093B6: rol     dword ptr [ebp-41Ch],15h
    loc_004093BD: mov     esi,dword ptr [ebp-434h]
    loc_004093C3: xor     ecx,eax
    loc_004093C5: mov     edx,dword ptr [ebp-430h]
    loc_004093CB: and     ecx,esi
    loc_004093CD: mov     ebx,dword ptr [ebp-438h]
    loc_004093D3: xor     dword ptr [ebp-1ACh],ecx
    loc_004093D9: mov     edi,dword ptr [ebp-420h]
    loc_004093DF: and     ebx,edx
    loc_004093E1: xor     dword ptr [ebp-1ACh],ebx
    loc_004093E7: mov     eax,dword ptr [ebp-41Ch]
    loc_004093ED: mov     esi,dword ptr [ebp-53Ch]
    loc_004093F3: xor     dword ptr [ebp-1ACh],edi
    loc_004093F9: mov     edx,dword ptr [ebp-430h]
    loc_004093FF: mov     edi,dword ptr [ebp-434h]
    loc_00409405: rol     dword ptr [ebp-1ACh],19h
    loc_0040940C: mov     ecx,dword ptr [ebp-1ACh]
    loc_00409412: add     ecx,eax
    loc_00409414: lea     ebx,[ecx+esi+3F84D5B5h]
    loc_0040941B: mov     eax,dword ptr [ebp-438h]
    loc_00409421: mov     esi,dword ptr [ebp-42Ch]
    loc_00409427: mov     dword ptr [ebp-43Ch],ebx
    loc_0040942D: not     ebx
    loc_0040942F: and     ebx,edx
    loc_00409431: mov     dword ptr [ebp-1BCh],ebx
    loc_00409437: and     eax,edi
    loc_00409439: mov     ecx,dword ptr [ebp-424h]
    loc_0040943F: xor     dword ptr [ebp-1BCh],eax
    loc_00409445: mov     edx,dword ptr [ebp-428h]
    loc_0040944B: xor     dword ptr [ebp-1BCh],esi
    loc_00409451: xor     dword ptr [ebp-1BCh],ecx
    loc_00409457: and     dword ptr [ebp-1BCh],edx
    loc_0040945D: mov     ebx,dword ptr [ebp-434h]
    loc_00409463: mov     eax,dword ptr [ebp-430h]
    loc_00409469: mov     edi,dword ptr [ebp-438h]
    loc_0040946F: mov     esi,dword ptr [ebp-434h]
    loc_00409475: xor     eax,ebx
    loc_00409477: and     eax,edi
    loc_00409479: mov     ecx,dword ptr [ebp-43Ch]
    loc_0040947F: mov     edx,dword ptr [ebp-424h]
    loc_00409485: xor     dword ptr [ebp-1BCh],eax
    loc_0040948B: and     ecx,esi
    loc_0040948D: mov     edi,dword ptr [ebp-560h]
    loc_00409493: mov     esi,dword ptr [ebp-434h]
    loc_00409499: xor     dword ptr [ebp-1BCh],ecx
    loc_0040949F: mov     ecx,dword ptr [ebp-438h]
    loc_004094A5: xor     dword ptr [ebp-1BCh],edx
    loc_004094AB: mov     edx,dword ptr [ebp-43Ch]
    loc_004094B1: rol     dword ptr [ebp-1BCh],19h
    loc_004094B8: and     edx,ecx
    loc_004094BA: mov     ecx,dword ptr [ebp-42Ch]
    loc_004094C0: rol     dword ptr [ebp-420h],15h
    loc_004094C7: mov     eax,dword ptr [ebp-1BCh]
    loc_004094CD: mov     ebx,dword ptr [ebp-420h]
    loc_004094D3: add     eax,ebx
    loc_004094D5: lea     ebx,[eax+edi-4AB8F6E9h]
    loc_004094DC: mov     edi,dword ptr [ebp-430h]
    loc_004094E2: mov     dword ptr [ebp-440h],ebx
    loc_004094E8: not     ebx
    loc_004094EA: and     ebx,esi
    loc_004094EC: mov     esi,dword ptr [ebp-428h]
    loc_004094F2: xor     ebx,edx
    loc_004094F4: xor     ebx,edi
    loc_004094F6: mov     eax,dword ptr [ebp-438h]
    loc_004094FC: xor     ebx,esi
    loc_004094FE: mov     edi,dword ptr [ebp-434h]
    loc_00409504: and     ebx,ecx
    loc_00409506: mov     edx,dword ptr [ebp-43Ch]
    loc_0040950C: mov     esi,dword ptr [ebp-438h]
    loc_00409512: mov     dword ptr [ebp-1CCh],ebx
    loc_00409518: mov     ebx,dword ptr [ebp-440h]
    loc_0040951E: xor     edi,eax
    loc_00409520: and     edi,edx
    loc_00409522: and     ebx,esi
    loc_00409524: xor     dword ptr [ebp-1CCh],edi
    loc_0040952A: xor     dword ptr [ebp-1CCh],ebx
    loc_00409530: mov     ecx,dword ptr [ebp-428h]
    loc_00409536: mov     edx,dword ptr [ebp-520h]
    loc_0040953C: xor     dword ptr [ebp-1CCh],ecx
    loc_00409542: mov     esi,dword ptr [ebp-438h]
    loc_00409548: mov     ecx,dword ptr [ebp-43Ch]
    loc_0040954E: rol     dword ptr [ebp-1CCh],19h
    loc_00409555: rol     dword ptr [ebp-424h],15h
    loc_0040955C: mov     edi,dword ptr [ebp-1CCh]
    loc_00409562: mov     eax,dword ptr [ebp-424h]
    loc_00409568: add     edi,eax
    loc_0040956A: lea     ebx,[edi+edx-6DE92A27h]
    loc_00409571: mov     eax,dword ptr [ebp-440h]
    loc_00409577: mov     dword ptr [ebp-444h],ebx
    loc_0040957D: not     ebx
    loc_0040957F: mov     edi,dword ptr [ebp-434h]
    loc_00409585: and     ebx,esi
    loc_00409587: mov     edx,dword ptr [ebp-42Ch]
    loc_0040958D: and     eax,ecx
    loc_0040958F: mov     dword ptr [ebp-1DCh],ebx
    loc_00409595: mov     ebx,dword ptr [ebp-43Ch]
    loc_0040959B: mov     esi,dword ptr [ebp-430h]
    loc_004095A1: xor     dword ptr [ebp-1DCh],eax
    loc_004095A7: mov     eax,dword ptr [ebp-438h]
    loc_004095AD: mov     ecx,dword ptr [ebp-440h]
    loc_004095B3: xor     dword ptr [ebp-1DCh],edi
    loc_004095B9: mov     edi,dword ptr [ebp-43Ch]
    loc_004095BF: xor     eax,ebx
    loc_004095C1: and     eax,ecx
    loc_004095C3: xor     dword ptr [ebp-1DCh],edx
    loc_004095C9: mov     edx,dword ptr [ebp-444h]
    loc_004095CF: and     dword ptr [ebp-1DCh],esi
    loc_004095D5: and     edx,edi
    loc_004095D7: xor     dword ptr [ebp-1DCh],eax
    loc_004095DD: xor     dword ptr [ebp-1DCh],edx
    loc_004095E3: mov     esi,dword ptr [ebp-42Ch]
    loc_004095E9: mov     ecx,dword ptr [ebp-57Ch]
    loc_004095EF: xor     dword ptr [ebp-1DCh],esi
    loc_004095F5: mov     edi,dword ptr [ebp-43Ch]
    loc_004095FB: mov     edx,dword ptr [ebp-440h]
    loc_00409601: rol     dword ptr [ebp-1DCh],19h
    loc_00409608: mov     esi,dword ptr [ebp-444h]
    loc_0040960E: rol     dword ptr [ebp-428h],15h
    loc_00409615: mov     eax,dword ptr [ebp-1DCh]
    loc_0040961B: mov     ebx,dword ptr [ebp-428h]
    loc_00409621: add     eax,ebx
    loc_00409623: lea     ebx,[eax+ecx-768604E5h]
    loc_0040962A: mov     ecx,dword ptr [ebp-438h]
    loc_00409630: mov     dword ptr [ebp-448h],ebx
    loc_00409636: not     ebx
    loc_00409638: and     ebx,edi
    loc_0040963A: and     esi,edx
    loc_0040963C: mov     edi,dword ptr [ebp-430h]
    loc_00409642: xor     ebx,esi
    loc_00409644: mov     edx,dword ptr [ebp-434h]
    loc_0040964A: xor     ebx,ecx
    loc_0040964C: mov     eax,dword ptr [ebp-440h]
    loc_00409652: mov     ecx,dword ptr [ebp-43Ch]
    loc_00409658: xor     ebx,edi
    loc_0040965A: mov     esi,dword ptr [ebp-444h]
    loc_00409660: and     ebx,edx
    loc_00409662: mov     edi,dword ptr [ebp-440h]
    loc_00409668: xor     ecx,eax
    loc_0040966A: mov     dword ptr [ebp-1ECh],ebx
    loc_00409670: and     ecx,esi
    loc_00409672: mov     ebx,dword ptr [ebp-448h]
    loc_00409678: xor     dword ptr [ebp-1ECh],ecx
    loc_0040967E: mov     edx,dword ptr [ebp-430h]
    loc_00409684: and     ebx,edi
    loc_00409686: xor     dword ptr [ebp-1ECh],ebx
    loc_0040968C: xor     dword ptr [ebp-1ECh],edx
    loc_00409692: rol     dword ptr [ebp-1ECh],19h
    loc_00409699: rol     dword ptr [ebp-42Ch],15h
    loc_004096A0: mov     eax,dword ptr [ebp-42Ch]
    loc_004096A6: mov     ecx,dword ptr [ebp-1ECh]
    loc_004096AC: mov     esi,dword ptr [ebp-570h]
    loc_004096B2: mov     ebx,dword ptr [ebp-440h]
    loc_004096B8: add     ecx,eax
    loc_004096BA: lea     edi,[ecx+esi-2ECEF45Ah]
    loc_004096C1: mov     edx,dword ptr [ebp-444h]
    loc_004096C7: mov     eax,dword ptr [ebp-448h]
    loc_004096CD: mov     dword ptr [ebp-44Ch],edi
    loc_004096D3: not     edi
    loc_004096D5: mov     esi,dword ptr [ebp-43Ch]
    loc_004096DB: and     edi,ebx
    loc_004096DD: mov     ecx,dword ptr [ebp-434h]
    loc_004096E3: and     eax,edx
    loc_004096E5: mov     dword ptr [ebp-1FCh],edi
    loc_004096EB: mov     edi,dword ptr [ebp-444h]
    loc_004096F1: mov     ebx,dword ptr [ebp-438h]
    loc_004096F7: xor     dword ptr [ebp-1FCh],eax
    loc_004096FD: mov     eax,dword ptr [ebp-440h]
    loc_00409703: mov     edx,dword ptr [ebp-448h]
    loc_00409709: xor     dword ptr [ebp-1FCh],esi
    loc_0040970F: xor     eax,edi
    loc_00409711: mov     esi,dword ptr [ebp-444h]
    loc_00409717: and     eax,edx
    loc_00409719: xor     dword ptr [ebp-1FCh],ecx
    loc_0040971F: mov     ecx,dword ptr [ebp-44Ch]
    loc_00409725: and     dword ptr [ebp-1FCh],ebx
    loc_0040972B: and     ecx,esi
    loc_0040972D: mov     ebx,dword ptr [ebp-434h]
    loc_00409733: xor     dword ptr [ebp-1FCh],eax
    loc_00409739: xor     dword ptr [ebp-1FCh],ecx
    loc_0040973F: xor     dword ptr [ebp-1FCh],ebx
    loc_00409745: rol     dword ptr [ebp-1FCh],19h
    loc_0040974C: rol     dword ptr [ebp-430h],15h
    loc_00409753: mov     edi,dword ptr [ebp-430h]
    loc_00409759: mov     eax,dword ptr [ebp-1FCh]
    loc_0040975F: mov     edx,dword ptr [ebp-578h]
    loc_00409765: mov     esi,dword ptr [ebp-444h]
    loc_0040976B: mov     ecx,dword ptr [ebp-448h]
    loc_00409771: add     eax,edi
    loc_00409773: mov     ebx,dword ptr [ebp-44Ch]
    loc_00409779: lea     edi,[eax+edx-67204A54h]
    loc_00409780: mov     dword ptr [ebp-450h],edi
    loc_00409786: mov     edx,dword ptr [ebp-440h]
    loc_0040978C: not     edi
    loc_0040978E: and     ebx,ecx
    loc_00409790: and     edi,esi
    loc_00409792: mov     esi,dword ptr [ebp-438h]
    loc_00409798: xor     edi,ebx
    loc_0040979A: mov     ecx,dword ptr [ebp-43Ch]
    loc_004097A0: xor     edi,edx
    loc_004097A2: rol     dword ptr [ebp-434h],15h
    loc_004097A9: xor     edi,esi
    loc_004097AB: mov     eax,dword ptr [ebp-448h]
    loc_004097B1: mov     edx,dword ptr [ebp-444h]
    loc_004097B7: and     edi,ecx
    loc_004097B9: mov     ebx,dword ptr [ebp-44Ch]
    loc_004097BF: mov     dword ptr [ebp-20Ch],edi
    loc_004097C5: mov     esi,dword ptr [ebp-448h]
    loc_004097CB: xor     edx,eax
    loc_004097CD: and     edx,ebx
    loc_004097CF: mov     edi,dword ptr [ebp-450h]
    loc_004097D5: mov     ecx,dword ptr [ebp-438h]
    loc_004097DB: xor     dword ptr [ebp-20Ch],edx
    loc_004097E1: and     edi,esi
    loc_004097E3: mov     eax,dword ptr [ebp-434h]
    loc_004097E9: mov     edx,dword ptr [ebp-524h]
    loc_004097EF: mov     esi,dword ptr [ebp-448h]
    loc_004097F5: xor     dword ptr [ebp-20Ch],edi
    loc_004097FB: xor     dword ptr [ebp-20Ch],ecx
    loc_00409801: rol     dword ptr [ebp-20Ch],19h
    loc_00409808: mov     ebx,dword ptr [ebp-20Ch]
    loc_0040980E: add     ebx,eax
    loc_00409810: lea     edi,[ebx+edx+2FFD72DBh]
    loc_00409817: mov     dword ptr [ebp-454h],edi
    loc_0040981D: not     edi
    loc_0040981F: and     edi,esi
    loc_00409821: mov     dword ptr [ebp-21Ch],edi
    loc_00409827: mov     ecx,dword ptr [ebp-44Ch]
    loc_0040982D: mov     eax,dword ptr [ebp-450h]
    loc_00409833: rol     dword ptr [ebp-438h],15h
    loc_0040983A: mov     ebx,dword ptr [ebp-444h]
    loc_00409840: and     eax,ecx
    loc_00409842: xor     dword ptr [ebp-21Ch],eax
    loc_00409848: mov     edx,dword ptr [ebp-43Ch]
    loc_0040984E: mov     edi,dword ptr [ebp-44Ch]
    loc_00409854: xor     dword ptr [ebp-21Ch],ebx
    loc_0040985A: mov     eax,dword ptr [ebp-448h]
    loc_00409860: mov     esi,dword ptr [ebp-440h]
    loc_00409866: xor     dword ptr [ebp-21Ch],edx
    loc_0040986C: mov     ecx,dword ptr [ebp-450h]
    loc_00409872: xor     eax,edi
    loc_00409874: mov     ebx,dword ptr [ebp-44Ch]
    loc_0040987A: mov     edx,dword ptr [ebp-454h]
    loc_00409880: and     eax,ecx
    loc_00409882: and     dword ptr [ebp-21Ch],esi
    loc_00409888: and     edx,ebx
    loc_0040988A: mov     esi,dword ptr [ebp-43Ch]
    loc_00409890: mov     edi,dword ptr [ebp-438h]
    loc_00409896: mov     ecx,dword ptr [ebp-548h]
    loc_0040989C: mov     ebx,dword ptr [ebp-450h]
    loc_004098A2: xor     dword ptr [ebp-21Ch],eax
    loc_004098A8: xor     dword ptr [ebp-21Ch],edx
    loc_004098AE: mov     edx,dword ptr [ebp-44Ch]
    loc_004098B4: xor     dword ptr [ebp-21Ch],esi
    loc_004098BA: mov     esi,dword ptr [ebp-454h]
    loc_004098C0: rol     dword ptr [ebp-21Ch],19h
    loc_004098C7: and     esi,ebx
    loc_004098C9: mov     ebx,dword ptr [ebp-444h]
    loc_004098CF: mov     eax,dword ptr [ebp-21Ch]
    loc_004098D5: add     eax,edi
    loc_004098D7: lea     edi,[eax+ecx-2FE52049h]
    loc_004098DE: mov     dword ptr [ebp-458h],edi
    loc_004098E4: mov     ecx,dword ptr [ebp-448h]
    loc_004098EA: not     edi
    loc_004098EC: and     edi,edx
    loc_004098EE: mov     edx,dword ptr [ebp-440h]
    loc_004098F4: xor     edi,esi
    loc_004098F6: xor     edi,ecx
    loc_004098F8: xor     edi,edx
    loc_004098FA: and     edi,ebx
    loc_004098FC: mov     dword ptr [ebp-22Ch],edi
    loc_00409902: mov     eax,dword ptr [ebp-450h]
    loc_00409908: mov     ecx,dword ptr [ebp-44Ch]
    loc_0040990E: mov     esi,dword ptr [ebp-454h]
    loc_00409914: mov     edx,dword ptr [ebp-450h]
    loc_0040991A: xor     ecx,eax
    loc_0040991C: rol     dword ptr [ebp-43Ch],15h
    loc_00409923: and     ecx,esi
    loc_00409925: mov     ebx,dword ptr [ebp-458h]
    loc_0040992B: xor     dword ptr [ebp-22Ch],ecx
    loc_00409931: mov     edi,dword ptr [ebp-440h]
    loc_00409937: and     ebx,edx
    loc_00409939: xor     dword ptr [ebp-22Ch],ebx
    loc_0040993F: mov     eax,dword ptr [ebp-43Ch]
    loc_00409945: mov     esi,dword ptr [ebp-530h]
    loc_0040994B: xor     dword ptr [ebp-22Ch],edi
    loc_00409951: mov     edx,dword ptr [ebp-450h]
    loc_00409957: mov     edi,dword ptr [ebp-454h]
    loc_0040995D: rol     dword ptr [ebp-22Ch],19h
    loc_00409964: mov     ecx,dword ptr [ebp-22Ch]
    loc_0040996A: add     ecx,eax
    loc_0040996C: lea     ebx,[ecx+esi-471E5013h]
    loc_00409973: mov     eax,dword ptr [ebp-458h]
    loc_00409979: mov     ecx,dword ptr [ebp-44Ch]
    loc_0040997F: mov     dword ptr [ebp-45Ch],ebx
    loc_00409985: not     ebx
    loc_00409987: and     ebx,edx
    loc_00409989: mov     dword ptr [ebp-23Ch],ebx
    loc_0040998F: and     eax,edi
    loc_00409991: mov     esi,dword ptr [ebp-444h]
    loc_00409997: xor     dword ptr [ebp-23Ch],eax
    loc_0040999D: mov     edx,dword ptr [ebp-448h]
    loc_004099A3: xor     dword ptr [ebp-23Ch],ecx
    loc_004099A9: xor     dword ptr [ebp-23Ch],esi
    loc_004099AF: and     dword ptr [ebp-23Ch],edx
    loc_004099B5: mov     ebx,dword ptr [ebp-454h]
    loc_004099BB: mov     eax,dword ptr [ebp-450h]
    loc_004099C1: rol     dword ptr [ebp-440h],15h
    loc_004099C8: mov     edi,dword ptr [ebp-458h]
    loc_004099CE: xor     eax,ebx
    loc_004099D0: mov     ecx,dword ptr [ebp-454h]
    loc_004099D6: and     eax,edi
    loc_004099D8: mov     esi,dword ptr [ebp-45Ch]
    loc_004099DE: xor     dword ptr [ebp-23Ch],eax
    loc_004099E4: mov     edx,dword ptr [ebp-444h]
    loc_004099EA: and     esi,ecx
    loc_004099EC: xor     dword ptr [ebp-23Ch],esi
    loc_004099F2: mov     ebx,dword ptr [ebp-440h]
    loc_004099F8: mov     edi,dword ptr [ebp-540h]
    loc_004099FE: xor     dword ptr [ebp-23Ch],edx
    loc_00409A04: mov     ecx,dword ptr [ebp-454h]
    loc_00409A0A: mov     esi,dword ptr [ebp-458h]
    loc_00409A10: rol     dword ptr [ebp-23Ch],19h
    loc_00409A17: mov     edx,dword ptr [ebp-45Ch]
    loc_00409A1D: mov     eax,dword ptr [ebp-23Ch]
    loc_00409A23: and     edx,esi
    loc_00409A25: mov     esi,dword ptr [ebp-44Ch]
    loc_00409A2B: add     eax,ebx
    loc_00409A2D: lea     ebx,[eax+edi+6A267E96h]
    loc_00409A34: mov     edi,dword ptr [ebp-450h]
    loc_00409A3A: mov     dword ptr [ebp-460h],ebx
    loc_00409A40: not     ebx
    loc_00409A42: mov     eax,dword ptr [ebp-458h]
    loc_00409A48: and     ebx,ecx
    loc_00409A4A: mov     ecx,dword ptr [ebp-448h]
    loc_00409A50: xor     ebx,edx
    loc_00409A52: xor     ebx,edi
    loc_00409A54: mov     edi,dword ptr [ebp-454h]
    loc_00409A5A: mov     edx,dword ptr [ebp-45Ch]
    loc_00409A60: xor     ebx,ecx
    loc_00409A62: and     ebx,esi
    loc_00409A64: mov     ecx,dword ptr [ebp-458h]
    loc_00409A6A: mov     dword ptr [ebp-24Ch],ebx
    loc_00409A70: mov     esi,dword ptr [ebp-460h]
    loc_00409A76: xor     edi,eax
    loc_00409A78: and     edi,edx
    loc_00409A7A: xor     dword ptr [ebp-24Ch],edi
    loc_00409A80: and     esi,ecx
    loc_00409A82: xor     dword ptr [ebp-24Ch],esi
    loc_00409A88: mov     ebx,dword ptr [ebp-448h]
    loc_00409A8E: mov     edx,dword ptr [ebp-598h]
    loc_00409A94: xor     dword ptr [ebp-24Ch],ebx
    loc_00409A9A: mov     ecx,dword ptr [ebp-458h]
    loc_00409AA0: mov     ebx,dword ptr [ebp-45Ch]
    loc_00409AA6: rol     dword ptr [ebp-24Ch],19h
    loc_00409AAD: rol     dword ptr [ebp-444h],15h
    loc_00409AB4: mov     edi,dword ptr [ebp-24Ch]
    loc_00409ABA: mov     eax,dword ptr [ebp-444h]
    loc_00409AC0: add     edi,eax
    loc_00409AC2: lea     esi,[edi+edx-45836FBBh]
    loc_00409AC9: mov     eax,dword ptr [ebp-460h]
    loc_00409ACF: mov     dword ptr [ebp-464h],esi
    loc_00409AD5: not     esi
    loc_00409AD7: mov     edi,dword ptr [ebp-454h]
    loc_00409ADD: and     esi,ecx
    loc_00409ADF: mov     edx,dword ptr [ebp-44Ch]
    loc_00409AE5: and     eax,ebx
    loc_00409AE7: mov     dword ptr [ebp-25Ch],esi
    loc_00409AED: mov     esi,dword ptr [ebp-45Ch]
    loc_00409AF3: mov     ecx,dword ptr [ebp-450h]
    loc_00409AF9: xor     dword ptr [ebp-25Ch],eax
    loc_00409AFF: mov     eax,dword ptr [ebp-458h]
    loc_00409B05: mov     ebx,dword ptr [ebp-460h]
    loc_00409B0B: xor     dword ptr [ebp-25Ch],edi
    loc_00409B11: mov     edi,dword ptr [ebp-45Ch]
    loc_00409B17: xor     eax,esi
    loc_00409B19: and     eax,ebx
    loc_00409B1B: xor     dword ptr [ebp-25Ch],edx
    loc_00409B21: mov     edx,dword ptr [ebp-464h]
    loc_00409B27: and     dword ptr [ebp-25Ch],ecx
    loc_00409B2D: and     edx,edi
    loc_00409B2F: xor     dword ptr [ebp-25Ch],eax
    loc_00409B35: xor     dword ptr [ebp-25Ch],edx
    loc_00409B3B: mov     ecx,dword ptr [ebp-44Ch]
    loc_00409B41: mov     ebx,dword ptr [ebp-52Ch]
    loc_00409B47: xor     dword ptr [ebp-25Ch],ecx
    loc_00409B4D: mov     edi,dword ptr [ebp-45Ch]
    loc_00409B53: mov     edx,dword ptr [ebp-460h]
    loc_00409B59: rol     dword ptr [ebp-25Ch],19h
    loc_00409B60: mov     ecx,dword ptr [ebp-464h]
    loc_00409B66: rol     dword ptr [ebp-448h],15h
    loc_00409B6D: mov     eax,dword ptr [ebp-25Ch]
    loc_00409B73: and     ecx,edx
    loc_00409B75: mov     esi,dword ptr [ebp-448h]
    loc_00409B7B: mov     edx,dword ptr [ebp-454h]
    loc_00409B81: add     eax,esi
    loc_00409B83: lea     esi,[eax+ebx-0ED38067h]
    loc_00409B8A: mov     ebx,dword ptr [ebp-458h]
    loc_00409B90: mov     dword ptr [ebp-468h],esi
    loc_00409B96: not     esi
    loc_00409B98: mov     eax,dword ptr [ebp-460h]
    loc_00409B9E: and     esi,edi
    loc_00409BA0: xor     esi,ecx
    loc_00409BA2: mov     edi,dword ptr [ebp-450h]
    loc_00409BA8: xor     esi,ebx
    loc_00409BAA: mov     ebx,dword ptr [ebp-45Ch]
    loc_00409BB0: mov     ecx,dword ptr [ebp-464h]
    loc_00409BB6: xor     esi,edi
    loc_00409BB8: and     esi,edx
    loc_00409BBA: xor     ebx,eax
    loc_00409BBC: mov     dword ptr [ebp-26Ch],esi
    loc_00409BC2: and     ebx,ecx
    loc_00409BC4: mov     edi,dword ptr [ebp-460h]
    loc_00409BCA: xor     dword ptr [ebp-26Ch],ebx
    loc_00409BD0: mov     edx,dword ptr [ebp-468h]
    loc_00409BD6: mov     esi,dword ptr [ebp-450h]
    loc_00409BDC: and     edx,edi
    loc_00409BDE: xor     dword ptr [ebp-26Ch],edx
    loc_00409BE4: xor     dword ptr [ebp-26Ch],esi
    loc_00409BEA: rol     dword ptr [ebp-26Ch],19h
    loc_00409BF1: rol     dword ptr [ebp-44Ch],15h
    loc_00409BF8: mov     eax,dword ptr [ebp-44Ch]
    loc_00409BFE: mov     ebx,dword ptr [ebp-26Ch]
    loc_00409C04: mov     ecx,dword ptr [ebp-574h]
    loc_00409C0A: mov     edx,dword ptr [ebp-460h]
    loc_00409C10: add     ebx,eax
    loc_00409C12: lea     edi,[ebx+ecx+24A19947h]
    loc_00409C19: mov     esi,dword ptr [ebp-464h]
    loc_00409C1F: mov     eax,dword ptr [ebp-468h]
    loc_00409C25: mov     dword ptr [ebp-46Ch],edi
    loc_00409C2B: not     edi
    loc_00409C2D: mov     ecx,dword ptr [ebp-45Ch]
    loc_00409C33: and     edi,edx
    loc_00409C35: mov     ebx,dword ptr [ebp-454h]
    loc_00409C3B: and     eax,esi
    loc_00409C3D: mov     dword ptr [ebp-27Ch],edi
    loc_00409C43: mov     edi,dword ptr [ebp-464h]
    loc_00409C49: mov     edx,dword ptr [ebp-458h]
    loc_00409C4F: xor     dword ptr [ebp-27Ch],eax
    loc_00409C55: mov     eax,dword ptr [ebp-460h]
    loc_00409C5B: mov     esi,dword ptr [ebp-468h]
    loc_00409C61: xor     dword ptr [ebp-27Ch],ecx
    loc_00409C67: xor     eax,edi
    loc_00409C69: mov     ecx,dword ptr [ebp-464h]
    loc_00409C6F: and     eax,esi
    loc_00409C71: xor     dword ptr [ebp-27Ch],ebx
    loc_00409C77: mov     ebx,dword ptr [ebp-46Ch]
    loc_00409C7D: and     dword ptr [ebp-27Ch],edx
    loc_00409C83: and     ebx,ecx
    loc_00409C85: mov     edx,dword ptr [ebp-454h]
    loc_00409C8B: xor     dword ptr [ebp-27Ch],eax
    loc_00409C91: xor     dword ptr [ebp-27Ch],ebx
    loc_00409C97: xor     dword ptr [ebp-27Ch],edx
    loc_00409C9D: rol     dword ptr [ebp-27Ch],19h
    loc_00409CA4: rol     dword ptr [ebp-450h],15h
    loc_00409CAB: mov     edi,dword ptr [ebp-450h]
    loc_00409CB1: mov     eax,dword ptr [ebp-27Ch]
    loc_00409CB7: rol     dword ptr [ebp-454h],15h
    loc_00409CBE: mov     esi,dword ptr [ebp-544h]
    loc_00409CC4: mov     ecx,dword ptr [ebp-464h]
    loc_00409CCA: mov     ebx,dword ptr [ebp-468h]
    loc_00409CD0: add     eax,edi
    loc_00409CD2: mov     edx,dword ptr [ebp-46Ch]
    loc_00409CD8: lea     edi,[eax+esi-4C6E9309h]
    loc_00409CDF: mov     esi,dword ptr [ebp-460h]
    loc_00409CE5: mov     dword ptr [ebp-470h],edi
    loc_00409CEB: not     edi
    loc_00409CED: and     edx,ebx
    loc_00409CEF: and     edi,ecx
    loc_00409CF1: mov     ecx,dword ptr [ebp-458h]
    loc_00409CF7: xor     edi,edx
    loc_00409CF9: mov     ebx,dword ptr [ebp-45Ch]
    loc_00409CFF: xor     edi,esi
    loc_00409D01: mov     edx,dword ptr [ebp-468h]
    loc_00409D07: mov     esi,dword ptr [ebp-464h]
    loc_00409D0D: xor     edi,ecx
    loc_00409D0F: mov     eax,dword ptr [ebp-46Ch]
    loc_00409D15: and     edi,ebx
    loc_00409D17: mov     ecx,dword ptr [ebp-468h]
    loc_00409D1D: xor     esi,edx
    loc_00409D1F: mov     dword ptr [ebp-28Ch],edi
    loc_00409D25: and     esi,eax
    loc_00409D27: mov     ebx,dword ptr [ebp-470h]
    loc_00409D2D: xor     dword ptr [ebp-28Ch],esi
    loc_00409D33: mov     edi,dword ptr [ebp-458h]
    loc_00409D39: and     ebx,ecx
    loc_00409D3B: xor     dword ptr [ebp-28Ch],ebx
    loc_00409D41: mov     edx,dword ptr [ebp-454h]
    loc_00409D47: mov     eax,dword ptr [ebp-564h]
    loc_00409D4D: xor     dword ptr [ebp-28Ch],edi
    loc_00409D53: mov     ecx,dword ptr [ebp-468h]
    loc_00409D59: mov     edi,dword ptr [ebp-46Ch]
    loc_00409D5F: rol     dword ptr [ebp-28Ch],19h
    loc_00409D66: mov     esi,dword ptr [ebp-28Ch]
    loc_00409D6C: add     esi,edx
    loc_00409D6E: lea     ebx,[esi+eax+801F2E2h]
    loc_00409D75: mov     edx,dword ptr [ebp-470h]
    loc_00409D7B: mov     esi,ebx
    loc_00409D7D: mov     dword ptr [ebp-474h],ebx
    loc_00409D83: mov     eax,dword ptr [ebp-464h]
    loc_00409D89: not     esi
    loc_00409D8B: and     esi,ecx
    loc_00409D8D: mov     ebx,dword ptr [ebp-45Ch]
    loc_00409D93: and     edx,edi
    loc_00409D95: mov     ecx,dword ptr [ebp-460h]
    loc_00409D9B: xor     esi,edx
    loc_00409D9D: mov     edi,dword ptr [ebp-46Ch]
    loc_00409DA3: xor     esi,eax
    loc_00409DA5: mov     eax,dword ptr [ebp-468h]
    loc_00409DAB: mov     edx,dword ptr [ebp-470h]
    loc_00409DB1: xor     esi,ebx
    loc_00409DB3: and     esi,ecx
    loc_00409DB5: mov     ebx,dword ptr [ebp-46Ch]
    loc_00409DBB: mov     ecx,dword ptr [ebp-474h]
    loc_00409DC1: xor     eax,edi
    loc_00409DC3: and     eax,edx
    loc_00409DC5: mov     edi,dword ptr [ebp-45Ch]
    loc_00409DCB: xor     esi,eax
    loc_00409DCD: and     ecx,ebx
    loc_00409DCF: rol     dword ptr [ebp-458h],15h
    loc_00409DD6: xor     esi,ecx
    loc_00409DD8: mov     edx,dword ptr [ebp-458h]
    loc_00409DDE: rol     dword ptr [ebp-45Ch],15h
    loc_00409DE5: xor     esi,edi
    loc_00409DE7: rol     esi,19h
    loc_00409DEA: lea     eax,[esi+edx]
    loc_00409DED: mov     esi,dword ptr [ebp-580h]
    loc_00409DF3: mov     ebx,dword ptr [ebp-46Ch]
    loc_00409DF9: mov     ecx,dword ptr [ebp-470h]
    loc_00409DFF: lea     eax,[eax+esi-7A7103EAh]
    loc_00409E06: mov     edi,dword ptr [ebp-474h]
    loc_00409E0C: mov     dword ptr [ebp-478h],eax
    loc_00409E12: mov     esi,eax
    loc_00409E14: mov     edx,dword ptr [ebp-468h]
    loc_00409E1A: not     esi
    loc_00409E1C: and     edi,ecx
    loc_00409E1E: and     esi,ebx
    loc_00409E20: mov     ebx,dword ptr [ebp-460h]
    loc_00409E26: xor     esi,edi
    loc_00409E28: xor     esi,edx
    loc_00409E2A: mov     edi,dword ptr [ebp-464h]
    loc_00409E30: mov     ecx,dword ptr [ebp-470h]
    loc_00409E36: xor     esi,ebx
    loc_00409E38: mov     ebx,dword ptr [ebp-46Ch]
    loc_00409E3E: mov     edx,dword ptr [ebp-474h]
    loc_00409E44: and     esi,edi
    loc_00409E46: mov     edi,dword ptr [ebp-470h]
    loc_00409E4C: xor     ebx,ecx
    loc_00409E4E: and     ebx,edx
    loc_00409E50: xor     esi,ebx
    loc_00409E52: mov     ecx,eax
    loc_00409E54: mov     ebx,dword ptr [ebp-460h]
    loc_00409E5A: and     ecx,edi
    loc_00409E5C: mov     edx,dword ptr [ebp-45Ch]
    loc_00409E62: xor     esi,ecx
    loc_00409E64: xor     esi,ebx
    loc_00409E66: mov     edi,dword ptr [ebp-470h]
    loc_00409E6C: rol     esi,19h
    loc_00409E6F: lea     eax,[esi+edx]
    loc_00409E72: mov     esi,dword ptr [ebp-594h]
    loc_00409E78: mov     ecx,dword ptr [ebp-474h]
    loc_00409E7E: mov     ebx,dword ptr [ebp-478h]
    loc_00409E84: lea     eax,[eax+esi+636920D8h]
    loc_00409E8B: mov     edx,dword ptr [ebp-46Ch]
    loc_00409E91: mov     dword ptr [ebp-47Ch],eax
    loc_00409E97: mov     esi,eax
    loc_00409E99: not     esi
    loc_00409E9B: and     ebx,ecx
    loc_00409E9D: and     esi,edi
    loc_00409E9F: mov     edi,dword ptr [ebp-464h]
    loc_00409EA5: xor     esi,ebx
    loc_00409EA7: mov     ecx,dword ptr [ebp-474h]
    loc_00409EAD: xor     esi,edx
    loc_00409EAF: mov     ebx,dword ptr [ebp-468h]
    loc_00409EB5: xor     esi,edi
    loc_00409EB7: mov     edi,dword ptr [ebp-470h]
    loc_00409EBD: mov     edx,dword ptr [ebp-478h]
    loc_00409EC3: and     esi,ebx
    loc_00409EC5: mov     ebx,dword ptr [ebp-474h]
    loc_00409ECB: rol     dword ptr [ebp-460h],15h
    loc_00409ED2: xor     edi,ecx
    loc_00409ED4: and     edi,edx
    loc_00409ED6: xor     esi,edi
    loc_00409ED8: mov     ecx,eax
    loc_00409EDA: mov     edi,dword ptr [ebp-464h]
    loc_00409EE0: and     ecx,ebx
    loc_00409EE2: mov     edx,dword ptr [ebp-460h]
    loc_00409EE8: xor     esi,ecx
    loc_00409EEA: xor     esi,edi
    loc_00409EEC: rol     esi,19h
    loc_00409EEF: lea     eax,[esi+edx]
    loc_00409EF2: mov     esi,dword ptr [ebp-538h]
    loc_00409EF8: lea     eax,[eax+esi+71574E69h]
    loc_00409EFF: mov     esi,eax
    loc_00409F01: mov     dword ptr [ebp-480h],eax
    loc_00409F07: mov     ebx,dword ptr [ebp-474h]
    loc_00409F0D: mov     ecx,dword ptr [ebp-478h]
    loc_00409F13: rol     dword ptr [ebp-464h],15h
    loc_00409F1A: not     esi
    loc_00409F1C: mov     edi,dword ptr [ebp-47Ch]
    loc_00409F22: mov     edx,dword ptr [ebp-470h]
    loc_00409F28: and     esi,ebx
    loc_00409F2A: mov     ebx,dword ptr [ebp-468h]
    loc_00409F30: and     edi,ecx
    loc_00409F32: xor     esi,edi
    loc_00409F34: mov     ecx,dword ptr [ebp-478h]
    loc_00409F3A: xor     esi,edx
    loc_00409F3C: mov     edi,dword ptr [ebp-46Ch]
    loc_00409F42: xor     esi,ebx
    loc_00409F44: mov     ebx,dword ptr [ebp-474h]
    loc_00409F4A: mov     edx,dword ptr [ebp-47Ch]
    loc_00409F50: and     esi,edi
    loc_00409F52: mov     edi,dword ptr [ebp-478h]
    loc_00409F58: xor     ebx,ecx
    loc_00409F5A: and     ebx,edx
    loc_00409F5C: xor     esi,ebx
    loc_00409F5E: mov     ecx,eax
    loc_00409F60: mov     ebx,dword ptr [ebp-468h]
    loc_00409F66: and     ecx,edi
    loc_00409F68: mov     edx,dword ptr [ebp-464h]
    loc_00409F6E: xor     esi,ecx
    loc_00409F70: xor     esi,ebx
    loc_00409F72: mov     edi,dword ptr [ebp-478h]
    loc_00409F78: rol     esi,19h
    loc_00409F7B: lea     eax,[esi+edx]
    loc_00409F7E: mov     esi,dword ptr [ebp-56Ch]
    loc_00409F84: mov     ecx,dword ptr [ebp-47Ch]
    loc_00409F8A: mov     ebx,dword ptr [ebp-480h]
    loc_00409F90: lea     eax,[eax+esi-5BA7015Dh]
    loc_00409F97: mov     edx,dword ptr [ebp-474h]
    loc_00409F9D: mov     dword ptr [ebp-484h],eax
    loc_00409FA3: mov     esi,eax
    loc_00409FA5: not     esi
    loc_00409FA7: and     ebx,ecx
    loc_00409FA9: and     esi,edi
    loc_00409FAB: mov     edi,dword ptr [ebp-46Ch]
    loc_00409FB1: xor     esi,ebx
    loc_00409FB3: mov     ebx,dword ptr [ebp-470h]
    loc_00409FB9: xor     esi,edx
    loc_00409FBB: mov     ecx,dword ptr [ebp-47Ch]
    loc_00409FC1: xor     esi,edi
    loc_00409FC3: mov     edi,dword ptr [ebp-478h]
    loc_00409FC9: mov     edx,dword ptr [ebp-480h]
    loc_00409FCF: and     esi,ebx
    loc_00409FD1: mov     ebx,dword ptr [ebp-47Ch]
    loc_00409FD7: xor     edi,ecx
    loc_00409FD9: and     edi,edx
    loc_00409FDB: mov     ecx,eax
    loc_00409FDD: and     ecx,ebx
    loc_00409FDF: xor     esi,edi
    loc_00409FE1: xor     esi,ecx
    loc_00409FE3: rol     dword ptr [ebp-468h],15h
    loc_00409FEA: mov     edi,dword ptr [ebp-46Ch]
    loc_00409FF0: mov     ebx,dword ptr [ebp-47Ch]
    loc_00409FF6: mov     edx,dword ptr [ebp-468h]
    loc_00409FFC: xor     esi,edi
    loc_00409FFE: mov     ecx,dword ptr [ebp-480h]
    loc_0040A004: rol     esi,19h
    loc_0040A007: mov     edi,dword ptr [ebp-484h]
    loc_0040A00D: lea     eax,[esi+edx]
    loc_0040A010: mov     esi,dword ptr [ebp-550h]
    loc_0040A016: mov     edx,dword ptr [ebp-478h]
    loc_0040A01C: and     edi,ecx
    loc_0040A01E: mov     ecx,dword ptr [ebp-474h]
    loc_0040A024: lea     eax,[eax+esi-0B6CC282h]
    loc_0040A02B: mov     esi,eax
    loc_0040A02D: mov     dword ptr [ebp-488h],eax
    loc_0040A033: not     esi
    loc_0040A035: and     esi,ebx
    loc_0040A037: mov     ebx,dword ptr [ebp-470h]
    loc_0040A03D: xor     esi,edi
    loc_0040A03F: xor     esi,edx
    loc_0040A041: mov     edi,dword ptr [ebp-480h]
    loc_0040A047: xor     esi,ebx
    loc_0040A049: mov     ebx,dword ptr [ebp-47Ch]
    loc_0040A04F: mov     edx,dword ptr [ebp-484h]
    loc_0040A055: and     esi,ecx
    loc_0040A057: mov     ecx,eax
    loc_0040A059: mov     eax,dword ptr [ebp-480h]
    loc_0040A05F: xor     ebx,edi
    loc_0040A061: and     ebx,edx
    loc_0040A063: mov     edi,dword ptr [ebp-470h]
    loc_0040A069: xor     esi,ebx
    loc_0040A06B: and     ecx,eax
    loc_0040A06D: rol     dword ptr [ebp-46Ch],15h
    loc_0040A074: xor     esi,ecx
    loc_0040A076: mov     ebx,dword ptr [ebp-46Ch]
    loc_0040A07C: rol     dword ptr [ebp-470h],15h
    loc_0040A083: xor     esi,edi
    loc_0040A085: mov     edx,dword ptr [ebp-55Ch]
    loc_0040A08B: rol     esi,19h
    loc_0040A08E: mov     ecx,dword ptr [ebp-484h]
    loc_0040A094: lea     eax,[esi+ebx]
    loc_0040A097: lea     eax,[eax+edx+0D95748Fh]
    loc_0040A09E: mov     esi,dword ptr [ebp-480h]
    loc_0040A0A4: mov     edi,dword ptr [ebp-488h]
    loc_0040A0AA: mov     dword ptr [ebp-48Ch],eax
    loc_0040A0B0: mov     edx,eax
    loc_0040A0B2: mov     ebx,dword ptr [ebp-47Ch]
    loc_0040A0B8: not     edx
    loc_0040A0BA: and     edi,ecx
    loc_0040A0BC: and     edx,esi
    loc_0040A0BE: mov     esi,dword ptr [ebp-474h]
    loc_0040A0C4: xor     edx,edi
    loc_0040A0C6: mov     ecx,dword ptr [ebp-478h]
    loc_0040A0CC: xor     edx,ebx
    loc_0040A0CE: mov     edi,dword ptr [ebp-484h]
    loc_0040A0D4: xor     edx,esi
    loc_0040A0D6: mov     esi,dword ptr [ebp-480h]
    loc_0040A0DC: and     edx,ecx
    loc_0040A0DE: mov     ebx,dword ptr [ebp-488h]
    loc_0040A0E4: mov     ecx,dword ptr [ebp-484h]
    loc_0040A0EA: xor     esi,edi
    loc_0040A0EC: and     esi,ebx
    loc_0040A0EE: mov     edi,eax
    loc_0040A0F0: mov     ebx,dword ptr [ebp-474h]
    loc_0040A0F6: xor     edx,esi
    loc_0040A0F8: and     edi,ecx
    loc_0040A0FA: mov     esi,dword ptr [ebp-470h]
    loc_0040A100: xor     edx,edi
    loc_0040A102: xor     edx,ebx
    loc_0040A104: mov     ecx,dword ptr [ebp-484h]
    loc_0040A10A: rol     edx,19h
    loc_0040A10D: lea     eax,[edx+esi]
    loc_0040A110: mov     edx,dword ptr [ebp-554h]
    loc_0040A116: mov     edi,dword ptr [ebp-488h]
    loc_0040A11C: mov     ebx,dword ptr [ebp-48Ch]
    loc_0040A122: lea     eax,[eax+edx+728EB658h]
    loc_0040A129: mov     esi,dword ptr [ebp-480h]
    loc_0040A12F: mov     dword ptr [ebp-490h],eax
    loc_0040A135: mov     edx,eax
    loc_0040A137: not     edx
    loc_0040A139: and     edx,ecx
    loc_0040A13B: and     ebx,edi
    loc_0040A13D: mov     ecx,dword ptr [ebp-478h]
    loc_0040A143: rol     dword ptr [ebp-474h],15h
    loc_0040A14A: xor     edx,ebx
    loc_0040A14C: xor     edx,esi
    loc_0040A14E: mov     edi,dword ptr [ebp-47Ch]
    loc_0040A154: xor     edx,ecx
    loc_0040A156: mov     ebx,dword ptr [ebp-488h]
    loc_0040A15C: mov     ecx,dword ptr [ebp-484h]
    loc_0040A162: mov     esi,dword ptr [ebp-48Ch]
    loc_0040A168: and     edx,edi
    loc_0040A16A: mov     edi,dword ptr [ebp-488h]
    loc_0040A170: xor     ecx,ebx
    loc_0040A172: and     ecx,esi
    loc_0040A174: xor     edx,ecx
    loc_0040A176: mov     ebx,eax
    loc_0040A178: mov     ecx,dword ptr [ebp-478h]
    loc_0040A17E: and     ebx,edi
    loc_0040A180: mov     esi,dword ptr [ebp-474h]
    loc_0040A186: xor     edx,ebx
    loc_0040A188: xor     edx,ecx
    loc_0040A18A: rol     edx,19h
    loc_0040A18D: lea     eax,[edx+esi]
    loc_0040A190: mov     edx,dword ptr [ebp-528h]
    loc_0040A196: lea     eax,[eax+edx+718BCD58h]
    loc_0040A19D: mov     edx,eax
    loc_0040A19F: mov     dword ptr [ebp-494h],eax
    loc_0040A1A5: mov     edi,dword ptr [ebp-488h]
    loc_0040A1AB: mov     ebx,dword ptr [ebp-48Ch]
    loc_0040A1B1: rol     dword ptr [ebp-478h],15h
    loc_0040A1B8: not     edx
    loc_0040A1BA: mov     ecx,dword ptr [ebp-490h]
    loc_0040A1C0: mov     esi,dword ptr [ebp-484h]
    loc_0040A1C6: and     edx,edi
    loc_0040A1C8: mov     edi,dword ptr [ebp-47Ch]
    loc_0040A1CE: and     ecx,ebx
    loc_0040A1D0: xor     edx,ecx
    loc_0040A1D2: mov     ebx,dword ptr [ebp-480h]
    loc_0040A1D8: mov     dword ptr [ebp-2A8h],ecx
    loc_0040A1DE: xor     edx,esi
    loc_0040A1E0: mov     ecx,dword ptr [ebp-48Ch]
    loc_0040A1E6: xor     edx,edi
    loc_0040A1E8: mov     edi,dword ptr [ebp-488h]
    loc_0040A1EE: mov     esi,dword ptr [ebp-490h]
    loc_0040A1F4: and     edx,ebx
    loc_0040A1F6: mov     ebx,dword ptr [ebp-48Ch]
    loc_0040A1FC: xor     edi,ecx
    loc_0040A1FE: and     edi,esi
    loc_0040A200: mov     ecx,eax
    loc_0040A202: mov     esi,dword ptr [ebp-47Ch]
    loc_0040A208: and     ecx,ebx
    loc_0040A20A: xor     edx,edi
    loc_0040A20C: xor     edx,ecx
    loc_0040A20E: mov     edi,dword ptr [ebp-478h]
    loc_0040A214: xor     edx,esi
    loc_0040A216: rol     edx,19h
    loc_0040A219: mov     ecx,dword ptr [ebp-48Ch]
    loc_0040A21F: lea     eax,[edx+edi]
    loc_0040A222: mov     edx,dword ptr [ebp-584h]
    loc_0040A228: mov     esi,dword ptr [ebp-490h]
    loc_0040A22E: mov     edi,dword ptr [ebp-494h]
    loc_0040A234: lea     ebx,[eax+edx-7DEAB512h]
    loc_0040A23B: mov     dword ptr [ebp-498h],ebx
    loc_0040A241: mov     edx,ebx
    loc_0040A243: mov     eax,dword ptr [ebp-488h]
    loc_0040A249: not     edx
    loc_0040A24B: and     edi,esi
    loc_0040A24D: mov     ebx,dword ptr [ebp-480h]
    loc_0040A253: mov     dword ptr [ebp-2ACh],edi
    loc_0040A259: and     edx,ecx
    loc_0040A25B: mov     ecx,dword ptr [ebp-484h]
    loc_0040A261: xor     edx,edi
    loc_0040A263: mov     esi,dword ptr [ebp-490h]
    loc_0040A269: xor     edx,eax
    loc_0040A26B: mov     eax,dword ptr [ebp-48Ch]
    loc_0040A271: xor     edx,ebx
    loc_0040A273: mov     edi,dword ptr [ebp-494h]
    loc_0040A279: mov     ebx,dword ptr [ebp-490h]
    loc_0040A27F: and     edx,ecx
    loc_0040A281: mov     ecx,dword ptr [ebp-498h]
    loc_0040A287: xor     eax,esi
    loc_0040A289: and     eax,edi
    loc_0040A28B: rol     dword ptr [ebp-47Ch],15h
    loc_0040A292: mov     esi,dword ptr [ebp-480h]
    loc_0040A298: and     ecx,ebx
    loc_0040A29A: xor     edx,eax
    loc_0040A29C: mov     edi,dword ptr [ebp-47Ch]
    loc_0040A2A2: xor     edx,ecx
    loc_0040A2A4: xor     edx,esi
    loc_0040A2A6: rol     edx,19h
    loc_0040A2A9: lea     eax,[edx+edi]
    loc_0040A2AC: mov     edx,dword ptr [ebp-59Ch]
    loc_0040A2B2: lea     ebx,[eax+edx+7B54A41Dh]
    loc_0040A2B9: mov     dword ptr [ebp-49Ch],ebx
    loc_0040A2BF: mov     ecx,dword ptr [ebp-490h]
    loc_0040A2C5: not     ebx
    loc_0040A2C7: rol     dword ptr [ebp-480h],15h
    loc_0040A2CE: mov     esi,dword ptr [ebp-494h]
    loc_0040A2D4: mov     edi,dword ptr [ebp-498h]
    loc_0040A2DA: and     ebx,ecx
    loc_0040A2DC: mov     eax,dword ptr [ebp-48Ch]
    loc_0040A2E2: mov     ecx,dword ptr [ebp-494h]
    loc_0040A2E8: mov     dword ptr [ebp-2B8h],ebx
    loc_0040A2EE: and     edi,esi
    loc_0040A2F0: mov     ebx,dword ptr [ebp-484h]
    loc_0040A2F6: xor     dword ptr [ebp-2B8h],edi
    loc_0040A2FC: mov     edx,dword ptr [ebp-488h]
    loc_0040A302: mov     dword ptr [ebp-2BCh],edi
    loc_0040A308: mov     edi,dword ptr [ebp-490h]
    loc_0040A30E: mov     esi,dword ptr [ebp-498h]
    loc_0040A314: xor     dword ptr [ebp-2B8h],eax
    loc_0040A31A: xor     edi,ecx
    loc_0040A31C: mov     eax,dword ptr [ebp-494h]
    loc_0040A322: and     edi,esi
    loc_0040A324: mov     ecx,dword ptr [ebp-480h]
    loc_0040A32A: mov     esi,dword ptr [ebp-58Ch]
    loc_0040A330: xor     dword ptr [ebp-2B8h],ebx
    loc_0040A336: mov     ebx,dword ptr [ebp-49Ch]
    loc_0040A33C: and     dword ptr [ebp-2B8h],edx
    loc_0040A342: and     ebx,eax
    loc_0040A344: mov     edx,dword ptr [ebp-484h]
    loc_0040A34A: xor     dword ptr [ebp-2B8h],edi
    loc_0040A350: xor     dword ptr [ebp-2B8h],ebx
    loc_0040A356: xor     dword ptr [ebp-2B8h],edx
    loc_0040A35C: rol     dword ptr [ebp-2B8h],19h
    loc_0040A363: mov     edi,dword ptr [ebp-2B8h]
    loc_0040A369: add     edi,ecx
    loc_0040A36B: lea     eax,[edi+esi-3DA5A64Bh]
    loc_0040A372: mov     dword ptr [ebp-4A0h],eax
    loc_0040A378: mov     ebx,dword ptr [ebp-488h]
    loc_0040A37E: mov     edx,dword ptr [ebp-4A0h]
    loc_0040A384: xor     dword ptr [ebp-2A8h],ebx
    loc_0040A38A: mov     ecx,dword ptr [ebp-494h]
    loc_0040A390: mov     esi,dword ptr [ebp-498h]
    loc_0040A396: xor     dword ptr [ebp-2A8h],edx
    loc_0040A39C: mov     edi,dword ptr [ebp-48Ch]
    loc_0040A3A2: mov     eax,dword ptr [ebp-49Ch]
    loc_0040A3A8: and     dword ptr [ebp-2A8h],ecx
    loc_0040A3AE: and     edi,esi
    loc_0040A3B0: mov     ebx,dword ptr [ebp-490h]
    loc_0040A3B6: rol     dword ptr [ebp-484h],15h
    loc_0040A3BD: mov     edx,dword ptr [ebp-4A0h]
    loc_0040A3C3: and     ebx,eax
    loc_0040A3C5: xor     dword ptr [ebp-2A8h],edi
    loc_0040A3CB: mov     ecx,dword ptr [ebp-484h]
    loc_0040A3D1: mov     dword ptr [ebp-2CCh],ebx
    loc_0040A3D7: mov     edi,dword ptr [ebp-56Ch]
    loc_0040A3DD: mov     eax,dword ptr [ebp-48Ch]
    loc_0040A3E3: xor     dword ptr [ebp-2A8h],ebx
    loc_0040A3E9: xor     dword ptr [ebp-2A8h],edx
    loc_0040A3EF: mov     edx,dword ptr [ebp-498h]
    loc_0040A3F5: rol     dword ptr [ebp-2A8h],19h
    loc_0040A3FC: mov     esi,dword ptr [ebp-2A8h]
    loc_0040A402: add     esi,ecx
    loc_0040A404: xor     dword ptr [ebp-2ACh],eax
    loc_0040A40A: lea     ebx,[esi+edi-63CF2AC7h]
    loc_0040A411: mov     dword ptr [ebp-4A4h],ebx
    loc_0040A417: xor     dword ptr [ebp-2ACh],ebx
    loc_0040A41D: and     dword ptr [ebp-2ACh],edx
    loc_0040A423: mov     ecx,dword ptr [ebp-2CCh]
    loc_0040A429: mov     esi,dword ptr [ebp-4A0h]
    loc_0040A42F: xor     dword ptr [ebp-2ACh],ecx
    loc_0040A435: mov     edi,dword ptr [ebp-494h]
    loc_0040A43B: mov     ebx,dword ptr [ebp-4A4h]
    loc_0040A441: rol     dword ptr [ebp-488h],15h
    loc_0040A448: and     edi,esi
    loc_0040A44A: mov     ecx,dword ptr [ebp-544h]
    loc_0040A450: xor     dword ptr [ebp-2ACh],edi
    loc_0040A456: mov     eax,dword ptr [ebp-488h]
    loc_0040A45C: mov     dword ptr [ebp-2D4h],edi
    loc_0040A462: mov     esi,dword ptr [ebp-490h]
    loc_0040A468: xor     dword ptr [ebp-2ACh],ebx
    loc_0040A46E: mov     ebx,dword ptr [ebp-49Ch]
    loc_0040A474: xor     dword ptr [ebp-2BCh],esi
    loc_0040A47A: rol     dword ptr [ebp-2ACh],19h
    loc_0040A481: mov     edx,dword ptr [ebp-2ACh]
    loc_0040A487: add     edx,eax
    loc_0040A489: lea     edi,[edx+ecx+2AF26013h]
    loc_0040A490: mov     eax,dword ptr [ebp-4A4h]
    loc_0040A496: mov     ecx,dword ptr [ebp-498h]
    loc_0040A49C: xor     dword ptr [ebp-2BCh],edi
    loc_0040A4A2: mov     edx,dword ptr [ebp-2D4h]
    loc_0040A4A8: and     ecx,eax
    loc_0040A4AA: and     dword ptr [ebp-2BCh],ebx
    loc_0040A4B0: mov     dword ptr [ebp-4A8h],edi
    loc_0040A4B6: xor     dword ptr [ebp-2BCh],edx
    loc_0040A4BC: mov     dword ptr [ebp-2DCh],ecx
    loc_0040A4C2: mov     esi,dword ptr [ebp-4A8h]
    loc_0040A4C8: mov     ebx,dword ptr [ebp-30h]
    loc_0040A4CB: xor     dword ptr [ebp-2BCh],ecx
    loc_0040A4D1: mov     ecx,dword ptr [ebp-49Ch]
    loc_0040A4D7: mov     edx,dword ptr [ebx+10h]
    loc_0040A4DA: xor     dword ptr [ebp-2BCh],esi
    loc_0040A4E0: mov     esi,dword ptr [ebp-494h]
    loc_0040A4E6: mov     ebx,dword ptr [ebp-4A0h]
    loc_0040A4EC: rol     dword ptr [ebp-2BCh],19h
    loc_0040A4F3: rol     dword ptr [ebp-48Ch],15h
    loc_0040A4FA: rol     dword ptr [ebp-490h],15h
    loc_0040A501: mov     eax,dword ptr [ebp-2BCh]
    loc_0040A507: mov     edi,dword ptr [ebp-48Ch]
    loc_0040A50D: add     eax,edi
    loc_0040A50F: add     eax,edx
    loc_0040A511: sub     eax,3A2E4FDDh
    loc_0040A516: mov     dword ptr [ebp-4ACh],eax
    loc_0040A51C: mov     eax,dword ptr [ebp-498h]
    loc_0040A522: mov     edi,dword ptr [ebp-4ACh]
    loc_0040A528: mov     edx,dword ptr [ebp-2DCh]
    loc_0040A52E: and     eax,ecx
    loc_0040A530: xor     eax,esi
    loc_0040A532: mov     ecx,dword ptr [ebp-4A8h]
    loc_0040A538: xor     eax,edi
    loc_0040A53A: mov     esi,dword ptr [ebp-49Ch]
    loc_0040A540: and     eax,ebx
    loc_0040A542: mov     edi,dword ptr [ebp-4ACh]
    loc_0040A548: xor     eax,edx
    loc_0040A54A: mov     dword ptr [ebp-2E0h],eax
    loc_0040A550: and     esi,ecx
    loc_0040A552: mov     edx,dword ptr [ebp-30h]
    loc_0040A555: xor     dword ptr [ebp-2E0h],esi
    loc_0040A55B: mov     ebx,dword ptr [ebp-490h]
    loc_0040A561: mov     eax,dword ptr [edx+50h]
    loc_0040A564: xor     dword ptr [ebp-2E0h],edi
    loc_0040A56A: mov     dword ptr [ebp-2E4h],esi
    loc_0040A570: rol     dword ptr [ebp-2E0h],19h
    loc_0040A577: mov     edi,dword ptr [ebp-2E0h]
    loc_0040A57D: add     edi,ebx
    loc_0040A57F: add     edi,eax
    loc_0040A581: add     edi,286085F0h
    loc_0040A587: mov     dword ptr [ebp-4B0h],edi
    loc_0040A58D: mov     ecx,dword ptr [ebp-4A0h]
    loc_0040A593: mov     eax,dword ptr [ebp-49Ch]
    loc_0040A599: rol     dword ptr [ebp-494h],15h
    loc_0040A5A0: mov     esi,dword ptr [ebp-498h]
    loc_0040A5A6: mov     ebx,dword ptr [ebp-4A4h]
    loc_0040A5AC: rol     dword ptr [ebp-498h],15h
    loc_0040A5B3: and     eax,ecx
    loc_0040A5B5: mov     edx,dword ptr [ebp-2E4h]
    loc_0040A5BB: mov     ecx,dword ptr [ebp-4ACh]
    loc_0040A5C1: xor     eax,esi
    loc_0040A5C3: mov     esi,dword ptr [ebp-4A0h]
    loc_0040A5C9: xor     eax,edi
    loc_0040A5CB: and     eax,ebx
    loc_0040A5CD: and     esi,ecx
    loc_0040A5CF: mov     dword ptr [ebp-2ECh],esi
    loc_0040A5D5: xor     eax,edx
    loc_0040A5D7: mov     ebx,dword ptr [ebp-494h]
    loc_0040A5DD: xor     eax,esi
    loc_0040A5DF: mov     ecx,dword ptr [ebp-4A4h]
    loc_0040A5E5: xor     eax,edi
    loc_0040A5E7: rol     eax,19h
    loc_0040A5EA: mov     esi,eax
    loc_0040A5EC: mov     eax,dword ptr [ebp-30h]
    loc_0040A5EF: add     esi,ebx
    loc_0040A5F1: mov     ebx,dword ptr [ebp-49Ch]
    loc_0040A5F7: mov     edx,dword ptr [eax+70h]
    loc_0040A5FA: mov     eax,dword ptr [ebp-4A8h]
    loc_0040A600: add     esi,edx
    loc_0040A602: mov     edx,dword ptr [ebp-4A0h]
    loc_0040A608: sub     esi,35BE86E8h
    loc_0040A60E: mov     dword ptr [ebp-4B4h],esi
    loc_0040A614: and     edx,ecx
    loc_0040A616: xor     edx,ebx
    loc_0040A618: mov     ecx,dword ptr [ebp-2ECh]
    loc_0040A61E: xor     edx,esi
    loc_0040A620: mov     ebx,dword ptr [ebp-4A4h]
    loc_0040A626: and     edx,eax
    loc_0040A628: xor     edx,ecx
    loc_0040A62A: mov     eax,dword ptr [ebp-498h]
    loc_0040A630: and     ebx,edi
    loc_0040A632: xor     edx,ebx
    loc_0040A634: xor     edx,esi
    loc_0040A636: mov     dword ptr [ebp-2F4h],ebx
    loc_0040A63C: rol     edx,19h
    loc_0040A63F: mov     ebx,edx
    loc_0040A641: mov     edx,dword ptr [ebp-30h]
    loc_0040A644: add     ebx,eax
    loc_0040A646: mov     eax,dword ptr [ebp-4A8h]
    loc_0040A64C: mov     ecx,dword ptr [edx+44h]
    loc_0040A64F: mov     edx,dword ptr [ebp-4A0h]
    loc_0040A655: add     ebx,ecx
    loc_0040A657: mov     ecx,dword ptr [ebp-4A4h]
    loc_0040A65D: sub     ebx,4724C711h
    loc_0040A663: mov     dword ptr [ebp-4B8h],ebx
    loc_0040A669: and     ecx,eax
    loc_0040A66B: mov     eax,dword ptr [ebp-4ACh]
    loc_0040A671: xor     ecx,edx
    loc_0040A673: xor     ecx,ebx
    loc_0040A675: mov     edx,dword ptr [ebp-2F4h]
    loc_0040A67B: and     ecx,eax
    loc_0040A67D: mov     eax,dword ptr [ebp-4A8h]
    loc_0040A683: xor     ecx,edx
    loc_0040A685: and     eax,esi
    loc_0040A687: xor     ecx,eax
    loc_0040A689: xor     ecx,ebx
    loc_0040A68B: mov     dword ptr [ebp-2FCh],eax
    loc_0040A691: mov     eax,dword ptr [ebp-30h]
    loc_0040A694: rol     ecx,19h
    loc_0040A697: rol     dword ptr [ebp-49Ch],15h
    loc_0040A69E: mov     dword ptr [ebp-2F8h],ecx
    loc_0040A6A4: rol     dword ptr [ebp-4A0h],15h
    loc_0040A6AB: mov     edx,dword ptr [ebp-49Ch]
    loc_0040A6B1: add     ecx,edx
    loc_0040A6B3: mov     edx,dword ptr [eax+20h]
    loc_0040A6B6: mov     eax,dword ptr [ebp-4A4h]
    loc_0040A6BC: rol     dword ptr [ebp-4A4h],15h
    loc_0040A6C3: add     ecx,edx
    loc_0040A6C5: sub     ecx,71862350h
    loc_0040A6CB: mov     dword ptr [ebp-4BCh],ecx
    loc_0040A6D1: mov     edx,dword ptr [ebp-4A8h]
    loc_0040A6D7: mov     ecx,dword ptr [ebp-4ACh]
    loc_0040A6DD: and     edx,ecx
    loc_0040A6DF: mov     ecx,dword ptr [ebp-4BCh]
    loc_0040A6E5: xor     edx,eax
    loc_0040A6E7: mov     eax,dword ptr [ebp-2FCh]
    loc_0040A6ED: xor     edx,ecx
    loc_0040A6EF: mov     ecx,dword ptr [ebp-4ACh]
    loc_0040A6F5: and     edx,edi
    loc_0040A6F7: xor     edx,eax
    loc_0040A6F9: mov     eax,dword ptr [ebp-4BCh]
    loc_0040A6FF: and     ecx,ebx
    loc_0040A701: xor     edx,ecx
    loc_0040A703: xor     edx,eax
    loc_0040A705: mov     dword ptr [ebp-304h],ecx
    loc_0040A70B: mov     eax,dword ptr [ebp-30h]
    loc_0040A70E: rol     edx,19h
    loc_0040A711: mov     dword ptr [ebp-300h],edx
    loc_0040A717: mov     ecx,dword ptr [ebp-4A0h]
    loc_0040A71D: add     edx,ecx
    loc_0040A71F: mov     ecx,dword ptr [eax+58h]
    loc_0040A722: mov     eax,dword ptr [ebp-4A8h]
    loc_0040A728: add     edx,ecx
    loc_0040A72A: add     edx,603A180Eh
    loc_0040A730: mov     dword ptr [ebp-4C0h],edx
    loc_0040A736: mov     edx,dword ptr [ebp-4ACh]
    loc_0040A73C: mov     ecx,dword ptr [ebp-4C0h]
    loc_0040A742: and     edx,edi
    loc_0040A744: xor     edx,eax
    loc_0040A746: mov     eax,dword ptr [ebp-304h]
    loc_0040A74C: xor     edx,ecx
    loc_0040A74E: mov     ecx,dword ptr [ebp-4BCh]
    loc_0040A754: and     edx,esi
    loc_0040A756: xor     edx,eax
    loc_0040A758: mov     eax,edi
    loc_0040A75A: and     eax,ecx
    loc_0040A75C: mov     dword ptr [ebp-30Ch],eax
    loc_0040A762: mov     ecx,dword ptr [ebp-4C0h]
    loc_0040A768: xor     edx,eax
    loc_0040A76A: mov     eax,dword ptr [ebp-4A4h]
    loc_0040A770: xor     edx,ecx
    loc_0040A772: rol     edx,19h
    loc_0040A775: add     edx,eax
    loc_0040A777: mov     eax,dword ptr [ebp-30h]
    loc_0040A77A: mov     eax,dword ptr [eax+74h]
    loc_0040A77D: add     edx,eax
    loc_0040A77F: add     edx,6C9E0E8Bh
    loc_0040A785: mov     eax,edi
    loc_0040A787: mov     dword ptr [ebp-4C4h],edx
    loc_0040A78D: mov     edi,dword ptr [ebp-4ACh]
    loc_0040A793: and     eax,esi
    loc_0040A795: rol     dword ptr [ebp-4A8h],15h
    loc_0040A79C: xor     eax,edi
    loc_0040A79E: xor     eax,edx
    loc_0040A7A0: rol     dword ptr [ebp-4ACh],15h
    loc_0040A7A7: and     eax,ebx
    loc_0040A7A9: mov     edx,dword ptr [ebp-30Ch]
    loc_0040A7AF: mov     edi,dword ptr [ebp-4A8h]
    loc_0040A7B5: xor     eax,edx
    loc_0040A7B7: mov     edx,esi
    loc_0040A7B9: and     edx,ecx
    loc_0040A7BB: mov     ecx,dword ptr [ebp-4C4h]
    loc_0040A7C1: xor     eax,edx
    loc_0040A7C3: xor     eax,ecx
    loc_0040A7C5: mov     ecx,dword ptr [ebp-30h]
    loc_0040A7C8: rol     eax,19h
    loc_0040A7CB: add     eax,edi
    loc_0040A7CD: mov     edi,dword ptr [ecx+38h]
    loc_0040A7D0: mov     ecx,dword ptr [ebp-4C4h]
    loc_0040A7D6: add     eax,edi
    loc_0040A7D8: mov     edi,esi
    loc_0040A7DA: mov     esi,dword ptr [ebp-4B0h]
    loc_0040A7E0: and     edi,ebx
    loc_0040A7E2: sub     eax,4FE175C2h
    loc_0040A7E7: mov     dword ptr [ebp-4C8h],eax
    loc_0040A7ED: xor     edi,esi
    loc_0040A7EF: xor     edi,eax
    loc_0040A7F1: mov     eax,dword ptr [ebp-4BCh]
    loc_0040A7F7: mov     esi,dword ptr [ebp-4C8h]
    loc_0040A7FD: and     edi,eax
    loc_0040A7FF: mov     eax,ebx
    loc_0040A801: xor     edi,edx
    loc_0040A803: and     eax,ecx
    loc_0040A805: mov     edx,dword ptr [ebp-4ACh]
    loc_0040A80B: xor     edi,eax
    loc_0040A80D: mov     ecx,dword ptr [ebp-30h]
    loc_0040A810: xor     edi,esi
    loc_0040A812: rol     edi,19h
    loc_0040A815: add     edi,edx
    loc_0040A817: mov     dword ptr [ebp-320h],edi
    loc_0040A81D: mov     esi,dword ptr [ecx+64h]
    loc_0040A820: mov     edx,dword ptr [ebp-4BCh]
    loc_0040A826: add     dword ptr [ebp-320h],esi
    loc_0040A82C: mov     esi,ebx
    loc_0040A82E: mov     ebx,dword ptr [ebp-4B4h]
    loc_0040A834: mov     edi,dword ptr [ebp-4C0h]
    loc_0040A83A: and     esi,edx
    loc_0040A83C: mov     ecx,dword ptr [ebp-320h]
    loc_0040A842: xor     esi,ebx
    loc_0040A844: mov     edx,dword ptr [ebp-4C8h]
    loc_0040A84A: sub     ecx,28EA883Fh
    loc_0040A850: mov     dword ptr [ebp-4CCh],ecx
    loc_0040A856: xor     esi,ecx
    loc_0040A858: and     esi,edi
    loc_0040A85A: xor     esi,eax
    loc_0040A85C: mov     eax,dword ptr [ebp-4BCh]
    loc_0040A862: and     eax,edx
    loc_0040A864: rol     dword ptr [ebp-4B0h],15h
    loc_0040A86B: xor     esi,eax
    loc_0040A86D: xor     esi,ecx
    loc_0040A86F: mov     dword ptr [ebp-324h],eax
    loc_0040A875: rol     esi,19h
    loc_0040A878: mov     ecx,dword ptr [ebp-4B0h]
    loc_0040A87E: lea     eax,[esi+ecx]
    loc_0040A881: mov     ecx,dword ptr [ebp-30h]
    loc_0040A884: mov     ebx,dword ptr [ecx+30h]
    loc_0040A887: add     eax,ebx
    loc_0040A889: sub     eax,42CEB4D9h
    loc_0040A88E: mov     dword ptr [ebp-4D0h],eax
    loc_0040A894: mov     ebx,dword ptr [ebp-4BCh]
    loc_0040A89A: mov     esi,dword ptr [ebp-4C0h]
    loc_0040A8A0: rol     dword ptr [ebp-4B4h],15h
    loc_0040A8A7: mov     edi,dword ptr [ebp-4B8h]
    loc_0040A8AD: and     ebx,esi
    loc_0040A8AF: rol     dword ptr [ebp-4B8h],15h
    loc_0040A8B6: mov     edx,dword ptr [ebp-4C4h]
    loc_0040A8BC: xor     ebx,edi
    loc_0040A8BE: xor     ebx,eax
    loc_0040A8C0: mov     eax,dword ptr [ebp-324h]
    loc_0040A8C6: mov     esi,dword ptr [ebp-4CCh]
    loc_0040A8CC: and     ebx,edx
    loc_0040A8CE: mov     edi,dword ptr [ebp-4D0h]
    loc_0040A8D4: xor     ebx,eax
    loc_0040A8D6: mov     eax,dword ptr [ebp-4C0h]
    loc_0040A8DC: mov     edx,dword ptr [ebp-4B4h]
    loc_0040A8E2: and     eax,esi
    loc_0040A8E4: xor     ebx,eax
    loc_0040A8E6: mov     esi,dword ptr [ebp-4C4h]
    loc_0040A8EC: xor     ebx,edi
    loc_0040A8EE: rol     ebx,19h
    loc_0040A8F1: lea     edi,[ebx+edx]
    loc_0040A8F4: mov     ebx,dword ptr [ecx+60h]
    loc_0040A8F7: mov     ecx,dword ptr [ebp-4C0h]
    loc_0040A8FD: mov     edx,dword ptr [ebp-4BCh]
    loc_0040A903: add     edi,ebx
    loc_0040A905: and     ecx,esi
    loc_0040A907: mov     ebx,dword ptr [ebp-4C8h]
    loc_0040A90D: add     edi,78AF2FDAh
    loc_0040A913: mov     dword ptr [ebp-4D4h],edi
    loc_0040A919: xor     ecx,edx
    loc_0040A91B: mov     esi,dword ptr [ebp-4D0h]
    loc_0040A921: xor     ecx,edi
    loc_0040A923: mov     edx,dword ptr [ebp-4B8h]
    loc_0040A929: and     ecx,ebx
    loc_0040A92B: xor     ecx,eax
    loc_0040A92D: mov     eax,dword ptr [ebp-4C4h]
    loc_0040A933: mov     ebx,dword ptr [ebp-30h]
    loc_0040A936: and     eax,esi
    loc_0040A938: xor     ecx,eax
    loc_0040A93A: xor     ecx,edi
    loc_0040A93C: rol     ecx,19h
    loc_0040A93F: lea     esi,[ecx+edx]
    loc_0040A942: mov     edx,dword ptr [ebx+78h]
    loc_0040A945: mov     ecx,dword ptr [ebp-4C8h]
    loc_0040A94B: mov     ebx,dword ptr [ebp-4C0h]
    loc_0040A951: add     esi,edx
    loc_0040A953: mov     edx,dword ptr [ebp-4C4h]
    loc_0040A959: add     esi,55605C60h
    loc_0040A95F: mov     dword ptr [ebp-4D8h],esi
    loc_0040A965: and     edx,ecx
    loc_0040A967: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040A96D: xor     edx,ebx
    loc_0040A96F: mov     ebx,dword ptr [ebp-4C8h]
    loc_0040A975: xor     edx,esi
    loc_0040A977: rol     dword ptr [ebp-4BCh],15h
    loc_0040A97E: and     edx,ecx
    loc_0040A980: xor     edx,eax
    loc_0040A982: and     ebx,edi
    loc_0040A984: mov     eax,dword ptr [ebp-30h]
    loc_0040A987: mov     ecx,dword ptr [ebp-4BCh]
    loc_0040A98D: mov     dword ptr [ebp-330h],ebx
    loc_0040A993: xor     edx,ebx
    loc_0040A995: xor     edx,esi
    loc_0040A997: rol     edx,19h
    loc_0040A99A: lea     ebx,[edx+ecx]
    loc_0040A99D: mov     edx,dword ptr [eax+40h]
    loc_0040A9A0: add     ebx,edx
    loc_0040A9A2: sub     ebx,19AADA0Dh
    loc_0040A9A8: mov     dword ptr [ebp-4DCh],ebx
    loc_0040A9AE: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040A9B4: mov     edx,dword ptr [ebp-4C8h]
    loc_0040A9BA: rol     dword ptr [ebp-4C0h],15h
    loc_0040A9C1: mov     eax,dword ptr [ebp-4C4h]
    loc_0040A9C7: and     edx,ecx
    loc_0040A9C9: rol     dword ptr [ebp-4C4h],15h
    loc_0040A9D0: mov     ecx,dword ptr [ebp-4D0h]
    loc_0040A9D6: xor     edx,eax
    loc_0040A9D8: xor     edx,ebx
    loc_0040A9DA: mov     eax,dword ptr [ebp-330h]
    loc_0040A9E0: and     edx,ecx
    loc_0040A9E2: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040A9E8: xor     edx,eax
    loc_0040A9EA: mov     eax,dword ptr [ebp-4C0h]
    loc_0040A9F0: and     ecx,esi
    loc_0040A9F2: xor     edx,ecx
    loc_0040A9F4: xor     edx,ebx
    loc_0040A9F6: mov     dword ptr [ebp-338h],ecx
    loc_0040A9FC: rol     edx,19h
    loc_0040A9FF: mov     ecx,edx
    loc_0040AA01: mov     edx,dword ptr [ebp-30h]
    loc_0040AA04: add     ecx,eax
    loc_0040AA06: mov     eax,dword ptr [edx+68h]
    loc_0040AA09: mov     edx,dword ptr [ebp-4C8h]
    loc_0040AA0F: add     ecx,eax
    loc_0040AA11: sub     ecx,55AA546Ch
    loc_0040AA17: mov     dword ptr [ebp-4E0h],ecx
    loc_0040AA1D: mov     eax,dword ptr [ebp-4D0h]
    loc_0040AA23: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040AA29: and     ecx,eax
    loc_0040AA2B: mov     eax,dword ptr [ebp-4E0h]
    loc_0040AA31: xor     ecx,edx
    loc_0040AA33: mov     edx,dword ptr [ebp-338h]
    loc_0040AA39: xor     ecx,eax
    loc_0040AA3B: mov     eax,dword ptr [ebp-4D0h]
    loc_0040AA41: and     ecx,edi
    loc_0040AA43: xor     ecx,edx
    loc_0040AA45: mov     edx,dword ptr [ebp-4E0h]
    loc_0040AA4B: and     eax,ebx
    loc_0040AA4D: xor     ecx,eax
    loc_0040AA4F: xor     ecx,edx
    loc_0040AA51: mov     dword ptr [ebp-340h],eax
    loc_0040AA57: rol     ecx,19h
    loc_0040AA5A: mov     eax,dword ptr [ebp-4C4h]
    loc_0040AA60: mov     edx,ecx
    loc_0040AA62: mov     ecx,dword ptr [ebp-30h]
    loc_0040AA65: add     edx,eax
    loc_0040AA67: mov     eax,dword ptr [ecx+7Ch]
    loc_0040AA6A: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040AA70: add     edx,eax
    loc_0040AA72: add     edx,57489862h
    loc_0040AA78: mov     eax,dword ptr [ebp-4D0h]
    loc_0040AA7E: mov     dword ptr [ebp-4E4h],edx
    loc_0040AA84: mov     edx,dword ptr [ebp-4E4h]
    loc_0040AA8A: and     eax,edi
    loc_0040AA8C: xor     eax,ecx
    loc_0040AA8E: mov     ecx,dword ptr [ebp-340h]
    loc_0040AA94: xor     eax,edx
    loc_0040AA96: mov     edx,dword ptr [ebp-4E0h]
    loc_0040AA9C: and     eax,esi
    loc_0040AA9E: xor     eax,ecx
    loc_0040AAA0: mov     ecx,edi
    loc_0040AAA2: and     ecx,edx
    loc_0040AAA4: xor     eax,ecx
    loc_0040AAA6: mov     dword ptr [ebp-348h],ecx
    loc_0040AAAC: mov     ecx,dword ptr [ebp-4E4h]
    loc_0040AAB2: rol     dword ptr [ebp-4C8h],15h
    loc_0040AAB9: mov     edx,dword ptr [ebp-4C8h]
    loc_0040AABF: xor     eax,ecx
    loc_0040AAC1: rol     dword ptr [ebp-4CCh],15h
    loc_0040AAC8: mov     ecx,dword ptr [ebp-30h]
    loc_0040AACB: rol     eax,19h
    loc_0040AACE: add     eax,edx
    loc_0040AAD0: mov     edx,dword ptr [ecx+3Ch]
    loc_0040AAD3: mov     ecx,dword ptr [ebp-4D0h]
    loc_0040AAD9: add     eax,edx
    loc_0040AADB: add     eax,63E81440h
    loc_0040AAE0: mov     dword ptr [ebp-4E8h],eax
    loc_0040AAE6: mov     edx,dword ptr [ebp-4E8h]
    loc_0040AAEC: mov     eax,edi
    loc_0040AAEE: and     eax,esi
    loc_0040AAF0: xor     eax,ecx
    loc_0040AAF2: mov     ecx,dword ptr [ebp-348h]
    loc_0040AAF8: xor     eax,edx
    loc_0040AAFA: mov     edx,dword ptr [ebp-4E4h]
    loc_0040AB00: and     eax,ebx
    loc_0040AB02: xor     eax,ecx
    loc_0040AB04: mov     ecx,esi
    loc_0040AB06: and     ecx,edx
    loc_0040AB08: mov     dword ptr [ebp-354h],ecx
    loc_0040AB0E: mov     edx,dword ptr [ebp-4E8h]
    loc_0040AB14: xor     eax,ecx
    loc_0040AB16: mov     ecx,dword ptr [ebp-4CCh]
    loc_0040AB1C: xor     eax,edx
    loc_0040AB1E: mov     edx,dword ptr [ebp-30h]
    loc_0040AB21: rol     eax,19h
    loc_0040AB24: add     eax,ecx
    loc_0040AB26: mov     ecx,dword ptr [edx+1Ch]
    loc_0040AB29: mov     edx,dword ptr [ebp-354h]
    loc_0040AB2F: add     eax,ecx
    loc_0040AB31: add     eax,55CA396Ah
    loc_0040AB36: mov     dword ptr [ebp-4ECh],eax
    loc_0040AB3C: mov     eax,esi
    loc_0040AB3E: and     eax,ebx
    loc_0040AB40: xor     eax,edi
    loc_0040AB42: mov     edi,dword ptr [ebp-4ECh]
    loc_0040AB48: mov     ecx,dword ptr [ebp-4E0h]
    loc_0040AB4E: xor     eax,edi
    loc_0040AB50: mov     edi,dword ptr [ebp-4E8h]
    loc_0040AB56: and     eax,ecx
    loc_0040AB58: xor     eax,edx
    loc_0040AB5A: mov     ecx,ebx
    loc_0040AB5C: mov     edx,dword ptr [ebp-4ECh]
    loc_0040AB62: mov     dword ptr [ebp-35Ch],eax
    loc_0040AB68: and     ecx,edi
    loc_0040AB6A: mov     edi,dword ptr [ebp-30h]
    loc_0040AB6D: xor     dword ptr [ebp-35Ch],ecx
    loc_0040AB73: rol     dword ptr [ebp-4D0h],15h
    loc_0040AB7A: mov     dword ptr [ebp-360h],ecx
    loc_0040AB80: mov     ecx,dword ptr [edi+0Ch]
    loc_0040AB83: mov     eax,dword ptr [ebp-4D0h]
    loc_0040AB89: xor     dword ptr [ebp-35Ch],edx
    loc_0040AB8F: rol     dword ptr [ebp-35Ch],19h
    loc_0040AB96: mov     edx,dword ptr [ebp-35Ch]
    loc_0040AB9C: add     edx,eax
    loc_0040AB9E: add     edx,ecx
    loc_0040ABA0: add     edx,2AAB10B6h
    loc_0040ABA6: mov     dword ptr [ebp-4F0h],edx
    loc_0040ABAC: mov     eax,dword ptr [ebp-4E0h]
    loc_0040ABB2: mov     edx,ebx
    loc_0040ABB4: rol     dword ptr [ebp-4D4h],15h
    loc_0040ABBB: mov     ecx,dword ptr [ebp-4F0h]
    loc_0040ABC1: and     edx,eax
    loc_0040ABC3: mov     eax,dword ptr [ebp-4E4h]
    loc_0040ABC9: xor     edx,esi
    loc_0040ABCB: mov     esi,dword ptr [ebp-360h]
    loc_0040ABD1: mov     edi,dword ptr [ebp-4ECh]
    loc_0040ABD7: xor     edx,ecx
    loc_0040ABD9: mov     ecx,dword ptr [ebp-4E0h]
    loc_0040ABDF: and     edx,eax
    loc_0040ABE1: xor     edx,esi
    loc_0040ABE3: mov     eax,dword ptr [ebp-4F0h]
    loc_0040ABE9: mov     dword ptr [ebp-368h],edx
    loc_0040ABEF: and     ecx,edi
    loc_0040ABF1: mov     edx,dword ptr [ebp-30h]
    loc_0040ABF4: xor     dword ptr [ebp-368h],ecx
    loc_0040ABFA: mov     esi,dword ptr [ebp-4D4h]
    loc_0040AC00: mov     dword ptr [ebp-36Ch],ecx
    loc_0040AC06: mov     ecx,dword ptr [edx+4]
    loc_0040AC09: mov     edx,dword ptr [ebp-4E8h]
    loc_0040AC0F: xor     dword ptr [ebp-368h],eax
    loc_0040AC15: mov     eax,dword ptr [ebp-4E4h]
    loc_0040AC1B: rol     dword ptr [ebp-368h],19h
    loc_0040AC22: mov     edi,dword ptr [ebp-368h]
    loc_0040AC28: add     edi,esi
    loc_0040AC2A: add     edi,ecx
    loc_0040AC2C: mov     ecx,dword ptr [ebp-4E0h]
    loc_0040AC32: sub     edi,4B33A3CCh
    loc_0040AC38: mov     dword ptr [ebp-4F4h],edi
    loc_0040AC3E: mov     esi,dword ptr [ebp-4E4h]
    loc_0040AC44: mov     edi,dword ptr [ebp-4F4h]
    loc_0040AC4A: and     ecx,eax
    loc_0040AC4C: xor     ecx,ebx
    loc_0040AC4E: mov     ebx,dword ptr [ebp-36Ch]
    loc_0040AC54: mov     eax,dword ptr [ebp-4F0h]
    loc_0040AC5A: xor     ecx,edi
    loc_0040AC5C: and     ecx,edx
    loc_0040AC5E: xor     ecx,ebx
    loc_0040AC60: mov     edi,dword ptr [ebp-4F4h]
    loc_0040AC66: and     esi,eax
    loc_0040AC68: mov     dword ptr [ebp-370h],ecx
    loc_0040AC6E: xor     dword ptr [ebp-370h],esi
    loc_0040AC74: mov     dword ptr [ebp-374h],esi
    loc_0040AC7A: xor     dword ptr [ebp-370h],edi
    loc_0040AC80: mov     ecx,dword ptr [ebp-30h]
    loc_0040AC83: mov     eax,dword ptr [ebp-4E8h]
    loc_0040AC89: rol     dword ptr [ebp-370h],19h
    loc_0040AC90: mov     ebx,dword ptr [ecx]
    loc_0040AC92: mov     esi,dword ptr [ebp-4E0h]
    loc_0040AC98: rol     dword ptr [ebp-4D8h],15h
    loc_0040AC9F: mov     edi,dword ptr [ebp-370h]
    loc_0040ACA5: mov     ecx,dword ptr [ebp-374h]
    loc_0040ACAB: mov     edx,dword ptr [ebp-4D8h]
    loc_0040ACB1: add     edi,edx
    loc_0040ACB3: add     edi,ebx
    loc_0040ACB5: rol     dword ptr [ebp-4DCh],15h
    loc_0040ACBC: add     edi,1141E8CEh
    loc_0040ACC2: mov     ebx,dword ptr [ebp-4E4h]
    loc_0040ACC8: rol     dword ptr [ebp-4E0h],15h
    loc_0040ACCF: mov     edx,dword ptr [ebp-4ECh]
    loc_0040ACD5: and     ebx,eax
    loc_0040ACD7: mov     dword ptr [ebp-4F8h],edi
    loc_0040ACDD: mov     eax,dword ptr [ebp-4F4h]
    loc_0040ACE3: xor     ebx,esi
    loc_0040ACE5: mov     esi,dword ptr [ebp-4E8h]
    loc_0040ACEB: xor     ebx,edi
    loc_0040ACED: and     ebx,edx
    loc_0040ACEF: xor     ebx,ecx
    loc_0040ACF1: mov     ecx,dword ptr [ebp-30h]
    loc_0040ACF4: and     esi,eax
    loc_0040ACF6: mov     dword ptr [ebp-37Ch],esi
    loc_0040ACFC: xor     ebx,esi
    loc_0040ACFE: mov     edx,dword ptr [ebp-4DCh]
    loc_0040AD04: xor     ebx,edi
    loc_0040AD06: mov     eax,dword ptr [ecx+48h]
    loc_0040AD09: rol     ebx,19h
    loc_0040AD0C: mov     esi,ebx
    loc_0040AD0E: mov     ebx,dword ptr [ebp-4ECh]
    loc_0040AD14: add     esi,edx
    loc_0040AD16: add     esi,eax
    loc_0040AD18: mov     eax,dword ptr [ebp-4E8h]
    loc_0040AD1E: mov     edx,dword ptr [ebp-4E4h]
    loc_0040AD24: mov     ecx,dword ptr [ebp-4F0h]
    loc_0040AD2A: sub     esi,5EAB7951h
    loc_0040AD30: and     eax,ebx
    loc_0040AD32: mov     dword ptr [ebp-4FCh],esi
    loc_0040AD38: xor     eax,edx
    loc_0040AD3A: mov     ebx,dword ptr [ebp-37Ch]
    loc_0040AD40: xor     eax,esi
    loc_0040AD42: mov     edx,dword ptr [ebp-4E0h]
    loc_0040AD48: and     eax,ecx
    loc_0040AD4A: mov     ecx,dword ptr [ebp-4ECh]
    loc_0040AD50: xor     eax,ebx
    loc_0040AD52: and     ecx,edi
    loc_0040AD54: xor     eax,ecx
    loc_0040AD56: xor     eax,esi
    loc_0040AD58: rol     eax,19h
    loc_0040AD5B: mov     ebx,eax
    loc_0040AD5D: mov     eax,dword ptr [ebp-30h]
    loc_0040AD60: add     ebx,edx
    loc_0040AD62: mov     edi,dword ptr [eax+6Ch]
    loc_0040AD65: add     ebx,edi
    loc_0040AD67: add     ebx,7C72E993h
    loc_0040AD6D: mov     dword ptr [ebp-500h],ebx
    loc_0040AD73: mov     edi,dword ptr [ebp-4ECh]
    loc_0040AD79: mov     edx,dword ptr [ebp-4F0h]
    loc_0040AD7F: mov     eax,dword ptr [ebp-4E8h]
    loc_0040AD85: and     edi,edx
    loc_0040AD87: mov     edx,dword ptr [ebp-4F4h]
    loc_0040AD8D: xor     edi,eax
    loc_0040AD8F: xor     edi,ebx
    loc_0040AD91: and     edi,edx
    loc_0040AD93: xor     edi,ecx
    loc_0040AD95: mov     ecx,dword ptr [ebp-4F0h]
    loc_0040AD9B: mov     edx,dword ptr [ebp-4F4h]
    loc_0040ADA1: and     ecx,esi
    loc_0040ADA3: xor     edi,ecx
    loc_0040ADA5: xor     edi,ebx
    loc_0040ADA7: rol     dword ptr [ebp-4E4h],15h
    loc_0040ADAE: rol     edi,19h
    loc_0040ADB1: mov     dword ptr [ebp-388h],ecx
    loc_0040ADB7: mov     eax,dword ptr [ebp-4E4h]
    loc_0040ADBD: rol     dword ptr [ebp-4E8h],15h
    loc_0040ADC4: lea     ecx,[edi+eax]
    loc_0040ADC7: mov     edi,dword ptr [ebp-30h]
    loc_0040ADCA: mov     eax,dword ptr [ebp-4ECh]
    loc_0040ADD0: rol     dword ptr [ebp-4ECh],15h
    loc_0040ADD7: mov     esi,dword ptr [edi+34h]
    loc_0040ADDA: mov     edi,dword ptr [ebp-4F8h]
    loc_0040ADE0: add     ecx,esi
    loc_0040ADE2: mov     esi,dword ptr [ebp-4F0h]
    loc_0040ADE8: sub     ecx,4C11EBEFh
    loc_0040ADEE: mov     dword ptr [ebp-504h],ecx
    loc_0040ADF4: and     esi,edx
    loc_0040ADF6: xor     esi,eax
    loc_0040ADF8: xor     esi,ecx
    loc_0040ADFA: mov     edx,dword ptr [ebp-388h]
    loc_0040AE00: and     esi,edi
    loc_0040AE02: mov     edi,dword ptr [ebp-4F4h]
    loc_0040AE08: xor     esi,edx
    loc_0040AE0A: mov     eax,dword ptr [ebp-4E8h]
    loc_0040AE10: and     edi,ebx
    loc_0040AE12: xor     esi,edi
    loc_0040AE14: xor     esi,ecx
    loc_0040AE16: rol     esi,19h
    loc_0040AE19: mov     ecx,dword ptr [ebp-4F0h]
    loc_0040AE1F: lea     edx,[esi+eax]
    loc_0040AE22: mov     eax,dword ptr [ebp-30h]
    loc_0040AE25: mov     esi,dword ptr [ebp-4F8h]
    loc_0040AE2B: mov     ebx,dword ptr [eax+18h]
    loc_0040AE2E: add     edx,ebx
    loc_0040AE30: mov     ebx,dword ptr [ebp-4F4h]
    loc_0040AE36: add     edx,636FBC2Ah
    loc_0040AE3C: mov     dword ptr [ebp-508h],edx
    loc_0040AE42: and     ebx,esi
    loc_0040AE44: mov     esi,dword ptr [ebp-4FCh]
    loc_0040AE4A: xor     ebx,ecx
    loc_0040AE4C: xor     ebx,edx
    loc_0040AE4E: mov     ecx,dword ptr [ebp-504h]
    loc_0040AE54: and     ebx,esi
    loc_0040AE56: mov     esi,dword ptr [ebp-4F8h]
    loc_0040AE5C: xor     ebx,edi
    loc_0040AE5E: mov     edi,dword ptr [eax+54h]
    loc_0040AE61: and     esi,ecx
    loc_0040AE63: xor     ebx,esi
    loc_0040AE65: xor     ebx,edx
    loc_0040AE67: mov     edx,dword ptr [ebp-4ECh]
    loc_0040AE6D: rol     ebx,19h
    loc_0040AE70: lea     ecx,[ebx+edx]
    loc_0040AE73: add     ecx,edi
    loc_0040AE75: add     ecx,2BA9C55Dh
    loc_0040AE7B: mov     dword ptr [ebp-50Ch],ecx
    loc_0040AE81: mov     ebx,dword ptr [ebp-4FCh]
    loc_0040AE87: mov     ecx,dword ptr [ebp-4F8h]
    loc_0040AE8D: mov     edx,dword ptr [ebp-4F4h]
    loc_0040AE93: mov     edi,dword ptr [ebp-50Ch]
    loc_0040AE99: and     ecx,ebx
    loc_0040AE9B: mov     ebx,dword ptr [ebp-500h]
    loc_0040AEA1: xor     ecx,edx
    loc_0040AEA3: xor     ecx,edi
    loc_0040AEA5: rol     dword ptr [ebp-4F0h],15h
    loc_0040AEAC: and     ecx,ebx
    loc_0040AEAE: mov     ebx,dword ptr [ebp-4FCh]
    loc_0040AEB4: rol     dword ptr [ebp-4F4h],15h
    loc_0040AEBB: xor     ecx,esi
    loc_0040AEBD: mov     esi,dword ptr [ebp-508h]
    loc_0040AEC3: mov     edx,dword ptr [ebp-50Ch]
    loc_0040AEC9: mov     edi,dword ptr [ebp-4F0h]
    loc_0040AECF: and     ebx,esi
    loc_0040AED1: xor     ecx,ebx
    loc_0040AED3: mov     esi,dword ptr [eax+28h]
    loc_0040AED6: xor     ecx,edx
    loc_0040AED8: rol     ecx,19h
    loc_0040AEDB: mov     edx,dword ptr [ebp-500h]
    loc_0040AEE1: add     ecx,edi
    loc_0040AEE3: add     ecx,esi
    loc_0040AEE5: mov     edi,dword ptr [ebp-4F8h]
    loc_0040AEEB: add     ecx,741831F6h
    loc_0040AEF1: mov     dword ptr [ebp-510h],ecx
    loc_0040AEF7: mov     ecx,dword ptr [ebp-4FCh]
    loc_0040AEFD: mov     esi,dword ptr [ebp-510h]
    loc_0040AF03: and     ecx,edx
    loc_0040AF05: mov     edx,dword ptr [ebp-504h]
    loc_0040AF0B: xor     ecx,edi
    loc_0040AF0D: xor     ecx,esi
    loc_0040AF0F: mov     edi,dword ptr [ebp-50Ch]
    loc_0040AF15: mov     esi,dword ptr [ebp-510h]
    loc_0040AF1B: and     ecx,edx
    loc_0040AF1D: xor     ecx,ebx
    loc_0040AF1F: mov     ebx,dword ptr [ebp-500h]
    loc_0040AF25: mov     edx,dword ptr [ebp-4F4h]
    loc_0040AF2B: and     ebx,edi
    loc_0040AF2D: xor     ecx,ebx
    loc_0040AF2F: mov     edi,dword ptr [eax+5Ch]
    loc_0040AF32: xor     ecx,esi
    loc_0040AF34: rol     ecx,19h
    loc_0040AF37: add     ecx,edx
    loc_0040AF39: mov     eax,dword ptr [ebp-504h]
    loc_0040AF3F: add     ecx,edi
    loc_0040AF41: mov     edi,dword ptr [ebp-500h]
    loc_0040AF47: sub     ecx,31A3C1EAh
    loc_0040AF4D: mov     esi,dword ptr [ebp-4FCh]
    loc_0040AF53: mov     dword ptr [ebp-514h],ecx
    loc_0040AF59: mov     edx,dword ptr [ebp-514h]
    loc_0040AF5F: and     edi,eax
    loc_0040AF61: mov     ecx,dword ptr [ebp-508h]
    loc_0040AF67: xor     edi,esi
    loc_0040AF69: mov     eax,dword ptr [ebp-510h]
    loc_0040AF6F: mov     esi,dword ptr [ebp-504h]
    loc_0040AF75: xor     edi,edx
    loc_0040AF77: and     edi,ecx
    loc_0040AF79: xor     edi,ebx
    loc_0040AF7B: and     esi,eax
    loc_0040AF7D: xor     edi,esi
    loc_0040AF7F: mov     dword ptr [ebp-390h],esi
    loc_0040AF85: mov     ebx,dword ptr [ebp-514h]
    loc_0040AF8B: mov     esi,dword ptr [ebp-508h]
    loc_0040AF91: xor     edi,ebx
    loc_0040AF93: rol     edi,19h
    loc_0040AF96: mov     ebx,dword ptr [ebp-500h]
    loc_0040AF9C: rol     dword ptr [ebp-4F8h],15h
    loc_0040AFA3: mov     eax,edi
    loc_0040AFA5: rol     dword ptr [ebp-4FCh],15h
    loc_0040AFAC: mov     edx,dword ptr [ebp-4F8h]
    loc_0040AFB2: add     eax,edx
    loc_0040AFB4: mov     edx,dword ptr [ebp-30h]
    loc_0040AFB7: mov     ecx,dword ptr [edx+2Ch]
    loc_0040AFBA: add     eax,ecx
    loc_0040AFBC: sub     eax,64786CE2h
    loc_0040AFC1: mov     ecx,dword ptr [ebp-50Ch]
    loc_0040AFC7: mov     dword ptr [ebp-518h],eax
    loc_0040AFCD: mov     eax,dword ptr [ebp-504h]
    loc_0040AFD3: mov     edi,dword ptr [ebp-518h]
    loc_0040AFD9: and     eax,esi
    loc_0040AFDB: xor     eax,ebx
    loc_0040AFDD: mov     esi,dword ptr [ebp-390h]
    loc_0040AFE3: mov     ebx,dword ptr [ebp-514h]
    loc_0040AFE9: xor     eax,edi
    loc_0040AFEB: mov     edi,dword ptr [ebp-508h]
    loc_0040AFF1: and     eax,ecx
    loc_0040AFF3: mov     ecx,dword ptr [ebp-518h]
    loc_0040AFF9: xor     eax,esi
    loc_0040AFFB: and     edi,ebx
    loc_0040AFFD: mov     esi,dword ptr [ebp-4FCh]
    loc_0040B003: xor     eax,edi
    loc_0040B005: mov     dword ptr [ebp-394h],edi
    loc_0040B00B: mov     ebx,dword ptr [edx+14h]
    loc_0040B00E: xor     eax,ecx
    loc_0040B010: rol     eax,19h
    loc_0040B013: mov     edi,dword ptr [ebp-50Ch]
    loc_0040B019: add     eax,esi
    loc_0040B01B: add     eax,ebx
    loc_0040B01D: mov     ecx,dword ptr [ebp-504h]
    loc_0040B023: sub     eax,502945CDh
    loc_0040B028: mov     dword ptr [ebp-51Ch],eax
    loc_0040B02E: mov     eax,dword ptr [ebp-508h]
    loc_0040B034: mov     esi,dword ptr [ebp-51Ch]
    loc_0040B03A: mov     ebx,dword ptr [ebp-510h]
    loc_0040B040: and     eax,edi
    loc_0040B042: mov     edx,dword ptr [ebp-394h]
    loc_0040B048: xor     eax,ecx
    loc_0040B04A: mov     edi,dword ptr [ebp-518h]
    loc_0040B050: xor     eax,esi
    loc_0040B052: mov     ecx,dword ptr [ebp-50Ch]
    loc_0040B058: and     eax,ebx
    loc_0040B05A: xor     eax,edx
    loc_0040B05C: mov     dword ptr [ebp-398h],eax
    loc_0040B062: mov     esi,dword ptr [ebp-51Ch]
    loc_0040B068: and     ecx,edi
    loc_0040B06A: xor     dword ptr [ebp-398h],ecx
    loc_0040B070: xor     dword ptr [ebp-398h],esi
    loc_0040B076: mov     edx,dword ptr [ebp-30h]
    loc_0040B079: mov     edi,dword ptr [ebp+8]
    loc_0040B07C: rol     dword ptr [ebp-398h],19h
    loc_0040B083: mov     eax,dword ptr [edx+8]
    loc_0040B086: mov     esi,dword ptr [edi+8]
    loc_0040B089: rol     dword ptr [ebp-500h],15h
    loc_0040B090: mov     ecx,dword ptr [ebp-398h]
    loc_0040B096: mov     edx,dword ptr [ebp-51Ch]
    loc_0040B09C: mov     ebx,dword ptr [ebp-500h]
    loc_0040B0A2: mov     edi,dword ptr [ebp-514h]
    loc_0040B0A8: add     ecx,ebx
    loc_0040B0AA: add     ecx,eax
    loc_0040B0AC: lea     ebx,[ecx+esi+6C24CF5Ch]
    loc_0040B0B3: mov     ecx,dword ptr [ebp+8]
    loc_0040B0B6: mov     eax,dword ptr [ebp-518h]
    loc_0040B0BC: mov     esi,dword ptr [ebp-510h]
    loc_0040B0C2: add     dword ptr [ecx+0Ch],edx
    loc_0040B0C5: mov     edx,dword ptr [ebp-508h]
    loc_0040B0CB: add     dword ptr [ecx+10h],eax
    loc_0040B0CE: mov     eax,dword ptr [ebp-504h]
    loc_0040B0D4: mov     dword ptr [ecx+8],ebx
    loc_0040B0D7: mov     ebx,dword ptr [ebp-50Ch]
    loc_0040B0DD: add     dword ptr [ecx+14h],edi
    loc_0040B0E0: add     dword ptr [ecx+18h],esi
    loc_0040B0E3: add     dword ptr [ecx+1Ch],ebx
    loc_0040B0E6: add     dword ptr [ecx+20h],edx
    loc_0040B0E9: add     dword ptr [ecx+24h],eax
    loc_0040B0EC: add     esp,594h
    loc_0040B0F2: pop     ebx
    loc_0040B0F3: pop     esi
    loc_0040B0F4: pop     edi
    loc_0040B0F5: pop     ebp
    loc_0040B0F6: ret
  };
}

void __declspec(naked) func_0040B100()
{
  __asm
  {
    loc_0040B100: push    ebp
    loc_0040B101: mov     ebp,esp
    loc_0040B103: push    edi
    loc_0040B104: push    esi
    loc_0040B105: push    ebx
    loc_0040B106: sub     esp,2Ch
    loc_0040B109: mov     esi,dword ptr [ebp+8]
    loc_0040B10C: mov     dword ptr [ebp-1Ch],80h
    loc_0040B113: mov     ecx,dword ptr [ebp+10h]
    loc_0040B116: mov     ebx,dword ptr [ebp+0Ch]
    loc_0040B119: mov     dword ptr [ebp-10h],esi
    loc_0040B11C: mov     eax,dword ptr [esi]
    loc_0040B11E: mov     dword ptr [ebp-18h],ecx
    loc_0040B121: mov     edx,dword ptr [ebp-18h]
    loc_0040B124: mov     ecx,eax
    loc_0040B126: mov     dword ptr [ebp-14h],ebx
    loc_0040B129: shr     ecx,3
    loc_0040B12C: shl     edx,3
    loc_0040B12F: and     ecx,7Fh
    loc_0040B132: add     eax,edx
    loc_0040B134: sub     dword ptr [ebp-1Ch],ecx
    loc_0040B137: cmp     eax,edx
    loc_0040B139: mov     dword ptr [esi],eax
    loc_0040B13B: jae loc_0040B188
    loc_0040B13D: mov     edx,dword ptr [esi+4]
    loc_0040B140: mov     edi,dword ptr [ebp-18h]
    loc_0040B143: mov     esi,dword ptr [ebp-18h]
    loc_0040B146: inc     edx
    loc_0040B147: shr     edi,1Dh
    loc_0040B14A: lea     ebx,[edx+edi]
    loc_0040B14D: mov     edx,dword ptr [ebp-10h]
    loc_0040B150: lea     eax,[ecx+esi]
    loc_0040B153: xor     edi,edi
    loc_0040B155: cmp     eax,7Fh
    loc_0040B158: mov     dword ptr [edx+4],ebx
    loc_0040B15B: ja loc_0040B1AA
    loc_0040B15D: sub     dword ptr [ebp-18h],edi
    loc_0040B160: mov     eax,dword ptr [ebp-10h]
    loc_0040B163: lea     esi,[eax+ecx+0A8h]
    loc_0040B16A: mov     dword ptr [ebp+8],esi
    loc_0040B16D: mov     ecx,dword ptr [ebp-14h]
    loc_0040B170: lea     edx,[edi+ecx]
    loc_0040B173: mov     dword ptr [ebp+0Ch],edx
    loc_0040B176: mov     edi,dword ptr [ebp-18h]
    loc_0040B179: mov     dword ptr [ebp+10h],edi
    loc_0040B17C: add     esp,2Ch
    loc_0040B17F: pop     ebx
    loc_0040B180: pop     esi
    loc_0040B181: pop     edi
    loc_0040B182: pop     ebp
    loc_0040B183: jmp memcpy
    loc_0040B188: mov     edi,dword ptr [ebp-10h]
    loc_0040B18B: mov     esi,dword ptr [ebp-18h]
    loc_0040B18E: mov     edx,dword ptr [edi+4]
    loc_0040B191: mov     edi,dword ptr [ebp-18h]
    loc_0040B194: lea     eax,[ecx+esi]
    loc_0040B197: shr     edi,1Dh
    loc_0040B19A: lea     ebx,[edx+edi]
    loc_0040B19D: mov     edx,dword ptr [ebp-10h]
    loc_0040B1A0: xor     edi,edi
    loc_0040B1A2: cmp     eax,7Fh
    loc_0040B1A5: mov     dword ptr [edx+4],ebx
    loc_0040B1A8: jbe loc_0040B15D
    loc_0040B1AA: mov     ebx,dword ptr [ebp-1Ch]
    loc_0040B1AD: lea     esi,[edx+ecx+0A8h]
    loc_0040B1B4: mov     dword ptr [esp+8],ebx
    loc_0040B1B8: mov     ecx,dword ptr [ebp-14h]
    loc_0040B1BB: mov     dword ptr [esp],esi
    loc_0040B1BE: mov     dword ptr [esp+4],ecx
    loc_0040B1C2: call memcpy
    loc_0040B1C7: mov     eax,dword ptr [ebp-10h]
    loc_0040B1CA: mov     edx,dword ptr [ebp-10h]
    loc_0040B1CD: mov     esi,dword ptr [ebp-10h]
    loc_0040B1D0: add     eax,0A8h
    loc_0040B1D5: add     edx,28h
    loc_0040B1D8: mov     ecx,eax
    loc_0040B1DA: mov     dword ptr [ebp-20h],eax
    loc_0040B1DD: mov     ebx,edx
    loc_0040B1DF: add     esi,128h
    loc_0040B1E5: mov     dword ptr [ebp-24h],edx
    loc_0040B1E8: jmp loc_0040B216
    loc_0040B1EA: lea     esi,[esi]
    loc_0040B1F0: movzx   edx,byte ptr [ecx+1]
    loc_0040B1F4: movzx   edi,byte ptr [ecx]
    loc_0040B1F7: movzx   eax,byte ptr [ecx+2]
    loc_0040B1FB: shl     edx,8
    loc_0040B1FE: or      edi,edx
    loc_0040B200: movzx   edx,byte ptr [ecx+3]
    loc_0040B204: shl     eax,10h
    loc_0040B207: or      edi,eax
    loc_0040B209: add     ecx,4
    loc_0040B20C: shl     edx,18h
    loc_0040B20F: or      edi,edx
    loc_0040B211: mov     dword ptr [ebx],edi
    loc_0040B213: add     ebx,4
    loc_0040B216: cmp     esi,ecx
    loc_0040B218: ja loc_0040B1F0
    loc_0040B21A: mov     ecx,dword ptr [ebp-10h]
    loc_0040B21D: mov     dword ptr [esp],ecx
    loc_0040B220: call func_004081B0
    loc_0040B225: mov     edi,dword ptr [ebp-1Ch]
    loc_0040B228: lea     ebx,[edi+7Fh]
    loc_0040B22B: cmp     ebx,dword ptr [ebp-18h]
    loc_0040B22E: jae loc_0040B295
    loc_0040B230: mov     ecx,dword ptr [ebp-14h]
    loc_0040B233: mov     edx,80h
    loc_0040B238: mov     dword ptr [esp+8],edx
    loc_0040B23C: lea     eax,[edi+ecx]
    loc_0040B23F: mov     dword ptr [esp+4],eax
    loc_0040B243: mov     ebx,dword ptr [ebp-20h]
    loc_0040B246: mov     dword ptr [esp],ebx
    loc_0040B249: call memcpy
    loc_0040B24E: mov     ecx,ebx
    loc_0040B250: mov     ebx,dword ptr [ebp-24h]
    loc_0040B253: jmp loc_0040B27B
    loc_0040B255: movzx   eax,byte ptr [ecx+1]
    loc_0040B259: movzx   edx,byte ptr [ecx]
    loc_0040B25C: shl     eax,8
    loc_0040B25F: or      edx,eax
    loc_0040B261: movzx   eax,byte ptr [ecx+2]
    loc_0040B265: shl     eax,10h
    loc_0040B268: or      edx,eax
    loc_0040B26A: movzx   eax,byte ptr [ecx+3]
    loc_0040B26E: add     ecx,4
    loc_0040B271: shl     eax,18h
    loc_0040B274: or      edx,eax
    loc_0040B276: mov     dword ptr [ebx],edx
    loc_0040B278: add     ebx,4
    loc_0040B27B: cmp     esi,ecx
    loc_0040B27D: ja loc_0040B255
    loc_0040B27F: mov     ebx,dword ptr [ebp-10h]
    loc_0040B282: sub     edi,0FFFFFF80h
    loc_0040B285: mov     dword ptr [esp],ebx
    loc_0040B288: call func_004081B0
    loc_0040B28D: lea     ebx,[edi+7Fh]
    loc_0040B290: cmp     ebx,dword ptr [ebp-18h]
    loc_0040B293: jb loc_0040B230
    loc_0040B295: xor     ecx,ecx
    loc_0040B297: jmp loc_0040B15D
    loc_0040B29C: lea     esi,[esi]
    loc_0040B2A0: push    ebp
    loc_0040B2A1: mov     ebp,esp
    loc_0040B2A3: lea     ecx,[ebp-16h]
    loc_0040B2A6: push    esi
    loc_0040B2A7: push    ebx
    loc_0040B2A8: sub     esp,20h
    loc_0040B2AB: mov     esi,dword ptr [ebp+8]
    loc_0040B2AE: mov     byte ptr [ebp-18h],19h
    loc_0040B2B2: mov     byte ptr [ebp-17h],40h
    loc_0040B2B6: lea     ebx,[esi+8]
    loc_0040B2B9: mov     edx,esi
    loc_0040B2BB: cmp     ebx,esi
    loc_0040B2BD: jbe loc_0040B2DF
    loc_0040B2BF: mov     eax,dword ptr [edx]
    loc_0040B2C1: add     edx,4
    loc_0040B2C4: mov     byte ptr [ecx],al
    loc_0040B2C6: shr     eax,8
    loc_0040B2C9: mov     byte ptr [ecx+1],al
    loc_0040B2CC: shr     eax,8
    loc_0040B2CF: mov     byte ptr [ecx+2],al
    loc_0040B2D2: shr     eax,8
    loc_0040B2D5: mov     byte ptr [ecx+3],al
    loc_0040B2D8: add     ecx,4
    loc_0040B2DB: cmp     ebx,edx
    loc_0040B2DD: ja loc_0040B2BF
    loc_0040B2DF: mov     eax,dword ptr [esi]
    loc_0040B2E1: mov     edx,76h
    loc_0040B2E6: shr     eax,3
    loc_0040B2E9: and     eax,7Fh
    loc_0040B2EC: cmp     eax,75h
    loc_0040B2EF: jbe loc_0040B2F6
    loc_0040B2F1: mov     edx,0F6h
    loc_0040B2F6: mov     dword ptr [esp],esi
    loc_0040B2F9: sub     edx,eax
    loc_0040B2FB: mov     ebx,0x0040E000
    loc_0040B300: mov     dword ptr [esp+8],edx
    loc_0040B304: mov     dword ptr [esp+4],ebx
    loc_0040B308: lea     ebx,[esi+28h]
    loc_0040B30B: call func_0040B100
    loc_0040B310: mov     dword ptr [esp],esi
    loc_0040B313: mov     ecx,0Ah
    loc_0040B318: lea     edx,[ebp-18h]
    loc_0040B31B: mov     dword ptr [esp+8],ecx
    loc_0040B31F: mov     dword ptr [esp+4],edx
    loc_0040B323: call func_0040B100
    loc_0040B328: mov     ecx,dword ptr [ebp+0Ch]
    loc_0040B32B: lea     edx,[esi+8]
    loc_0040B32E: jmp loc_0040B350
    loc_0040B330: mov     eax,dword ptr [edx]
    loc_0040B332: mov     byte ptr [ecx],al
    loc_0040B334: mov     eax,dword ptr [edx]
    loc_0040B336: shr     eax,8
    loc_0040B339: mov     byte ptr [ecx+1],al
    loc_0040B33C: movzx   eax,word ptr [edx+2]
    loc_0040B340: mov     byte ptr [ecx+2],al
    loc_0040B343: movzx   eax,byte ptr [edx+3]
    loc_0040B347: add     edx,4
    loc_0040B34A: mov     byte ptr [ecx+3],al
    loc_0040B34D: add     ecx,4
    loc_0040B350: cmp     ebx,edx
    loc_0040B352: ja loc_0040B330
    loc_0040B354: mov     dword ptr [esp],esi
    loc_0040B357: mov     ecx,128h
    loc_0040B35C: xor     edx,edx
    loc_0040B35E: mov     dword ptr [esp+8],ecx
    loc_0040B362: mov     dword ptr [esp+4],edx
    loc_0040B366: call memset
    loc_0040B36B: add     esp,20h
    loc_0040B36E: pop     ebx
    loc_0040B36F: pop     esi
    loc_0040B370: pop     ebp
    loc_0040B371: ret
  };
}

void __declspec(naked) func_0040B6B0(char *)
{
  __asm
  {
    loc_0040B6B0: push    ebp
    loc_0040B6B1: xor     edx,edx
    loc_0040B6B3: mov     ebp,esp
    loc_0040B6B5: push    edi
    loc_0040B6B6: xor     eax,eax
    loc_0040B6B8: mov     ecx,243F6A88h
    loc_0040B6BD: push    esi
    loc_0040B6BE: mov     edi,85A308D3h
    loc_0040B6C3: lea     esi,[ebp-148h]
    loc_0040B6C9: push    ebx
    loc_0040B6CA: sub     esp,15Ch
    loc_0040B6D0: mov     dword ptr [ebp-144h],edx
    loc_0040B6D6: mov     edx,3707344h
    loc_0040B6DB: mov     ebx,13198A2Eh
    loc_0040B6E0: mov     dword ptr [ebp-134h],edx
    loc_0040B6E6: mov     edx,dword ptr [ebp+8]
    loc_0040B6E9: mov     dword ptr [ebp-148h],eax
    loc_0040B6EF: mov     eax,0A4093822h
    loc_0040B6F4: mov     dword ptr [ebp-140h],ecx
    loc_0040B6FA: mov     ecx,299F31D0h
    loc_0040B6FF: mov     dword ptr [ebp-13Ch],edi
    loc_0040B705: mov     edi,82EFA98h
    loc_0040B70A: mov     dword ptr [ebp-138h],ebx
    loc_0040B710: mov     ebx,0EC4E6C89h
    loc_0040B715: mov     dword ptr [ebp-12Ch],ecx
    loc_0040B71B: mov     dword ptr [esp],edx
    loc_0040B71E: mov     dword ptr [ebp-128h],edi
    loc_0040B724: lea     edi,[esi+8]
    loc_0040B727: mov     dword ptr [ebp-124h],ebx
    loc_0040B72D: lea     ebx,[ebp-140h]
    loc_0040B733: mov     dword ptr [ebp-130h],eax
    loc_0040B739: call strlen
    loc_0040B73E: mov     dword ptr [esp+8],eax
    loc_0040B742: mov     eax,dword ptr [ebp+8]
    loc_0040B745: mov     dword ptr [esp],esi
    loc_0040B748: mov     dword ptr [esp+4],eax
    loc_0040B74C: call func_0040B100
    loc_0040B751: mov     byte ptr [ebp-158h],19h
    loc_0040B758: cmp     ebx,esi
    loc_0040B75A: mov     edx,esi
    loc_0040B75C: mov     byte ptr [ebp-157h],40h
    loc_0040B763: lea     ecx,[ebp-156h]
    loc_0040B769: jbe loc_0040B794
    loc_0040B76B: mov     edi,ebx
    loc_0040B76D: lea     esi,[esi]
    loc_0040B770: mov     eax,dword ptr [edx]
    loc_0040B772: mov     byte ptr [ecx],al
    loc_0040B774: mov     eax,dword ptr [edx]
    loc_0040B776: shr     eax,8
    loc_0040B779: mov     byte ptr [ecx+1],al
    loc_0040B77C: movzx   eax,word ptr [edx+2]
    loc_0040B780: mov     byte ptr [ecx+2],al
    loc_0040B783: movzx   eax,byte ptr [edx+3]
    loc_0040B787: add     edx,4
    loc_0040B78A: mov     byte ptr [ecx+3],al
    loc_0040B78D: add     ecx,4
    loc_0040B790: cmp     ebx,edx
    loc_0040B792: ja loc_0040B770
    loc_0040B794: mov     eax,dword ptr [esi]
    loc_0040B796: mov     edx,76h
    loc_0040B79B: shr     eax,3
    loc_0040B79E: and     eax,7Fh
    loc_0040B7A1: cmp     eax,75h
    loc_0040B7A4: jbe loc_0040B7AB
    loc_0040B7A6: mov     edx,0F6h
    loc_0040B7AB: mov     dword ptr [esp],esi
    loc_0040B7AE: sub     edx,eax
    loc_0040B7B0: lea     ebx,[ebp-158h]
    loc_0040B7B6: mov     dword ptr [esp+8],edx
    loc_0040B7BA: mov     edx, [phashdata1]
    loc_0040B7BF: mov     dword ptr [esp+4],edx
    loc_0040B7C3: call func_0040B100
    loc_0040B7C8: mov     dword ptr [esp+4],ebx
    loc_0040B7CC: mov     ecx,0Ah
    loc_0040B7D1: lea     ebx,[esi+28h]
    loc_0040B7D4: mov     dword ptr [esp+8],ecx
    loc_0040B7D8: mov     dword ptr [esp],esi
    loc_0040B7DB: call func_0040B100
    loc_0040B7E0: mov     edx,dword ptr [ebp+8]
    loc_0040B7E3: mov     ecx,edi
    loc_0040B7E5: jmp loc_0040B803
    loc_0040B7E7: mov     eax,dword ptr [ecx]
    loc_0040B7E9: add     ecx,4
    loc_0040B7EC: mov     byte ptr [edx],al
    loc_0040B7EE: shr     eax,8
    loc_0040B7F1: mov     byte ptr [edx+1],al
    loc_0040B7F4: shr     eax,8
    loc_0040B7F7: mov     byte ptr [edx+2],al
    loc_0040B7FA: shr     eax,8
    loc_0040B7FD: mov     byte ptr [edx+3],al
    loc_0040B800: add     edx,4
    loc_0040B803: cmp     ebx,ecx
    loc_0040B805: ja loc_0040B7E7
    loc_0040B807: mov     dword ptr [esp],esi
    loc_0040B80A: mov     ebx,128h
    loc_0040B80F: xor     edi,edi
    loc_0040B811: mov     dword ptr [esp+8],ebx
    loc_0040B815: mov     dword ptr [esp+4],edi
    loc_0040B819: call memset
    loc_0040B81E: add     esp,15Ch
    loc_0040B824: pop     ebx
    loc_0040B825: pop     esi
    loc_0040B826: pop     edi
    loc_0040B827: pop     ebp
    loc_0040B828: ret
  };
}

