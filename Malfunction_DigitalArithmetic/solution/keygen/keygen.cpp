// keygen for malfunction's crackme #5 "Digital Arithmetic"
// 2/2009 andrewl
#define _CRT_SECURE_NO_DEPRECATE 1
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

// globals
UINT g_CurrentRandomValue;

ULONGLONG inputs[10];    
ULONGLONG outputs[10];

void SrandFrom8Dwords(PVOID p)
{
    PDWORD pd=(PDWORD)p;

    g_CurrentRandomValue=0;

    for(UINT i=0; i<8; ++i)
        g_CurrentRandomValue += pd[i];
}

void __declspec(naked) __stdcall Make8ByteHash(PUCHAR name, PUCHAR hash)
{
  __asm
  {
    loc_00402AED: push    ebp
    loc_00402AEE: mov     ebp,esp
    loc_00402AF0: mov     esi,dword ptr [ebp+8]
    loc_00402AF3: add     esi,1Fh
    loc_00402AF6: mov     ecx,20h
    loc_00402AFB: mov     edx,0ACh
    loc_00402B00: mov     edi,dword ptr [ebp+0Ch]
    loc_00402B03: add     edi,7
    loc_00402B06: movzx   eax,byte ptr [esi]
    loc_00402B09: add     edx,eax
    loc_00402B0B: xchg    dl,dh
    loc_00402B0D: cmp     ecx,8
    loc_00402B10: ja      loc_00402B15
    loc_00402B12: mov     byte ptr [edi],dl
    loc_00402B14: dec     edi
    loc_00402B15: mov     byte ptr [esi],dl
    loc_00402B17: dec     esi
    loc_00402B18: dec     ecx
    loc_00402B19: jne     loc_00402B06
    loc_00402B1B: leave
    loc_00402B1C: ret     8
  };
}


__declspec(naked) void __stdcall PadName(PCHAR name, INT len)
{
  __asm
  {
    loc_00401EE2: push    ebp
    loc_00401EE3: mov     ebp,esp
    loc_00401EE5: mov     edi,dword ptr [ebp+0Ch]
    loc_00401EE8: mov     esi,edi
    loc_00401EEA: mov     ebx,dword ptr [ebp+8]
    loc_00401EED: cmp     edi,20h
    loc_00401EF0: jae     loc_00401F03
    loc_00401EF2: dec     esi
    loc_00401EF3: mov     al,byte ptr [ebx+esi]
    loc_00401EF6: mov     byte ptr [ebx+edi],al
    loc_00401EF9: inc     edi
    loc_00401EFA: test    esi,esi
    loc_00401EFC: jne     loc_00401EED
    loc_00401EFE: mov     esi,dword ptr [ebp+0Ch]
    loc_00401F01: jmp     loc_00401EED
    loc_00401F03: leave
    loc_00401F04: ret     8
  };
}

__declspec(naked) void __stdcall Rand()
{
  __asm
  {
    loc_00402A11: mov     ecx,[g_CurrentRandomValue]
    loc_00402A17: imul    ecx,ecx,343FDh
    loc_00402A1D: add     ecx,269EC3h
    loc_00402A23: mov     [g_CurrentRandomValue], ecx
    loc_00402A29: mov     eax,ecx
    loc_00402A2B: shr     eax,10h
    loc_00402A2E: and     eax,7FFFh
    loc_00402A33: ret
  };
}

__declspec(naked) void __stdcall SwapRandom8Bytes()
{
  __asm
  {
    loc_00402A34: push    ebp
    loc_00402A35: mov     ebp,esp
    loc_00402A37: sub     esp,4
    loc_00402A3A: call    Rand
    loc_00402A3F: and     eax,7
    loc_00402A42: mov     dword ptr [ebp-4],eax
    loc_00402A45: call    Rand
    loc_00402A4A: and     eax,7
    loc_00402A4D: mov     ebx,eax
    loc_00402A4F: mov     edx,dword ptr [ebp-4]
    loc_00402A52: mov     esi,dword ptr [ebp+8]
    loc_00402A55: cmp     ebx,edx
    loc_00402A57: je      loc_00402A62
    loc_00402A59: xchg    al,byte ptr [esi+ebx]
    loc_00402A5C: xchg    al,byte ptr [esi+edx]
    loc_00402A5F: xchg    al,byte ptr [esi+ebx]
    loc_00402A62: leave
    loc_00402A63: ret     4
  };
}

__declspec(naked) void __stdcall MakeRandomArray20h(PUCHAR array)
{
  __asm
  {
    loc_004030E2: push    ebp
    loc_004030E3: mov     ebp,esp
    loc_004030E5: sub     esp,0Ch
    loc_004030E8: mov     esi,dword ptr [ebp+8]
    loc_004030EB: lea     eax,[esi]
    loc_004030ED: mov     dword ptr [ebp-0Ch],eax
    loc_004030F0: lea     ebx,[esi+8]
    loc_004030F3: mov     dword ptr [ebp-8],ebx
    loc_004030F6: lea     edx,[esi+10h]
    loc_004030F9: mov     dword ptr [ebp-4],edx
    loc_004030FC: mov     ecx,8
    loc_00403101: dec     ecx
    loc_00403102: mov     byte ptr [eax],cl
    loc_00403104: mov     byte ptr [ebx],cl
    loc_00403106: mov     byte ptr [edx],cl
    loc_00403108: inc     eax
    loc_00403109: inc     ebx
    loc_0040310A: inc     edx
    loc_0040310B: test    ecx,ecx
    loc_0040310D: jne     loc_00403101
    loc_0040310F: mov     ecx,64h
    loc_00403114: push    ecx
    loc_00403115: push    dword ptr [ebp-0Ch]
    loc_00403118: call    SwapRandom8Bytes
    loc_0040311D: push    dword ptr [ebp-8]
    loc_00403120: call    SwapRandom8Bytes
    loc_00403125: push    dword ptr [ebp-4]
    loc_00403128: call    SwapRandom8Bytes
    loc_0040312D: pop     ecx
    loc_0040312E: dec     ecx
    loc_0040312F: jne     loc_00403114
    loc_00403131: mov     edi,dword ptr [ebp+8]
    loc_00403134: lea     edi,[edi+18h]
    loc_00403137: mov     ecx,8
    loc_0040313C: push    ecx
    loc_0040313D: push    edi
    loc_0040313E: call    Rand
    loc_00403143: mov     ecx,6
    loc_00403148: xor     edx,edx
    loc_0040314A: div     ecx
    loc_0040314C: pop     edi
    loc_0040314D: pop     ecx
    loc_0040314E: mov     byte ptr [edi],dl
    loc_00403150: inc     edi
    loc_00403151: dec     ecx
    loc_00403152: jne     loc_0040313C
    loc_00403154: leave
    loc_00403155: ret     4
  };
}

void DoOperations(PUCHAR operands, PUCHAR descr, PUCHAR result)
{    
    PUCHAR oper_i0 = descr;
    PUCHAR oper_i1 = descr+8;
    PUCHAR result_i = descr+16;
    PUCHAR ops = descr+24;

    for(INT i=0; i<8; ++i)
    {
        CHAR op = ops[i];
        UCHAR oper_a = operands[oper_i0[i]]; // UCHAR so my debugger shows them properly
        UCHAR oper_b = operands[oper_i1[i]];
        CHAR r;

        if(op==0)
            r=oper_a+oper_b;
        if(op==1)
            r=oper_a-oper_b;
        if(op==2)
            r=oper_a*oper_b;
        if(op==3) 
            r=(oper_a<=oper_b)?oper_a:oper_b;
        if(op==4) 
            r=(oper_a>oper_b)?oper_a:oper_b;
        if(op==5)
            r=oper_a^oper_b;

        result[result_i[i]] = r;
    }
}

void PrintBytes(PVOID pt, INT num)
{
    PUCHAR p = (PUCHAR)pt;

    for(INT i=0; i<num; ++i)
        printf("%02X ", p[i]);

    printf("\n");
}

UCHAR QWBit(ULONGLONG input, UCHAR bit)
{
    return (input & ((ULONGLONG)1<<bit))>>bit;
}

// returns true if the increment occured
// returns false if the increment overflowed
BOOL IncrementLoopvarSet(PUCHAR set, UINT size)
{
    BOOL bCarry;

    for(INT i=0; i<size; ++i)
    {
        bCarry=0;
        
        if(set[i]==63)
        {
            bCarry=1;
            set[i]=0;
        }
        else
            set[i]++;

        if(!bCarry)
            break;
    }

    return !bCarry;
}

BOOL TestSolution(PUCHAR subset, UINT subset_size, UINT target_bit)
{
    BOOL bRet=1;

    // for each equation
    for(UINT i=0; i<10; ++i)
    {
        UCHAR bit_result=0;

        // for each bit in the input (subset of column vectors)
        for(UINT j=0; j<subset_size; ++j)
        {
            bit_result ^= QWBit(inputs[i], subset[j]);
        }

        if(QWBit(outputs[i], target_bit) != bit_result)
        {
            bRet=0;
            break;
        }
    }

    return bRet;
}

// 
//
vector<UCHAR> FindSubsetLimitedSolution(UINT limit, UINT target_bit)
{
    vector<UCHAR> vRet;

    UCHAR subset[64]; // max 64, only <inputs> will be used, though
    memset(subset,0,64);

    do
    {
        if(TestSolution(subset, limit, target_bit))
        {
            for(INT i=0; i<limit; ++i)
                vRet.push_back(subset[i]);

            break;
        }

    } while(IncrementLoopvarSet(subset, limit));

    return vRet;
}

// find a subset of the columns from the input qwords
// nand to the target_bit column of the output qwords?
//
vector<UCHAR> FindSubsetSolution(UINT target_bit)
{
    vector<UCHAR> vRet;

    for(UINT i=2; i<64; ++i)
    {
        vRet = FindSubsetLimitedSolution(i, target_bit);

        if(!vRet.empty())
            break;
    }

    return vRet;
}

VOID main(INT ac, PCHAR *av)
{
    // get name
    // pad the name
    CHAR name[33];
    memset(name,0,33);
    if(ac>1)
        strcpy(name,av[1]);
    else
        strcpy(name,"malfunction");
    PadName(name, strlen(name));
    printf("\n");
    printf("padded name: %s\n", name);

    // initialize randomizer 
    SrandFrom8Dwords(name);
    printf("\n");
    printf("initialized random: %08X\n", g_CurrentRandomValue);

    // make random arrays
    UCHAR RandArray_2[32];
    UCHAR RandArray_1[32];
    UCHAR RandArray_0[32];
    MakeRandomArray20h(RandArray_2);
    MakeRandomArray20h(RandArray_1);
    MakeRandomArray20h(RandArray_0);
    printf("\n");
    printf("randomized arrays:\n");
    PrintBytes(RandArray_2, 32);
    PrintBytes(RandArray_1, 32);
    PrintBytes(RandArray_0, 32);

    // 
    printf("\n");
    printf("generating the inputs/outputs\n");
    UCHAR Hash8Bytes[8];
    UCHAR Result2[8], Result1[8];

    for(INT i=0; i<10; ++i)
    {
        printf("round: %d\n", i);

        Make8ByteHash((PUCHAR)name, Hash8Bytes);
        printf("hash: ");
        PrintBytes(Hash8Bytes, 8);

        inputs[i] = *(PULONGLONG)Hash8Bytes;

        DoOperations(Hash8Bytes, RandArray_2, Result2); // Result2
        printf("result pass 0: ");
        PrintBytes(Result2, 8);
        DoOperations(Result2, RandArray_1, Result1);
        printf("result pass 1: ");
        PrintBytes(Result1, 8);
        DoOperations(Result1, RandArray_0, Result2);
        printf("result pass 2: ");
        PrintBytes(Result2, 8);

        outputs[i] = *(PULONGLONG)Result2;
    }

    //
    printf("\n");
    printf("Inputs/Outputs\n");
    for(INT i=0; i<10; ++i)
        printf("%016I64X/%016I64X\n", inputs[i], outputs[i]);

    // define solution type
    typedef struct _TRIPLET
    {
        DWORD src0;
        DWORD src1;
        DWORD dst;
    } TRIPLET, *PTRIPLET;
    vector<TRIPLET> XorSolution;
    vector<TRIPLET> NandSolution;

    //
    printf("\n");
    printf("determining bit positions for which inputs' bits XOR to outputs' bits\n");

    UINT NextFreeBit=128;

    for(UINT i=0; i<64; ++i)
    {
        vector<UCHAR> vRet = FindSubsetSolution(i);

        printf("for outputs' bit %d, XOR inputs' bits: ", i);

        if(vRet.empty())
            printf("<no solution>\n");
        else
        {
            for(UINT j=0; j<vRet.size(); ++j)
                printf("%d ", vRet[j]);

            // nothing ever needs more than 3 bits, so i just hardcode
            // in these two cases
            if(vRet.size()==2)
            {
                TRIPLET tri;

                tri.src0=vRet[0];
                tri.src1=vRet[1];
                tri.dst=64+i;

                XorSolution.push_back(tri);
                printf("<%d,%d,%d>", tri.src0, tri.src1, tri.dst);
            }
            else if(vRet.size()==3)
            {
                TRIPLET tri;

                tri.src0=vRet[0];
                tri.src1=vRet[1];
                tri.dst=NextFreeBit;
                NextFreeBit++;

                XorSolution.push_back(tri);
                printf("<%d,%d,%d>", tri.src0, tri.src1, tri.dst);

                tri.src0=vRet[2];
                tri.src1=tri.dst;
                tri.dst=64+i;

                XorSolution.push_back(tri);
                printf("<%d,%d,%d>", tri.src0, tri.src1, tri.dst);
            }
            //else
                // this never happens, i think :)
        }

        printf("\n");
    }

    // synthesize the xor gates using nand gates
    //

    printf("\n");
    printf("synthesizing XOR gate soluting with NAND gates\n");
    for(UINT i=0; i<XorSolution.size(); ++i)
    {
        TRIPLET tri = XorSolution[i];
        printf("XOR <%d,%d,%d> TO NAND: ", tri.src0, tri.src1, tri.dst);
        // construct XOR using NAND like:
        // XOR(A,B) = NAND(NAND(A,(NAND(A,B)),NAND(B,NAND(A,B)))

        // t0 = NAND(A,B);
        // t1 = NAND(A,t0);
        // t2 = NAND(B,t0);
        // XOR(A,B) = NAND(t1,t2);

        // construct t0:
        TRIPLET t0;
        t0.src0=tri.src0;
        t0.src1=tri.src1;
        t0.dst=NextFreeBit;
        NextFreeBit++;
        NandSolution.push_back(t0);
        printf("<%d,%d,%d>", t0.src0, t0.src1, t0.dst);

        // construct t1:
        TRIPLET t1;
        t1.src0=tri.src0;
        t1.src1=t0.dst;
        t1.dst=NextFreeBit;
        NextFreeBit++;
        NandSolution.push_back(t1);
        printf("<%d,%d,%d>", t1.src0, t1.src1, t1.dst);

        // construct t2;
        TRIPLET t2;
        t2.src0=tri.src1;
        t2.src1=t0.dst;
        t2.dst=NextFreeBit;
        NextFreeBit++;
        NandSolution.push_back(t2);
        printf("<%d,%d,%d>", t2.src0, t2.src1, t2.dst);

        // construct result
        TRIPLET res;
        res.src0=t1.dst;
        res.src1=t2.dst;
        res.dst=tri.dst;
        NandSolution.push_back(res);
        printf("<%d,%d,%d>", res.src0, res.src1, res.dst);

        printf("\n");
    }

    printf("\n");
    printf("writing key.dat\n");
    HANDLE hFile=CreateFile("key.dat",GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    DWORD dwRet=0;
    BOOL bRet=WriteFile(hFile,&NandSolution[0],NandSolution.size()*sizeof(TRIPLET),&dwRet,0);
    CloseHandle(hFile);

    if(!bRet)
        printf("was error writing file!\n");
}
