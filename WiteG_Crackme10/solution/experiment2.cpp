#define _CRT_SECURE_NO_DEPRECATE 1
#include <windows.h>

#include <stdio.h>

extern "C"
{
#include "c:\code\lib\miracl5.3.3\include\miracl.h"
}
#pragma comment(lib, "c:\\code\\lib\\miracl5.3.3\\ms32.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

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

void print_point(epoint * P)
{
    if(point_at_infinity(P)) {
        printf("(inf)");
        return;
    }
    big x = mirvar(0);
    big y = mirvar(0);
    epoint_get(P, x, y);
    printf("(");
    printb(x);
    printf(",");
    printb(y);
    printf(")");
    mirkill(x);
    mirkill(y);
}

VOID main(INT ac, PCHAR *av)
{
    //
    miracl * mip = mirsys(100, 10);
    mip->IOBASE = 16;
    
    //
    big zero = mirvar(0);
    big one = mirvar(1);
    
    // initialize curve
    big secp160r1_a = mirvar(0);
    big secp160r1_b = mirvar(0);
    big secp160r1_p = mirvar(0);
    big secp160r1_n = mirvar(0);
    big secp160r1_x = mirvar(0);
    big secp160r1_y = mirvar(0);

    cinstr(secp160r1_a, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFC");
    cinstr(secp160r1_b, "1C97BEFC54BD7A8B65ACF89F81D4D4ADC565FA45");
    cinstr(secp160r1_p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFF");

    ecurve_init(secp160r1_a,secp160r1_b,secp160r1_p,MR_PROJECTIVE);

    //cinstr(secp160r1_n, "100000000000000000001F4C8F927AED3CA752257");
    cinstr(secp160r1_n, "100000000000000000001F4C8F927AED3CA752257");
    cinstr(secp160r1_x, "4A96B5688EF573284664698968C38BB913CBFC82"); // generator point G
    cinstr(secp160r1_y, "23A628553168947D59DCC912042351377AC5FB32");

    epoint *G = epoint_init();
    if(!epoint_set(secp160r1_x, secp160r1_y, 0, G))
    {
        printf("POINT DOES NOT EXIST!\n");
        return;
    }

    printf("G: ");
    print_point(G);
    printf("\n");

    big coeff = mirvar(0);
    epoint *temp_point = epoint_init();
    
    // try *1
    //
    // regular
    cinstr(coeff, "1");
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");
    // minus coeff
    subtract(secp160r1_n, coeff, coeff);
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");

    // try *123
    //
    // regular
    cinstr(coeff, "123");
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");
    // minus coeff
    subtract(secp160r1_n, coeff, coeff);
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");

    // try *DEADBEEF
    //
    // regular
    cinstr(coeff, "DEADBEEF");
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");
    // minus coeff
    subtract(secp160r1_n, coeff, coeff);
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");

    // now try one that is over half of the N
    //
    // try *DEADBEEF
    //
    // regular
    cinstr(coeff, "100000000000000000001F4C8F927AED3CA000000");
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");
    // minus coeff
    subtract(secp160r1_n, coeff, coeff);
    printb(coeff);
    printf(" * G = ");
    ecurve_mult(coeff, G, temp_point);
    print_point(temp_point);
    printf("\n");
}
