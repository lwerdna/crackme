// keygen to dihux's "Keygenme Nr.2"
// 6/03/2009 andrewl

#include <windows.h>
#include <stdio.h>
extern "C" {
#include "miracl.h"
}

VOID main(INT ac, PCHAR *av)
{
    CHAR buff[1024];

    PCHAR name="dihux";
    if(ac>1)
        name=av[1];
    if(strlen(name)<=4)
        { printf("name too short!\n"); goto done; }
    if(strlen(name)>20)
        { printf("name too long!\n"); goto done; }
    CHAR prodkey[30];
    strcpy(prodkey,"37911-DIHUX-62119-FUNNY-XXXXX");
    sprintf(prodkey+24, "%05X", GetTickCount());
    prodkey[29]=0;

    miracl *mip=mirsys(256, 0);
    mip->IOBASE=16;

    big N=mirvar(0);
    bytes_to_big(strlen(name),name,N);
    big P_=mirvar(0);
    cinstr(P_, "CBEC5F1F97FB14C803CA"); // P-1
    big R=mirvar(0);
    cinstr(R, "1BBE0FE2BADBB5B5854"); // R, where 2^R = X (mod P)
    big S_=mirvar(0);
    cinstr(S_, "3E8D7E69A6195CC4FAD6"); // 2*S (mod P-1), where 2^S = Y (mod P)
   
    big B=mirvar(0);
    negify(S_, S_);

    mad(R,N,S_,P_,P_,B); // B = R*N - 2*S (mod P-1)

    cotstr(B, buff);
    printf("      name: %s\n", name);
    printf("   product: %s\n", prodkey);
    printf("activation: 2-%s\n\n\n", buff);

    done:
    printf("ctrL+c to quit!\n");
    while(1);

}
