#define INFO "WiteG Crackme #10 keygen by andrewl - May 04th, 2009"

#define _CRT_SECURE_NO_DEPRECATE 1
#include <windows.h>

#include <stdio.h>

extern "C"
{
#include "c:\code\lib\miracl5.3.3\include\miracl.h"
}
#pragma comment(lib, "c:\\code\\lib\\miracl5.3.3\\ms32.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

void printb_(big a)
{
    CHAR buff[256];
    cotstr(a, buff);
    printf("%s\n", buff);
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
    CHAR user2[256];
    memset(user, 0, 256);
    strcpy(user, "witeg");
    
    if(ac > 1)
        strcpy(user, av[1]);

    if(strlen(user)<4)
        { printf("name too short!\n"); return; }
            
    printf("user: %s\n", user);

    //
    miracl * mip = mirsys(100, 16);
    mip->IOBASE = 16;
    
    // useful vars
    big zero = mirvar(0);
    big one = mirvar(1);
    big ta = mirvar(0); // temps
    big tb = mirvar(0);
    big tc = mirvar(0);

    // initialize curve
    //
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

    cinstr(secp160r1_n, "100000000000000000001F4C8F927AED3CA752257");
    cinstr(secp160r1_x, "4A96B5688EF573284664698968C38BB913CBFC82"); // generator point G
    cinstr(secp160r1_y, "23A628553168947D59DCC912042351377AC5FB32");

    epoint *G = epoint_init();
    epoint_set(secp160r1_x, secp160r1_y, 0, G);

    epoint *temp_point = epoint_init();

    // hash of messages
    //
    big H1 = mirvar(0);
    big H2 = mirvar(0);
    hashing((PUCHAR)user, strlen(user), H1);
    strcpy(user2, user);
    strcat(user2, ", you just cracked my 10th crackme.. congrats!");
    hashing((PUCHAR)user2, strlen(user2), H2);

    // generate k, r, d_A, Q_A
    //
    big k = mirvar(0);
    big r = mirvar(0);
    big d_A = mirvar(0);
    epoint * Q_A = epoint_init();   // public key
    big pointH = mirvar(0);         // x-coord of public key

    irand(GetTickCount());

    while(1)
    {
        // choose random k
        bigbits(161, k);

        // compute r = x coord of k*G
        ecurve_mult(k, G, temp_point);
        epoint_get(temp_point, r, r);

        // compute d_A
        subtract(secp160r1_n, k, ta);
        divide(ta, secp160r1_n, secp160r1_n);               // ta = N-k
        mad(H1, ta, zero, secp160r1_n, secp160r1_n, tb);    // tb = (N-k) * H1
        mad(H2, k, zero, secp160r1_n, secp160r1_n, tc);     // tc = k * H2
        subtract(tc, tb, d_A);                              // d_A = (k * H2 - (N-k) * H1)
        divide(d_A, secp160r1_n, secp160r1_n);
        if(exsign(d_A) < 0)
            add(d_A, secp160r1_n, d_A);
        mad(r, ta, zero, secp160r1_n, secp160r1_n, tb);     // tb = (N-k) * r
        mad(k, r, zero, secp160r1_n, secp160r1_n, tc);      // tc = k * r
        subtract(tb, tc, ta);                               // ta = (N-k) * r - k * r
        divide(ta, secp160r1_n, secp160r1_n);
        if(exsign(ta) < 0)
            add(ta, secp160r1_n, ta);
        xgcd(ta, secp160r1_n, ta, ta, ta);                  // ta = ((N-k) * r - k * r)^(-1)
        mad(d_A, ta, zero, secp160r1_n, secp160r1_n, d_A);  // d_A = (k * H2 - (N-k) * H1) * ((N-k) * r - k * r)^(-1)
        divide(d_A, secp160r1_n, secp160r1_n);

        // compute Q_A (crackme calls this pointH)
        ecurve_mult(d_A, G, Q_A);

        // should we generate another? require y coord of
        // Q_A have same lsb as r
        epoint_get(Q_A, pointH, tb); 

        if(remain(r, 2) == remain(tb, 2))
            break;
    }

    // back-substitute d_A solve for s
    //
    // s = k^(-1) * (H1 + r * d_A)
    // s = (N-k)^(-1) * (H2 + r * d_A)
    big s = mirvar(0);
    mad(r, d_A, H1, secp160r1_n, secp160r1_n, s);           // s = r * d_A + H1
    copy(k, ta);                                            
    xgcd(ta, secp160r1_n, ta, ta, ta);                      // ta = k^(-1) (mod N)
    mad(s, ta, zero, secp160r1_n, secp160r1_n, s);          // s = (r * d_A + H1) * k^(-1)

    printb_(pointH);
    printb_(r);
    printb_(s);

    while(1);
}
