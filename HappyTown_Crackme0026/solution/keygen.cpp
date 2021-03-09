#define INFO "happytown's CrackMe_0026 keygen by andrewl - May 05th, 2009"

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

void hashing(unsigned char *dataIn, int lenIn, big hash)
{
    char h[20];
    sha sh;

    shs_init(&sh);
    for (int i=0;i<lenIn;i++)
        shs_process(&sh,dataIn[i]);

    shs_hash(&sh,h);
    bytes_to_big(20,h,hash);
}

VOID main(INT ac, PCHAR *av)
{
    printf("\n" INFO "\n\n");

    CHAR user[256];
    memset(user, 0, 256);
    strcpy(user, "happytown");

    if(ac > 1)
        strcpy(user, av[1]);

    if(strlen(user)<3 || strlen(user)>0x18)
    { printf("name should be between 3 and 24 chars!\n"); return; }

    //
    miracl * mip = mirsys(128, 16);
    mip->IOBASE = 16;

    // general purpose vars
    big zero = mirvar(0);
    big one = mirvar(1);
    epoint * temp_point = epoint_init();
    big gcd = mirvar(0);

    //
    big h = mirvar(0);
    hashing((PUCHAR)user, strlen(user), h);
    printf("hash: ");
    printb_(h);

    // initialize curve
    big a = mirvar(0);
    big b = mirvar(0);
    big p = mirvar(0);
    cinstr(a, "2982");
    cinstr(b, "3408");
    cinstr(p, "AEBF94CEE3E707");
    ecurve_init(a,b,p,MR_PROJECTIVE);

    // points on curve
    big G_x = mirvar(0);
    big Q_A_x = mirvar(0);
    cinstr(G_x, "7A3E808599A525");
    cinstr(Q_A_x, "9F70A02013BC9B");
    epoint *G = epoint_init();
    epoint_set(G_x, G_x, 0, G);         // G = (7A3E808599A525,28BE7FAFD2A052)
    epoint *Q_A = epoint_init();
    epoint_set(Q_A_x, Q_A_x, 0, Q_A);   // Q_A = (9F70A02013BC9B,9E0B275B93CF5E)

    // generator order, private key
    big n = mirvar(0);
    cinstr(n, "AEBF94D5C6AA71");
    big d_A = mirvar(0);
    cinstr(d_A, "9D3F1E3CDDA5E5");

    // compute k, s, r
    big k = mirvar(1);
    big s = mirvar(0);
    big r = mirvar(0);

    UINT seed = GetTickCount();
    irand(seed);

    while(1)
    {
        bigbits(55, k);                     // k = <rand 56-bit>

        egcd(k, n, gcd);                    // ensure k has inverse
        if(compare(gcd, one))
            continue;

        ecurve_mult(k, G, temp_point);
        epoint_get(temp_point, r, r);       // r = x_coord (k * G)

        big k_inv = mirvar(0);              // compute k^(-1)
        copy(k, k_inv);
        xgcd(k_inv, n, k_inv, k_inv, k_inv);

        mad(r, d_A, h, n, n, s);            // s = r * d_A + h (mod n)
        mad(s, k_inv, k_inv, n, n, s);      // s = k^(-1) * (r * d_A + h) (mod n)

        egcd(s, n, gcd);                    // ensure s has inverse
        if(!compare(gcd, one))
            break;
    }

    /*
    // verify resulting point
    big s_inv = mirvar(0);
    copy(s, s_inv);
    xgcd(s_inv, n, s_inv, s_inv, s_inv); // get s^(-1)
    big u1 = mirvar(0);
    mad(s_inv, h, h, n, n, u1);         // u1 = s^(-1) * h
    big u2 = mirvar(0);
    mad(s_inv, r, r, n, n, u2);         // u2 = s^(-1) * r
    ecurve_mult2(u1, G, u2, Q_A, temp_point);
    printf("verification point (x coord should match r): ");
    print_point(temp_point);
    printf("\n");

    // verify effective coefficient on G
    big eff_c = mirvar(0);
    mad(u2, d_A, u1, n, n, eff_c);      // eff_c = u1 + u2 * d_A
    printf("effective coefficient on G (should match k): ");
    printb_(eff_c);
    printf("\n");
    */

    // output key
    printf("user: %s\n", user);
    printf(" key: ");
    printb(r);
    printf("-");
    printb(s);
    printf("\n");
    while(1);

}

