#define INFO "GiveMeMoney keygen by andrewl - April 19th, 2009"

#include <windows.h>

#include <stdio.h>

extern "C"
{
#include "c:\code\lib\miracl5.3.3\include\miracl.h"
}
#pragma comment(lib, "c:\\code\\lib\\miracl5.3.3\\ms32.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void Encode(big A, PCHAR buff)
{
    static CHAR alpha[] = "BCDFGHJKMPQRTVWXY2346789";

    UINT buff_i = 0;

    big B = mirvar(24);
    big C = mirvar(0);
    big zero = mirvar(0);

    for(UINT i=0; i<18; ++i)
    {
        UINT mod = 0;

        if(compare(A, zero))
        {
            divide(A, B, C);
            big_to_bytes(4, A, (PCHAR) &mod, 0);
            copy(C, A);
        }

        buff[buff_i++] = alpha[mod];
    }

    buff[buff_i] = 0;

    if(compare(A, zero))
        printf("major encoding error!\n");
}

void printb(big a)
{
    CHAR buff[256];
    cotstr(a, buff);
    printf("%s", buff);
}

void printb_(big a)
{
    CHAR buff[256];
    cotstr(a, buff);
    printf("%s\n", buff);
}

void main()
{
    printf("\n" INFO "\n\n");
    // vars
    CHAR buff[256];
    CHAR serial_a[64];
    CHAR serial_b[64];

    miracl * mip = mirsys(256, 0);
    mip->IOBASE = 16;

    //
    big X = mirvar(0);
    big Y = mirvar(0);

    // initialize curve
    big A = mirvar(0);
    cinstr(A, "7CE2B32DC975CB2CD7A3");
    big B = mirvar(0);
    cinstr(B, "5C4FA534800984A831DF");
    big P = mirvar(0);
    cinstr(P, "3BF5E3B76B1FCBB088A8B");
    ecurve_init(A, B, P, MR_AFFINE);

    // initialize random point
    big inX = mirvar(0);
    cinstr(inX, "DEADBEEFDEADBEEF");
    big inY = mirvar(0);
    cinstr(inY, "2dc52dfe6888eb8599e22");
    epoint * p0 = epoint_init();
    epoint_set(inX, inY, 0, p0);
    big t0 = mirvar(GetTickCount());
    ecurve_mult(t0, p0, p0);
    epoint_get(p0, X, Y);
    
    printf("generated random point P == (");
    printb(X);
    printf(", ");
    printb(Y);
    printf("\n");

    Encode(X, serial_a);    // the X coord of the random point is the first
                            // element of the serial

    // multiply by crackme constant scalar
    big N = mirvar(0);
    cinstr(N, "9a2786d35245da83eb6");
    ecurve_mult(N, p0, p0);
    epoint_get(p0, X, Y);
    printf("9a2786d35245da83eb6*P == (");
    printb(X);
    printf(", ");
    printb(Y);
    printf(")\n");

    // find inverse
    // we want serialB^-1 (mod X coord of G*ECPoint(inX, inY)) == 6efb6202cd9477d2738d
    // so serialB == 6efb6202cd9477d2738d^-1 (mod X)
    // using XGCD(6efb6202cd9477d2738d, X)
    //
    big T = mirvar(0);
    cinstr(T, "6efb6202cd9477d2738d"); 

    big gcd_a = mirvar(0);
    big gcd_b = mirvar(0);
    big gcd = mirvar(0);
    INT r = xgcd(T, X, gcd_a, gcd_b, gcd);
    printf("xgcd() returned %d\n", r);

    printf("gcd_a: ");
    printb_(gcd_a);
    printf("gcd_b: ");
    printb_(gcd_b);
    printf("gcd: ");
    printb_(gcd);

    if(exsign(gcd_a) == -1)
    {
        printf("IT'S NEGATIVE!\n");
        add(gcd_a, X, gcd_a);
    }

    printf("6efb6202cd9477d2738d^-1 (mod ");
    printb(X);
    printf(") == ");
    printb_(gcd_a);

    Encode(gcd_a, serial_b);    // the second half of the serial is this inverse

    printf("serial_a: %s\n", serial_a);
    printf("serial_b: %s\n", serial_b);
    printf("------------\n");
    printf("final serial: %s%s\n", serial_a, serial_b);
    printf("------------\n");
    
    // ctrl+c dude!
    while(1);
}
