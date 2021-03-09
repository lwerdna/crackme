/*
Keygen for Waganono's WagaTemplate :P - June 05, 2009 andrewl

key: 1B8CB34B0AE101AF0A8B08A200106301

Here is disassembly:

.text:00403040 DoMath  proc near                       ; CODE XREF: VerifySerial+A5
.text:00403040         xor     eax, eax
.text:00403042         or      eax, 5
.text:00403045         emms
.text:00403047         movaps  xmm0, oword ptr serial_partD
.text:0040304E         movaps  xmm1, oword ptr ds:oword_403020 ; 3.601337e-043: 7.988102e-041: 6.164064e-039: 1.716068e-038
.text:00403055         movaps  xmm2, oword ptr ds:oword_403030 ; 6.694230e-032: 1.163846e-021: 1.083367e-031: 2.468510e-038
.text:0040305C
.text:0040305C loc_40305C:                             ; CODE XREF: DoMath+20
.text:0040305C         addps   xmm1, xmm0
.text:0040305F         dec     eax
.text:00403060         jnz     short loc_40305C        ;
.text:00403060                                         ;
.text:00403062         cmpps   xmm2, xmm1, 0
.text:00403066         movmskps eax, xmm2              ; Extract Packed Single-Precision Floating-Point Sign Mask
.text:00403066                                         ;
.text:00403069         cmp     eax, 0Dh                ; 1101 = neg, neg, pos, neg ??
.text:0040306C         ja      goodboy
.text:00403072         xor     eax, eax
.text:00403074
.text:00403074 goodboy:                                ; CODE XREF: DoMath+2C
.text:00403074         emms
.text:00403076         retn

*/

#include <windows.h>
#include <stdio.h>
#include <string.h>

void float_as_hex(float f)
{
    PCHAR lookup="0123456789ABCDEF";
    UCHAR buff[4];
    memcpy(buff,&f,4);
    buff[0]^=buff[3]^=buff[0]^=buff[3]; // bswap :P
    buff[1]^=buff[2]^=buff[1]^=buff[2];
    for(UINT i=0;i<4;++i)
        printf("%c%c",lookup[(buff[i]&0xF0)>>4],lookup[buff[i]&0x0F]);
}

void main()
{
    float a,b,c,d,t0,t1;

    UINT vals[8] = {    0x00000101, 0x0000dead, 0x00431ee7, 0x00badcfe,
                        0x0badcaca, 0x1cafe01e, 0x0c0ca10e, 0x01066602  };

    memcpy(&t0,vals,4);
    memcpy(&t1,vals+4,4);
    a=(t1-t0)/5;
    memcpy(&t0,vals+1,4);
    memcpy(&t1,vals+5,4);
    b=(t1-t0)/5;
    memcpy(&t0,vals+2,4);
    memcpy(&t1,vals+6,4);
    c=(t1-t0)/5;
    memcpy(&t0,vals+3,4);
    memcpy(&t1,vals+7,4);
    d=(t1-t0)/5;

    printf("key: ");
    // listed first -> xmm0[1]
    float_as_hex(b);
    // listed second -> xmm0[2]
    float_as_hex(c);
    // listed third -> xmm0[0]
    float_as_hex(a);
    // listed fourth -> xmm0[3]
    float_as_hex(d);
}   
