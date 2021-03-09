// keygen to D-Racinez Moi by Waganono
// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"

// crt
#include <stdio.h>
#include <conio.h>

void fixup_rips();

// from quadratic_residue
extern void solve_squared_mod(PUCHAR panswer, PULONG answerlen, PUCHAR ybytes, ULONG ylen, PUCHAR mbytes, ULONG mlen);
extern void test_chinese_remainder_theorem();
extern void test_solve_quadratic_residue();
void derive_prefix_for_hash(BIGNUM BN_target, PCHAR prefix);
void transform_username(char * username, BIGNUM * result);
void solve_quadratic_residue_const1(BIGNUM * y, BIGNUM * x);

void main(int argc, char * argv[])
{
    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    CHAR   buffer[1024]={0};
    ULONG   ulRet=0;

    char negchar='#';

    if(argc < 2)
    {
        printf("supply username as argument\n");
        return;
    }

    printf("generating serial for %s\n", argv[1]);

    BIGNUM stuff_user;
    BN_init(&stuff_user);
    transform_username(argv[1], &stuff_user);

    printf("----- number generated from username: %s\n", BN_bn2hex(&stuff_user));

    //
    // we will later generate some value x such that the result of x^2 % const1 == number generated from username
    //
    // x^2 = number generated from username (mod const 1)
    //

    BIGNUM *const1=0;
    BN_dec2bn(&const1, "3231059773210568767339731308062401168932613017316655150232323931789052315453509684929908820129");

    BIGNUM * const2=0;
    BN_hex2bn(&const2, "60A699BFB7DD9D97B13AE247AC6A281C9382F135FDCFA240D281518B671C919D5ABD625548C0DA09D135C1643E8ABA4F933C82E363D1A5CB72738C9FF44C4004D99E4DDDA533E5332F93E78F0FE9");

    BIGNUM *factor1=0, *factor2=0;
    BN_dec2bn(&factor1, "56314315727265148662503030763343660191795076067");
    BN_dec2bn(&factor2, "57375460067007762984026787123334422029973026987");

    /*
    BIGNUM sum;
    BN_init(&sum);

    BN_add(&sum, &x, const2);

    CHAR as_hex[512]={0};
    strcpy(as_hex, BN_bn2hex(&sum));

    printf("Added, we get: %s\n", as_hex);
    */


    printf("solving x^2 %% const1 == the number generated from username\n");

    BIGNUM x;
    BN_init(&x);
    solve_quadratic_residue_const1(&stuff_user, &x);

    printf("----- x: %s\n", BN_bn2hex(&x));

    // creating a different answer the easy way: adding the modulus
    BIGNUM x2;
    BN_init(&x2);
    BN_add(&x2, &x, const1);

    printf("----- x2: %s\n", BN_bn2hex(&x2));

    // write these dudes to memory in string form, concatenated
    UINT theulong=0;
    strcpy(buffer, BN_bn2hex(&x));
    theulong=strlen(buffer);
    strcat(buffer, BN_bn2hex(&x2));

    printf("back to back in mem (with ulong divider: %d): %s\n", theulong, buffer);

    // make a BN out of this
    BIGNUM * almost=0;
    BN_hex2bn(&almost, buffer);
    
    printf("made a BN out of that region, ensuring we'd get it back: %s\n", BN_bn2hex(almost));

    // we want a number that, when const2 is added, yields almost
    BN_sub(almost, almost, const2);

    if(BN_is_negative(almost))
        negchar='@';
    else
        negchar='#';

    BN_set_negative(almost, 0);

    printf("This number, when const is added, yields huge region number = %s\n", BN_bn2hex(almost));

    printf("deriving what prefix string will yield this big number\n");
    fixup_rips();

    memset(buffer, 0, 1024);
    derive_prefix_for_hash(*almost, buffer);
    printf("----- prefix: %s\n", buffer);

    //
    CHAR serial[1024]={0};
    sprintf(serial, "%s%c%d , %s , %s\n", buffer, negchar, theulong, BN_bn2hex(factor1), BN_bn2hex(factor2));

    printf("**********************************************************\n");
    printf("**********************************************************\n");
    printf("  USER:\n");
    printf("    %s\n", argv[1]);
    printf("SERIAL:\n");
    printf("    %s\n", serial);
    printf("**********************************************************\n");
    printf("**********************************************************\n");

    printf("----- hit a key to copy the serial to clipboard\n");
    _getch();


    OpenClipboard(NULL);
    EmptyClipboard();
    HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE, strlen(serial));
    char * pdata = (char *)GlobalLock(hData);
    memcpy(pdata, serial, strlen(serial));
    GlobalUnlock(hData);
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();

    printf("----- hit a key to close\n");
    _getch();


    return;
}
