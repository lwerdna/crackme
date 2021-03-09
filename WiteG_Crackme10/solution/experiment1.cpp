// experimental prog to see if some way to get -G
//
// shows that (<order of G> - 1) * G == -G
// 2009 andrewl

// eg 23*(11,10) == (11,13)

// from certicom:
/*
As a very small example, consider an elliptic curve over the field F23. With a = 1 and b = 0, the elliptic curve equation is y2 = x3 + x. The point (9,5) satisfies this equation since:

y2 mod p = x3 + x mod p

25 mod 23 = 729 + 9 mod 23

25 mod 23 = 738 mod 23

2 = 2

The 23 points which satisfy this equation are:

(0,0) (1,5) (1,18) (9,5) (9,18) (11,10) (11,13) (13,5)

(13,18) (15,3) (15,20) (16,8) (16,15) (17,10) (17,13) (18,10)

(18,13) (19,1) (19,22) (20,4) (20,19) (21,6) (21,17) 
*/

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

    for(int i=strlen(buff); i<2; ++i)
        printf("0");

    printf("%s", buff);
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
    printb(x);
    printf(",");
    printb(y);
    mirkill(x);
    mirkill(y);
}

VOID main(INT ac, PCHAR *av)
{
    //
    miracl * mip = mirsys(100, 10);
    mip->IOBASE = 10;
    
    //
    big zero = mirvar(0);
    big one = mirvar(1);
    
    // initialize curve
    ecurve_init(mirvar(1), mirvar(0), mirvar(23), MR_AFFINE);

    epoint *G = epoint_init();

    for(UINT x=0; x<22; ++x)
    {
        for(UINT y=0; y<22; ++y)
        {
            big bx = mirvar(x);
            big by = mirvar(y);

            if(epoint_set(bx, by, 0, G))
            {
                //print_point(G);
                //printf("\n");

                epoint *temp_point = epoint_init();

                for(UINT i=1; i<=24; ++i)
                {
                    big coeff = mirvar(i);
                    ecurve_mult(coeff, G, temp_point);
                    print_point(temp_point);
                    printf(" ");
                    mirkill(coeff);
                }

                printf("\n");
            }

            mirkill(bx);
            mirkill(by);
        }
    }
}
