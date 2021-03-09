#define INFO "Keygen to HappyTown's Crackme_0030 - 2009 andrewl/crackmes.de"

#include <windows.h>
#include <stdio.h>

extern "C" {
#include "c:\code\lib\miracl5.3.3\include\miracl.h"
}
#pragma comment(lib, "c:\\code\\lib\\miracl5.3.3\\ms32.lib")
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")

VOID printb_(CHAR *tag, big n)
{
    CHAR buff[256];
    cotstr(n, buff);
    printf("%s: %s\n", tag, buff);
}

VOID printb(big n)
{
    CHAR buff[256];
    cotstr(n, buff);
    printf("%s", buff);
}

VOID main(INT ac, PCHAR *av)
{
    miracl *mir = mirsys(256, 16);
    mir->IOBASE = 16;

    printf("-----------------\n");
    printf(INFO "\n");
    printf("-----------------\n");

    // form user <concat> "&PEdiy" buff
    //
    CHAR user[512];
    if(ac>1)
        strcpy(user, av[1]);
    else
    {
        printf("supply arg to change username\n");
        strcpy(user, "HappyTown");
    }
    CHAR userBuff[512];
    strcpy(userBuff, user);
    strcat(userBuff, "&PEdiy");
    UINT userLen = strlen(userBuff);

    // compute U = big ( first_ten_bytes ( sha1 ( userbuff ) ) )
    //
    BYTE digest[20];
    sha sh;
    shs_init(&sh);
    for(INT i=0; i<userLen; ++i)
        shs_process(&sh, userBuff[i]);
    shs_hash(&sh, (PCHAR)digest);
    printf("hash: ");
    for(INT i=0; i<20; ++i)
        printf("%02X ", digest[i]);
    printf("\n");
    big u = mirvar(0);
    bytes_to_big(10, (PCHAR)digest, u);
    printb_("u", u);

    // some vars
    //
    big t0 = mirvar(0);
    big t1 = mirvar(0);
    big one = mirvar(1);
    big zero = mirvar(0);

    // constants
    //
    big n = mirvar(0);
    cinstr(n, "E97E36F9426708D10516A001FC358367B8ECBB7210388B971C886AA4A44845F1");
    big p = mirvar(0);
    cinstr(p, "EB8D197C10BA775BA2A785085C44A0C3");
    big q = mirvar(0);
    cinstr(q, "FDC35FF9D4A7BBCAD7577E99D8C8533B");
    big c = mirvar(0);
    cinstr(c, "FC1E242B3E7FC09993FE14EC88B799ACFD68BC83115F2F85C3E94E7D0FEC3F3");

    // (p-1)/2 for testing using Euler's critereon
    big p_crit = mirvar(0);
    cinstr(p_crit, "75C68CBE085D3BADD153C2842E225061");

    // (q-1)/2
    big q_crit = mirvar(0);
    cinstr(q_crit, "7EE1AFFCEA53DDE56BABBF4CEC64299D");

    // (p+1)/4 for finding square root using Lagrange's formula
    big p_lagrange = mirvar(0);
    cinstr(p_lagrange, "3AE3465F042E9DD6E8A9E14217112831");

    // (q+1)/4
    big q_lagrange = mirvar(0);
    cinstr(q_lagrange, "3F70D7FE7529EEF2B5D5DFA6763214CF");

    // find some A and B satisfying C*A + B = U (mod N);
    //
    printf("generating a and b...\n");

    UINT loopIters = 0;

    big a = mirvar(0);
    big b = mirvar(0);

    irand(GetTickCount());

    while(1)
    {
        loopIters++;

        bigbits(255, a);

        // test if quadratic residue of p and q
        // probability of this passing is 25%
        powmod(a, p_crit, p, t0);
        if(compare(t0, one))
            continue;
        powmod(a, q_crit, q, t0);
        if(compare(t0, one))
            continue;

        // k now solve for B
        multiply(c, a, t0);         // t0 = c*a
        subtract(u, t0, b);         // b = c*a - u
        powmod(b, one, n, b);       // b = (positive) (c*a - u) (mod n)
    
        printf("trial:\n");
        printb_("a", a);
        printb_("b", b);

        // test if b is quadratic residue of p and q
        powmod(b, p_crit, p, t0);
        if(compare(t0, one))
            continue;
        powmod(b, q_crit, q, t0);
        if(compare(t0, one))
            continue;

        printf("acceptable! after %d iterations\n", loopIters);
        
        break;
    }

    printf("finding square root of A\n");
    // now we we must find X:
    // X^2 = A (mod N)
    // X^2 = A (mod P*Q)

    // split to:

    // X1 = A^((P+1)/4) (mod P)
    // X2 = A^((Q+1)/4) (mod Q)
    //
    big x1 = mirvar(0);
    powmod(a, p_lagrange, p, x1);
    big x2 = mirvar(0);
    powmod(a, q_lagrange, q, x2);

    // now we have:
    //
    // X = X1 (mod P)
    // X = X2 (mod Q)
    //
    // find X using CRT
    big modulii[2];
    modulii[0] = p;
    modulii[1] = q;

    big remainders[2];
    remainders[0] = x1;
    remainders[1] = x2;

    big x = mirvar(0);
    big_chinese chi;
    crt_init(&chi, 2, modulii);
    crt(&chi, remainders, x);

    printb_("x", x);

    // do the same thing to find Y:
    //
    printf("finding square root of B\n");

    powmod(b, p_lagrange, p, x1);
    powmod(b, q_lagrange, q, x2);
    big y = mirvar(0);
    crt(&chi, remainders, y);

    printb_("y", y);

    // print serial! :)
    //
    printf("-----------------\n");
    printf("  user: %s\n", user);
    printf("serial: ");
    printb(y);
    printf("-");
    printb(x);
    printf("\n");
    printf("-----------------\n");

    printf("ctrL+c to quit\n");
    while(1);
}

    
