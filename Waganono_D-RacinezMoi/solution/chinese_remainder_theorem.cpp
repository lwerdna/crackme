// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"

// from extended_euclidean
extern void extended_euclidean(BIGNUM * u, BIGNUM * v, BIGNUM * f1, BIGNUM * f2, BIGNUM * gcd);

//
// Written from the Wikipedia article :)
//
// input: a1, n1, a2, n2
// output: x
//
// very simplified: solves non-general case:
// x = a1 (mod n1)
// x = a2 (mod n2)
// and n1 and n2 are coprime
//
void chinese_remainder_theorem(BIGNUM * a1, BIGNUM * n1, BIGNUM * a2, BIGNUM * n2, BIGNUM * x)
{
    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    // 1
    BIGNUM one;
    BN_init(&one);
    BN_one(&one);

    // temp
    BIGNUM temp;
    BN_init(&temp);

    // find r1, s1 such that r1*n1 + s1*n2 = 1;
    BIGNUM r1, s1;
    BN_init(&r1);
    BN_init(&s1);
    extended_euclidean(n1, n2, &r1, &s1, &temp);

    // find r2, s2 such that r2*n2 + r2*n2
    BIGNUM r2, s2;
    BN_init(&r2);
    BN_init(&s2);
    extended_euclidean(n2, n1, &r2, &s2, &temp);

    //printf("r1:%s s1:%s r2:%s s2:%s\n", BN_bn2dec(&r1), BN_bn2dec(&s1), BN_bn2dec(&r2), BN_bn2dec(&s2));
    
    // e1
    BIGNUM e1;
    BN_init(&e1);
    BN_mul(&e1, &s1, n2, ctx);

    // e2
    BIGNUM e2;
    BN_init(&e2);
    BN_mul(&e2, &s2, n1, ctx);

    // temp = a1*e1 + a2*e1
    BN_mul(&e1, &e1, a1, ctx);
    BN_mul(&e2, &e2, a2, ctx);
    BN_add(&temp, &e1, &e2);

    // result
    BN_copy(x, &temp);

    // free
    BN_free(&one);
    BN_free(&temp);
    BN_free(&r1);
    BN_free(&s1);
    BN_free(&r2);
    BN_free(&s2);
    BN_free(&e1);
    BN_free(&e2);
}

void test_chinese_remainder_theorem()
{
    // solve
    //
    // x = 2 (mod 3)
    // x = 3 (mod 5)
    //
    ULONG temp;
 
    BIGNUM a1, a2, n1, n2, x;
    BN_init(&a1); BN_init(&a2); BN_init(&n1); BN_init(&n2); BN_init(&x);
   
    //
    temp = 0x02;
    BN_bin2bn((PUCHAR)&temp, 1, &a1);
    temp = 0x03;
    BN_bin2bn((PUCHAR)&temp, 1, &n1);
    temp = 0x03;
    BN_bin2bn((PUCHAR)&temp, 1, &a2);
    temp = 0x05;
    BN_bin2bn((PUCHAR)&temp, 1, &n2);

    chinese_remainder_theorem(&a1, &n1, &a2, &n2, &x);

    printf("x: %s\n", BN_bn2dec(&x));
    printf("(should be 8, or another solution to x^2 = 4 (mod 15))\n");

    BN_free(&a1); BN_free(&a2); BN_free(&n1); BN_free(&n2); BN_free(&x);
}

