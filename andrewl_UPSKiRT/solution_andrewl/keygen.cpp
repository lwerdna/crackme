// test keygen for my "upskirt" crackme
//

// os
#include <windows.h>

// stdio
#include <stdio.h>
#include <time.h>

extern "C" {
// miracl
#include <miracl.h>
}

CHAR g_buff[512];

void printbig(big b)
{
    cotstr(b, g_buff);
    printf("%s\n", g_buff);
}

void main(int argc, char * argv[])
{
    srand(time(NULL));


    // put required chars in first block
    char block0[25];
    memset(block0, '\0', 25);
    char required[]="#cRaCkInG4NeWbIeS";
    for(int i=0; i<strlen(required); ++i)
    {
        int spot=0;

        do
        {
            spot=rand()%24;
        }
        while(block0[spot]);

        block0[spot] = required[i];
    }

    // fill in the rest
    char hexchars[]="0123456789ABCDEF";
    for(int i=0; i<24; ++i)
        if(!block0[i])
            block0[i]=hexchars[rand()%16];

    // print it out
    printf("block0: %s\n", block0);


    // general purpose vars
    

    // init miracl
    miracl *mip=mirsys(256, 0);
    mip->IOBASE=16;

    // general purpose miracl vars
    big s=mirvar(0);
    big t=mirvar(0);

    // make X
    CHAR munch[24];
    memcpy(munch, block0, 24);

    for(int i=0; i<12; ++i)
        munch[i] ^= (munch[i+12] << 4);

    big X=mirvar(0);
    bytes_to_big(12, munch, X);
    printf("X: "); printbig(X);

    big p0=mirvar(0);
    big p1=mirvar(0);
    
    cinstr(p0,"19FBD41D69AA3D86009A968D");
    cinstr(p1,"1B6F141F98EEB619BC036051");

    // k, given any X, find s, t such that:
    // s*p1 - t*p2 = X
    // and
    // -s*p1 + t*p2 = Y

    big inv_p0=mirvar(0);
    big inv_p1=mirvar(1);
    big gcd=mirvar(0);

    xgcd(p0,p1,inv_p0,inv_p1,gcd);

    printf("inv_p0: "); printbig(inv_p0);
    printf("X: "); printbig(X);
    printf("p1: "); printbig(p1);

    //
    // to solve s*p0 + t*p1 = X
    //
    // we solve both equivalent equations:

    // s*p0 = X (mod p1)
    // s = 1/p0 X (mod p1)
    // 
    mad(inv_p0,X,X,p1,p1,s);
   
    printf("0: "); printbig(s);
    multiply(s,p0,t);
    subtract(t,X,t);
    divide(t,p1,t);

    printf("s: "); printbig(s);
    printf("t: "); printbig(t);

    CHAR serial[72+1];
    memset(serial, 0, 72+1);

    strcpy(serial, block0);
    strcat(serial, "-");

    cotstr(s, g_buff);
    for(int i=0; i<(24-strlen(g_buff)); ++i)
        strcat(serial, "0");
    strcat(serial, g_buff);

    strcat(serial, "-");

    cotstr(t, g_buff);
    for(int i=0; i<(24-strlen(g_buff)); ++i)
        strcat(serial, "0");
    strcat(serial, g_buff);

    printf("[*]\n");
    printf("[*] key: %s\n", serial);
    printf("[*]\n");

}


