// solution to NeoN's 192 bits keygenme
// 2/06/2008 andrewl
//
// Need Victor Shoup's NTL lib
//
// compile: C:\projects\keygen_montez>cl /W4 keygen.cpp /EHsc \
// /I c:\path\to\NTL\Include /link c:\path\to\NTL\NTL.lib
// 

#include <stdio.h>
#include <windows.h>
#include <iostream>

#define NTL_NO_MIN_MAX
#include "NTL/ZZ.h"

using namespace NTL;

char g_lookup[] = "5W0DKA69ONIT1SUXZY23478BCEFGHJLMPQV";

using namespace std;

int charToLookupIndex(char c)
{
    int i;

    for(i=0; i<sizeof(g_lookup); ++i)
        if(g_lookup[i] == c)
            return i;

    return -1;
}

unsigned __int64 TRANSFERREDFUNC(char * serial, int len)
{
    int i;
    unsigned __int64 result = 0;

    for(i=len-1; i>=0; --i)
    {
        result = result * 0x23 + charToLookupIndex(serial[i]);
        //printf("On char (%c), result: 0x%08X'%08X (%I64d)\n", serial[i], result.HighPart, result.LowPart, result.QuadPart);
    }

    return result;
}

void TRANSFERREDFUNCINVERSE(unsigned __int64 outcome, char * buffer, unsigned int len)
{
    unsigned __int64 runner = 1;
    unsigned int i;

    for(i=0; i<len; ++i)
    {
        buffer[i] = g_lookup[(outcome % (0x23*runner)) / runner];
        runner *= 0x23;
    }

    buffer[i] = '\0';
}

void print_ZZ(char * message, ZZ& in)
{
    unsigned char byteBuffer[64]={'\0'};
    unsigned int n=NumBytes(in);
    BytesFromZZ(byteBuffer, in, n);
    printf("%s (%d bytes) 0x", message, n);
	for(int i=n-1; i>=0; --i)
			printf("%02X", 0x000000FF & byteBuffer[i]);
    printf(" (");
    if(n==1)
        printf("%d", 0x000000FF ^ (byteBuffer[0]-0x30));
    else if(n==4)
        printf("%d", *(int *)byteBuffer);
    else if(n==8)
        printf("%I64d", *(__int64 *)byteBuffer);
    else
        printf("?");
    printf(")\n");
    cout << "NTL SAYS: " << in << endl;
}

__int64 SolveLinearCongruence(unsigned __int64 iB)
{
    unsigned char byteBuff[8];
    
    ZZ A = ZZFromBytes((unsigned char *)"\x68\x4A\x09\x73\x7E\x1E\xF2\x5B", 8); // 0x5BF21E7E73094A68
    ZZ B = ZZFromBytes((unsigned char *)&iB, sizeof(iB));
    ZZ N = ZZFromBytes((unsigned char *)"\x00\x00\x00\x00\x00\x00\x00\x00\x01", 9); // 2^64
    ZZ D, R, S;

    XGCD(D, R, S, A, N);

    if(R*A + S*N != D)
        return -1;

    //ZZ X = R*B/D;
    ZZ Solution = (R*B/D) % (N/D);

    //print_ZZ("Solution: ", Solution);
    
    //ZZ Check = MulMod(A, Solution, N);
    //print_ZZ("Check: ", Check);
    //print_ZZ("Match Check: ", B);
    if(NumBytes(Solution)!=8)
        return -1;
    
    BytesFromZZ(byteBuff, Solution, 8);

    return *(unsigned __int64 *)byteBuff;
}

int main()
{
    int i;

    // these values are computed to equal a caca when xor'd
    unsigned __int64 caca_xor1 = 0;
    unsigned __int64 caca_xor2 = 0;

    // all these values, when shifted right 16h, yield 0xCACA
    unsigned __int64 cacas[] =    {    0x00000032B2800000,
                                        0x00000032B2900000,
                                        0x00000032B2A00000,
                                        0x00000032B2B00000  };
    
    //for(i=0; i<4; ++i)
    //    printf("%016X\n", cacas[i]>>0x16);

    // find two numbers that xor to a caca
    {
        // choose a random caca
        unsigned __int64 caca = cacas[GetTickCount() % 4];

        caca_xor1 = (__int64) GetTickCount() | ((__int64)GetTickCount() << 32);

        // we want our random number to have unset top 3 bits so it can survive
        // the shift
        caca_xor1 &= 0x1FFFFFFFFFFFFFFF; 

        caca_xor2 = 0;

        for(i=0; i<64; ++i)
        {
            unsigned __int64 bitMask = (__int64) 0x0000000000000001 << i;

            if(caca & bitMask) // if bit set in target value caca_xor2 and caca_xor1 must be different
            {
                if(!(caca_xor1 & bitMask))
                    caca_xor2 |= bitMask;
            }
            else                // otherwise they must match
                caca_xor2 |= (bitMask & caca_xor1);
        }
    }
    
    caca_xor1 *= 8;
    caca_xor2 *= 8;

    printf("caca_xor1 post mul: 0x%016I64X (%I64d)\n", caca_xor1, caca_xor1);
    printf("caca_xor2 post mul: 0x%016I64X (%I64d)\n", caca_xor2, caca_xor2);

    unsigned __int64 Half1 = SolveLinearCongruence(caca_xor1);
    unsigned __int64 PreHalf2 = SolveLinearCongruence(caca_xor2);
    unsigned __int64 Half2 = Half1 ^ PreHalf2;

    printf("Half1: is %016I64X (%I64d)\n", Half1, Half1);
    printf("After multiplication it's 0x%016I64X\n", 0x5BF21E7E73094A68*Half1);
    printf("Which should match caca_xor1\n");

    printf("PreHalf1: is %016I64X (%I64d)\n", PreHalf2, PreHalf2);
    printf("After multiplication it's 0x%016I64X\n", 0x5BF21E7E73094A68*PreHalf2);
    printf("Which should match caca_xor2\n");

    printf("Half2: is %016I64X (%I64d)\n", Half2, Half2);

    char chHalf1[0x0C+1]={0};
    char chHalf2[0x0C+1]={0};
    TRANSFERREDFUNCINVERSE(Half1, chHalf1, 0x0C);
    TRANSFERREDFUNCINVERSE(Half2, chHalf2, 0x0C);

    printf("%s computes to %016I64X\n", chHalf1, TRANSFERREDFUNC(chHalf1, 0x0C));
    printf("%s computes to %016I64X\n", chHalf2, TRANSFERREDFUNC(chHalf2, 0x0C));

    char chFinalSerial[0x1D+1]={'-'};
    memset(chFinalSerial, '-', 0x1D);
    memcpy(chFinalSerial, chHalf1, 5);
    memcpy(chFinalSerial+0x06, chHalf1+0x05, 5);
    memcpy(chFinalSerial+0x0C, chHalf1+0x0A, 2);
    memcpy(chFinalSerial+0x0E, chHalf2, 3);
    memcpy(chFinalSerial+0x12, chHalf2+0x03, 5);
    memcpy(chFinalSerial+0x18, chHalf2+0x08, 4);
    memcpy(chFinalSerial+0x1C, "W\0", 2);

    printf("Final serial: %s\n", chFinalSerial);
}
