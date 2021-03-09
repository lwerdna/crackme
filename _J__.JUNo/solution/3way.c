/********************************************************************\
 *                                                                    *
 * C specification of the threeway block cipher                       *
 *                                                                    *
 \********************************************************************/

#define   STRT_E   0x0b0b /* round constant of first encryption round */ 
#define   STRT_D   0xb1b1 /* round constant of first decryption round */
#define     NMBR       11 /* number of rounds is 11                   */

typedef   unsigned long int  word32 ; 
/* the program only works correctly if long = 32bits */

void mu(word32 *a)       /* inverts the order of the bits of a */
{
    int i ;
    word32 b[3] ;

    b[0] = b[1] = b[2] = 0 ;
    for( i=0 ; i<32 ; i++ )
    {
        b[0] <<= 1 ; b[1] <<= 1 ; b[2] <<= 1 ;
        if(a[0]&1) b[2] |= 1 ;
        if(a[1]&1) b[1] |= 1 ;
        if(a[2]&1) b[0] |= 1 ;
        a[0] >>= 1 ; a[1] >>= 1 ; a[2] >>= 1 ;
    }

    a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}


void gamma(word32 *a)   /* the nonlinear step */
{
    word32 b[3] ;

    b[0] = a[0] ^ (a[1]|(~a[2])) ; 
    b[1] = a[1] ^ (a[2]|(~a[0])) ; 
    b[2] = a[2] ^ (a[0]|(~a[1])) ; 

    a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}


void theta(word32 *a)    /* the linear step */
{
    word32 b[3];

    b[0] = a[0] ^  (a[0]>>16) ^ (a[1]<<16) ^     (a[1]>>16) ^ (a[2]<<16) ^
        (a[1]>>24) ^ (a[2]<<8)  ^     (a[2]>>8)  ^ (a[0]<<24) ^
        (a[2]>>16) ^ (a[0]<<16) ^     (a[2]>>24) ^ (a[0]<<8)  ;
    b[1] = a[1] ^  (a[1]>>16) ^ (a[2]<<16) ^     (a[2]>>16) ^ (a[0]<<16) ^
        (a[2]>>24) ^ (a[0]<<8)  ^     (a[0]>>8)  ^ (a[1]<<24) ^
        (a[0]>>16) ^ (a[1]<<16) ^     (a[0]>>24) ^ (a[1]<<8)  ;
    b[2] = a[2] ^  (a[2]>>16) ^ (a[0]<<16) ^     (a[0]>>16) ^ (a[1]<<16) ^
        (a[0]>>24) ^ (a[1]<<8)  ^     (a[1]>>8)  ^ (a[2]<<24) ^
        (a[1]>>16) ^ (a[2]<<16) ^     (a[1]>>24) ^ (a[2]<<8)  ;

    a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}

void pi_1(word32 *a)   
{
    a[0] = (a[0]>>10) ^ (a[0]<<22);  
    a[2] = (a[2]<<1)  ^ (a[2]>>31);
}

void pi_2(word32 *a)   
{
    a[0] = (a[0]<<1)  ^ (a[0]>>31);
    a[2] = (a[2]>>10) ^ (a[2]<<22);
}

void rho(word32 *a)    /* the round function       */
{
    theta(a) ; 
    pi_1(a) ; 
    gamma(a) ; 
    pi_2(a) ;
}

void rndcon_gen(word32 strt,word32 *rtab)
{                           /* generates the round constants */
    int i ;

    for(i=0 ; i<=NMBR ; i++ )
    {
        rtab[i] = strt ;
        strt <<= 1 ; 
        if( strt&0x10000 ) strt ^= 0x11011 ;
    }
}



void encrypt(word32 *a, word32 *k)
{
    char i ;
    word32 rcon[NMBR+1] ;

    rndcon_gen(STRT_E,rcon) ; 
    for( i=0 ; i<NMBR ; i++ )   
    {
        a[0] ^= k[0] ^ (rcon[i]<<16) ; 
        a[1] ^= k[1] ; 
        a[2] ^= k[2] ^ rcon[i] ;
        rho(a) ;
    }
    a[0] ^= k[0] ^ (rcon[NMBR]<<16) ; 
    a[1] ^= k[1] ; 
    a[2] ^= k[2] ^ rcon[NMBR] ;
    theta(a) ;
}


void decrypt(word32 *a, word32 *k)
{             
    char i ;
    word32 ki[3] ;          /* the `inverse' key             */
    word32 rcon[NMBR+1] ;   /* the `inverse' round constants */

    ki[0] = k[0] ; ki[1] = k[1] ; ki[2] = k[2] ; 
    theta(ki) ;
    mu(ki) ;

    rndcon_gen(STRT_D,rcon) ; 

    mu(a) ;
    for( i=0 ; i<NMBR ; i++ )
    {
        a[0] ^= ki[0] ^ (rcon[i]<<16) ; 
        a[1] ^= ki[1] ; 
        a[2] ^= ki[2] ^ rcon[i] ;
        rho(a) ;
    }
    a[0] ^= ki[0] ^ (rcon[NMBR]<<16) ; 
    a[1] ^= ki[1] ; 
    a[2] ^= ki[2] ^ rcon[NMBR] ;
    theta(a) ;
    mu(a) ;
}

#define _CRT_SECURE_NO_DEPRECATE 1
#include <stdio.h>
#include <stdlib.h>

void printvec(word32 *a)
{
    printf("%08x %08x %08x\n",a[0],a[1],a[2]) ;
}

#ifndef DISCLUDE_MAIN
main()
{
    word32 a[3], k[3] ;

    scanf("%x %x %x %x %x %x",a,a+1,a+2,k,k+1,k+2) ;

    printf("plaintext: "); 
    printvec(a);
    printf("key: "); 
    printvec(k);

    encrypt(a, k); 

    printf("E(a, k): ");
    printvec(a);
    
    decrypt(a, k); 
    printf("D(E(a, k), k): ");
    printvec(a);

    decrypt(a, k); 
    printf("D(a, k): ");
    printvec(a);

    encrypt(a, k);
    printf("E(D(a, k)): ");
    printvec(a);

    /*  TEST VALUES 

key        : 00000000 00000000 00000000
plaintext  : 00000001 00000001 00000001
ciphertext : ad21ecf7 83ae9dc4 4059c76e

key        : 00000004 00000005 00000006
plaintext  : 00000001 00000002 00000003
ciphertext : cab920cd d6144138 d2f05b5e

key        : bcdef012 456789ab def01234
plaintext  : 01234567 9abcdef0 23456789
ciphertext : 7cdb76b2 9cdddb6d 0aa55dbb

key        : cab920cd d6144138 d2f05b5e
plaintext  : ad21ecf7 83ae9dc4 4059c76e
ciphertext : 15b155ed 6b13f17c 478ea871

     */
}

#endif
