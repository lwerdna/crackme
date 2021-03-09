// 2008 andrewl

#define _CRT_SECURE_NO_DEPRECATE 1

// OS
#include <windows.h>

// CRT
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>

// OpenSSL
#include <openssl\bn.h>
#include "idiotopenssl.h"

// ripped functions
void func_0040B6B0(char *p);

void printbytes(char * p, int n)
{
    for(int i=0; i<n; ++i)
        printf("%02X", p[i] & 0xFF);
    printf("\n");
}

void main(int argc, char *argv[])
{
    BIGNUM p, q, hash2, e, one, m, phi, inv, key;

    BN_init(&p);
    BN_init(&q);
    BN_init(&hash2);
    BN_init(&e);
    BN_init(&m);
    BN_init(&phi);
    BN_init(&inv);
    BN_init(&one);
    BN_init(&key);

    BN_one(&one);

    BN_CTX * ctx = BN_CTX_new();

    printf("Keygen to \".DEMETEr Keygenme.\" by _J_\n");

    if(argc<2)
        { printf("NEED \"USER iD\" as argument\n"); goto end; }

    char *buffer=(char *)malloc(64);
    memset(buffer, 0, 0x40);
    strcpy(buffer, argv[1]);
    
    func_0040B6B0(buffer);
    BN_bin2bn((PUCHAR)buffer, 32, &p);
    printf("hash0: %s\n", BN_bn2hex(&p));

    func_0040B6B0(buffer);
    BN_bin2bn((PUCHAR)buffer, 32, &q);
    printf("hash1: %s\n", BN_bn2hex(&q));

    func_0040B6B0(buffer);
    BN_bin2bn((PUCHAR)buffer, 32, &hash2);
    printf("hash2: %s\n", BN_bn2hex(&hash2));

    // increment p until it is prime
    while(!BN_is_prime(&p, BN_prime_checks, 0, ctx, NULL))
        BN_add(&p, &p, &one);
    printf("p: %s\n", BN_bn2hex(&p));

    // increment q until it is prime
    while(!BN_is_prime(&q, BN_prime_checks, 0, ctx, NULL))
        BN_add(&q, &q, &one);
    printf("q: %s\n", BN_bn2hex(&q));

    DWORD dwVolSerial;
    GetVolumeInformation(0, 0, 0, &dwVolSerial, 0, 0, 0, 0);
    dwVolSerial =   ((dwVolSerial&0xFF000000)>>24) |
                    ((dwVolSerial&0x00FF0000)>>8) |
                    ((dwVolSerial&0x0000FF00)<<8) |
                    ((dwVolSerial&0x000000FF)<<24);
    BN_bin2bn((PUCHAR)&dwVolSerial, 4, &e);
    printf("volume serial: %s\n", BN_bn2hex(&e));

    // increment e until it is prime
    while(!BN_is_prime(&e, BN_prime_checks, 0, ctx, NULL))
        BN_add(&e, &e, &one);
    printf("e: %s\n", BN_bn2hex(&e));

    // calculate m = p * q
    BN_mul(&m, &p, &q, ctx);
    printf("m: %s\n", BN_bn2hex(&m));

    // calculate (p-1)*(q-1)
    BN_sub(&p, &p, &one);
    BN_sub(&q, &q, &one);
    BN_mul(&phi, &p, &q, ctx);
    printf("phi(m): %s\n", BN_bn2hex(&phi));

    // calculate X such that e * X % ((p-1)*(q-1)) = 1
    BN_mod_inverse(&inv, &e, &phi, ctx);
    printf("d: %s\n", BN_bn2hex(&inv));

    // we must solve hash2 = serial^d (mod m) = DECRYPT(serial)
    // or "what ciphertext, decrypted, yields hash2?"
    // easy, the cyphertext of hash2:
    // hash2 ^ e (mod m) = ENCRYPT(hash2)

    BN_mod_exp(&key, &hash2, &e, &m, ctx);

    char * szSerial = (char *)malloc(1024);
    strcpy(szSerial, BN_bn2hex(&key));

    printf("**********************************************************\n");
    printf("**********************************************************\n");
    printf("  USER:\n");
    printf("    %s\n", argv[1]);
    printf("SERIAL:\n");
    printf("    %s\n", szSerial);
    printf("**********************************************************\n");
    printf("**********************************************************\n");

    printf("----- hit a key to copy the serial to clipboard\n");
    _getch();

    OpenClipboard(NULL);
    EmptyClipboard();
    HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE, strlen(szSerial)+1);
    char * pdata = (char *)GlobalLock(hData);
    memcpy(pdata, szSerial, strlen(szSerial)+1);
    GlobalUnlock(hData);
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();

    end:

    BN_CTX_free(ctx);

    free(buffer);
    free(szSerial);

    printf("----- hit a key to close\n");
    _getch();

    return;
}
