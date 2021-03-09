// ----------------------------------------------------------------
//
// Keygen to "VM Keygenme" by Genaytek
//
// 8/2008 andrewl
//
// ----------------------------------------------------------------

// OS includes
#include <windows.h>

// stdio prototypes
extern "C" void * memset(void *, int, unsigned int);
extern "C" void * memcpy(void *, const void *, unsigned int);
extern "C" unsigned int strlen(const char *);
extern "C" void printf(char *, ...);

// ----------------------------------------------------------------
//
// BIT OPERATION DEFINES
//
// ----------------------------------------------------------------
#define ROL_DW(D,N) ((D<<N)|(D>>(32-N)))
#define ROR_DW(D,N) ((D<<(32-N))|(D>>N))
#define ROL_B(D,N) ((D<<N)|(D>>(8-N)))
#define ROR_B(D,N) ((D<<(8-N))|(D>>N))

// ----------------------------------------------------------------
//
// SERIAL-MANIPULATING FUNCTIONS
//
// ----------------------------------------------------------------

PCHAR character_set = "aAb0cBd1eCf2gDh3jEk4lFm5nGp6qHr7sJt8uKv9w";

CHAR character_set_lookup(CHAR c)
{
    for(int i=0; i<41; ++i)
        if(character_set[i]==c)
            return i;

    return -1;
}

void base41_encode(DWORD d, PCHAR p)
{
    memset(p, 'a', 6); p[7]=0; // leading 0 in character_set

    for(int i=5; i>=0 && d; --i)
    {
        p[i] = character_set[d%41];
        d/=41;
    }
}

//
// assumes p is 6-character string with valid coeff characters
void base41_decode(PCHAR p, PDWORD pd)
{
    *pd=0;
    for(int i=0; i<6; ++i)
        *pd = *pd * 41 + character_set_lookup(p[i]);
}

//
// inverse of PCODE from [40355B, 4035A3]
void INVERSE_PCODE_40355B(PDWORD p0, PDWORD p1, PDWORD p2)
{
    // the forward flow was:
    // 1) rol dword0 7 bits
    // 2) ror dword1 9 bits
    // 3) ror dword2 11 bits
    // 4) dword0 ^= dword1
    // 5) dword2 += dword1
    // 6) dword2 -= dword0

    *p2 += *p0;
    *p2 -= *p1;
    *p0 ^= *p1;
    *p2 = ROL_DW(*p2, 11);
    *p1 = ROL_DW(*p1, 9);
    *p0 = ROR_DW(*p0, 7);
}

// ----------------------------------------------------------------
//
// FUNCTIONS RE-CONSTRUCTED FROM PCODE
// 
// ----------------------------------------------------------------

void PCODE_4037BD(PCHAR user, PUCHAR buff)
{
	UCHAR mybyte=0;
	DWORD adder=0;
	
	int k=0;

	for(int i=0x60-1; i>=0; --i)
	{
		// calculate byte 
		mybyte ^= user[k];
		mybyte ^= 0x75;
		mybyte += (UCHAR) (adder & 0xFF);

		// store byte
		buff[i] = mybyte;

		// update adder
		adder += 3;
		adder ^= 0x45;
		adder = ROL_DW(adder, 3);

		// update continuing username i
		if(k==strlen(user)-1)
		    k=0;
	    else
		    k++;
	}
}

void PCODE_4038D5(PDWORD pd, PUCHAR bytes)
{
	*pd = 0x1A2B3C4D;

	for(int j=0; j<0xFF; ++j)
	for(int i=0; i<0x5D; ++i)
	{
		*pd ^= *(PDWORD)(bytes+i);
		*pd = ROL_DW(*pd, 7);
	}
}

void PCODE_40382A(PBYTE bytes, PDWORD p0, PDWORD p1)
{
	DWORD t;
	*p0 = 0x13A1DCB4;
	*p1 = 0x45E8ADC1;

	for(int j=0; j<0x28; ++j)
	{
		for(int i=0; i<0x30; i+=4)
		{
			*p0 ^= *(PDWORD)(bytes+i);
			*p0 = ROL_DW(*p0, 3);
			*p0 += *(PDWORD)(bytes+i+0x30);	
		}

		*p0 ^= *p1;
		t = *p0;
		*p0 = *p1;
		*p1 = t;
	}
}

// sums all 4-byte regions (DWORDS) present in the buffer built
// from the username
void PCODE_4038B0(PBYTE bytes, PDWORD pd)
{
    *pd=0;
    
    for(int i=0; i<0x60-3; ++i)
        *pd += *(PDWORD)(bytes+i);
}

void PCODE_403B40(DWORD d0, DWORD d1, PDWORD result)
{
	UCHAR buff[8]={0};

	*(PDWORD)(buff) = d0;
    *(PDWORD)(buff+4) = d1;

	PDWORD p0 = (PDWORD)buff;
	PDWORD p1 = (PDWORD)(buff+4);
	
	for(int i=0; i<7; ++i)
	{
		buff[i] += buff[i+1];
		buff[i] -= i;
		*p0 = ROL_DW(*p0, 5);
		*p1 = ROR_DW(*p1, 5);
	}	

	LONG A=0;
	LONG B=0x45;
	
	for(int i=0; i<4; ++i)
	{
		A = A+buff[i]+1;	
		B *= B;
		A *= B;
	}	

	LONG C=0;
	LONG D=0x35;
	
	for(int i=4; i<8; ++i)
	{
		C = C-buff[i]+1;	
		D *= D;
		C *= D;
	}	

	*result = A * C;
}

// implemented by the pcode at 4035E2
//
// k0:k1 = encryption key
// d0:d1 = plaintext
//
void encrypt(DWORD k0, DWORD k1, DWORD d0, DWORD d1)
{
   	UCHAR key[8]={0}; // k0, k1
    UCHAR dwords[8]={0}; // serial0, serial1

	*(PDWORD)(key) = k0;
    *(PDWORD)(key+4) = k1;

    *(PDWORD)(dwords) = d0;
    *(PDWORD)(dwords+4) = d1;

	PDWORD pk0 = (PDWORD)key;
	PDWORD pk1 = (PDWORD)(key+4);
    PDWORD pd0 = (PDWORD)dwords;
    PDWORD pd1 = (PDWORD)(dwords+4);

    //
    DWORD from_pair;
    PCODE_403B40(*pk0, *pk1, &from_pair);

    for(int k=0; k<10; ++k)
    {
        // this is inlined pcode from 403916:
        //
        for(int x=0; x<100; ++x)
        {
            for(int i=0; i<7; ++i)
            {
                BYTE r1;
                r1 = dwords[i] ^ key[i];
                r1 -= key[i+1];
                r1 += 0x12;
                dwords[i] = r1;
            }

            for(int i=0; i<16; ++i)
            {
                *pd0 = ROL_DW(*pd0, 3);
                *pd1 = ROR_DW(*pd1, 3);

                *pd0 ^= *pk0;
                *pd1 ^= *pk1;

                *pd0 += *pk1;
                *pd1 += *pk0;
            }


            // this implementation is near identical to the PCODE one at 403A0F, but the strange
            // while(var>7) var-=7 logic is difficult to invert, so following this  code  is  an
            // alternate implementation using a simpler lookup table scheme

            /* 
            DWORD r2=0;
            DWORD temp=0;

            for(int i=32; i>0; --i)
            {
                DWORD bitmask = 1 << i;

                if(from_pair & bitmask)
                {
                    temp = i;
                    while(temp>7) temp-=7;
                    printf("i:%d temp:%d r2:%d\n", i, temp, r2);
                    dwords[temp] ^= key[r2];
                }
                else
                {
                    temp=r2;
                    printf("i:%d r2:%d\n", i, r2);
                    dwords[temp] = ~dwords[temp];
                    dwords[temp] ^= temp;
                }
                if(++r2>7)
                    r2=0;
            }
            */

            // 
            // here is simplified version of PCODE_403A0F
            //

            int lookupa[33] = {'X', 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4};
            int lookupb[33] = {'X', 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0};
           
            for(int i=32; i>0; --i)
            {
                int a = lookupa[i];
                int b = lookupb[i];

                if(from_pair & (1<<i))
                    dwords[a] ^= key[b];
                else
                {
                    dwords[b] = ~dwords[b];
                    dwords[b] ^= b;
                }
            }

            for(int i=0; i<8; ++i)
            {
                dwords[7-i] ^= dwords[i];
                dwords[i] = ROL_B(dwords[i], 3);
            }

            *pd0 = ROL_DW(*pd0, 7);
            *pd1 = ROR_DW(*pd1, 7);
        }
    }
}

// inverse of the PCODE at 4035E2
//
// k0:k1 = encryption key (in)
// c0:c1 = ciphertext (in)
// p0:p1 = plaintext (out)
//
void decrypt(DWORD k0, DWORD k1, DWORD c0, DWORD c1, PDWORD p0, PDWORD p1, BOOL first_call)
{
   	UCHAR key[8]={0}; 
    UCHAR dwords[8]={0};

	*(PDWORD)(key) = k0;
    *(PDWORD)(key+4) = k1;

    *(PDWORD)(dwords) = c0;
    *(PDWORD)(dwords+4) = c1;

	PDWORD pk0 = (PDWORD)key;
	PDWORD pk1 = (PDWORD)(key+4);
    PDWORD pc0 = (PDWORD)dwords;
    PDWORD pc1 = (PDWORD)(dwords+4);

    DWORD from_pair;
    PCODE_403B40(*pk0, *pk1, &from_pair);

    for(int k=0; k<((first_call)?10:15); ++k)
    {
        // this is inlined pcode from 403916:
        //
        for(int x=0; x<100; ++x)
        {

            *pc1 = ROL_DW(*pc1, 7);
            *pc0 = ROR_DW(*pc0, 7);

            for(int i=7; i>=0; --i)
            {
                dwords[i] = ROR_B(dwords[i], 3);
                dwords[7-i] ^= dwords[i];
            }

            int lookupa[33] = {'X', 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4};
            int lookupb[33] = {'X', 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0};

            for(int i=1; i<=32; ++i)
            {
                int a = lookupa[i];
                int b = lookupb[i];

                if(from_pair & (1<<i))
                    dwords[a] ^= key[b];
                else
                {
                    dwords[b] ^= b;
                    dwords[b] = ~dwords[b];
                }
            }

            for(int i=0; i<16; ++i)
            {
                *pc1 -= *pk0;
                *pc0 -= *pk1;

                *pc1 ^= *pk1;
                *pc0 ^= *pk0;

                *pc1 = ROL_DW(*pc1, 3);
                *pc0 = ROR_DW(*pc0, 3);
            }

            for(int i=6; i>=0; --i)
            {
                dwords[i] -= 0x12;
                dwords[i] += key[i+1];
                dwords[i] ^= key[i];
            }
        }
    }

    *p0 = *pc0;
    *p1 = *pc1;
}

// ----------------------------------------------------------------
//
// FINALLY, THE KEYGEN :)
// 
// ----------------------------------------------------------------
void main(void)
{
    printf("[*] Keygen for \"Genaytyk's VM KeygenMe\" 2008 andrewl\n");

    // ----------------------------------------------------------------
    // PARSE COMMAND LINE
    // ----------------------------------------------------------------
    PCHAR user_name = GetCommandLine();
   
    while(*(user_name++)!=' ' && *user_name!='\0');

    if(!strlen(user_name))
    {
        printf("[*] No username argument, defaulting..\n");
        user_name = "NAME";
    }

    printf("[*] Calculating serial for user: -%s-\n", user_name);

    // ----------------------------------------------------------------
    // MIMIC CRACKME'S BEHAVIOR ON USER NAME
    // ----------------------------------------------------------------
    UCHAR name_bytes[0x61]={0};
	PCODE_4037BD(user_name, name_bytes);

    printf("[*] Formed username bytes: \n");
	for(int i=0; i<0x60; ++i)
	{ if(!((i)%8)) printf("    "); printf("%02X ", name_bytes[i] & 0xFF); if(!((i+1)%8)) printf("\n"); } 
	printf("\n");

    //
    DWORD name_bytes_sum;
    PCODE_4038B0(name_bytes, &name_bytes_sum);
    printf("[*] Sum of DWORDS in username bytes: %08X\n", name_bytes_sum);

    //
    DWORD name_dword=0;
	PCODE_4038D5(&name_dword, name_bytes);
	printf("[*] Formed username DWORD: %08X\n", name_dword);

    //
    DWORD name_pair0, name_pair1;
	PCODE_40382A(name_bytes, &name_pair0, &name_pair1);
	printf("[*] Formed username DWORD pair: %08X, %08X\n", name_pair0, name_pair1);

    // ----------------------------------------------------------------
    // INVERT CRACKME'S SERIAL REQUIREMENT
    // ----------------------------------------------------------------
    DWORD d0, d1, d2, t;

    #define OKAY 0x59414B4F
    #define _GUY 0x5955475F
    decrypt(name_dword, 0x6B79745F, OKAY, _GUY, &t, &d2, 0);
    decrypt(name_pair0, name_pair1, t, name_bytes_sum, &d0, &d1, 1);
    
    // ----------------------------------------------------------------
    // FORM, REPORT STRING SERIAL
    // ----------------------------------------------------------------                                  
    CHAR serial[] = "XXXXXX-XXXXXX-XXXXXX";

    INVERSE_PCODE_40355B(&d0, &d1, &d2);
    base41_encode(d0, serial);
    base41_encode(d1, serial+7);
    base41_encode(d2, serial+14);

    printf("[*] Serial: %s\n", serial);

    // ----------------------------------------------------------------
    // PAUSE UNTIL KEYPRESS
    // ----------------------------------------------------------------    
    ReadConsole(GetStdHandle(STD_INPUT_HANDLE), serial, 1, &d0, 0);
}
