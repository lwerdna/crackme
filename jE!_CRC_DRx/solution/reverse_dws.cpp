// 2008 andrewl

#include <windows.h>

#include <stdio.h>

typedef unsigned long DWORD;

void print4dws(DWORD * DZ)
{
        PCHAR p = (PCHAR)DZ;
        for(int i=0; i<4; ++i)
            printf("%08X ", DZ[i]);

        for(int i=0; i<16; ++i)
            if(*p < '~' && p[i] > ' ')
                printf("%c", p[i]);
            else
                printf(".");
        printf("\n");
}

void main(void)
{
    DWORD DR_2ND[4];
   
    // FIND DWORDS OF 2ND WRITE
    //
    DR_2ND[0] = 'sseM';
    DR_2ND[1] = 'Bega';
    DR_2ND[2] = 'Axo';
    DR_2ND[3] = 0x4030C3;       // HW bp loc

    for(int i=0; i<16; ++i)
    {
        DR_2ND[2] ^= DR_2ND[3];
        DR_2ND[1] ^= DR_2ND[3];
        DR_2ND[0] ^= DR_2ND[3];
        DR_2ND[0] ^= DR_2ND[2];
        DR_2ND[2] ^= DR_2ND[1];
        DR_2ND[1] ^= DR_2ND[0];
        DR_2ND[3] -= 0x17187;
    }

    // FIND DWORDS OF 1ST WRITE
    //
    DWORD DR_1ST[4];

    DR_1ST[0] = 'resU';
    DR_1ST[1] = '23';
    DR_1ST[2] = 0; // doesn't matter
    DR_1ST[3] = DR_2ND[3];

    for(int i=0; i<16; ++i)
    {
        DR_1ST[2] ^= DR_1ST[3];
        DR_1ST[1] ^= DR_1ST[3];
        DR_1ST[0] ^= DR_1ST[3];
        DR_1ST[0] ^= DR_1ST[2];
        DR_1ST[2] ^= DR_1ST[1];
        DR_1ST[1] ^= DR_1ST[0];
        DR_1ST[3] -= 0x17187;
    }

    // print 'em

    printf("DR[0..3]: ");
    print4dws(DR_1ST);

    printf("DR[5..7]: ");
    print4dws(DR_2ND);

    printf("-\n");

    // FOR DEMONSTRATION PURPOSES, MOVE FORWARD NOW, EMULATING CRACKME BEHAVIOR
    //

    DWORD DR[4];
    
    memcpy(DR, DR_1ST, 4*sizeof(*DR));
    
    printf("  file: ");
    print4dws(DR);
  
    for(int i=0; i<16; ++i)
    {
        DR[3] += 0x17187;
        DR[1] ^= DR[0];
        DR[2] ^= DR[1];
        DR[0] ^= DR[2];
        DR[0] ^= DR[3];
        DR[1] ^= DR[3];
        DR[2] ^= DR[3];

        printf("mix %02d: ", i);
        print4dws(DR);
    }

    memcpy(DR, DR_2ND, 3*sizeof(*DR));
    // DR[3] is remaining from previous mix 

    printf("-\n");

    printf("  file: ");
    print4dws(DR);
  
    for(int i=0; i<16; ++i)
    {
        DR[3] += 0x17187;
        DR[1] ^= DR[0];
        DR[2] ^= DR[1];
        DR[0] ^= DR[2];
        DR[0] ^= DR[3];
        DR[1] ^= DR[3];
        DR[2] ^= DR[3];

        printf("mix %02d: ", i);
        print4dws(DR);
    }
}
