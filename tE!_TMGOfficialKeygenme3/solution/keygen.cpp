char *info= "KEYGEN \"TMG official keygenme #3\" 2008 andrewl\n";

/* RELEVENT CODE FROM CRACKME:
 
.text:0040116B         mov     edi, eax
.text:0040116D         lea     eax, [esp+20Ch+context]
.text:00401174         push    eax
.text:00401175         call    MD5_Init
.text:0040117A         mov     ecx, [esp+210h+len_name]
.text:0040117E         add     esp, 4
.text:00401181         lea     edx, [esp+20Ch+user]
.text:00401188         lea     eax, [esp+20Ch+context]
.text:0040118F         push    ecx
.text:00401190         push    edx
.text:00401191         push    eax
.text:00401192         call    MD5_Update
.text:00401197         add     esp, 0Ch
.text:0040119A         lea     ecx, [esp+20Ch+context]
.text:004011A1         lea     edx, [esp+20Ch+hash]
.text:004011A5         push    ecx
.text:004011A6         push    edx
.text:004011A7         call    MD5_Final               ; take hash of username
.text:004011A7                                         ;
.text:004011AC         mov     eax, miracl_settings
.text:004011B1         add     esp, 8
.text:004011B4         lea     edx, [esp+20Ch+hash]
.text:004011B8         mov     dword ptr [eax+22Ch], 100h
.text:004011C2         mov     ecx, miracl_settings
.text:004011C8         push    edx
.text:004011C9         push    ebp
.text:004011CA         mov     dword ptr [ecx+23Ch], 10h
.text:004011D4         call    cinstr                  ; md5(username)
.text:004011D4                                         ;
.text:004011D9         mov     eax, miracl_settings
.text:004011DE         add     esp, 8                  ;
.text:004011DE                                         ;
.text:004011E1         push    offset C1               ; "37A218F214C32D79"
.text:004011E6         push    esi                     ; esi = bignum_37A218F214C32D79
.text:004011E7         mov     dword ptr [eax+22Ch], 10h
.text:004011F1         call    cinstr
.text:004011F6         add     esp, 8                  ;
.text:004011F6                                         ;
.text:004011F9         push    ebp
.text:004011FA         push    esi                     ;  mod: C1
.text:004011FB         push    3                       ;  exp: 3
.text:004011FD         push    ebp                     ; base: md5(username)
.text:004011FE         call    powmod1
.text:00401203         add     esp, 10h                ; ebp: M = md5(username)^3 (mod P)
.text:00401203                                         ;
.text:00401206
.text:00401206 GET_SERIAL_COMPONENTS:
.text:00401206         mov     edx, [esp+20Ch+A]
.text:0040120A         lea     ecx, [esp+20Ch+serial]
.text:0040120E         push    ecx
.text:0040120F         push    edx
.text:00401210         call    cinstr                  ; A = serial[0..15]
.text:00401210                                         ;
.text:00401215         mov     ecx, [esp+214h+B]
.text:00401219         add     esp, 8
.text:0040121C         lea     eax, [esp+20Ch+str_serial_B]
.text:00401223         push    eax
.text:00401224         push    ecx
.text:00401225         call    cinstr                  ; B = serial[16..31]
.text:00401225                                         ;
.text:0040122A
.text:0040122A GET_PRIME_MINUS_1:
.text:0040122A         add     esp, 8
.text:0040122D         push    offset P                ; "C9D94F46D0984F42"
.text:00401232         push    esi
.text:00401233         call    cinstr
.text:00401238
.text:00401238 GET_Y:
.text:00401238         mov     edx, [esp+214h+Y]
.text:0040123C         add     esp, 8
.text:0040123F         push    offset Y                ; "91D4D6EF46B05C78"
.text:00401244         push    edx
.text:00401245         call    cinstr                  ;
.text:00401245                                         ;
.text:0040124A         mov     eax, [esp+214h+G]
.text:0040124E         add     esp, 8
.text:00401251         push    offset G                ; "4B45042B684BCBD1"
.text:00401256         push    eax
.text:00401257         call    cinstr
.text:0040125C         add     esp, 8
.text:0040125F
.text:0040125F INCREMENT_TO_PRIME:
.text:0040125F         push    esi
.text:00401260         push    1
.text:00401262         push    esi
.text:00401263         call    add                     ; esi: P
.text:00401263                                         ;
.text:00401268         mov     ecx, [esp+218h+B]
.text:0040126C         mov     edx, [esp+218h+A]
.text:00401270         add     esp, 0Ch
.text:00401273         push    ebx
.text:00401274         push    esi
.text:00401275         push    ecx
.text:00401276         push    edx
.text:00401277         call    powmod2                 ; ebx: A^B (mod P)
.text:00401277                                         ;
.text:0040127C         mov     eax, [esp+21Ch+A]
.text:00401280         mov     ecx, [esp+21Ch+Y]
.text:00401284         add     esp, 10h
.text:00401287         push    edi
.text:00401288         push    esi                     ;  mod: P
.text:00401289         push    eax                     ;  exp: A
.text:0040128A         push    ecx                     ; base: Y
.text:0040128B         call    powmod2                 ; edi = Y^A (mod P)
.text:0040128B                                         ;
.text:00401290         add     esp, 10h
.text:00401293         push    edi
.text:00401294         push    esi
.text:00401295         push    esi                     ;  mod: P
.text:00401296         push    edi
.text:00401297         push    edi                     ; f1: Y^A (mod P)
.text:00401298         push    ebx                     ; f2: A^B (mod P)
.text:00401299         call    mulmod                  ; edi: Y^A * A^B (mod P)
.text:00401299                                         ;
.text:0040129E         mov     edx, [esp+224h+G]
.text:004012A2         add     esp, 18h
.text:004012A5         push    ebx
.text:004012A6         push    esi                     ; P
.text:004012A7         push    ebp                     ; M
.text:004012A8         push    edx                     ; G
.text:004012A9         call    powmod2                 ; ebx = G^M (mod P)
.text:004012A9                                         ;
.text:004012AE         add     esp, 10h
.text:004012B1         push    edi                     ; Y * X^B (mod n)
.text:004012B2         push    ebx                     ; G^M mod P
.text:004012B3         call    compare
*/

// os
#include <windows.h>

// stdio
#include <stdio.h>

// miracl
extern "C" {
#include <miracl.h>

#include <global.h>
#include <md5.h>
}

// globals
char g_buff[512];

// functions
void print_bigln(char *m, big a)
{
    g_buff[0]=0;
    cotstr(a, g_buff);
    printf("%s ",m);
    for(int i=0; i<(16-strlen(g_buff)); ++i) printf("0");
    printf("%s\n",g_buff);
}

void print_big(big a)
{
    g_buff[0]=0;
    cotstr(a, g_buff);
    for(int i=0; i<(16-strlen(g_buff)); ++i) printf("0");
    printf("%s",g_buff);
}

void main(int argc, char * argv[])
{

    printf("[*] %s",info);

    // general variables
    DWORD dwRet;

    // args
    CHAR *user="thigo";

    if(argc<2)
        printf("[*] No user argument, defaulting..\n");
    else
        user=argv[1];

    printf("[*] Calculating key for user: %s\n", user);

    // Message is derived from username:
    //
    // MU = 37A218F214C32D79 = 4008794046322650489 = 3*3*29*71*216329072706419
    //
    // M = MD5(user)^3 mod MU
    
    // 
    //
    // P-1 = C9D94F46D0984F42 = 14544743637135675202 = 2*2305357*3154553424293
    // P = C9D94F46D0984F43 = 14544743637135675203 = prime
    // G = 4B45042B684BCBD1 = 5423745910717533137 = 17*541*5867
    //
    // is G really a primitive root of P? yes:
    // G^((P-1)/2) mod P = G^7272371818567837601 mod P = 14544743637135675202 != 1
    // G^((P-1)/2305357) mod P = G^6309106848586 mod P = 1808119380712922532 != 1
    // G^((P-1)/3154553424293) mod P = G^4610714 mod P = 1643557918521199747 != 1
    //
    // X = 6C18DA28FDD8FEF1 = 7789215425129676529
    // Y = 91D4D6EF46B05C78 = 10508260153733700728 = 2*2*2*23*23*113*49123*447323621
    //   = G^X
    //

    miracl *mip=mirsys(256, 0);
    mip->IOBASE=16;

    big MU=mirvar(0); cinstr(MU,"37A218F214C32D79");     
    big PHI=mirvar(0); cinstr(PHI,"C9D94F46D0984F42"); print_bigln("[*] PHI:",PHI);
    big P=mirvar(0); incr(PHI,1,P); print_bigln("[*] P:",P);
    big Y=mirvar(0); cinstr(Y,"91D4D6EF46B05C78"); print_bigln("[*] Y:",Y);
    big G=mirvar(0); cinstr(G,"4B45042B684BCBD1"); print_bigln("[*] G:",G);
    big X=mirvar(0); cinstr(X,"6C18DA28FDD8FEF1"); print_bigln("[*] X:",X);

    // calculate M = MD5(user)^3 mod MU
    big M=mirvar(0);
    big three=mirvar(3);
    UCHAR hash[16]={0};
    MD5_CTX context;
    MD5Init(&context);
    MD5Update(&context,(PUCHAR)user,strlen(user));
    MD5Final(hash, &context);
    bytes_to_big(16,(char*)hash,M);
    powmod(M,three,MU,M);
    print_bigln("[*] M:",M);

    // Serial: [A: 16 characters][B: 16 characters]
    // 
    // crackme checks:
    //
    // Y^A * A^B = G^M (MOD P)
    // (G^X)^A * A^B = G^M (MOD P)
    // G^(XA) * A^B = G^M (MOD P)
    //
    // Since A is a member of the group Zp^*, it can be expressed as
    // the generator G raised the power of a member of the group mod
    // P, call this member K
    //
    // G^(XA) * (G^K)^B = G^M (MOD P)
    // G^(XA) * G^(KB) = G^M (MOD P)
    // G^(XA + KB) = G^M (MOD P)
    // XA + KB = M (MOD P-1)
    //
    // If we choose K, GCD(K,P-1)=1, then K is guaranteed to have a
    // multiplicative inverse (MOD P-1) and thus we may compute B:
    //
    // B = K^1(M - XA) (MOD P-1)
    //
    
    // Generate K:
    irand(GetTickCount());
    big gcd=mirvar(0);
    big K=mirvar(0);
    while(1)
    {
        bigbits(64,K);
        egcd(K,PHI,gcd);
        if(size(gcd)==1) break;
    }
    print_bigln("[*] K:",K); 

    // Find A
    big A=mirvar(0);
    powmod(G,K,P,A);
    print_bigln("[*] A:",A);

    // Find 1/K (MOD P-1)
    big KINV=mirvar(0);
    xgcd(K,PHI,KINV,KINV,KINV);
    print_bigln("[*] 1/K (MOD P-1):",KINV);

    // Find B
    big one=mirvar(1);
    big B=mirvar(0);
    multiply(X,A,B); //B=XA
    subtract(M,B,B); //B=M-XA   ...will likely have a negative number here
    multiply(B,KINV,B); 
    powmod(B,one,PHI,B); // ignorant man's modulus
    if(exsign(B)<0) add(B,PHI,B);
    print_bigln("[*] B:",B);

    // final key is just A and B concatenated...
    //
    printf("[*]\n");
    printf("[*] key: ");
    print_big(A);
    print_big(B);
    printf("\n");
    printf("[*]\n");

    // keypress
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), g_buff, 1, &dwRet, 0);
}

