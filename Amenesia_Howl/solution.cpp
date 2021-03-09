#define INFO "Solution to Amenesia's \"Howl\" - Oct_8_2009 - andrewl/crackmes.de -"

/*
quick tut:
---------

from your name and a hardcoded poem "howl", crackme generates 52 dword key
and 4 dword target values (see GetCryptoValues())

entered serial is decoded to 4 dwords

these 4 dwords are enciphered using the 52 dword key (finite field
ops used) and the result must be the 4 dword target values (see
BlockCipher() and disassembly at end of source)

the inverse of this is made by reversing the operations and inverting
field elements when required (see BlockCipherInverse())

example codes:
-------------
  name: Amenesia
serial: 0078085504F756881557200171498BED

  name: crackmes.de
serial: 4181994561F18C7F5FEACF7056FA0BBF

*/

#include <windows.h>
#include <stdio.h>

#define PRIMITIVE_POLY 0x80000009
// x^31 + x^3 + 1

DWORD FieldMul(DWORD multiplicand, DWORD multiplier, DWORD modulus)
{
    DWORD d_mask;
    DWORD result;

    //
    if(multiplier > multiplicand)
    {
        DWORD temp = multiplier;
        multiplier = multiplicand;
        multiplicand = temp;
    }

    // measure the degree of the modulus
    d_mask = 1 << 31;

    while(!(d_mask & modulus))
        d_mask >>= 1;

    // calculate the product
    result = 0;
        
    while(multiplier)
    {
        // if the current coeff of the muliplier is set
        //   then add the multiplicand to the result
        if(multiplier & 1)
            result ^= multiplicand;

        multiplier >>= 1;

        multiplicand <<= 1;

        // if degree(multiplicand) >= degree(modulus)
        //   then subtract the modulus
        if(multiplicand & d_mask)
            multiplicand ^= modulus;
    }

    return result;
}

DWORD FieldAdd(DWORD addend_a, DWORD addend_b)
{
    return addend_a ^ addend_b;
}

DWORD FieldDivide(DWORD dividend, DWORD divisor, DWORD *remainder)
{
    DWORD quotient = 0;

    // position the divisor all the way to the left of a 32-bit data type
    // count the degree of this divisor
    INT degree = 31;

    while(!(divisor & 0x80000000))
    {
        divisor <<= 1;
        degree--;
    }

    quotient = 0;

    for(INT bit = 31; bit >= degree; --bit)
    {
        if(dividend & (1<<bit))
        {
            quotient |= (1<<(bit-degree));

            dividend ^= divisor;
        }

        // slide the divisor to the right across the dividend
        divisor >>= 1;
    }

    *remainder = dividend;

    return quotient;
}

// purposely did not collapse this into a routine that swaps the a and b
// the code is a twice as long this way, but more than twice as clear
//
DWORD FieldEGCD(DWORD a, DWORD b, DWORD primitive, DWORD *r, DWORD *s)
{
    DWORD sum;
    DWORD product;
    DWORD quotient;
    DWORD remainder;

    // 
    DWORD gcd = 0;

    // throughout the computation we'll keep track of the current a, b
    // expressed in terms of the original a and b
    DWORD r_a = 1, s_a = 0; // a = 1*a + 0*b
    DWORD r_b = 0, s_b = 1; // b = 0*b + 1*a

    while(a && b)
    {
        if(a > b)
        {
            quotient = FieldDivide(a, b, &remainder);
            a = remainder;

            // update the expression for a in terms of original a and b
            //
            product = FieldMul(quotient, r_b, primitive);
            r_a = FieldAdd(r_a, product);       // r_a = r_a - quotient * (r_b);

            product = FieldMul(quotient, s_b, primitive);
            s_a = FieldAdd(s_a, product);       // s_a = s_a - quotient * (s_b);
        }
        else
        {
            quotient = FieldDivide(b, a, &remainder);
            b = remainder;

            // update the expression for b in terms of original a and b
            //
            product = FieldMul(quotient, r_a, primitive);
            r_b = FieldAdd(r_b, product);       // r_a = r_a - quotient * (r_a);

            product = FieldMul(quotient, s_a, primitive);
            s_b = FieldAdd(s_b, product);       // s_b = s_b - quotient * (s_a);
        }
    }

    if(a)
    {
        *s = s_a;
        *r = r_a;
        return a;
    }
    else
    {
        *s = s_b;
        *r = r_b;
        return b;
    }
}

DWORD FieldInvert(DWORD a, DWORD primitive)
{
    DWORD r, s;

    FieldEGCD(a, primitive, primitive, &r, &s);

    return r;
}

VOID GetCryptoValues(PCHAR name, PDWORD key, PDWORD plain)
{
    PCHAR howl="I saw the best minds of my gener"
        "ation destroyed by madness, star"
        "ving hysterical naked, dragging "
        "themselves through the negro str"
        "eets at dawn looking for an angr"
        "y fix, angelheaded hipsters burn"
        "ing for the ancient heavenly con"
        "nection to the starry dynamo in "
        "the machinery of night, - Ginsbe"
        "rg";

    CHAR namerep[256];
    CHAR table[256];

    memset(namerep,0,256);
    for(INT i=0; i<255; ++i)
        namerep[i] = name[i%strlen(name)];

    for(INT i=0; i<256; ++i)
        table[i]=i;

    BYTE sum=0;

    for(INT i=0; i<256; ++i)
    {
        sum+=namerep[i] + table[i];
        BYTE temp=table[i];
        table[i]=table[sum];
        table[sum]=temp;
    }

    BYTE table_[256];
    memset(table_, 0, 256);
    memcpy(table_, howl, 0xE0);
    
    sum=0;
    DWORD edx=0xDC; // affects first 0xE0 bytes
    DWORD esi=1;

    while(!(edx & 0x80000000))
    {
        sum += namerep[esi];
        BYTE temp = table[sum];
        table[sum] = table[esi];
        table[esi] = temp;

        BYTE xorr = namerep[esi] + namerep[sum];
        table_[edx] ^= xorr;

        edx--;
        esi++;
    }

    PUINT p = (PUINT)table_;
    for(INT i=0; i<0x34; ++i) // 0x34 dwords -> first 0xD0 bytes
    {
        p[i] |= 1;
        p[i] &= 0x7FFFFFFF;
    }

    // the "MustMatchSerial" dwords are 0xD0 bytes into the table_ array
    for(INT i=0; i<4; ++i)
    {
        DWORD temp = p[0x34+i];
        temp |= 0x01000000;
        temp &= 0xFFFFFF7F;
        p[0x34+i] = temp;
    }

    memcpy(key, table_, 0xD0);
    memcpy(plain, table_+0xD0, 0x10);
}

DWORD bswap(DWORD x)
{
    return (x << 24) |
            ((x << 8) & 0x00FF0000) |
            ((x >> 8) & 0x0000FF00) |
            (x >> 24);
}

VOID BlockCipher(PDWORD block, PDWORD key)
{
    for(INT i=0; i<4; ++i)
        block[i] = bswap(block[i]);

    // 8 * 6 = 48 key accesses here
    for(INT round=0; round<8; ++round)
    {
        block[0] = FieldMul(block[0], *key++, PRIMITIVE_POLY);
        block[1] = FieldAdd(block[1], *key++);
        block[2] = FieldAdd(block[2], *key++);
        block[3] = FieldMul(block[3], *key++, PRIMITIVE_POLY);

        DWORD t1; // t1 = (block[0] + block[2]) * key
        t1 = FieldAdd(block[0], block[2]);
        t1 = FieldMul(t1, *key++, PRIMITIVE_POLY);

        DWORD t2; // t2 = key * ((block[0] + block[2]) * key + block[1] + block[3])
        t2 = FieldAdd(block[1], block[3]);
        t2 = FieldAdd(t1, t2); 
        t2 = FieldMul(t2, *key++, PRIMITIVE_POLY);

        block[0] = FieldAdd(block[0], t2);
        block[2] = FieldAdd(block[2], t2);
        block[1] = FieldAdd(block[1], t1);
        block[1] = FieldAdd(block[1], t2);
        block[3] = FieldAdd(block[3], t1);
        block[3] = FieldAdd(block[3], t2);
    }

    // addition 4 key access here, total 52
    block[0] = FieldMul(block[0], *key++, PRIMITIVE_POLY);
    block[1] = FieldAdd(block[1], *key++);
    block[2] = FieldAdd(block[2], *key++);
    block[3] = FieldMul(block[3], *key++, PRIMITIVE_POLY);

    for(INT i=0; i<4; ++i)
        block[i] = bswap(block[i]);
}

VOID BlockCipherInverse(PDWORD block, PDWORD key)
{
    key += 51;

    for(INT i=0; i<4; ++i)
        block[i] = bswap(block[i]);

    block[3] = FieldMul(block[3], FieldInvert(*key--, PRIMITIVE_POLY), PRIMITIVE_POLY); 
    block[2] = FieldAdd(block[2], *key--);
    block[1] = FieldAdd(block[1], *key--);
    block[0] = FieldMul(block[0], FieldInvert(*key--, PRIMITIVE_POLY), PRIMITIVE_POLY);

    for(INT round=0; round<8; ++round)
    {
        DWORD keyA = *key--; // for t2 calc
        DWORD keyB = *key--; // for t1 calc

        DWORD t1, t2;

        t1 = FieldAdd(block[0], block[2]);
        t1 = FieldMul(t1, keyB, PRIMITIVE_POLY);

        t2 = FieldAdd(block[1], block[3]);
        t2 = FieldAdd(t1, t2); 
        t2 = FieldMul(t2, keyA, PRIMITIVE_POLY);

        block[3] = FieldAdd(block[3], t2);
        block[3] = FieldAdd(block[3], t1);
        block[1] = FieldAdd(block[1], t2);
        block[1] = FieldAdd(block[1], t1);
        block[2] = FieldAdd(block[2], t2);
        block[0] = FieldAdd(block[0], t2);

        block[3] = FieldMul(block[3], FieldInvert(*key--, PRIMITIVE_POLY), PRIMITIVE_POLY);
        block[2] = FieldAdd(block[2], *key--);
        block[1] = FieldAdd(block[1], *key--);
        block[0] = FieldMul(block[0], FieldInvert(*key--, PRIMITIVE_POLY), PRIMITIVE_POLY);
    }

    for(INT i=0; i<4; ++i)
        block[i] = bswap(block[i]);
}

INT main(INT ac, PCHAR *av)
{
    printf(INFO "\n\n");

    CHAR name[256]="Amenesia";
    if(ac>1)
        strcpy(name,av[1]);

    DWORD key[52];
    DWORD plain[4];

    GetCryptoValues(name, key, plain);

    // key is 52 dwords
    printf("key: \n");
    for(INT i=0; i<52; ++i)
    {
        printf("%08X ", key[i]);
        if((i+1)%4 == 0)
            printf("\n");
    }

    printf("plain: \n");
    for(INT i=0; i<4; ++i)
        printf("%08X ", plain[i]);
    printf("\n");

    printf("inverting cipher:\n");
    BlockCipherInverse(plain, key);
    printf("%08X %08X %08X %08X\n", plain[0], plain[1], plain[2], plain[3]);

/*
    printf("(check) ciphering the inversion:\n"); 
    BlockCipher(plain, key);
    printf("%08X %08X %08X %08X\n", plain[0], plain[1], plain[2], plain[3]);
*/

    printf("\n-----------------------------------------------------------\n");
    printf("  name: %s\n", name);
    printf("serial: %08X%08X%08X%08X\n", bswap(plain[0]), bswap(plain[1]), bswap(plain[2]), bswap(plain[3]));
    printf("-----------------------------------------------------------\n");

    printf("\n\nctrL+c to quit!\n");
    while(1);
}

/* block cipher comments:

CODE:0040127E DoBlockCipher   proc near               ; CODE XREF: GoGo+B9p
CODE:0040127E                 pusha
CODE:0040127F                 mov     ecx, 3
CODE:00401284
CODE:00401284 loc_401284:                             ; CODE XREF: DoBlockCipher+17j
CODE:00401284                 mov     eax, ds:serial_dw0[ecx*4]
CODE:0040128B                 bswap   eax
CODE:0040128D                 mov     ds:serial_dw0[ecx*4], eax
CODE:00401294                 dec     ecx
CODE:00401295                 jns     short loc_401284 ;
CODE:00401295                                         ;
CODE:00401297                 mov     ds:counter_init_8, 8
CODE:0040129E
CODE:0040129E loc_40129E:                             ; CODE XREF: DoBlockCipher+226j
CODE:0040129E                 mov     ecx, ds:pTable
CODE:004012A4                 add     ds:pTable, 4    ;
CODE:004012A4                                         ;
CODE:004012AB                 mov     ebx, [ecx]      ; get current table value
CODE:004012AD                 mov     eax, ds:serial_dw0
CODE:004012B2                 xor     ecx, ecx
CODE:004012B4                 cmp     eax, ebx
CODE:004012B6                 ja      short serial_above_table ;
CODE:004012B6                                         ;
CODE:004012B8                 xchg    eax, ebx        ; ensure eax > ebx
CODE:004012B8                                         ;  (smaller ebx becomes multiplier)
CODE:004012B9
CODE:004012B9 serial_above_table:                     ; CODE XREF: DoBlockCipher+38j
CODE:004012B9                                         ; DoBlockCipher+66j ...
CODE:004012B9                 cmp     ebx, 0
CODE:004012BC                 jz      short done      ; STEP: serial[0] *= table[i]
CODE:004012BC                                         ;
CODE:004012BE                 test    ebx, 1
CODE:004012C4                 jz      short loc_4012D6 ;
CODE:004012C4                                         ;
CODE:004012C6                 xor     ecx, eax
CODE:004012C8                 cmp     ecx, 80000009h
CODE:004012CE                 jb      short loc_4012D6
CODE:004012D0                 xor     ecx, 80000009h
CODE:004012D6
CODE:004012D6 loc_4012D6:                             ; CODE XREF: DoBlockCipher+46j
CODE:004012D6                                         ; DoBlockCipher+50j
CODE:004012D6                 shr     ebx, 1
CODE:004012D8                 shl     eax, 1          ; msb -> cf
CODE:004012DA                 jnb     short loc_4012DF ;
CODE:004012DA                                         ;
CODE:004012DC                 xor     eax, 12h        ; if the msb was set pre-shift, then do a late
CODE:004012DC                                         ; addition of 80000009 (notice 9<<1 == 0x12)
CODE:004012DF
CODE:004012DF loc_4012DF:                             ; CODE XREF: DoBlockCipher+5Cj
CODE:004012DF                 cmp     eax, 80000009h
CODE:004012E4                 jb      short serial_above_table
CODE:004012E6                 xor     eax, 80000009h
CODE:004012EB                 jmp     short serial_above_table
CODE:004012ED ; ---------------------------------------------------------------------------
CODE:004012ED
CODE:004012ED done:                                   ; CODE XREF: DoBlockCipher+3Ej
CODE:004012ED                 mov     ds:serial_dw0, ecx ; STEP: serial[0] *= table[i]
CODE:004012ED                                         ;
CODE:004012F3                 mov     ecx, ds:pTable
CODE:004012F9                 add     ds:pTable, 4    ;
CODE:004012F9                                         ;
CODE:00401300                 mov     ecx, [ecx]
CODE:00401302                 mov     eax, ds:serial_dw1
CODE:00401307                 xor     eax, ecx
CODE:00401309                 cmp     ebx, 80000009h
CODE:0040130F                 jb      short loc_401317 ; STEP: serial[1] += table[i]
CODE:0040130F                                         ;
CODE:00401311                 xor     ebx, 80000009h
CODE:00401317
CODE:00401317 loc_401317:                             ; CODE XREF: DoBlockCipher+91j
CODE:00401317                 mov     ds:serial_dw1, eax ; STEP: serial[1] += table[i]
CODE:00401317                                         ;
CODE:0040131C                 mov     ecx, ds:pTable
CODE:00401322                 add     ds:pTable, 4
CODE:00401329                 mov     ecx, [ecx]
CODE:0040132B                 mov     eax, ds:serial_dw2
CODE:00401330                 xor     eax, ecx
CODE:00401332                 cmp     ebx, 80000009h
CODE:00401338                 jb      short loc_401340 ; STEP: serial[2] += table[i]
CODE:00401338                                         ;
CODE:0040133A                 xor     ebx, 80000009h
CODE:00401340
CODE:00401340 loc_401340:                             ; CODE XREF: DoBlockCipher+BAj
CODE:00401340                 mov     ds:serial_dw2, eax ; STEP: serial[2] += table[i]
CODE:00401340                                         ;
CODE:00401345                 mov     ecx, ds:pTable
CODE:0040134B                 add     ds:pTable, 4
CODE:00401352                 mov     ebx, [ecx]
CODE:00401354                 mov     eax, ds:serial_dw3
CODE:00401359                 xor     ecx, ecx
CODE:0040135B                 cmp     eax, ebx
CODE:0040135D                 ja      short loc_401360
CODE:0040135F                 xchg    eax, ebx
CODE:00401360
CODE:00401360 loc_401360:                             ; CODE XREF: DoBlockCipher+DFj
CODE:00401360                                         ; DoBlockCipher+10Dj ...
CODE:00401360                 cmp     ebx, 0
CODE:00401363                 jz      short loc_401394 ; STEP: serial[3] *= table[i]
CODE:00401363                                         ;
CODE:00401365                 test    ebx, 1
CODE:0040136B                 jz      short loc_40137D
CODE:0040136D                 xor     ecx, eax
CODE:0040136F                 cmp     ecx, 80000009h
CODE:00401375                 jb      short loc_40137D
CODE:00401377                 xor     ecx, 80000009h
CODE:0040137D
CODE:0040137D loc_40137D:                             ; CODE XREF: DoBlockCipher+EDj
CODE:0040137D                                         ; DoBlockCipher+F7j
CODE:0040137D                 shr     ebx, 1
CODE:0040137F                 shl     eax, 1
CODE:00401381                 jnb     short loc_401386
CODE:00401383                 xor     eax, 12h
CODE:00401386
CODE:00401386 loc_401386:                             ; CODE XREF: DoBlockCipher+103j
CODE:00401386                 cmp     eax, 80000009h
CODE:0040138B                 jb      short loc_401360
CODE:0040138D                 xor     eax, 80000009h
CODE:00401392                 jmp     short loc_401360
CODE:00401394 ; ---------------------------------------------------------------------------
CODE:00401394
CODE:00401394 loc_401394:                             ; CODE XREF: DoBlockCipher+E5j
CODE:00401394                 mov     ds:serial_dw3, ecx ; STEP: serial[3] *= table[i]
CODE:00401394                                         ;
CODE:0040139A                 mov     ebx, ds:serial_dw0
CODE:004013A0                 mov     eax, ds:serial_dw2
CODE:004013A5                 xor     ebx, eax        ;
CODE:004013A5                                         ;
CODE:004013A7                 mov     edx, ds:serial_dw1
CODE:004013AD                 mov     eax, ds:serial_dw3
CODE:004013B2                 xor     edx, eax        ; edx = (serial_dw1 + serial_dw3)
CODE:004013B2                                         ;
CODE:004013B4                 mov     eax, ebx        ; eax = (serial_dw0 + serial_dw2)
CODE:004013B6                 mov     ecx, ds:pTable
CODE:004013BC                 add     ds:pTable, 4
CODE:004013C3                 mov     ebx, [ecx]      ; ebx = table[i]
CODE:004013C5                 xor     ecx, ecx
CODE:004013C7                 cmp     eax, ebx
CODE:004013C9                 ja      short loc_4013CC
CODE:004013CB                 xchg    eax, ebx
CODE:004013CC
CODE:004013CC loc_4013CC:                             ; CODE XREF: DoBlockCipher+14Bj
CODE:004013CC                                         ; DoBlockCipher+179j ...
CODE:004013CC                 cmp     ebx, 0
CODE:004013CF                 jz      short loc_401400 ; t1 = esi = (serial_dw0 + serial_dw2) * table[i]
CODE:004013D1                 test    ebx, 1
CODE:004013D7                 jz      short loc_4013E9
CODE:004013D9                 xor     ecx, eax
CODE:004013DB                 cmp     ecx, 80000009h
CODE:004013E1                 jb      short loc_4013E9
CODE:004013E3                 xor     ecx, 80000009h
CODE:004013E9
CODE:004013E9 loc_4013E9:                             ; CODE XREF: DoBlockCipher+159j
CODE:004013E9                                         ; DoBlockCipher+163j
CODE:004013E9                 shr     ebx, 1
CODE:004013EB                 shl     eax, 1
CODE:004013ED                 jnb     short loc_4013F2
CODE:004013EF                 xor     eax, 12h
CODE:004013F2
CODE:004013F2 loc_4013F2:                             ; CODE XREF: DoBlockCipher+16Fj
CODE:004013F2                 cmp     eax, 80000009h
CODE:004013F7                 jb      short loc_4013CC
CODE:004013F9                 xor     eax, 80000009h
CODE:004013FE                 jmp     short loc_4013CC
CODE:00401400 ; ---------------------------------------------------------------------------
CODE:00401400
CODE:00401400 loc_401400:                             ; CODE XREF: DoBlockCipher+151j
CODE:00401400                 mov     esi, ecx        ; t1 = esi = (serial_dw0 + serial_dw2) * table[i]
CODE:00401402                 xor     edx, ecx        ; edx = (serial_dw0 + serial_dw2) * table[i] + (serial_dw1 + serial_dw3)
CODE:00401404                 cmp     edx, 80000009h
CODE:0040140A                 jb      short loc_401412
CODE:0040140C                 xor     edx, 80000009h
CODE:00401412
CODE:00401412 loc_401412:                             ; CODE XREF: DoBlockCipher+18Cj
CODE:00401412                 mov     ecx, ds:pTable
CODE:00401418                 add     ds:pTable, 4
CODE:0040141F                 mov     ebx, [ecx]
CODE:00401421                 mov     eax, edx        ; eax = (serial_dw0 + serial_dw2) * table[i] + (serial_dw1 + serial_dw3)
CODE:00401423                 xor     ecx, ecx
CODE:00401425                 cmp     eax, ebx        ; ebx = table[i]
CODE:00401427                 ja      short loc_40142A
CODE:00401429                 xchg    eax, ebx
CODE:0040142A
CODE:0040142A loc_40142A:                             ; CODE XREF: DoBlockCipher+1A9j
CODE:0040142A                                         ; DoBlockCipher+1D7j ...
CODE:0040142A                 cmp     ebx, 0
CODE:0040142D                 jz      short loc_40145E ; esi =
CODE:0040142D                                         ; ((serial_dw0 + serial_dw2) * table[i]) +
CODE:0040142D                                         ; table[i] * ((serial_dw0 + serial_dw2) * table[i] + (serial_dw1 + serial_dw3))
CODE:0040142F                 test    ebx, 1
CODE:00401435                 jz      short loc_401447
CODE:00401437                 xor     ecx, eax
CODE:00401439                 cmp     ecx, 80000009h
CODE:0040143F                 jb      short loc_401447
CODE:00401441                 xor     ecx, 80000009h
CODE:00401447
CODE:00401447 loc_401447:                             ; CODE XREF: DoBlockCipher+1B7j
CODE:00401447                                         ; DoBlockCipher+1C1j
CODE:00401447                 shr     ebx, 1
CODE:00401449                 shl     eax, 1
CODE:0040144B                 jnb     short loc_401450
CODE:0040144D                 xor     eax, 12h
CODE:00401450
CODE:00401450 loc_401450:                             ; CODE XREF: DoBlockCipher+1CDj
CODE:00401450                 cmp     eax, 80000009h
CODE:00401455                 jb      short loc_40142A
CODE:00401457                 xor     eax, 80000009h
CODE:0040145C                 jmp     short loc_40142A
CODE:0040145E ; ---------------------------------------------------------------------------
CODE:0040145E
CODE:0040145E loc_40145E:                             ; CODE XREF: DoBlockCipher+1AFj
CODE:0040145E                 xor     esi, ecx        ; esi =
CODE:0040145E                                         ; ((serial_dw0 + serial_dw2) * table[i]) +
CODE:0040145E                                         ; table[i] * ((serial_dw0 + serial_dw2) * table[i] + (serial_dw1 + serial_dw3))
CODE:00401460                 cmp     esi, 80000009h
CODE:00401466                 jb      short loc_40146E
CODE:00401468                 xor     esi, 80000009h
CODE:0040146E
CODE:0040146E loc_40146E:                             ; CODE XREF: DoBlockCipher+1E8j
CODE:0040146E                 mov     eax, ds:serial_dw0
CODE:00401473                 xor     eax, ecx
CODE:00401475                 mov     ds:serial_dw0, eax ;
CODE:00401475                                         ;
CODE:0040147A                 mov     eax, ds:serial_dw2
CODE:0040147F                 xor     eax, ecx
CODE:00401481                 mov     ds:serial_dw2, eax ;
CODE:00401481                                         ;
CODE:00401486                 mov     eax, ds:serial_dw1
CODE:0040148B                 xor     eax, esi
CODE:0040148D                 mov     ds:serial_dw1, eax ;
CODE:0040148D                                         ;
CODE:00401492                 mov     eax, ds:serial_dw3
CODE:00401497                 xor     eax, esi
CODE:00401499                 mov     ds:serial_dw3, eax ;
CODE:00401499                                         ;
CODE:0040149E                 dec     ds:counter_init_8
CODE:004014A4                 jnz     loc_40129E      ;
CODE:004014A4                                         ;
CODE:004014AA                 mov     ecx, ds:pTable
CODE:004014B0                 add     ds:pTable, 4
CODE:004014B7                 mov     ebx, [ecx]
CODE:004014B9                 mov     eax, ds:serial_dw0 ; dw0 *= table[i]
CODE:004014BE                 xor     ecx, ecx
CODE:004014C0                 cmp     eax, ebx
CODE:004014C2                 ja      short loc_4014C5
CODE:004014C4                 xchg    eax, ebx
CODE:004014C5
CODE:004014C5 loc_4014C5:                             ; CODE XREF: DoBlockCipher+244j
CODE:004014C5                                         ; DoBlockCipher+272j ...
CODE:004014C5                 cmp     ebx, 0
CODE:004014C8                 jz      short loc_4014F9 ; STEP dw0 = dw0 * table
CODE:004014C8                                         ;
CODE:004014CA                 test    ebx, 1
CODE:004014D0                 jz      short loc_4014E2
CODE:004014D2                 xor     ecx, eax
CODE:004014D4                 cmp     ecx, 80000009h
CODE:004014DA                 jb      short loc_4014E2
CODE:004014DC                 xor     ecx, 80000009h
CODE:004014E2
CODE:004014E2 loc_4014E2:                             ; CODE XREF: DoBlockCipher+252j
CODE:004014E2                                         ; DoBlockCipher+25Cj
CODE:004014E2                 shr     ebx, 1
CODE:004014E4                 shl     eax, 1
CODE:004014E6                 jnb     short loc_4014EB
CODE:004014E8                 xor     eax, 12h
CODE:004014EB
CODE:004014EB loc_4014EB:                             ; CODE XREF: DoBlockCipher+268j
CODE:004014EB                 cmp     eax, 80000009h
CODE:004014F0                 jb      short loc_4014C5
CODE:004014F2                 xor     eax, 80000009h
CODE:004014F7                 jmp     short loc_4014C5
CODE:004014F9 ; ---------------------------------------------------------------------------
CODE:004014F9
CODE:004014F9 loc_4014F9:                             ; CODE XREF: DoBlockCipher+24Aj
CODE:004014F9                 mov     ds:serial_dw0, ecx ; STEP dw0 = dw0 * table
CODE:004014F9                                         ;
CODE:004014FF                 mov     ecx, ds:pTable
CODE:00401505                 add     ds:pTable, 4
CODE:0040150C                 mov     ebx, [ecx]
CODE:0040150E                 mov     eax, ds:serial_dw1
CODE:00401513                 xor     eax, ebx
CODE:00401515                 cmp     ebx, 80000009h
CODE:0040151B                 jb      short loc_401523
CODE:0040151D                 xor     ebx, 80000009h
CODE:00401523
CODE:00401523 loc_401523:                             ; CODE XREF: DoBlockCipher+29Dj
CODE:00401523                 mov     ds:serial_dw1, eax
CODE:00401528                 mov     ecx, ds:pTable
CODE:0040152E                 add     ds:pTable, 4
CODE:00401535                 mov     ecx, [ecx]
CODE:00401537                 mov     eax, ds:serial_dw2
CODE:0040153C                 xor     eax, ecx
CODE:0040153E                 cmp     ebx, 80000009h
CODE:00401544                 jb      short loc_40154C
CODE:00401546                 xor     ebx, 80000009h
CODE:0040154C
CODE:0040154C loc_40154C:                             ; CODE XREF: DoBlockCipher+2C6j
CODE:0040154C                 mov     ds:serial_dw2, eax
CODE:00401551                 mov     ecx, ds:pTable
CODE:00401557                 add     ds:pTable, 4
CODE:0040155E                 mov     ebx, [ecx]
CODE:00401560                 mov     eax, ds:serial_dw3
CODE:00401565                 xor     ecx, ecx
CODE:00401567                 cmp     eax, ebx
CODE:00401569                 ja      short loc_40156C
CODE:0040156B                 xchg    eax, ebx
CODE:0040156C
CODE:0040156C loc_40156C:                             ; CODE XREF: DoBlockCipher+2EBj
CODE:0040156C                                         ; DoBlockCipher+319j ...
CODE:0040156C                 cmp     ebx, 0
CODE:0040156F                 jz      short loc_4015A0
CODE:00401571                 test    ebx, 1
CODE:00401577                 jz      short loc_401589
CODE:00401579                 xor     ecx, eax
CODE:0040157B                 cmp     ecx, 80000009h
CODE:00401581                 jb      short loc_401589
CODE:00401583                 xor     ecx, 80000009h
CODE:00401589
CODE:00401589 loc_401589:                             ; CODE XREF: DoBlockCipher+2F9j
CODE:00401589                                         ; DoBlockCipher+303j
CODE:00401589                 shr     ebx, 1
CODE:0040158B                 shl     eax, 1
CODE:0040158D                 jnb     short loc_401592
CODE:0040158F                 xor     eax, 12h
CODE:00401592
CODE:00401592 loc_401592:                             ; CODE XREF: DoBlockCipher+30Fj
CODE:00401592                 cmp     eax, 80000009h
CODE:00401597                 jb      short loc_40156C
CODE:00401599                 xor     eax, 80000009h
CODE:0040159E                 jmp     short loc_40156C
CODE:004015A0 ; ---------------------------------------------------------------------------
CODE:004015A0
CODE:004015A0 loc_4015A0:                             ; CODE XREF: DoBlockCipher+2F1j
CODE:004015A0                 mov     ds:serial_dw3, ecx
CODE:004015A6                 mov     ecx, 3
CODE:004015AB
CODE:004015AB loc_4015AB:                             ; CODE XREF: DoBlockCipher+33Ej
CODE:004015AB                 mov     eax, ds:serial_dw0[ecx*4]
CODE:004015B2                 bswap   eax
CODE:004015B4                 mov     ds:serial_dw0[ecx*4], eax
CODE:004015BB                 dec     ecx
CODE:004015BC                 jns     short loc_4015AB
CODE:004015BE                 popa
CODE:004015BF                 retn
CODE:004015BF DoBlockCipher   endp
*/
