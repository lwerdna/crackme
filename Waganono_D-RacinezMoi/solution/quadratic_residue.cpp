// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"

void chinese_remainder_theorem(BIGNUM * a1, BIGNUM * n1, BIGNUM * a2, BIGNUM * n2, BIGNUM * x);

//
// tests if a number is a quadratic residue of C, composed of two primes p1, and p2
//
bool is_quadratic_residue(BIGNUM * a, BIGNUM * p1, BIGNUM *p2)
{
    bool bFuncRet=1;

    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    //
    BIGNUM *one=0, *two=0;
    BN_dec2bn(&one, "1");
    BN_dec2bn(&two, "2");

    // temp
    BIGNUM temp;
    BN_init(&temp); 

    BN_copy(&temp, p1);
    BN_sub(&temp, &temp, one);
    BN_div(&temp, 0, &temp, two, ctx);
    BN_mod_exp(&temp, a, &temp, p1, ctx);

    if(BN_cmp(&temp, one)!=0)
        bFuncRet=0;

    BN_copy(&temp, p2);
    BN_sub(&temp, &temp, one);
    BN_div(&temp, 0, &temp, two, ctx);
    BN_mod_exp(&temp, a, &temp, p2, ctx);

    if(BN_cmp(&temp, one)!=0)
        bFuncRet=0;

    BN_mul(&temp, p1, p2, ctx);
    //printf("Is %s a quadratic residue of %s? %d\n", BN_bn2dec(a), BN_bn2dec(&temp), bFuncRet);

    return bFuncRet;
}

//
// solves special case of:
//
// x^2 = y (mod C)
//
// where C factors into two primes factor1 and factor2
//
// and factor1 = 3 (mod 4)
// and factor2 = 3 (mod 4)
//
void solve_quadratic_residue(BIGNUM * y, BIGNUM * factor1, BIGNUM * factor2, BIGNUM * x)
{
    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    // temp
    BIGNUM temp;
    BN_init(&temp);

    // N
    BIGNUM N;
    BN_init(&N);
    BN_mul(&N, factor1, factor2, ctx);

    // 1, 4
    BIGNUM *one=0, *three=0, *four=0;
    BN_dec2bn(&one, "1");
    BN_dec2bn(&three, "3");
    BN_dec2bn(&four, "4");

    // guarantee that y is really a quadratic residue of N
    if(!is_quadratic_residue(y, factor1, factor2))
        printf("major error!!! %s is not a quadratic residue of %s\n", BN_bn2hex(y), BN_bn2hex(&N));

    // guarantee that factor = 3 (mod 4) so we can do the Legendre trick
    BN_div(0, &temp, factor1, four, ctx);
    if(BN_cmp(&temp, three))
        printf("error: incoming factor %s is not = 3 (mod 4)\n", BN_bn2dec(factor1));
    BN_div(0, &temp, factor2, four, ctx);
    if(BN_cmp(&temp, three))
        printf("error: incoming factor %s is not = 3 (mod 4)\n", BN_bn2dec(factor2));

    BIGNUM y1, y2;
    BN_init(&y1);
    BN_init(&y2);
    BN_copy(&y1, y);
    BN_copy(&y2, y);
    
    // reduce the size of the problem if we're trying to do x^2 = y (mod C) when y > C
    if(BN_cmp(&y1, factor1) > 0) // if y1 > factor1
    {
        BN_mod(&y1, &y1, factor1, ctx); // y1 = y1 % factor1
        printf("Reduced y1 to %s\n", BN_bn2dec(&y1));
    }

    if(BN_cmp(&y2, factor2) > 0) // if y2 > factor2
    {
        BN_mod(&y2, &y2, factor2, ctx); // y2 = y2 % factor2
        printf("Reduced y2 to %s\n", BN_bn2dec(&y2));
    }

    // we have:
    //
    // (eq01)       x^2 = y (mod const1)
    //
    // if y is indeed a quadratic residue, then we must find x, which
    // I like to think of as a "y (mod const1) square root"
    //
    // this is a problem known to be equivalently difficult to factoring const1
    //
    // used msieve to factor const1 - we instead solve these two:
    //
    // (eq02)       x^2 = y (mod factor1)
    // (eq03)       x^2 = y (mod factor2)
    //
    // since factor1 = 3 (mod 4)
    //
    // (eq04)       x = y^((factor1+1)/4) (mod factor1)
    //
    // and similarly for factor2
    //
    // so we easily arrive at two solutions, s1 and s2

    BIGNUM s1, s2;
    BN_init(&s1);
    BN_init(&s2);

    BN_copy(&s1, factor1);
    BN_add(&s1, &s1, one);
    BN_div(&s1, 0, &s1, four, ctx);
    BN_mod_exp(&s1, &y1, &s1, factor1, ctx); // s1 = y1^s1 % factor1

    BN_copy(&s2, factor2);
    BN_add(&s2, &s2, one);
    BN_div(&s2, 0, &s2, four, ctx);
    BN_mod_exp(&s2, &y2, &s2, factor2, ctx);

    // check answers
    BN_mod_sqr(&temp, &s1, factor1, ctx); // s1^2 % factor1
    if(BN_cmp(&temp, &y1) != 0)              // == y
        printf("Fuck man, intermediate answer is wrong! (s1:%s factor1:%s y1:%s)\n", BN_bn2dec(&s1), BN_bn2dec(factor1), BN_bn2dec(&y1));

    BN_mod_sqr(&temp, &s2, factor2, ctx);
    if(BN_cmp(&temp, &y2) != 0)
    {
        printf("Fuck man, intermediate answer is wrong!\n");
        printf("x^2 = %s (mod %s)\n", BN_bn2hex(&y2), BN_bn2hex(factor2));
        printf("found x = %s\n", BN_bn2hex(&s2));
    }

    //printf("Got solutions s1:%s s2:%s\n", BN_bn2dec(&s1), BN_bn2dec(&s2));

    //
    // when s1 is a solution, factor1+s1 is also, 2*factor1+s1 is also, etc.
    //
    // put differently, we can define solutions S 
    //
    // (eq05)       S = s1 (mod factor1)
    //
    // so since there are multiple solutions to eq02, eq03, can we find single
    // number z that satisfies both? if so, the equations would look like this:
    //
    // (eq06)       z = s1 (mod factor1)
    // (eq07)       z = s2 (mod factor2)
    //
    // the Chinese remainder theorem states that there is a solution when factor1
    // and factor2 are coprime, which they are, since they are the only two factors
    // of a prime number
 
    BIGNUM z;
    BN_init(&z);
    chinese_remainder_theorem(&s1, factor1, &s2, factor2, &z);
   
    // so we find z, and
    //
    // (eq08)       z^2 = y (mod factor1)
    // (eq09)       z^2 = y (mod factor2)
    //
    // and therefore
    //
    // (eq10)       z^2 = y (mod factor1*factor2)
    //
    // (eq11)       z^2 = y (mod const1)
    //

    // normalize
    BN_set_negative(&z, 0);
    BN_mod(&z, &z, &N, ctx); // solution = solution % (factor1*factor2);

    // return result
    BN_copy(x, &z);

    // free
    BN_free(one);
    BN_free(four);
    BN_free(&s1);
    BN_free(&s2);
    BN_free(&z);
}

//
// solves x^2 = y (mod const1)
//
// input: y
// output: x
//
void solve_quadratic_residue_const1(BIGNUM * y, BIGNUM * x)
{
    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    // temp
    BIGNUM temp;
    BN_init(&temp);

    BIGNUM *const1=0;
    BN_dec2bn(&const1, "3231059773210568767339731308062401168932613017316655150232323931789052315453509684929908820129");

    BIGNUM *factor1=0, *factor2=0;
    BN_dec2bn(&factor1, "56314315727265148662503030763343660191795076067");
    BN_dec2bn(&factor2, "57375460067007762984026787123334422029973026987");

    BN_mul(&temp, factor1, factor2, ctx);
    if(BN_cmp(&temp, const1) != 0)
        printf("The factors are wrong the factors are wrong!\n");

    solve_quadratic_residue(y, factor1, factor2, x);

    BN_free(&temp);
    BN_free(const1);
    BN_free(factor1);
    BN_free(factor2);
}

void test_solve_quadratic_residue()
{
    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    // solve x^2 = 4 (mod 21)

    BIGNUM *four=0, *three=0, *seven=0, answer;
    BN_init(&answer);
    BN_dec2bn(&four, "4");
    BN_dec2bn(&three, "3");
    BN_dec2bn(&seven, "7");
    solve_quadratic_residue(four, three, seven, &answer);
    printf("The answer is (should be solution to x^2 = 4 (mod 21): %s\n", BN_bn2dec(&answer));
 
    BIGNUM *factor1=0, *factor2=0, *target=0, *N=0;
    BN_dec2bn(&factor1, "47");
    BN_dec2bn(&factor2, "107");
    BN_dec2bn(&target, "717");
    BN_dec2bn(&N, "5029");
    // try x^2 = 20 (mod 47*97)


    solve_quadratic_residue(target, factor1, factor2, &answer);
    printf("The answer is (should be solution to x^2 = 717 (mod 5029): %s\n", BN_bn2dec(&answer));

    is_quadratic_residue(four, factor1, factor2);
    is_quadratic_residue(three, factor1, factor2);
    is_quadratic_residue(seven, factor1, factor2);
    is_quadratic_residue(factor1, factor1, factor2);
    is_quadratic_residue(factor2, factor1, factor2);
    is_quadratic_residue(target, factor1, factor2);
 
    BIGNUM *const1=0;
    BN_dec2bn(&const1, "3231059773210568767339731308062401168932613017316655150232323931789052315453509684929908820129");

    printf("const1: %s\n", BN_bn2dec(const1));

    BIGNUM *rand=0;
    BN_dec2bn(&rand, "9288827");
    solve_quadratic_residue_const1(rand, &answer);
    printf("The answer: (when squared will give y): %s\n", BN_bn2dec(&answer));
    BN_mod_sqr(&answer, &answer, const1, ctx);
    printf("answer^2 = %s\n", BN_bn2dec(&answer));
}

