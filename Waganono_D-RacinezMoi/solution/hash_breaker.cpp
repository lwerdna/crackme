// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"

// externs
extern UCHAR transform_prefix0[];
typedef void (*PFN_TRANSFORM_PREFIX0)(PCHAR, PUCHAR);

UINT BN_bytesize(BIGNUM *pBN)
{
    PUCHAR p = (PUCHAR)pBN->d;
    UINT size=pBN->top*4;
    p += size-1;
    while((*p--)==0)
        --size;
    return size;
}

void strcatchar(char * str, char a)
{
    char temp[2]={0};
    temp[0]=a;

    strcat(str, temp);
}

char * wagalphabet_lookahead[] = {
    "A", "1", "B", "2", "C", "3", "D", "4",
    "E", "5", "9", "-", "7", "H", "8", "I",
    "J", "K", "L", "M", "N", "O", "P", "Q",
    "R", "S", "T", "U", "V", "W", "Y", "Z",
    "AA", "A1", "AB", "A2", "AC", "A3", "AD", "A4",
    "AE", "A5", "A9", "A-", "A7", "AH", "A8", "AI",
    "AJ", "AK", "AL", "AM", "AN", "AO", "AP", "AQ",
    "AR", "AS", "AT", "AU", "AV", "AW", "AY", "AZ",
    "1A", "11", "1B", "12", "1C", "13", "1D", "14",
    "1E", "15", "19", "1-", "17", "1H", "18", "1I",
    "1J", "1K", "1L", "1M", "1N", "1O", "1P", "1Q",
    "1R", "1S", "1T", "1U", "1V", "1W", "1Y", "1Z",
    "BA", "B1", "BB", "B2", "BC", "B3", "BD", "B4",
    "BE", "B5", "B9", "B-", "B7", "BH", "B8", "BI",
    "BJ", "BK", "BL", "BM", "BN", "BO", "BP", "BQ",
    "BR", "BS", "BT", "BU", "BV", "BW", "BY", "BZ",
    "2A", "21", "2B", "22", "2C", "23", "2D", "24",
    "2E", "25", "29", "2-", "27", "2H", "28", "2I",
    "2J", "2K", "2L", "2M", "2N", "2O", "2P", "2Q",
    "2R", "2S", "2T", "2U", "2V", "2W", "2Y", "2Z",
    "CA", "C1", "CB", "C2", "CC", "C3", "CD", "C4",
    "CE", "C5", "C9", "C-", "C7", "CH", "C8", "CI",
    "CJ", "CK", "CL", "CM", "CN", "CO", "CP", "CQ",
    "CR", "CS", "CT", "CU", "CV", "CW", "CY", "CZ",
    "3A", "31", "3B", "32", "3C", "33", "3D", "34",
    "3E", "35", "39", "3-", "37", "3H", "38", "3I",
    "3J", "3K", "3L", "3M", "3N", "3O", "3P", "3Q",
    "3R", "3S", "3T", "3U", "3V", "3W", "3Y", "3Z",
    "DA", "D1", "DB", "D2", "DC", "D3", "DD", "D4",
    "DE", "D5", "D9", "D-", "D7", "DH", "D8", "DI",
    "DJ", "DK", "DL", "DM", "DN", "DO", "DP", "DQ",
    "DR", "DS", "DT", "DU", "DV", "DW", "DY", "DZ",
    "4A", "41", "4B", "42", "4C", "43", "4D", "44",
    "4E", "45", "49", "4-", "47", "4H", "48", "4I",
    "4J", "4K", "4L", "4M", "4N", "4O", "4P", "4Q",
    "4R", "4S", "4T", "4U", "4V", "4W", "4Y", "4Z",
    "EA", "E1", "EB", "E2", "EC", "E3", "ED", "E4",
    "EE", "E5", "E9", "E-", "E7", "EH", "E8", "EI",
    "EJ", "EK", "EL", "EM", "EN", "EO", "EP", "EQ",
    "ER", "ES", "ET", "EU", "EV", "EW", "EY", "EZ",
    "5A", "51", "5B", "52", "5C", "53", "5D", "54",
    "5E", "55", "59", "5-", "57", "5H", "58", "5I",
    "5J", "5K", "5L", "5M", "5N", "5O", "5P", "5Q",
    "5R", "5S", "5T", "5U", "5V", "5W", "5Y", "5Z",
    "9A", "91", "9B", "92", "9C", "93", "9D", "94",
    "9E", "95", "99", "9-", "97", "9H", "98", "9I",
    "9J", "9K", "9L", "9M", "9N", "9O", "9P", "9Q",
    "9R", "9S", "9T", "9U", "9V", "9W", "9Y", "9Z",
    "-A", "-1", "-B", "-2", "-C", "-3", "-D", "-4",
    "-E", "-5", "-9", "--", "-7", "-H", "-8", "-I",
    "-J", "-K", "-L", "-M", "-N", "-O", "-P", "-Q",
    "-R", "-S", "-T", "-U", "-V", "-W", "-Y", "-Z",
    "7A", "71", "7B", "72", "7C", "73", "7D", "74",
    "7E", "75", "79", "7-", "77", "7H", "78", "7I",
    "7J", "7K", "7L", "7M", "7N", "7O", "7P", "7Q",
    "7R", "7S", "7T", "7U", "7V", "7W", "7Y", "7Z",
    "HA", "H1", "HB", "H2", "HC", "H3", "HD", "H4",
    "HE", "H5", "H9", "H-", "H7", "HH", "H8", "HI",
    "HJ", "HK", "HL", "HM", "HN", "HO", "HP", "HQ",
    "HR", "HS", "HT", "HU", "HV", "HW", "HY", "HZ",
    "8A", "81", "8B", "82", "8C", "83", "8D", "84",
    "8E", "85", "89", "8-", "87", "8H", "88", "8I",
    "8J", "8K", "8L", "8M", "8N", "8O", "8P", "8Q",
    "8R", "8S", "8T", "8U", "8V", "8W", "8Y", "8Z",
    "IA", "I1", "IB", "I2", "IC", "I3", "ID", "I4",
    "IE", "I5", "I9", "I-", "I7", "IH", "I8", "II",
    "IJ", "IK", "IL", "IM", "IN", "IO", "IP", "IQ",
    "IR", "IS", "IT", "IU", "IV", "IW", "IY", "IZ",
    "JA", "J1", "JB", "J2", "JC", "J3", "JD", "J4",
    "JE", "J5", "J9", "J-", "J7", "JH", "J8", "JI",
    "JJ", "JK", "JL", "JM", "JN", "JO", "JP", "JQ",
    "JR", "JS", "JT", "JU", "JV", "JW", "JY", "JZ",
    "KA", "K1", "KB", "K2", "KC", "K3", "KD", "K4",
    "KE", "K5", "K9", "K-", "K7", "KH", "K8", "KI",
    "KJ", "KK", "KL", "KM", "KN", "KO", "KP", "KQ",
    "KR", "KS", "KT", "KU", "KV", "KW", "KY", "KZ",
    "LA", "L1", "LB", "L2", "LC", "L3", "LD", "L4",
    "LE", "L5", "L9", "L-", "L7", "LH", "L8", "LI",
    "LJ", "LK", "LL", "LM", "LN", "LO", "LP", "LQ",
    "LR", "LS", "LT", "LU", "LV", "LW", "LY", "LZ",
    "MA", "M1", "MB", "M2", "MC", "M3", "MD", "M4",
    "ME", "M5", "M9", "M-", "M7", "MH", "M8", "MI",
    "MJ", "MK", "ML", "MM", "MN", "MO", "MP", "MQ",
    "MR", "MS", "MT", "MU", "MV", "MW", "MY", "MZ",
    "NA", "N1", "NB", "N2", "NC", "N3", "ND", "N4",
    "NE", "N5", "N9", "N-", "N7", "NH", "N8", "NI",
    "NJ", "NK", "NL", "NM", "NN", "NO", "NP", "NQ",
    "NR", "NS", "NT", "NU", "NV", "NW", "NY", "NZ",
    "OA", "O1", "OB", "O2", "OC", "O3", "OD", "O4",
    "OE", "O5", "O9", "O-", "O7", "OH", "O8", "OI",
    "OJ", "OK", "OL", "OM", "ON", "OO", "OP", "OQ",
    "OR", "OS", "OT", "OU", "OV", "OW", "OY", "OZ",
    "PA", "P1", "PB", "P2", "PC", "P3", "PD", "P4",
    "PE", "P5", "P9", "P-", "P7", "PH", "P8", "PI",
    "PJ", "PK", "PL", "PM", "PN", "PO", "PP", "PQ",
    "PR", "PS", "PT", "PU", "PV", "PW", "PY", "PZ",
    "QA", "Q1", "QB", "Q2", "QC", "Q3", "QD", "Q4",
    "QE", "Q5", "Q9", "Q-", "Q7", "QH", "Q8", "QI",
    "QJ", "QK", "QL", "QM", "QN", "QO", "QP", "QQ",
    "QR", "QS", "QT", "QU", "QV", "QW", "QY", "QZ",
    "RA", "R1", "RB", "R2", "RC", "R3", "RD", "R4",
    "RE", "R5", "R9", "R-", "R7", "RH", "R8", "RI",
    "RJ", "RK", "RL", "RM", "RN", "RO", "RP", "RQ",
    "RR", "RS", "RT", "RU", "RV", "RW", "RY", "RZ",
    "SA", "S1", "SB", "S2", "SC", "S3", "SD", "S4",
    "SE", "S5", "S9", "S-", "S7", "SH", "S8", "SI",
    "SJ", "SK", "SL", "SM", "SN", "SO", "SP", "SQ",
    "SR", "SS", "ST", "SU", "SV", "SW", "SY", "SZ",
    "TA", "T1", "TB", "T2", "TC", "T3", "TD", "T4",
    "TE", "T5", "T9", "T-", "T7", "TH", "T8", "TI",
    "TJ", "TK", "TL", "TM", "TN", "TO", "TP", "TQ",
    "TR", "TS", "TT", "TU", "TV", "TW", "TY", "TZ",
    "UA", "U1", "UB", "U2", "UC", "U3", "UD", "U4",
    "UE", "U5", "U9", "U-", "U7", "UH", "U8", "UI",
    "UJ", "UK", "UL", "UM", "UN", "UO", "UP", "UQ",
    "UR", "US", "UT", "UU", "UV", "UW", "UY", "UZ",
    "VA", "V1", "VB", "V2", "VC", "V3", "VD", "V4",
    "VE", "V5", "V9", "V-", "V7", "VH", "V8", "VI",
    "VJ", "VK", "VL", "VM", "VN", "VO", "VP", "VQ",
    "VR", "VS", "VT", "VU", "VV", "VW", "VY", "VZ",
    "WA", "W1", "WB", "W2", "WC", "W3", "WD", "W4",
    "WE", "W5", "W9", "W-", "W7", "WH", "W8", "WI",
    "WJ", "WK", "WL", "WM", "WN", "WO", "WP", "WQ",
    "WR", "WS", "WT", "WU", "WV", "WW", "WY", "WZ",
    "YA", "Y1", "YB", "Y2", "YC", "Y3", "YD", "Y4",
    "YE", "Y5", "Y9", "Y-", "Y7", "YH", "Y8", "YI",
    "YJ", "YK", "YL", "YM", "YN", "YO", "YP", "YQ",
    "YR", "YS", "YT", "YU", "YV", "YW", "YY", "YZ",
    "ZA", "Z1", "ZB", "Z2", "ZC", "Z3", "ZD", "Z4",
    "ZE", "Z5", "Z9", "Z-", "Z7", "ZH", "Z8", "ZI",
    "ZJ", "ZK", "ZL", "ZM", "ZN", "ZO", "ZP", "ZQ",
    "ZR", "ZS", "ZT", "ZU", "ZV", "ZW", "ZY", "ZZ"
};

UCHAR area[512]={0};

INT bytesize_area(PUCHAR area, int atleast)
{
    area += 511;

    INT size=512;

    while(*area==0 && size>=0)
    {
        size--;
        area--;
    }

    if(size < atleast)
        size=atleast;

    return size;
}

void derive_prefix_for_hash(BIGNUM BN_targetz, PCHAR prefix)
{
    PFN_TRANSFORM_PREFIX0 pfn=(PFN_TRANSFORM_PREFIX0)(void *)transform_prefix0;

    UINT target_bytesize = BN_bytesize(&BN_targetz);

    //printf("target: %s\n", BN_bn2hex(&BN_targetz));
    //printf("In decimal that's: %s\n", BN_bn2dec(&BN_targetz));
    //printf("bytesize is: %d\n", target_bytesize);

    BIGNUM BN_target;
    BN_init(&BN_target);

    // reverse ordering - guts of BN are stored little end forwards, but oddly when you do bin2bn, it expected high end first
    PUCHAR reverse=new UCHAR[target_bytesize];
    memcpy(reverse, BN_targetz.d, target_bytesize);
    BN_bin2bn(reverse, target_bytesize, &BN_target);
    delete [] reverse;

    memset(area, 0, 512);


    BIGNUM BN_temp;
    BN_init(&BN_temp);

    BIGNUM BN_difference;
    BN_init(&BN_difference);

    // current record = (max number)
    BIGNUM BN_difference_record;
    BN_init(&BN_difference_record);
    memset(area, 0xFF, 512);
    BN_bin2bn(area, target_bytesize, &BN_difference_record);
    memset(area, 0, 512);

    // current record (index in wagalphabet)
    UINT wagalphabet_i_record=0;

    while(1)
    {
        // find appended char which gets us closest
        for(UINT i=0; i<(32+1024); ++i)
        {
            // generate trial prefix
            CHAR trial_prefix[512]={0};
            strcpy(trial_prefix, prefix);
            strcat(trial_prefix, wagalphabet_lookahead[i]);

            // run it through the hasher
            memset(area, 0, 512);
            pfn(trial_prefix, area);

            // generate big number from it
            //printf("(area: %02X %02X %02X %02X %02X.. len:%d) ", area[0], area[1], area[2], area[3], area[4], bytesize_area(area, target_bytesize));
            BN_bin2bn(area, bytesize_area(area, target_bytesize), &BN_temp);
            //printf("HASH(\"%s\")=%s", trial_prefix, BN_bn2hex(&BN_temp));

            // is generated number less or equal to target? (needs to be)
            if(BN_cmp(&BN_temp, &BN_target) > 0)
            {
                //printf("\n");
                continue;
            }

            // how big is generated number from the target?
            BN_sub(&BN_difference, &BN_temp, &BN_target);
            BN_set_negative(&BN_difference, 0);

            //printf(" (added: %s) (i: %d) ", wagalphabet_lookahead[i], i);

            // if it's less or equal than current record
            if(BN_cmp(&BN_difference, &BN_difference_record) <= 0)
            {
                // save new BN record
                BN_copy(&BN_difference_record, &BN_difference);
                // save what index in wagalphabet that was
                wagalphabet_i_record=i;

                //printf(" new record distance: %s", BN_bn2hex(&BN_difference_record));
            }

            //printf("\n");
        }

        // * copy just the first char from the combo we added *
        strcatchar(prefix, wagalphabet_lookahead[wagalphabet_i_record][0]);

        // recompute what the distance from target will be (will be further, only one character in effect now)
        memset(area, 0, 512);
        pfn(prefix, area);
        BN_bin2bn(area, bytesize_area(area, target_bytesize), &BN_temp);
        BN_sub(&BN_difference, &BN_temp, &BN_target);
        if(BN_is_zero(&BN_difference))
        {
            printf("answer: %s hashes to %s\n", prefix, BN_bn2hex(&BN_temp));
            //printf("FINAL!\n");
            break;
        }

        //printf("********** winner this round: **************\n");
        
        //printf("current distance record: %s\n", BN_bn2hex(&BN_difference_record));
        //printf("\"%s\" hashes to %s\n", prefix, BN_bn2hex(&BN_temp), BN_bn2hex(&BN_difference));
    }
}


