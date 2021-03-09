// keygen to upb's "push the pusher" crackme
// 2009 andrewl

#include <windows.h>

#include <stdio.h>

// random stuff
//
INT g_rand_val = 0;
VOID my_srand(INT seed) {
    g_rand_val = seed;
}
WORD my_rand() {
    g_rand_val = (g_rand_val * 0x343FD) + 0x269EC3;
    return (g_rand_val >> 16) & 0x7FFF;
}

// crc stuff
// 
// #include "crc.h"
// <rip>
unsigned long crc_table[256];

unsigned char crc_table_bytes[1024] =
{
    0x00, 0x00, 0x00, 0x00, 0x96, 0x30, 0x07, 0x77, // .....0.w
    0x2C, 0x61, 0x0E, 0xEE, 0xBA, 0x51, 0x09, 0x99, // ,a...Q..
    0x19, 0xC4, 0x6D, 0x07, 0x8F, 0xF4, 0x6A, 0x70, // ..m...jp
    0x35, 0xA5, 0x63, 0xE9, 0xA3, 0x95, 0x64, 0x9E, // 5.c...d.
    0x32, 0x88, 0xDB, 0x0E, 0xA4, 0xB8, 0xDC, 0x79, // 2......y
    0x1E, 0xE9, 0xD5, 0xE0, 0x88, 0xD9, 0xD2, 0x97, // ........
    0x2B, 0x4C, 0xB6, 0x09, 0xBD, 0x7C, 0xB1, 0x7E, // +L...|.~
    0x07, 0x2D, 0xB8, 0xE7, 0x91, 0x1D, 0xBF, 0x90, // .-......
    0x64, 0x10, 0xB7, 0x1D, 0xF2, 0x20, 0xB0, 0x6A, // d.... .j
    0x48, 0x71, 0xB9, 0xF3, 0xDE, 0x41, 0xBE, 0x84, // Hq...A..
    0x7D, 0xD4, 0xDA, 0x1A, 0xEB, 0xE4, 0xDD, 0x6D, // }......m
    0x51, 0xB5, 0xD4, 0xF4, 0xC7, 0x85, 0xD3, 0x83, // Q.......
    0x56, 0x98, 0x6C, 0x13, 0xC0, 0xA8, 0x6B, 0x64, // V.l...kd
    0x7A, 0xF9, 0x62, 0xFD, 0xEC, 0xC9, 0x65, 0x8A, // z.b...e.
    0x4F, 0x5C, 0x01, 0x14, 0xD9, 0x6C, 0x06, 0x63, // O\...l.c
    0x63, 0x3D, 0x0F, 0xFA, 0xF5, 0x0D, 0x08, 0x8D, // c=......
    0xC8, 0x20, 0x6E, 0x3B, 0x5E, 0x10, 0x69, 0x4C, // . n;^.iL
    0xE4, 0x41, 0x60, 0xD5, 0x72, 0x71, 0x67, 0xA2, // .A`.rqg.
    0xD1, 0xE4, 0x03, 0x3C, 0x47, 0xD4, 0x04, 0x4B, // ...<G..K
    0xFD, 0x85, 0x0D, 0xD2, 0x6B, 0xB5, 0x0A, 0xA5, // ....k...
    0xFA, 0xA8, 0xB5, 0x35, 0x6C, 0x98, 0xB2, 0x42, // ...5l..B
    0xD6, 0xC9, 0xBB, 0xDB, 0x40, 0xF9, 0xBC, 0xAC, // ....@...
    0xE3, 0x6C, 0xD8, 0x32, 0x75, 0x5C, 0xDF, 0x45, // .l.2u\.E
    0xCF, 0x0D, 0xD6, 0xDC, 0x59, 0x3D, 0xD1, 0xAB, // ....Y=..
    0xAC, 0x30, 0xD9, 0x26, 0x3A, 0x00, 0xDE, 0x51, // .0.&:..Q
    0x80, 0x51, 0xD7, 0xC8, 0x16, 0x61, 0xD0, 0xBF, // .Q...a..
    0xB5, 0xF4, 0xB4, 0x21, 0x23, 0xC4, 0xB3, 0x56, // ...!#..V
    0x99, 0x95, 0xBA, 0xCF, 0x0F, 0xA5, 0xBD, 0xB8, // ........
    0x9E, 0xB8, 0x02, 0x28, 0x08, 0x88, 0x05, 0x5F, // ...(..._
    0xB2, 0xD9, 0x0C, 0xC6, 0x24, 0xE9, 0x0B, 0xB1, // ....$...
    0x87, 0x7C, 0x6F, 0x2F, 0x11, 0x4C, 0x68, 0x58, // .|o/.LhX
    0xAB, 0x1D, 0x61, 0xC1, 0x3D, 0x2D, 0x66, 0xB6, // ..a.=-f.
    0x90, 0x41, 0xDC, 0x76, 0x06, 0x71, 0xDB, 0x01, // .A.v.q..
    0xBC, 0x20, 0xD2, 0x98, 0x2A, 0x10, 0xD5, 0xEF, // . ..*...
    0x89, 0x85, 0xB1, 0x71, 0x1F, 0xB5, 0xB6, 0x06, // ...q....
    0xA5, 0xE4, 0xBF, 0x9F, 0x33, 0xD4, 0xB8, 0xE8, // ....3...
    0xA2, 0xC9, 0x07, 0x78, 0x34, 0xF9, 0x00, 0x0F, // ...x4...
    0x8E, 0xA8, 0x09, 0x96, 0x18, 0x98, 0x0E, 0xE1, // ........
    0xBB, 0x0D, 0x6A, 0x7F, 0x2D, 0x3D, 0x6D, 0x08, // ..j.-=m.
    0x97, 0x6C, 0x64, 0x91, 0x01, 0x5C, 0x63, 0xE6, // .ld..\c.
    0xF4, 0x51, 0x6B, 0x6B, 0x62, 0x61, 0x6C, 0x1C, // .Qkkbal.
    0xD8, 0x30, 0x65, 0x85, 0x4E, 0x00, 0x62, 0xF2, // .0e.N.b.
    0xED, 0x95, 0x06, 0x6C, 0x7B, 0xA5, 0x01, 0x1B, // ...l{...
    0xC1, 0xF4, 0x08, 0x82, 0x57, 0xC4, 0x0F, 0xF5, // ....W...
    0xC6, 0xD9, 0xB0, 0x65, 0x50, 0xE9, 0xB7, 0x12, // ...eP...
    0xEA, 0xB8, 0xBE, 0x8B, 0x7C, 0x88, 0xB9, 0xFC, // ....|...
    0xDF, 0x1D, 0xDD, 0x62, 0x49, 0x2D, 0xDA, 0x15, // ...bI-..
    0xF3, 0x7C, 0xD3, 0x8C, 0x65, 0x4C, 0xD4, 0xFB, // .|..eL..
    0x58, 0x61, 0xB2, 0x4D, 0xCE, 0x51, 0xB5, 0x3A, // Xa.M.Q.:
    0x74, 0x00, 0xBC, 0xA3, 0xE2, 0x30, 0xBB, 0xD4, // t....0..
    0x41, 0xA5, 0xDF, 0x4A, 0xD7, 0x95, 0xD8, 0x3D, // A..J...=
    0x6D, 0xC4, 0xD1, 0xA4, 0xFB, 0xF4, 0xD6, 0xD3, // m.......
    0x6A, 0xE9, 0x69, 0x43, 0xFC, 0xD9, 0x6E, 0x34, // j.iC..n4
    0x46, 0x88, 0x67, 0xAD, 0xD0, 0xB8, 0x60, 0xDA, // F.g...`.
    0x73, 0x2D, 0x04, 0x44, 0xE5, 0x1D, 0x03, 0x33, // s-.D...3
    0x5F, 0x4C, 0x0A, 0xAA, 0xC9, 0x7C, 0x0D, 0xDD, // _L...|..
    0x3C, 0x71, 0x05, 0x50, 0xAA, 0x41, 0x02, 0x27, // <q.P.A.'
    0x10, 0x10, 0x0B, 0xBE, 0x86, 0x20, 0x0C, 0xC9, // ..... ..
    0x25, 0xB5, 0x68, 0x57, 0xB3, 0x85, 0x6F, 0x20, // %.hW..o 
    0x09, 0xD4, 0x66, 0xB9, 0x9F, 0xE4, 0x61, 0xCE, // ..f...a.
    0x0E, 0xF9, 0xDE, 0x5E, 0x98, 0xC9, 0xD9, 0x29, // ...^...)
    0x22, 0x98, 0xD0, 0xB0, 0xB4, 0xA8, 0xD7, 0xC7, // ".......
    0x17, 0x3D, 0xB3, 0x59, 0x81, 0x0D, 0xB4, 0x2E, // .=.Y....
    0x3B, 0x5C, 0xBD, 0xB7, 0xAD, 0x6C, 0xBA, 0xC0, // ;\...l..
    0x20, 0x83, 0xB8, 0xED, 0xB6, 0xB3, 0xBF, 0x9A, //  .......
    0x0C, 0xE2, 0xB6, 0x03, 0x9A, 0xD2, 0xB1, 0x74, // .......t
    0x39, 0x47, 0xD5, 0xEA, 0xAF, 0x77, 0xD2, 0x9D, // 9G...w..
    0x15, 0x26, 0xDB, 0x04, 0x83, 0x16, 0xDC, 0x73, // .&.....s
    0x12, 0x0B, 0x63, 0xE3, 0x84, 0x3B, 0x64, 0x94, // ..c..;d.
    0x3E, 0x6A, 0x6D, 0x0D, 0xA8, 0x5A, 0x6A, 0x7A, // >jm..Zjz
    0x0B, 0xCF, 0x0E, 0xE4, 0x9D, 0xFF, 0x09, 0x93, // ........
    0x27, 0xAE, 0x00, 0x0A, 0xB1, 0x9E, 0x07, 0x7D, // '......}
    0x44, 0x93, 0x0F, 0xF0, 0xD2, 0xA3, 0x08, 0x87, // D.......
    0x68, 0xF2, 0x01, 0x1E, 0xFE, 0xC2, 0x06, 0x69, // h......i
    0x5D, 0x57, 0x62, 0xF7, 0xCB, 0x67, 0x65, 0x80, // ]Wb..ge.
    0x71, 0x36, 0x6C, 0x19, 0xE7, 0x06, 0x6B, 0x6E, // q6l...kn
    0x76, 0x1B, 0xD4, 0xFE, 0xE0, 0x2B, 0xD3, 0x89, // v....+..
    0x5A, 0x7A, 0xDA, 0x10, 0xCC, 0x4A, 0xDD, 0x67, // Zz...J.g
    0x6F, 0xDF, 0xB9, 0xF9, 0xF9, 0xEF, 0xBE, 0x8E, // o.......
    0x43, 0xBE, 0xB7, 0x17, 0xD5, 0x8E, 0xB0, 0x60, // C......`
    0xE8, 0xA3, 0xD6, 0xD6, 0x7E, 0x93, 0xD1, 0xA1, // ....~...
    0xC4, 0xC2, 0xD8, 0x38, 0x52, 0xF2, 0xDF, 0x4F, // ...8R..O
    0xF1, 0x67, 0xBB, 0xD1, 0x67, 0x57, 0xBC, 0xA6, // .g..gW..
    0xDD, 0x06, 0xB5, 0x3F, 0x4B, 0x36, 0xB2, 0x48, // ...?K6.H
    0xDA, 0x2B, 0x0D, 0xD8, 0x4C, 0x1B, 0x0A, 0xAF, // .+..L...
    0xF6, 0x4A, 0x03, 0x36, 0x60, 0x7A, 0x04, 0x41, // .J.6`z.A
    0xC3, 0xEF, 0x60, 0xDF, 0x55, 0xDF, 0x67, 0xA8, // ..`.U.g.
    0xEF, 0x8E, 0x6E, 0x31, 0x79, 0xBE, 0x69, 0x46, // ..n1y.iF
    0x8C, 0xB3, 0x61, 0xCB, 0x1A, 0x83, 0x66, 0xBC, // ..a...f.
    0xA0, 0xD2, 0x6F, 0x25, 0x36, 0xE2, 0x68, 0x52, // ..o%6.hR
    0x95, 0x77, 0x0C, 0xCC, 0x03, 0x47, 0x0B, 0xBB, // .w...G..
    0xB9, 0x16, 0x02, 0x22, 0x2F, 0x26, 0x05, 0x55, // ..."/&.U
    0xBE, 0x3B, 0xBA, 0xC5, 0x28, 0x0B, 0xBD, 0xB2, // .;..(...
    0x92, 0x5A, 0xB4, 0x2B, 0x04, 0x6A, 0xB3, 0x5C, // .Z.+.j..
    0xA7, 0xFF, 0xD7, 0xC2, 0x31, 0xCF, 0xD0, 0xB5, // ....1...
    0x8B, 0x9E, 0xD9, 0x2C, 0x1D, 0xAE, 0xDE, 0x5B, // ...,...[
    0xB0, 0xC2, 0x64, 0x9B, 0x26, 0xF2, 0x63, 0xEC, // ..d.&.c.
    0x9C, 0xA3, 0x6A, 0x75, 0x0A, 0x93, 0x6D, 0x02, // ..ju..m.
    0xA9, 0x06, 0x09, 0x9C, 0x3F, 0x36, 0x0E, 0xEB, // ....?6..
    0x85, 0x67, 0x07, 0x72, 0x13, 0x57, 0x00, 0x05, // .g.r.W..
    0x82, 0x4A, 0xBF, 0x95, 0x14, 0x7A, 0xB8, 0xE2, // .J...z..
    0xAE, 0x2B, 0xB1, 0x7B, 0x38, 0x1B, 0xB6, 0x0C, // .+.{8...
    0x9B, 0x8E, 0xD2, 0x92, 0x0D, 0xBE, 0xD5, 0xE5, // ........
    0xB7, 0xEF, 0xDC, 0x7C, 0x21, 0xDF, 0xDB, 0x0B, // ...|!...
    0xD4, 0xD2, 0xD3, 0x86, 0x42, 0xE2, 0xD4, 0xF1, // ....B...
    0xF8, 0xB3, 0xDD, 0x68, 0x6E, 0x83, 0xDA, 0x1F, // ...hn...
    0xCD, 0x16, 0xBE, 0x81, 0x5B, 0x26, 0xB9, 0xF6, // ....[&..
    0xE1, 0x77, 0xB0, 0x6F, 0x77, 0x47, 0xB7, 0x18, // .w.owG..
    0xE6, 0x5A, 0x08, 0x88, 0x70, 0x6A, 0x0F, 0xFF, // .Z..pj..
    0xCA, 0x3B, 0x06, 0x66, 0x5C, 0x0B, 0x01, 0x11, // .;.f\...
    0xFF, 0x9E, 0x65, 0x8F, 0x69, 0xAE, 0x62, 0xF8, // ..e.i.b.
    0xD3, 0xFF, 0x6B, 0x61, 0x45, 0xCF, 0x6C, 0x16, // ..kaE.l.
    0x78, 0xE2, 0x0A, 0xA0, 0xEE, 0xD2, 0x0D, 0xD7, // x.......
    0x54, 0x83, 0x04, 0x4E, 0xC2, 0xB3, 0x03, 0x39, // T..N...9
    0x61, 0x26, 0x67, 0xA7, 0xF7, 0x16, 0x60, 0xD0, // a&g...`.
    0x4D, 0x47, 0x69, 0x49, 0xDB, 0x77, 0x6E, 0x3E, // MGiI.wn>
    0x4A, 0x6A, 0xD1, 0xAE, 0xDC, 0x5A, 0xD6, 0xD9, // Jj...Z..
    0x66, 0x0B, 0xDF, 0x40, 0xF0, 0x3B, 0xD8, 0x37, // f..@.;.7
    0x53, 0xAE, 0xBC, 0xA9, 0xC5, 0x9E, 0xBB, 0xDE, // S.......
    0x7F, 0xCF, 0xB2, 0x47, 0xE9, 0xFF, 0xB5, 0x30, // ...G...0
    0x1C, 0xF2, 0xBD, 0xBD, 0x8A, 0xC2, 0xBA, 0xCA, // ........
    0x30, 0x93, 0xB3, 0x53, 0xA6, 0xA3, 0xB4, 0x24, // 0..S...$
    0x05, 0x36, 0xD0, 0xBA, 0x93, 0x06, 0xD7, 0xCD, // .6......
    0x29, 0x57, 0xDE, 0x54, 0xBF, 0x67, 0xD9, 0x23, // )W.T.g.#
    0x2E, 0x7A, 0x66, 0xB3, 0xB8, 0x4A, 0x61, 0xC4, // .zf..Ja.
    0x02, 0x1B, 0x68, 0x5D, 0x94, 0x2B, 0x6F, 0x2A, // ..h].+o*
    0x37, 0xBE, 0x0B, 0xB4, 0xA1, 0x8E, 0x0C, 0xC3, // 7.......
    0x1B, 0xDF, 0x05, 0x5A, 0x8D, 0xEF, 0x02, 0x2D  // ...Z...-
};

unsigned long crc32(unsigned char * p_input, unsigned int len, unsigned int crc)
{
    __asm
    {
        loc_00401003: jmp     loop_check

        loop_next:    mov     eax,dword ptr [len]
        loc_00401008: sub     eax,1
        loc_0040100B: mov     dword ptr [len],eax
        loop_check:   cmp     dword ptr [len],0
        loc_00401012: jbe     loop_last

        loop_body:    mov     ecx,dword ptr [crc]
        loc_00401017: shr     ecx,8
        loc_0040101A: and     ecx,0FFFFFFh              // ecx = CRC >> 8

        loc_00401020: mov     edx,dword ptr [p_input]
        loc_00401023: movzx   eax,byte ptr [edx]
        loc_00401026: xor     eax,dword ptr [crc]
        loc_00401029: and     eax,0FFh                  // eax = CRC ^ *pinput (just the lo byte)

        loc_0040102E: xor     ecx, crc_table[eax*4]
        loc_00401035: mov     dword ptr [crc],ecx       // CRC = (CRC >> 8) ^ table[CRC ^ *pinput]

        loc_00401038: mov     ecx,dword ptr [p_input]   // p_input++
        loc_0040103B: add     ecx,1
        loc_0040103E: mov     dword ptr [p_input],ecx

        loc_00401041: jmp     loop_next
        loop_last:    nop
    };

    return crc;
}

PCHAR hextab="1234567890ABCDEF";

void main(INT ac, PCHAR av[])
{
    PCHAR user = "crackmes.de";
    if(ac>1) user=av[1];
    else printf("(user can be changed with argument)\n");
    printf("processing user: %s\n",user);

    memcpy(crc_table, crc_table_bytes, 1024);

    UCHAR buf[0x1000];

    UCHAR msgenc[0x45] =
    {
        0x9B, 0x2F, 0x51, 0x95, 0x49, 0x3D, 0xEC, 0xD7, // ./Q.I=..
        0xCE, 0x23, 0x5B, 0x75, 0x12, 0x25, 0xB1, 0x7C, // .#[u.%.|
        0xF7, 0xEF, 0x05, 0xFD, 0x6F, 0xEA, 0xA7, 0x01, // ....o...
        0x7E, 0xA1, 0xE6, 0xD7, 0x69, 0x7F, 0xDA, 0xD2, // ~...i...
        0x66, 0x62, 0xB8, 0xAC, 0x06, 0xEA, 0xC9, 0x4C, // fb.....L
        0x6C, 0x22, 0x25, 0xCD, 0x41, 0x55, 0xDC, 0x80, // l"%.AU..
        0x7F, 0x4C, 0x58, 0x9B, 0x29, 0x8E, 0xFF, 0x86, // .LX.)...
        0xB2, 0xCF, 0x0B, 0x96, 0x9C, 0xAE, 0xA9, 0xD9, // ........
        0xE9, 0x0F, 0x9E, 0xEA, 0x00                    // .....   
    };

    // generate first part of serial:
    CHAR serial[256];
    memset(serial,0,256);
    serial[0]=hextab[GetTickCount()&0xF];
    serial[1]=hextab[(GetTickCount()&0xF0)>>4];
    serial[2]=hextab[(GetTickCount()&0xF00)>>8];
    serial[3]=hextab[(GetTickCount()&0xF000)>>12];
    strcat(serial,"-");
    printf("building on serial: %s\n",serial);

    // emulate crackme to produce CRC32 input buffer
    memset(buf,0,0x1000);
    memcpy(buf,msgenc,0x45);
    for(INT i=0;i<strlen(user);++i)
        buf[i]^=user[i];
    my_srand(*(PUINT)serial);
    for(INT i=0;i<0x1000;++i)
        buf[i]^=(my_rand()>>4);
    printf("start of input buffer: ");
    for(INT i=0;i<16;++i)
        printf("%02X ",0xFF&buf[i]);
    printf("\n");

    // determine how to change buffer
	ULONG crc=crc32((PUCHAR)buf,0xFFC,0x21337455);
    printf("\"trap\" value: %08X\n",crc);

    ULONG old_last4=*(PULONG)(buf+0xFFC);
    printf("old: %08X\n",old_last4);

    ULONG new_last4=0x86C92F0B^crc;
    printf("new: %08X\n",new_last4);

    // apply it and check
    *(PULONG)(buf+0xFFC)=new_last4;
	crc=crc32((PUCHAR)buf,0x1000,0x21337455);
    printf("CRC (this should be 0xFAF3CCCE): %08X\n",crc);

    // encode changes
    printf("encoding serial...\n");
    ULONG changes=old_last4^new_last4;
    __asm
    {
        mov edx,[changes];
        bswap edx;
        mov [changes],edx
    }
    for(UINT i=0;i<32;++i)
    {
        if(changes&(0x1<<i))
        {
            UINT position=16+i;
            CHAR buffx[5];
            buffx[0]=hextab[position/16];
            buffx[1]=hextab[position%16];
            buffx[2]=hextab[position/16]; // eh just do one bit at a time... don't wanna write code
            buffx[3]=hextab[position%16]; // to track consecutive 1's...
            buffx[4]=0;
            strcat(serial,buffx);
        }
    }

    printf("-------------------\n");
    printf("name: %s\n",user);
    printf("serial: %s\n",serial);
     printf("-------------------\n");

    printf("\nctrl+c to quit\n");
    while(1);
}
