#define INFO "Keygen to so61pi's \"eygenMe#1\" by andrewl - Sept 28th, 2009"

#include <windows.h>
#include <stdio.h>

UINT ExpMod(UINT b, UINT e, UINT m)
{
    UINT64 answer = 1;
    UINT64 runner = b;

    while(e)
    {
        if(e & 1)
            answer = (answer * runner) % m;

        e >>= 1;

        runner = (runner * runner) % m;
    }

    return answer;
}

INT main(INT ac, PCHAR *av)
{
    printf(INFO "\n\n");

    CHAR name[128];
    CHAR name_crypted[128];
    CHAR serial[128];

    UINT n;
    UINT sum_name = 0;

    strcpy(name, "andrewl");
    if(ac>1)
        strcpy(name, av[1]);

    // crackme encrypts each char of the name name[i]^157 (mod 221)
    //
    // p = 13
    // q = 17
    // e = 157
    // d = 181          (157^(-1) (mod 12*16))
    n = strlen(name);

    for(INT i=0; i<n; ++i)
        name_crypted[i] = ExpMod(name[i], 157, 0xDD);

    printf("name (ciphertext): ");
    for(INT i=0; i<n; ++i)
        printf("%02X ", (BYTE)name_crypted[i]);

    printf("\n");

    // crackme sums the values:
    for(INT i=0; i<n; ++i)
        sum_name += ((BYTE)name_crypted[i] ^ 0x7F);

    printf("sum(name): %d\n", sum_name);

    // crackme encrypts each char of the serial serial[i]^157 (mod 253)
    // and then sums the ciphertext bytes:
    //
    // p = 11
    // q = 23
    // e = 157
    // d = 213        (157^(-1) (mod 10*22))

    // we want to discover which ciphertext bytes (which are summed) have
    // corresponding plaintexts which are printable...

    /*
    for(INT i=1; i<253; ++i)
    {
        CHAR pt = ExpMod(i, 213, 253);
        if(pt >= '!' && pt <= '~')
            printf("'%c' (%d) -> %d\n", pt, pt, i);
    }
    */

    // we get this:
    // plain -> cipher
    // ---------------
    // 'U' (85) -> 2
    // 'h' (104) -> 3
    // '^' (94) -> 8
    // 'x' (120) -> 10
    // '!' (33) -> 11
    // ')' (41) -> 13
    // 'T' (84) -> 17
    // 'P' (80) -> 20
    // 'L' (76) -> 21
    // '{' (123) -> 29
    // 'S' (83) -> 30
    // 'b' (98) -> 32
    // '8' (56) -> 34
    // 'V' (86) -> 37
    // '2' (50) -> 41
    // 'c' (99) -> 44
    // '-' (45) -> 45
    // ']' (93) -> 47
    // 'l' (108) -> 48
    // 'Q' (81) -> 49
    // '_' (95) -> 50
    // 'y' (121) -> 55
    // 'R' (82) -> 58
    // '@' (64) -> 59
    // 'e' (101) -> 62
    // '=' (61) -> 63
    // '+' (43) -> 65
    // 'z' (122) -> 67
    // 's' (115) -> 69
    // 'J' (74) -> 79
    // '(' (40) -> 83
    // 'Z' (90) -> 84
    // 'B' (66) -> 88
    // '"' (34) -> 89
    // 'F' (70) -> 93
    // '>' (62) -> 94
    // '#' (35) -> 95
    // 'H' (72) -> 96
    // '6' (54) -> 98
    // '4' (52) -> 101
    // ';' (59) -> 104
    // '|' (124) -> 108
    // 'Y' (89) -> 111
    // '\' (92) -> 115
    // 'A' (65) -> 120
    // 'M' (77) -> 121
    // 'a' (97) -> 125
    // '}' (125) -> 126
    // 'q' (113) -> 130
    // '~' (126) -> 135
    // '5' (53) -> 136
    // 'r' (114) -> 137
    // ''' (39) -> 140
    // ':' (58) -> 141
    // 'X' (88) -> 143
    // 'd' (100) -> 144
    // 'G' (71) -> 146
    // 'K' (75) -> 147
    // '7' (55) -> 154
    // '`' (96) -> 156
    // '.' (46) -> 161
    // 't' (116) -> 162
    // 'o' (111) -> 166
    // '<' (60) -> 168
    // '3' (51) -> 171
    // 'O' (79) -> 172
    // 'i' (105) -> 173
    // 'm' (109) -> 175
    // ',' (44) -> 176
    // 'N' (78) -> 177
    // 'k' (107) -> 178
    // 'g' (103) -> 181
    // 'D' (68) -> 183
    // '/' (47) -> 185
    // '0' (48) -> 192
    // '$' (36) -> 196
    // 'W' (87) -> 197
    // 'C' (67) -> 199
    // '&' (38) -> 201
    // 'w' (119) -> 202
    // 'E' (69) -> 207
    // 'v' (118) -> 211
    // '%' (37) -> 214
    // 'u' (117) -> 215
    // 'f' (102) -> 218
    // 'n' (110) -> 220
    // '9' (57) -> 227
    // '[' (91) -> 229
    // '1' (49) -> 234
    // '*' (42) -> 235
    // 'j' (106) -> 237
    // '?' (63) -> 244
    // 'I' (73) -> 248
    // 'p' (112) -> 249

    // maybe we can make a number base out of this... suppose we could get 1, 2, 4, 8, ... 
    // then we could encode any number using these sequences! (then it is just binary coeff's)

    CHAR * lookups[12] = { "", // no way to get a 1
                            "U", // 2
                            "UU", // 4 = 2 + 2
                            "^", // 8
                            "^^", // 16
                            "b", // 32
                            "bb", // 64
                            "ah", // 128 = 125 + 3
                            "I^", // 256 = 248 + 8
                            "I^I^", // 512
                            "I^I^I^I^", // 1024
                            "I^I^I^I^I^I^I^I^", // 2048
                        };

    // but we can't get a '1', so at some step, we'll need to get one more than our even
    // powers of 2

    CHAR * lookups_add1[12] = { "", // 
                            "h", // 3
                            "Uh", // 5
                            "hhh", // 9
                            "T", // 17
                            "hS", // 33
                            "+", // 65
                            "}h", // 129
                            "p^", // 257
                            "p^p^)U", // 513
                            "p^p^p^pUU", // 1025
                            "ppppppppyU", // 2049
                        };
    // haha cheap!

    // now encode the value of the serial sum

    BOOL needOdd = (sum_name % 2) ? 1 : 0;

    if(needOdd)
        sum_name = sum_name - 1;

    BOOL didOdd = 0;

    serial[0] = 0;

    for(INT i=0; i<16; ++i)
    {
        if(sum_name & (1 << i))
        {
            if(needOdd & !didOdd)
            {
                strcat(serial, lookups_add1[i]);
                didOdd = 1;
            }
            else
            {
                strcat(serial, lookups[i]);
            }
        }
    }

    printf("------------------------------------------------\n");
    printf("  name: %s\n", name);
    printf("serial: %s\n", serial);
    printf("------------------------------------------------\n");

    printf("\nctrl+c to quit\n");
    while(1);

    return 0;
}
