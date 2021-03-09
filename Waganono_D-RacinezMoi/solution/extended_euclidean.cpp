// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"

//
// Written from "Algorithm X" in Knuth Volume 2
//
// input: u, v
// output: f1, f2, gcd
//
// Such that f1*u + f2*v == gcd
//
void extended_euclidean(BIGNUM * u, BIGNUM * v, BIGNUM * f1, BIGNUM * f2, BIGNUM * gcd)
{
    // (u1, u2, u3) <-- (1, 0, u)
    BIGNUM u1, u2, u3;
    BN_init(&u1); BN_init(&u2); BN_init(&u3);
    BN_one(&u1);
    BN_zero(&u2);
    BN_copy(&u3, u);

    // (v1, v2, v3) <--- (0, 1, v)
    BIGNUM v1, v2, v3;
    BN_init(&v1); BN_init(&v2); BN_init(&v3);
    BN_zero(&v1);
    BN_one(&v2);
    BN_copy(&v3, v);

    // q - holds quotient
    BIGNUM q;
    BN_init(&q);

    // temp variables - for swapping
    BIGNUM t1, t2, t3;
    BN_init(&t1); BN_init(&t2); BN_init(&t3);

    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    while(!BN_is_zero(&v3))
    {
        /*
        printf("q:%s u1:%s u2:%s u3:%s v1:%s v2:%s v3:%s\n", 
                BN_bn2dec(&q), 
                BN_bn2dec(&u1),
                BN_bn2dec(&u2),
                BN_bn2dec(&u3),
                BN_bn2dec(&v1),
                BN_bn2dec(&v2),
                BN_bn2dec(&v3)
              );
        */

        BN_div(&q, 0, &u3, &v3, ctx);

        // (t1, t2, t3) <--- (u1, u2, u3) - (v1, v2, v3) q
        BN_copy(&t1, &v1);
        BN_copy(&t2, &v2);
        BN_copy(&t3, &v3);

        BN_mul(&t1, &t1, &q, ctx);
        BN_mul(&t2, &t2, &q, ctx);
        BN_mul(&t3, &t3, &q, ctx);

        BN_sub(&t1, &u1, &t1);
        BN_sub(&t2, &u2, &t2);
        BN_sub(&t3, &u3, &t3);
    
        // (u1, u2, u3) <--- (v1, v2, v3)
        BN_copy(&u1, &v1);
        BN_copy(&u2, &v2);
        BN_copy(&u3, &v3);

        // (v1, v2, v3) <--- (t1, t2, t3)
        BN_copy(&v1, &t1);
        BN_copy(&v2, &t2);
        BN_copy(&v3, &t3);
    }

    // copy results
    BN_copy(f1, &u1);
    BN_copy(f2, &u2);
    BN_copy(gcd, &u3);

    // free variables
    BN_free(&u1); BN_free(&u2); BN_free(&u3);
    BN_free(&v1); BN_free(&v2); BN_free(&v3);
    BN_free(&t1); BN_free(&t2); BN_free(&t3);
    BN_free(&q);
}

void test_extended_euclidean()
{
    ULONG temp;
 
    BIGNUM u, v, gcd, f1, f2;
    BN_init(&u); BN_init(&v); BN_init(&gcd); BN_init(&f1); BN_init(&f2);
   
    // u
    temp=0xC69F0000; // 0x00, 0x00, 0x9F, 0xC6 // 40902 in BIGNUM byte order (big endian)
    BN_bin2bn((PUCHAR)&temp, 4, &u);

    // v
    temp=0x4C5E0000; // 0x00, 0x00, 0x5E, 0x4C // 24140 in BIGNUM byte order (big endian)
    BN_bin2bn((PUCHAR)&temp, 4, &v);

    extended_euclidean(&u, &v, &f1, &f2, &gcd);

    printf("f1 (should be 337): %s\n", BN_bn2dec(&f1));
    printf("f2 (should be -571): %s\n", BN_bn2dec(&f2));
    printf("gcd (should be 34): %s\n", BN_bn2dec(&gcd));

    BN_free(&u); BN_free(&v); BN_free(&gcd); BN_free(&f1); BN_free(&f2);
}
