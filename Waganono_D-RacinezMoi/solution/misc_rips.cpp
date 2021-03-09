// 2008 andrewl

#include <windows.h>

#pragma section(".rips")
__declspec(allocate(".rips")) UCHAR transform_user0[] =
{
  0x55,                                           //00: push    ebp
  0x8B, 0xEC,                                     //01: mov     ebp,esp
  0x51,                                           //03: push    ecx
  0x53,                                           //04: push    ebx
  0x56,                                           //05: push    esi
  0x57,                                           //06: push    edi
  0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00,       //07: mov     dword ptr [ebp-4],0
  0x60,                                           //0E: pushad
  0x33, 0xC9,                                     //0F: xor     ecx,ecx
  0x8B, 0x75, 0x08,                               //11: mov     esi,dword ptr [ebp+8]
  0xBB, 0xCA, 0xED, 0xAF, 0x1C,                   //14: mov     ebx,1CAFEDCAh
  0x3E, 0x0F, 0xBE, 0x04, 0x0E,                   //19: movsx   eax,byte ptr ds:[esi+ecx]
  0x41,                                           //1E: inc     ecx
  0xD3, 0xC3,                                     //1F: rol     ebx,cl
  0xF7, 0xEB,                                     //21: imul    ebx
  0x31, 0x45, 0xFC,                               //23: xor     dword ptr [ebp-4],eax
  0x29, 0x55, 0xFC,                               //26: sub     dword ptr [ebp-4],edx
  0x3B, 0x4D, 0x0C,                               //29: cmp     ecx,dword ptr [ebp+0Ch]
  0x75, 0xEB,                                     //2C: jne     image00100000+0x78a1 (001078a1)
  0x61,                                           //2E: popad
  0x8B, 0x45, 0xFC,                               //2F: mov     eax,dword ptr [ebp-4]
  0x5F,                                           //32: pop     edi
  0x5E,                                           //33: pop     esi
  0x5B,                                           //34: pop     ebx
  0x8B, 0xE5,                                     //35: mov     esp,ebp
  0x5D,                                           //37: pop     ebp
  0xC3                                            //38: ret
};

// approximate C code
//
//void transform_prefix0(PCHAR prefix, PULONG area)
//{
//    UCHAR lookup_shl[] =        {0x20, 0x1D, 0x1F, 0x1C, 0x1E};
//    UCHAR lookup_subfrom[] =    {0x1B, 0x18, 0x1A, 0x17, 0x19};
//    UCHAR lookup_shr[] =        {0x03, 0x01, 0x04, 0x02, 0x20};
//    UCHAR lookup_passlen[] =    {0x06, 0x05, 0x06, 0x05, 0x06};
//    UCHAR lookup_and[] =        {0x00, 0x07, 0x01, 0x0F, 0x03};
//    ULONG i=0;
//    ULONG mini_i=0;
//    ULONG accum_or=0;
//    ULONG loopvar=0;
//
//    loop_restart:
//
//    if(prefix[i]==0)
//        goto zero_dword_area_quit;
//
//    restart:
//
//    for(loopvar=0; ; loopvar++)
//    {
//        if(loopvar==5)
//            goto restart;
//
//        accum_or=0;
//        mini_i=0;
//
//        if(loopvar!=0)
//        {
//            CHAR c = prefix[i-1];
//            accum_or = index_in_wagalphabet(c);
//            accum_or = accum_or & lookup_and[loopvar];
//            accum_or = accum_or << lookup_shl[loopvar];
//        }
//        
//        while(mini_i != lookup_passlen[loopvar])
//        {
//            if(prefix[i+mini_i]==0)
//                break;
//
//            CHAR c = prefix[i+mini_i];
//            ULONG t = index_in_wagalphabet(c);
//
//            ULONG shl = lookup_subfrom[loopvar] - 5*mini_i;
//            shl = shl & 0xFF;
//            ULONG orval = t << shl;
//            accum_or = accum_or | orval;
//
//            mini_i++;
//        }
//
//        if((loopvar != 4) &&
//            (mini_i == lookup_passlen[loopvar]))
//        {
//            CHAR c = prefix[i+mini_i];
//            ULONG t = index_in_wagalphabet(c);
//            ULONG shr = lookup_shr[loopvar];
//            t = t >> shr;
//            accum_or |= t;
//        }
//
//        __asm
//        {
//            push eax;
//            mov eax, [accum_or];
//            bswap eax;
//            mov [accum_or], eax;
//            pop eax;
//        }
//
//        *area = accum_or;
//
//        area++;
//
//        i = i + lookup_passlen[loopvar] + 1;
//
//        if(mini_i != lookup_passlen[loopvar])
//            break;
//    }
//
//    zero_dword_area_quit:
//    *area=0;
//}
#pragma section(".rips")
__declspec(allocate(".rips")) UCHAR transform_prefix0[] =
{
  0x55,                                           //00: push    ebp
  0x8B, 0xEC,                                     //01: mov     ebp,esp
  0x83, 0xEC, 0x40,                               //03: sub     esp,40h
  0x53,                                           //06: push    ebx
  0x56,                                           //07: push    esi
  0x57,                                           //08: push    edi
  0xC7, 0x45, 0xE8, 0x00, 0x00, 0x00, 0x00,       //09: mov     dword ptr [ebp-18h],0
  0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 0x00,       //10: mov     dword ptr [ebp-0Ch],0
  0xC7, 0x45, 0xC4, 0x00, 0x00, 0x00, 0x00,       //17: mov     dword ptr [ebp-3Ch],0
  0x8B, 0x45, 0x0C,                               //1E: mov     eax,dword ptr [ebp+0Ch]
  0x89, 0x45, 0xC8,                               //21: mov     dword ptr [ebp-38h],eax
  0xC6, 0x45, 0xDC, 0x20,                         //24: mov     byte ptr [ebp-24h],20h
  0xC6, 0x45, 0xDD, 0x1D,                         //28: mov     byte ptr [ebp-23h],1Dh
  0xC6, 0x45, 0xDE, 0x1F,                         //2C: mov     byte ptr [ebp-22h],1Fh
  0xC6, 0x45, 0xDF, 0x1C,                         //30: mov     byte ptr [ebp-21h],1Ch
  0xC6, 0x45, 0xE0, 0x1E,                         //34: mov     byte ptr [ebp-20h],1Eh
  0xC6, 0x45, 0xCC, 0x1B,                         //38: mov     byte ptr [ebp-34h],1Bh
  0xC6, 0x45, 0xCD, 0x18,                         //3C: mov     byte ptr [ebp-33h],18h
  0xC6, 0x45, 0xCE, 0x1A,                         //40: mov     byte ptr [ebp-32h],1Ah
  0xC6, 0x45, 0xCF, 0x17,                         //44: mov     byte ptr [ebp-31h],17h
  0xC6, 0x45, 0xD0, 0x19,                         //48: mov     byte ptr [ebp-30h],19h
  0xC6, 0x45, 0xD4, 0x03,                         //4C: mov     byte ptr [ebp-2Ch],3
  0xC6, 0x45, 0xD5, 0x01,                         //50: mov     byte ptr [ebp-2Bh],1
  0xC6, 0x45, 0xD6, 0x04,                         //54: mov     byte ptr [ebp-2Ah],4
  0xC6, 0x45, 0xD7, 0x02,                         //58: mov     byte ptr [ebp-29h],2
  0xC6, 0x45, 0xD8, 0x20,                         //5C: mov     byte ptr [ebp-28h],20h
  0xC6, 0x45, 0xEC, 0x06,                         //60: mov     byte ptr [ebp-14h],6
  0xC6, 0x45, 0xED, 0x05,                         //64: mov     byte ptr [ebp-13h],5
  0xC6, 0x45, 0xEE, 0x06,                         //68: mov     byte ptr [ebp-12h],6
  0xC6, 0x45, 0xEF, 0x05,                         //6C: mov     byte ptr [ebp-11h],5
  0xC6, 0x45, 0xF0, 0x06,                         //70: mov     byte ptr [ebp-10h],6
  0xC6, 0x45, 0xF8, 0x00,                         //74: mov     byte ptr [ebp-8],0
  0xC6, 0x45, 0xF9, 0x07,                         //78: mov     byte ptr [ebp-7],7
  0xC6, 0x45, 0xFA, 0x01,                         //7C: mov     byte ptr [ebp-6],1
  0xC6, 0x45, 0xFB, 0x0F,                         //80: mov     byte ptr [ebp-5],0Fh
  0xC6, 0x45, 0xFC, 0x03,                         //84: mov     byte ptr [ebp-4],3
  0x8B, 0x4D, 0x08,                               //88: mov     ecx,dword ptr [ebp+8]
  0x03, 0x4D, 0xE8,                               //8B: add     ecx,dword ptr [ebp-18h]
  0x0F, 0xBE, 0x11,                               //8E: movsx   edx,byte ptr [ecx]
  0x85, 0xD2,                                     //91: test    edx,edx
  0x0F, 0x84, 0x50, 0x01, 0x00, 0x00,             //93: je      image00100000+0x767b (0010767b)
  0xC7, 0x45, 0xE4, 0x00, 0x00, 0x00, 0x00,       //99: mov     dword ptr [ebp-1Ch],0
  0xEB, 0x09,                                     //A0: jmp     image00100000+0x753d (0010753d)
  0x8B, 0x45, 0xE4,                               //A2: mov     eax,dword ptr [ebp-1Ch]
  0x83, 0xC0, 0x01,                               //A5: add     eax,1
  0x89, 0x45, 0xE4,                               //A8: mov     dword ptr [ebp-1Ch],eax
  0x83, 0x7D, 0xE4, 0x05,                         //AB: cmp     dword ptr [ebp-1Ch],5
  0x0F, 0x83, 0x26, 0x01, 0x00, 0x00,             //AF: jae     image00100000+0x766d (0010766d)
  0xC7, 0x45, 0xC4, 0x00, 0x00, 0x00, 0x00,       //B5: mov     dword ptr [ebp-3Ch],0
  0x8B, 0x4D, 0xC4,                               //BC: mov     ecx,dword ptr [ebp-3Ch]
  0x89, 0x4D, 0xF4,                               //BF: mov     dword ptr [ebp-0Ch],ecx
  0x83, 0x7D, 0xE4, 0x00,                         //C2: cmp     dword ptr [ebp-1Ch],0
  0x74, 0x2D,                                     //C6: je      image00100000+0x7587 (00107587)
  0x8B, 0x55, 0x08,                               //C8: mov     edx,dword ptr [ebp+8]
  0x03, 0x55, 0xE8,                               //CB: add     edx,dword ptr [ebp-18h]
  0x8A, 0x42, 0xFF,                               //CE: mov     al,byte ptr [edx-1]
  0x50,                                           //D1: push    eax
  0xE8, 0xEF, 0xFE, 0xFF, 0xFF,                   //D2: call    image00100000+0x7458 (00107458)
  0x83, 0xC4, 0x04,                               //D7: add     esp,4
  0x8B, 0x4D, 0xE4,                               //DA: mov     ecx,dword ptr [ebp-1Ch]
  0x33, 0xD2,                                     //DD: xor     edx,edx
  0x8A, 0x54, 0x0D, 0xF8,                         //DF: mov     dl,byte ptr [ebp+ecx-8]
  0x23, 0xC2,                                     //E3: and     eax,edx
  0x8B, 0x4D, 0xE4,                               //E5: mov     ecx,dword ptr [ebp-1Ch]
  0x33, 0xD2,                                     //E8: xor     edx,edx
  0x8A, 0x54, 0x0D, 0xDC,                         //EA: mov     dl,byte ptr [ebp+ecx-24h]
  0x8B, 0xCA,                                     //EE: mov     ecx,edx
  0xD3, 0xE0,                                     //F0: shl     eax,cl
  0x89, 0x45, 0xC4,                               //F2: mov     dword ptr [ebp-3Ch],eax
  0x8B, 0x45, 0xE4,                               //F5: mov     eax,dword ptr [ebp-1Ch]
  0x33, 0xC9,                                     //F8: xor     ecx,ecx
  0x8A, 0x4C, 0x05, 0xEC,                         //FA: mov     cl,byte ptr [ebp+eax-14h]
  0x39, 0x4D, 0xF4,                               //FE: cmp     dword ptr [ebp-0Ch],ecx
  0x74, 0x56,                                     //01: je      image00100000+0x75eb (001075eb)
  0x8B, 0x55, 0xE8,                               //03: mov     edx,dword ptr [ebp-18h]
  0x03, 0x55, 0xF4,                               //06: add     edx,dword ptr [ebp-0Ch]
  0x8B, 0x45, 0x08,                               //09: mov     eax,dword ptr [ebp+8]
  0x0F, 0xBE, 0x0C, 0x10,                         //0C: movsx   ecx,byte ptr [eax+edx]
  0x85, 0xC9,                                     //10: test    ecx,ecx
  0x75, 0x02,                                     //12: jne     image00100000+0x75a8 (001075a8)
  0xEB, 0x43,                                     //14: jmp     image00100000+0x75eb (001075eb)
  0x8B, 0x55, 0xE8,                               //16: mov     edx,dword ptr [ebp-18h]
  0x03, 0x55, 0xF4,                               //19: add     edx,dword ptr [ebp-0Ch]
  0x8B, 0x45, 0x08,                               //1C: mov     eax,dword ptr [ebp+8]
  0x8A, 0x0C, 0x10,                               //1F: mov     cl,byte ptr [eax+edx]
  0x51,                                           //22: push    ecx
  0xE8, 0x9E, 0xFE, 0xFF, 0xFF,                   //23: call    image00100000+0x7458 (00107458)
  0x83, 0xC4, 0x04,                               //28: add     esp,4
  0x89, 0x45, 0xC0,                               //2B: mov     dword ptr [ebp-40h],eax
  0x8B, 0x55, 0xE4,                               //2E: mov     edx,dword ptr [ebp-1Ch]
  0x33, 0xC0,                                     //31: xor     eax,eax
  0x8A, 0x44, 0x15, 0xCC,                         //33: mov     al,byte ptr [ebp+edx-34h]
  0x8B, 0xC8,                                     //37: mov     ecx,eax
  0x8B, 0x55, 0xF4,                               //39: mov     edx,dword ptr [ebp-0Ch]
  0x6B, 0xD2, 0x05,                               //3C: imul    edx,edx,5
  0x2B, 0xCA,                                     //3F: sub     ecx,edx
  0x8B, 0x45, 0xC0,                               //41: mov     eax,dword ptr [ebp-40h]
  0xD3, 0xE0,                                     //44: shl     eax,cl
  0x8B, 0x4D, 0xC4,                               //46: mov     ecx,dword ptr [ebp-3Ch]
  0x0B, 0xC8,                                     //49: or      ecx,eax
  0x89, 0x4D, 0xC4,                               //4B: mov     dword ptr [ebp-3Ch],ecx
  0x8B, 0x55, 0xF4,                               //4E: mov     edx,dword ptr [ebp-0Ch]
  0x83, 0xC2, 0x01,                               //51: add     edx,1
  0x89, 0x55, 0xF4,                               //54: mov     dword ptr [ebp-0Ch],edx
  0xEB, 0x9C,                                     //57: jmp     image00100000+0x7587 (00107587)
  0x8B, 0x45, 0xE4,                               //59: mov     eax,dword ptr [ebp-1Ch]
  0x33, 0xC9,                                     //5C: xor     ecx,ecx
  0x8A, 0x4C, 0x05, 0xEC,                         //5E: mov     cl,byte ptr [ebp+eax-14h]
  0x39, 0x4D, 0xF4,                               //62: cmp     dword ptr [ebp-0Ch],ecx
  0x74, 0x05,                                     //65: je      image00100000+0x75fe (001075fe)
  0xE9, 0x8A, 0x00, 0x00, 0x00,                   //67: jmp     image00100000+0x7688 (00107688)
  0x83, 0x7D, 0xE4, 0x04,                         //6C: cmp     dword ptr [ebp-1Ch],4
  0x74, 0x28,                                     //70: je      image00100000+0x762c (0010762c)
  0x8B, 0x55, 0xE8,                               //72: mov     edx,dword ptr [ebp-18h]
  0x03, 0x55, 0xF4,                               //75: add     edx,dword ptr [ebp-0Ch]
  0x8B, 0x45, 0x08,                               //78: mov     eax,dword ptr [ebp+8]
  0x8A, 0x0C, 0x10,                               //7B: mov     cl,byte ptr [eax+edx]
  0x51,                                           //7E: push    ecx
  0xE8, 0x42, 0xFE, 0xFF, 0xFF,                   //7F: call    image00100000+0x7458 (00107458)
  0x83, 0xC4, 0x04,                               //84: add     esp,4
  0x8B, 0x55, 0xE4,                               //87: mov     edx,dword ptr [ebp-1Ch]
  0x33, 0xC9,                                     //8A: xor     ecx,ecx
  0x8A, 0x4C, 0x15, 0xD4,                         //8C: mov     cl,byte ptr [ebp+edx-2Ch]
  0xD3, 0xE8,                                     //90: shr     eax,cl
  0x8B, 0x4D, 0xC4,                               //92: mov     ecx,dword ptr [ebp-3Ch]
  0x0B, 0xC8,                                     //95: or      ecx,eax
  0x89, 0x4D, 0xC4,                               //97: mov     dword ptr [ebp-3Ch],ecx
  0x8B, 0x45, 0xC4,                               //9A: mov     eax,dword ptr [ebp-3Ch]
  0x0F, 0xC8,                                     //9D: bswap   eax
  0x89, 0x45, 0xC4,                               //9F: mov     dword ptr [ebp-3Ch],eax
  0x8B, 0x55, 0xC8,                               //A2: mov     edx,dword ptr [ebp-38h]
  0x8B, 0x45, 0xC4,                               //A5: mov     eax,dword ptr [ebp-3Ch]
  0x89, 0x02,                                     //A8: mov     dword ptr [edx],eax
  0x8B, 0x4D, 0xC8,                               //AA: mov     ecx,dword ptr [ebp-38h]
  0x83, 0xC1, 0x04,                               //AD: add     ecx,4
  0x89, 0x4D, 0xC8,                               //B0: mov     dword ptr [ebp-38h],ecx
  0x8B, 0x55, 0xE4,                               //B3: mov     edx,dword ptr [ebp-1Ch]
  0x33, 0xC0,                                     //B6: xor     eax,eax
  0x8A, 0x44, 0x15, 0xEC,                         //B8: mov     al,byte ptr [ebp+edx-14h]
  0x8B, 0x4D, 0xE8,                               //BC: mov     ecx,dword ptr [ebp-18h]
  0x8D, 0x54, 0x01, 0x01,                         //BF: lea     edx,[ecx+eax+1]
  0x89, 0x55, 0xE8,                               //C3: mov     dword ptr [ebp-18h],edx
  0x8B, 0x45, 0xE4,                               //C6: mov     eax,dword ptr [ebp-1Ch]
  0x33, 0xC9,                                     //C9: xor     ecx,ecx
  0x8A, 0x4C, 0x05, 0xEC,                         //CB: mov     cl,byte ptr [ebp+eax-14h]
  0x39, 0x4D, 0xF4,                               //CF: cmp     dword ptr [ebp-0Ch],ecx
  0x74, 0x02,                                     //D2: je      image00100000+0x7668 (00107668)
  0xEB, 0x1E,                                     //D4: jmp     image00100000+0x7686 (00107686)
  0xE9, 0xC7, 0xFE, 0xFF, 0xFF,                   //D6: jmp     image00100000+0x7534 (00107534)
  0x8B, 0x55, 0xE8,                               //DB: mov     edx,dword ptr [ebp-18h]
  0x83, 0xEA, 0x01,                               //DE: sub     edx,1
  0x89, 0x55, 0xE8,                               //E1: mov     dword ptr [ebp-18h],edx
  0xE9, 0x9F, 0xFE, 0xFF, 0xFF,                   //E4: jmp     image00100000+0x751a (0010751a)
  0x8B, 0x45, 0xC8,                               //E9: mov     eax,dword ptr [ebp-38h]
  0xC7, 0x00, 0x00, 0x00, 0x00, 0x00,             //EC: mov     dword ptr [eax],0
  0xEB, 0x04,                                     //F2: jmp     image00100000+0x768a (0010768a)
  0xEB, 0xF3,                                     //F4: jmp     image00100000+0x767b (0010767b)
  0xEB, 0xA2,                                     //F6: jmp     image00100000+0x762c (0010762c)
  0x5F,                                           //F8: pop     edi
  0x5E,                                           //F9: pop     esi
  0x5B,                                           //FA: pop     ebx
  0x8B, 0xE5,                                     //FB: mov     esp,ebp
  0x5D,                                           //FD: pop     ebp
  0xC3                                            //FE: ret
};

// approximate C code
//
//UINT index_in_wagalphabet(CHAR c)
//{
//    CHAR wagalphabet[]="A1B2C3D4E59-7H8IJKLMNOPQRSTUVWYZ";
//
//    for(int i=0; i<32; ++i)
//        if(wagalphabet[i]==c)
//            return i;
//
//    return -1;
//}
#pragma section(".rips")
__declspec(allocate(".rips")) CHAR wagalphabet[]="A1B2C3D4E59-7H8IJKLMNOPQRSTUVWYZ"; 

#pragma section(".rips")
__declspec(allocate(".rips")) UCHAR index_in_wagalphabet[] =
{
  0x55,                                           //00: push    ebp
  0x8B, 0xEC,                                     //01: mov     ebp,esp
  0x51,                                           //03: push    ecx
  0xC7, 0x45, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF,       //04: mov     dword ptr [ebp-4],0FFFFFFFFh
  0x8B, 0x45, 0xFC,                               //0B: mov     eax,dword ptr [ebp-4]
  0x83, 0xC0, 0x01,                               //0E: add     eax,1
  0x89, 0x45, 0xFC,                               //11: mov     dword ptr [ebp-4],eax
  0x83, 0x7D, 0xFC, 0x20,                         //14: cmp     dword ptr [ebp-4],20h
  0x74, 0x19,                                     //18: je      image00100000+0x748b (0010748b)
  0x8B, 0x4D, 0xFC,                               //1A: mov     ecx,dword ptr [ebp-4]
  0x0F, 0xBE, 0x91, 0x00, 0xB0, 0x12, 0x00,       //1D: movsx   edx,byte ptr image00100000+0x2b000 (0012b000)[ecx]
  0x0F, 0xBE, 0x45, 0x08,                         //24: movsx   eax,byte ptr [ebp+8]
  0x3B, 0xD0,                                     //28: cmp     edx,eax
  0x75, 0x05,                                     //2A: jne     image00100000+0x7489 (00107489)
  0x8B, 0x45, 0xFC,                               //2C: mov     eax,dword ptr [ebp-4]
  0xEB, 0x05,                                     //2F: jmp     image00100000+0x748e (0010748e)
  0xEB, 0xD8,                                     //31: jmp     image00100000+0x7463 (00107463)
  0x83, 0xC8, 0xFF,                               //33: or      eax,0FFFFFFFFh
  0x8B, 0xE5,                                     //36: mov     esp,ebp
  0x5D,                                           //38: pop     ebp
  0xC3                                            //39: ret
};


