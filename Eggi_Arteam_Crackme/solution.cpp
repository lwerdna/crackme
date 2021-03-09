// keygen for Eggi's "Arteam Crackme" - MMDDYY 032009 andrewl
//

// 1.
// crackme sums your serial characters + strlen(serial) to arrive at
// a word value

// 2.
// this word value acts as a decryption key for the code:
    unsigned char foo[20] =
    {
        0xEE, 0x12, 0xEC, 0x6A, 0xD5, 0x52, 0x84, 0x7A, // ...j.R.z
        0xBC, 0x43, 0xC4, 0x12, 0xD7, 0xED, 0x52, 0x82, // .C....R.
        0x14, 0x82, 0x14, 0x82                          // ....    
    };

// 3.
// crackme gives clue to half of decryption key by comparing
// foo[0] with 0x6A, so we know lo word of key is 0x84

// 4.
// brute the other byte of the key until the decrypted assembly
// language has typical instructions in it (see calculate_score())


#include <windows.h>
#include <stdio.h>
#include <time.h>

// z0mbie's EXtended Diassembler Engine
extern "C"
{
#include "xde\xde.h"
}
#pragma comment(lib, "xde\\xde102.lib")

UINT calculate_score(PUCHAR src)
{
    UINT score = 0;

    xde_instr instr;

    UINT offs = 0;

    while(1)
    {
        if(offs > 20)
            break;

        UINT ret = xde_disasm(src + offs, &instr);

        // bad disassembly means low score
        if(!ret || instr.flag & C_BAD || instr.flag == C_ERROR)
        {
            break;
        }

        // some typical instructions that score points
        if( (instr.opcode == 0xFF) ||                                   // call ind
            (instr.opcode == 0xE8) ||                                   // rel call
            ((instr.opcode <= 0x7F) && (instr.opcode >= 0x72)) ||       // conditional jump
            (instr.opcode == 0x68) ||                                   // push imm
            (instr.opcode == 0x53) ||
           (instr.opcode == 0x6A) ||                                   // another push
           0
        )
        {
            score++;
        }

        offs++;
    }

    return score;
}

WORD determine_key()
{


    UINT best_score = 0;
    WORD best_key = 0;

    for(UINT i=0; i<256; ++i)
    {
        WORD trial_key = 0x0084 | (i<<8);

        // do the decryption
        UCHAR bar[20];
        memcpy(bar, foo, 20);
        for(UINT j=0; j<10; ++j)
            *(PWORD)(bar+2*j) ^= trial_key;

        // how good is the disassembly?
        UINT score = calculate_score(bar);

        printf("key %04X has score: %d\n", trial_key, score);

        if(score > best_score)
        {
            best_score = score;
            best_key = trial_key;
        }
    }

    return best_key;
}

WORD calc_key(PCHAR serial)
{
    UINT val = strlen(serial);

    for(UINT i=0; i<strlen(serial); ++i)
        val += serial[i];

    return val;
}

void main()
{
    srand(time(0));

    // determine key
    WORD key = determine_key();
    printf("key: %04X\n", key);

    // init serial
    CHAR serial[256];
    memset(serial, 0, 256);

    // add characters to serial until xor key is surpassed
    PCHAR alphabet = "0123456789;:<=>?@ABCDEFGHIJKLMNOPQRSTUVWXZ";
    while(calc_key(serial) < key)
        strncat(serial, alphabet + (rand() % 42), 1);

    // decrement characters until xor key is met
    while(calc_key(serial) != key)
    {
        UINT i = rand() % 36;

        if(serial[i] <= '0')
            continue;

        --serial[i];
    }

    // print key :)
    printf("serial: %s\n", serial);
    printf("\n");
    printf("note that this must be the first serial entered - previously entered bad\n");
    printf("serials to not have their effects undone\n");
    printf("ctrl+c to close\n");
    while(1);
}

