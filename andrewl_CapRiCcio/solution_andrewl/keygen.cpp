char *info = "Keygen to \"Capriccio\" - Aug 03, 2009 - andrewl";

#include <windows.h>
#include <stdio.h>

#ifdef TEST
#define EQU_BITS (3+1)
#define EQUATIONS_N 3
#else
#define EQU_BITS (64+1)
#define EQUATIONS_N 64
#endif
typedef UCHAR EQU[EQU_BITS];
EQU g_equations[EQUATIONS_N];

UINT64 CRC64_table[256];

VOID CRC64_generate()
{
    UINT64 poly = 0xC96C5795D7870F42;

    for(INT i=0; i<256; ++i)
    {
    	UINT64 crc = i;

    	for(UINT j=0; j<8; ++j)
    	{
    		if(crc & 1)
            {
                crc >>= 1;
    			crc ^= poly;
            }
    		else
    		{
    			crc >>= 1;
            }
    	}
    
        CRC64_table[i] = crc;
    }
}

UINT64 CRC64_calculate(PBYTE stream, UINT n)
{
    UINT64 crc = 0;

    for(INT i=0; i<n; ++i)
    {
        BYTE index = stream[i] ^ crc;

        crc = (crc >> 8);

        crc ^= CRC64_table[index];
    }

    return crc;
}



void EQU_XOR(EQU c, EQU a, EQU b);
void EQU_XCHG(EQU a, EQU b);
BOOL EQU_ISNONZERO(EQU a);

void EQU_XOR(EQU c, EQU a, EQU b)
{
   for(UINT i=0; i<EQU_BITS; ++i)
       c[i] = a[i] ^ b[i];
}

void EQU_XCHG(EQU a, EQU b)
{
    for(UINT i=0; i<EQU_BITS; ++i)
    {
        INT temp = b[i];
        b[i] = a[i];
        a[i] = temp;
    }
}

BOOL EQU_ISNONZERO(EQU a)
{
   for(UINT i=0; i<(EQU_BITS-1); ++i)
       if(a[i])
           return 1;

   return 0;
}

void EQU_FILL_COLUMN(UINT64 filler, UINT c)
{
    for(UINT i=0; i<EQUATIONS_N; ++i)
        g_equations[i][c] = !!(filler & (0x8000000000000000 >> i));
}

void EQU_FILL_ROW(UINT64 filler, UINT c)
{
     for(UINT i=0; i<(EQU_BITS-1); ++i)
        g_equations[c][i] = !!(filler & (0x8000000000000000 >> i));
}

void EQU_PRINT(EQU a)
{
#ifdef TEST
    for(UINT i=0; i<(EQU_BITS-1); ++i)
        printf("%d ", a[i]);

    printf("[%d]\n", a[EQU_BITS-1]);
#else
    // convert the bytes representing bits to real bytes
    UCHAR bytes[EQU_BITS/8];
    memset(bytes, 0, EQU_BITS/8);

    for(UINT i=0; i<EQU_BITS-1; ++i)
        bytes[i/8] |= (a[i]<<7) >> (i%8);

    // now print the bytes out
    for(UINT i=0; i<EQU_BITS/8; ++i)
        printf("%02X ", bytes[i]);

    // print out augmented bit
    printf("[%d]\n", a[EQU_BITS-1]);
#endif
}

void EQUS_PRINT()
{
    for(UINT i=0; i<EQUATIONS_N; ++i)
        EQU_PRINT(g_equations[i]);
}

CHAR region[256] = {   ' ', ' ', ' ', ' ', ' ', ' ', 
                                'G', 'F', '(', '2', '^', '6', '4', ')', '[', 'X', ']', '/', '(', 'x', '^', '6',
                                '4', ' ', '+', ' ', 'x', '^', '6', '2', ' ', '+', ' ', 'x', '^', '5', '7', ' ', 
                                '+', ' ', 'x', '^', '5', '5', ' ', '+', ' ', 'x', '^', '5', '4', ' ', '+', ' ', 
                                'x', '^', '5', '3', ' ', '+', ' ', 'x', '^', '5', '2', ' ', '+', ' ', 'x', '^', 
                                '4', '7', ' ', '+', ' ', 'x', '^', '4', '6', ' ', '+', ' ', 'x', '^', '4', '5', 
                                ' ', '+', ' ', 'x', '^', '4', '0', ' ', '+', ' ', 'x', '^', '3', '9', ' ', '+', 
                                ' ', 'x', '^', '3', '8', ' ', '+', ' ', 'x', '^', '3', '7', ' ', '+', ' ', 'x', 
                                '^', '3', '5', ' ', '+', ' ', 'x', '^', '3', '3', ' ', '+', ' ', 'x', '^', '3', 
                                '2', ' ', '+', ' ', 'x', '^', '3', '1', ' ', '+', ' ', 'x', '^', '2', '9', ' ', 
                                '+', ' ', 'x', '^', '2', '7', ' ', '+', ' ', 'x', '^', '2', '4', ' ', '+', ' ', 
                                'x', '^', '2', '3', ' ', '+', ' ', 'x', '^', '2', '2', ' ', '+', ' ', 'x', '^', 
                                '2', '1', ' ', '+', ' ', 'x', '^', '1', '9', ' ', '+', ' ', 'x', '^', '1', '7', 
                                ' ', '+', ' ', 'x', '^', '1', '3', ' ', '+', ' ', 'x', '^', '1', '2', ' ', '+', 
                                ' ', 'x', '^', '1', '0', ' ', '+', ' ', 'x', '^', '9', ' ', '+', ' ', 'x', '^',
                                '7', ' ', '+', ' ', 'x', '^', '4', ' ', '+', ' ', 'x', '^', '1', ' ', '+', ' ',
                                '1', ')', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'
                        };

void main(INT ac, PCHAR *av)
{
    UINT64 history[64];

    for(UINT i=0; i<64; ++i)
        history[i] = (UINT64)1 << i;

    printf("\n%s\n\n", info);



#ifndef TEST
    CRC64_generate();

    printf("[*] parsing args..\n");
    UINT nName;
    PCHAR name;
    if(ac<2)
    {
        name = "andrewl";
        printf("no name argument, defaulting...\n");
    }
    else
        name = av[1];
    printf("\n");
    nName = strlen(name);

    // emulate how crackme modifies the buffer
    for(UINT i=0; i<nName; ++i)
        region[i<<4] = name[i];
    
    // zero the location of where the serial gets written
    UINT oSerial = nName * 4;
    for(UINT i=0; i<8; ++i)
        region[oSerial+i] = 0;

    // take CRC
    UINT64 crcA = CRC64_calculate((PBYTE)region, 256);
    printf("crcA calculated: %016I64X\n", crcA);

    // crcB = crcA + target_CRC
    UINT64 crcB = crcA ^ 0x6963636972706163;
    printf("crcB required: %016I64X\n", crcB);

    // zero the equations
    for(UINT i=0; i<EQUATIONS_N; ++i)
        for(UINT j=0; j<EQU_BITS; ++j)
            g_equations[i][j] = 0;

    // crcB becomes the augment column
    EQU_FILL_COLUMN(crcB, 64);

    // for each bit that can be set in the serial, calculate a crc -> get a basis
    UINT64 crcs[64];
    BYTE region_[256];
    memset(region_, 0, 256);

    for(UINT i=0; i<64; ++i)
    {
        UINT64 serial = (UINT64)1 << i;
        
        *(PUINT64)(region_ + oSerial) = serial;

        UINT64 crc = CRC64_calculate((PBYTE)(region_ + oSerial), 256 - oSerial);

        crcs[i] = crc;
        printf("serial %016I64X has crc %016I64X\n", serial, crc);

        EQU_FILL_COLUMN(crc, i);

    }

    EQUS_PRINT();

#else
    /*
    g_equations[0][0] = 1;
    g_equations[0][1] = 0;
    g_equations[0][2] = 1;
    g_equations[0][3] = 0;

    g_equations[1][0] = 1;
    g_equations[1][1] = 1;
    g_equations[1][2] = 1;
    g_equations[1][3] = 0;

    g_equations[2][0] = 0;
    g_equations[2][1] = 1;
    g_equations[2][2] = 1;
    g_equations[2][3] = 1;
    */

    g_equations[0][0] = 1;
    g_equations[0][1] = 0;
    g_equations[0][2] = 1;
    g_equations[0][3] = 0;

    g_equations[1][0] = 1;
    g_equations[1][1] = 1;
    g_equations[1][2] = 1;
    g_equations[1][3] = 1;

    g_equations[2][0] = 0;
    g_equations[2][1] = 1;
    g_equations[2][2] = 1;
    g_equations[2][3] = 0;


#endif

    printf("[*] Equations:\n");
    EQUS_PRINT();

    /*
    UINT64 which = 0x115282956AF9D8C0;
    UINT64 check=0;
    for(UINT i=0; i<64; ++i)
        if(which & ((UINT64)1 << i))
            check ^= crcs[i];
    printf("xor for fun: %016I64X\n", check);
    */
    //while(1);


    // reduce rows
    //

    // for each coefficient in the g_equations
    for(UINT coeff=0; coeff<(EQU_BITS-1); ++coeff)
    {
        // hunt first equation with nonzero coeff
        // starting with coeff'th equation (due to echelon shape)
        UINT pivot;
        for(pivot=coeff; pivot<EQUATIONS_N; ++pivot)
        {
            if(g_equations[pivot][coeff])
                break;

        }

        printf("pivot at: %d\n", pivot);

        // not found? next coeff then
        if(pivot>=EQUATIONS_N)
            {
                printf("FUCKED!\n"); 
                printf("coeff is: %d\n", coeff);
                EQUS_PRINT();
                while(1); 
            }

        // for any remaining row with <coeff> bit set, xor with pivot
        for(UINT k=0; k<EQUATIONS_N; ++k)
        {
            if(k==pivot)
                continue;

            if(g_equations[k][coeff])
            {
                EQU_XOR(g_equations[k], g_equations[k], g_equations[pivot]);

                history[k] ^= history[pivot];
                printf("equ%02d ^= equ%02d (new history: %016I64X, old history: %016I64X)\n", k, pivot, history[k], history[k] ^ history[pivot]);

                if(!EQU_ISNONZERO(g_equations[k]))
                {
                    printf("just put equation %d to zero! (xor'd with equation %d)\n\n", k, pivot);
                    printf("his history: %016I64X\n", history[k]);

                    UINT64 kk = history[k];
                    UINT64 check=0;
                    for(UINT i=0; i<64; ++i)
                    {
                        if(i != k && (kk & ((UINT64)1 << i)))
                            check ^= crcs[i];
                    }

                    printf("final: %016I64X\n", check);
                    while(1);
                }

            }
        }

        EQU_XCHG(g_equations[coeff], g_equations[pivot]);

        EQUS_PRINT();
        printf("--\n");
    }
    printf("\n");

    printf("[*] Equations after Gauss-Jordan:\n");
    EQUS_PRINT();

#ifndef TEST
    // go down the augment column to reap the result
    UINT64 crcB_ = 0;
    UINT64 serial = 0; 

    for(UINT i=0; i<64; ++i)
    {
        if(g_equations[i][64])
        {
            serial |= ((UINT64)1 << i);
            printf("adding serial with %d'th bit set\n", i);
            crcB_ ^= crcs[i];
        }
    }

    *(PUINT64)(region_ + oSerial) = serial;
    UINT64 crc = CRC64_calculate((PBYTE)(region_ + oSerial), 256 - oSerial);
    printf("test test crc: %016I64X\n", crc);


    printf("answer: %016I64X\n", serial);
    printf("crcB check value: %016I64X (should equal target: %016I64X\n", crcB_, crcB);
#endif

    printf("\n\n");
    printf("-------------------------\n");
    printf("   user: %s\n", name);
    printf(" serial: %016I64X\n", serial);
    printf("-------------------------\n");

    printf("\n\n");
    printf("ctrl+c to quit\n");
    while(1);

}

