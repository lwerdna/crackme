char *info= "KEYGEN \"Keygenme 2008 by Crosys\" 2008 andrewl\n";

// os
#include <windows.h>

// c standard lib
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// miracl
extern "C" {
#include <miracl.h>

#include <global.h>
#include <md5.h>
}

// globals
char g_buff[512];

// functions

// brute force the checks at 401192
void brute_00401192(void)
{
    DWORD i=0;

    for(i=0xFFFFFFFF; i!=0; --i)
    {
        DWORD a, b, c, d;

        a = (i & 0xFF000000) >> 24;
        b = (i & 0xFF0000) >> 16;
        c = (i & 0xFF00) >> 8;
        d = (i & 0xFF) >> 0;

        UCHAR r=0;

        DWORD temp=0;

          __asm
          {
                          push    ebp
                          mov     ebx, [a]
                          mov     esi, [b]
                          mov     edi, [c]
                          mov     eax, [d]
            loc_0040112A: lea     ecx,[esi+esi*2]
            loc_0040112D: lea     ebp,[eax+eax*4]
            loc_00401130: sub     ecx,edi
            loc_00401135: lea     edx,[ecx+ebx*4]
            loc_00401138: lea     ecx,[edx+ecx*2]
            loc_0040113B: add     ebp,ecx
            loc_0040113D: lea     ecx,[ebx*4]
            loc_00401144: lea     edx,[ecx+edi*8]
            loc_00401147: mov     ecx,edi
            loc_00401149: add     ecx,edx
            loc_0040114B: lea     edx,[esi*8]
            loc_00401152: add     ecx,eax
            loc_00401154: sub     edx,esi
            loc_00401156: add     ecx,ecx
            loc_00401158: sub     ecx,edx
                          xchg    ebp, [esp]
            loc_0040115A: mov     [temp],ecx
                          xchg    ebp, [esp]
            loc_0040115E: lea     ecx,[eax+eax]
            loc_00401161: imul    eax,edi
            loc_00401164: imul    eax,esi
            loc_00401167: sub     ecx,esi
            loc_00401169: imul    eax,ebx
            loc_0040116C: shl     ecx,2
            loc_0040116F: mov     edx,ecx
            loc_00401171: lea     ecx,[edi+edi*2]
            loc_00401174: sub     edx,ebx
            loc_00401176: lea     ecx,[ecx+ecx*4]
            loc_00401179: lea     ecx,[ecx+edx*2]
            loc_0040117C: lea     edx,[eax+eax*2]
            loc_0040117F: shl     edx,3
            loc_00401182: mov     eax,66666667h
            loc_00401187: imul    edx
            loc_00401189: sar     edx,1
            loc_0040118B: mov     eax,edx
            loc_0040118D: shr     eax,1Fh
            loc_00401190: add     edx,eax
            loc_00401192: cmp     ebp,0BAh
            loc_00401198: jne     loc_004011B9
                          xchg    ebp, [esp]
            loc_0040119A: cmp     [temp],0FCh
                          xchg    ebp, [esp]
            loc_004011A2: jne     loc_004011B9
            loc_004011A4: cmp     ecx,0B1h
            loc_004011AA: jne     loc_004011B9
            loc_004011AC: cmp     edx,0E700h
            loc_004011B2: jne     loc_004011B9
                          xchg    ebp, [esp]
            loc_004011B4: mov     [r],1
                          xchg    ebp, [esp]
            loc_004011B9: pop     ebp
          };

        if(r)
        {
            printf("Found! %d %d %d %d\n", a, b, c, d);
            break;
        }
  }
}

void print_bigln(char *m, big a)
{
    g_buff[0]=0;
    cotstr(a, g_buff);
    printf("%s",m);
    printf("%s\n",g_buff);
}

void print_big(big a)
{
    g_buff[0]=0;
    cotstr(a, g_buff);
    printf("%s",g_buff);
}

void main(int argc, char * argv[])
{
    printf("[*] %s",info);

    // general variables
    DWORD dwRet;
    miracl *mip=mirsys(256, 0);
    mip->IOBASE=16;

    // make message
    srand(time(0));
    char msg[9]="CAFE0000";
    for(int i=0;i<8;++i)
        msg[i]=33+(rand()%93);
    big M=mirvar(0);
    UCHAR hash[16]={0};
    MD5_CTX context;
    MD5Init(&context);
    MD5Update(&context,(PUCHAR)msg,8);
    MD5Final(hash, &context);
    bytes_to_big(8,(char*)hash,M);
    print_bigln("[*] M:",M);

    // G: 4964487852872863996512856848
    big G=mirvar(0); cinstr(G,"100A8731C4A45A47A0906B10"); print_bigln("[*] G:",G);

    // Y: 52267259776770581361584121916
    big Y=mirvar(0); cinstr(Y,"A8E276C5FDF00FA415C2283C"); print_bigln("[*] Y:",Y);

    // Q: 10207867916036547437
    big Q=mirvar(0); cinstr(Q,"8DA9A1C93977236D");         print_bigln("[*] Q:",Q);

    // P: 60835712804148883187189330887 ~48 bits
    big P=mirvar(0); cinstr(P,"C4921F47591E845FB382B3C7"); print_bigln("[*] P:",P);

    // P-1: 60835712804148883187189330887
    // factors into 2 3 113 163 53927 10207867916036547437

    // G^X = Y
    // X: 74020797241683 found in 15 minutes, 3 seconds using Dario Alpern's DILOG solver
    //
    big X=mirvar(0); cinstr(X,"43524F535953");             print_bigln("[*] X:",X);

    // Serial: [M: 8 characters][R: 8 characters][S: 8 characters]
    // 
    // crackme checks:
    //
    // R = G^(H(M)*S^-1(MOD Q)) * Y^(R*S^-1(MOD Q)) (MOD P)(MOD Q) 
    //
    // This is directly DSA signature verification, so we just sign the message:
    //
    // R = (G^K mod P) mod Q
    // S = K^-1 (H(M) + XR) mod Q
    //
    // In other words, we solved the equation H(M) = SK - XR (mod Q) For R, S
    // after choosing random K value.
    //

    // generate K
    irand(GetTickCount());
    big K=mirvar(0);
    bigbits(63,K); // same size as Q
    print_bigln("[*] K:",K); 

    // Find R
    big one=mirvar(1);
    big R=mirvar(0);
    powmod(G,K,P,R);
    powmod(R,one,Q,R);
    print_bigln("[*] R:",R);

    // Find 1/K (MOD Q)
    big KINV=mirvar(0);
    xgcd(K,Q,KINV,KINV,KINV);
    print_bigln("[*] 1/K (MOD Q):",KINV);

    // Find S
    big S=mirvar(0);
    multiply(X,R,S);
    add(S,M,S);
    multiply(S,KINV,S);
    powmod(S,one,Q,S);
    print_bigln("[*] S:",S);

    // print first serial number
    // 0000 0001 and 0000 0001 are any two coprime numbers
    // the 20 08 07 and 11 were found via brute_00401192()
    printf("[*]\n");
    printf("[*] First serial: 0000 0001 0000 0001 2008 0711\n");

    // serial is just message and the signature pieces R and S
    printf("[*]\n");
    printf("[*] Second Serial: ");
    printf("%s-",msg);
    mip->IOBASE=24;
    print_big(R);
    print_bigln("-",S);
    printf("[*]\n");
    
    // keypress
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), g_buff, 1, &dwRet, 0);
}

