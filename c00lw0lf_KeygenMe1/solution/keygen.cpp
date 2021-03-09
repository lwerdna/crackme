// 8/28/2008 andrewl

// os
#include <windows.h>

// stdio
#include <stdio.h>

// miracl
extern "C" {
#include <miracl.h>
}

void main(int argc, char * argv[])
{
    printf("[*] Keygen for \"c00lw0lf's KeygenMe1\" 2008 andrewl\n");

    // general variables
    DWORD dwRet;
    char buff[256];

    // args
    CHAR volume_serial[16];

    if(argc<2)
    {
        printf("[*] No key argument, defaulting..\n");
        GetVolumeInformation("C:\\", 0, 0, &dwRet, 0, 0, 0, 0);
        wsprintf(volume_serial, "%u", dwRet);
    }
    else
        strcpy(volume_serial, argv[1]);

    printf("[*] Calculating key for volume serial: %s\n", volume_serial);

    //   n: 666AAA422FDF79E1D4E41EDDC4D42C51 // from crackme
    //   p: 838512BE2D7B26B3                 // factored
    //   q: C759F807A2BCC2EB                 // factored
    // phi: 666AAA422FDF79E08A051417F49C42B4 // (p-1)*(q-1)
    //   d: 29F8EEDBC262484C2E3F60952B73D067 // from crackme
    //   e: 65537                            // d^-1(mod phi)
   
    // crackme checks that:
    //
    // key^d == serial
    //
    // we reverse this by serial^e
    //
    // now:
    //   key^d = serial
    // = (serial^e)^d == serial
    // = serial^(ed) == serial
    //
    // this is true when d = e^1(phi(n)) (RSA Scheme)

    miracl *mip=mirsys(256, 0);
    mip->IOBASE=16;

    // required numbers for cipher
    big n=mirvar(0);
    cinstr(n, "666AAA422FDF79E1D4E41EDDC4D42C51");
    big e=mirvar(0x65537);

    // form plaintext value using volume serial number
    big text=mirvar(0);
    bytes_to_big(strlen(volume_serial), volume_serial, text);
    cotstr(text, buff);
    printf("[*] Value derived from volume serial: %s\n", buff);
    cotstr(e, buff);

    // plaintext -> ciphertext, print out serial
    powmod(text, e, n, text);
    cotstr(text, buff);
    printf("[*]\n");
    printf("[*] Serial: %s\n", buff);
    printf("[*]\n");

    // pause until keypress
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buff, 1, &dwRet, 0);

    // 
    mirkill(n);
    mirkill(e);
    mirkill(text);
}
