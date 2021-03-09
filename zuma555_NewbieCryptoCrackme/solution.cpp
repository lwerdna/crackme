// keygen to zuma555's crypto crackme 1 - oct24_2009 andrewl/crackmes.de
// example codes:
// zuma555/XXZXAAJ-XZJXKXJ
// crackmes.de/XXAAXAX-XKMMMXX
// #FFIJ(*U#f??/XXAJMZX-XKJMXJX
//
// quick tut:
// serial is AAAA-BBBB
// where A and B are base 6 encoded nums
// crackme checks A*2802 + B*304 == 2*hash(name)
// since gcd(2802,304)=2, multiples of them (the A and B we control) can be used to target any even number
#include <windows.h>
#include <stdio.h>
INT main(INT ac, PCHAR *av)
{
    PCHAR name="zuma555";
    if(ac>1)
        name=av[1];
    printf("name: %s\n",name);
    // calc hash
    BYTE hash=strlen(name);
    for(int i=0;i<strlen(name);++i)
    {
        hash+=name[i];
        hash+=0x76;
        hash*=(strlen(name)-i);
        hash*=2;
    }
    printf("hash: %08X\n",hash);
    //gcd(1401,152)=1
    //bezout(1401,152) to find -23*1401+212*152=1
    //now we can target any N with (N*-23)*1401+(N*212)*152=N
    UINT a=hash*23;
    UINT b=hash*212;
    printf("a: %d\n",a);
    printf("b: %d\n",b);
    //now just encode as base 6 number...
    //we know largest possible number is 255*1189 = 303195 which is divisible by 6^7
    PCHAR lookup="XZMAJK";
    CHAR serial_partA[9],serial_partB[9];
    for(INT i=0;i<8;++i)
    {
        serial_partA[6-i]=lookup[a%6];
        a/=6;
        serial_partB[6-i]=lookup[b%6];
        b/=6;
    }
    serial_partA[8]=0;
    serial_partB[8]=0;
    printf("serial: %s-%s\n",serial_partA,serial_partB);
    printf("ctrL+C to quit!\n");
    while(1);
} 
