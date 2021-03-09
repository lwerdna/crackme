// KEYGENERATOR FOR ENCRYPTO'S AURORA
// Protection: CRC32,BlockCipher and Nyberg Rueppel Cryptosystem
// CME COLLAB (c) 12-09-2009

#include <windows.h>
#include <stdio.h>

extern "C"
{
#include "miracl\include\miracl.h"
};

#pragma comment(lib, "ms32.lib")
miracl *mip = NULL;

/*
Serial encoding
*/
void encode(unsigned char * p, unsigned int n, char * out)
{
    char * alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    // bits ordered 0... from MSB to LSB
    #define GETBIT(X) (((p[(X)/8] & (1<<(7-(X)%8))))?1:0)

    unsigned int cursor = 0;
    unsigned int n_bits = n*8;

    for(INT i=0; i<n_bits; i+=5)
    {
        unsigned int left = n_bits - i;
        if(left > 5)
            left = 5;

        UCHAR temp = 0;
        for(INT j=0; j<left; ++j)
            temp |= (GETBIT(i+j)<<(4-j));

        out[cursor++] = alphabet[temp];
    }

    out[cursor] = 0;
}

/*
CRC32
*/

unsigned int crc32(unsigned char * p, unsigned int n)
{
    unsigned int crc_table[256] = 
    {
        0x00000000,0x77073096,0xee0e612c,0x990951ba,
        0x076dc419,0x706af48f,0xe963a535,0x9e6495a3,
        0x0edb8832,0x79dcb8a4,0xe0d5e91e,0x97d2d988,
        0x09b64c2b,0x7eb17cbd,0xe7b82d07,0x90bf1d91,
        0x1db71064,0x6ab020f2,0xf3b97148,0x84be41de,
        0x1adad47d,0x6ddde4eb,0xf4d4b551,0x83d385c7,
        0x136c9856,0x646ba8c0,0xfd62f97a,0x8a65c9ec,
        0x14015c4f,0x63066cd9,0xfa0f3d63,0x8d080df5,
        0x3b6e20c8,0x4c69105e,0xd56041e4,0xa2677172,
        0x3c03e4d1,0x4b04d447,0xd20d85fd,0xa50ab56b,
        0x35b5a8fa,0x42b2986c,0xdbbbc9d6,0xacbcf940,
        0x32d86ce3,0x45df5c75,0xdcd60dcf,0xabd13d59,
        0x26d930ac,0x51de003a,0xc8d75180,0xbfd06116,
        0x21b4f4b5,0x56b3c423,0xcfba9599,0xb8bda50f,
        0x2802b89e,0x5f058808,0xc60cd9b2,0xb10be924,
        0x2f6f7c87,0x58684c11,0xc1611dab,0xb6662d3d,
        0x76dc4190,0x01db7106,0x98d220bc,0xefd5102a,
        0x71b18589,0x06b6b51f,0x9fbfe4a5,0xe8b8d433,
        0x7807c9a2,0x0f00f934,0x9609a88e,0xe10e9818,
        0x7f6a0dbb,0x086d3d2d,0x91646c97,0xe6635c01,
        0x6b6b51f4,0x1c6c6162,0x856530d8,0xf262004e,
        0x6c0695ed,0x1b01a57b,0x8208f4c1,0xf50fc457,
        0x65b0d9c6,0x12b7e950,0x8bbeb8ea,0xfcb9887c,
        0x62dd1ddf,0x15da2d49,0x8cd37cf3,0xfbd44c65,
        0x4db26158,0x3ab551ce,0xa3bc0074,0xd4bb30e2,
        0x4adfa541,0x3dd895d7,0xa4d1c46d,0xd3d6f4fb,
        0x4369e96a,0x346ed9fc,0xad678846,0xda60b8d0,
        0x44042d73,0x33031de5,0xaa0a4c5f,0xdd0d7cc9,
        0x5005713c,0x270241aa,0xbe0b1010,0xc90c2086,
        0x5768b525,0x206f85b3,0xb966d409,0xce61e49f,
        0x5edef90e,0x29d9c998,0xb0d09822,0xc7d7a8b4,
        0x59b33d17,0x2eb40d81,0xb7bd5c3b,0xc0ba6cad,
        0xedb88320,0x9abfb3b6,0x03b6e20c,0x74b1d29a,
        0xead54739,0x9dd277af,0x04db2615,0x73dc1683,
        0xe3630b12,0x94643b84,0x0d6d6a3e,0x7a6a5aa8,
        0xe40ecf0b,0x9309ff9d,0x0a00ae27,0x7d079eb1,
        0xf00f9344,0x8708a3d2,0x1e01f268,0x6906c2fe,
        0xf762575d,0x806567cb,0x196c3671,0x6e6b06e7,
        0xfed41b76,0x89d32be0,0x10da7a5a,0x67dd4acc,
        0xf9b9df6f,0x8ebeeff9,0x17b7be43,0x60b08ed5,
        0xd6d6a3e8,0xa1d1937e,0x38d8c2c4,0x4fdff252,
        0xd1bb67f1,0xa6bc5767,0x3fb506dd,0x48b2364b,
        0xd80d2bda,0xaf0a1b4c,0x36034af6,0x41047a60,
        0xdf60efc3,0xa867df55,0x316e8eef,0x4669be79,
        0xcb61b38c,0xbc66831a,0x256fd2a0,0x5268e236,
        0xcc0c7795,0xbb0b4703,0x220216b9,0x5505262f,
        0xc5ba3bbe,0xb2bd0b28,0x2bb45a92,0x5cb36a04,
        0xc2d7ffa7,0xb5d0cf31,0x2cd99e8b,0x5bdeae1d,
        0x9b64c2b0,0xec63f226,0x756aa39c,0x026d930a,
        0x9c0906a9,0xeb0e363f,0x72076785,0x05005713,
        0x95bf4a82,0xe2b87a14,0x7bb12bae,0x0cb61b38,
        0x92d28e9b,0xe5d5be0d,0x7cdcefb7,0x0bdbdf21,
        0x86d3d2d4,0xf1d4e242,0x68ddb3f8,0x1fda836e,
        0x81be16cd,0xf6b9265b,0x6fb077e1,0x18b74777,
        0x88085ae6,0xff0f6a70,0x66063bca,0x11010b5c,
        0x8f659eff,0xf862ae69,0x616bffd3,0x166ccf45,
        0xa00ae278,0xd70dd2ee,0x4e048354,0x3903b3c2,
        0xa7672661,0xd06016f7,0x4969474d,0x3e6e77db,
        0xaed16a4a,0xd9d65adc,0x40df0b66,0x37d83bf0,
        0xa9bcae53,0xdebb9ec5,0x47b2cf7f,0x30b5ffe9,
        0xbdbdf21c,0xcabac28a,0x53b39330,0x24b4a3a6,
        0xbad03605,0xcdd70693,0x54de5729,0x23d967bf,
        0xb3667a2e,0xc4614ab8,0x5d681b02,0x2a6f2b94,
        0xb40bbe37,0xc30c8ea1,0x5a05df1b,0x2d02ef8d
    };

    unsigned int result = 0xFFFFFFFF;

    for(unsigned int i=0; i<n; ++i)
    {
            unsigned int jjunk = crc_table[p[i] ^ (result & 0xFF)];

            result = (result >> 8) ^ jjunk;
    }

    return ~result;
}

/*
ENCRYPTO CIPHER

128 bit block-cipher.

*/
//-------------------------------------------------------

#define DELTA 0x9E3779B9
unsigned long bsw(unsigned long in)
{
	return (((in & 0x000000FF) << 24)
	+ ((in & 0x0000FF00) << 8)
	+ ((in & 0x00FF0000) >> 8)
	+ ((in & 0xFF000000) >> 24));
}

unsigned long ROL(unsigned long v, int p){
  return (v << p)|(v >> (32 - p));
} 
unsigned long ROR(unsigned long v, int p){
  return (v >> p)|(v << (32 - p));
}
unsigned short edxBOX[4] = {0xB05B, 0xE727, 0xD7C8, 0x844F};
unsigned short ediBOX[64] = {
      0xCEA6, 0x3FE5, 0xE8BA, 0x7805, 0xB8F0, 0x26E6, 0x950B, 0x02C9, 0x8CD8, 
      0xDCA6, 0x2FB6, 0xA8E9, 0xD65C, 0x7322, 0x514A, 0x1238, 0xB2CE, 0x1705, 
      0xDEB6, 0xF940, 0x04B9, 0x4FA8, 0x636D, 0xBFE5, 0x6DA6, 0x142F, 0x0E9F, 
      0xC62F, 0xA5A6, 0xDDA3, 0x0D28, 0xD7DE, 0x3A9A, 0x7755, 0xBB8A, 0x1EBF, 
      0x43D9, 0x3F8D, 0x47B6, 0x61F8, 0x318E, 0xAA3D, 0x52BB, 0xB85F, 0x274A, 
      0x52FC, 0x169B, 0xD73A, 0xDAC7, 0xECBB, 0xCBDA, 0xCDD6, 0x5AAC, 0xAAF3, 
      0xA702, 0xC977, 0x5FC5, 0x3C95, 0x8533, 0x4A87, 0xB05B, 0xE727, 0xD7C8, 
      0x844F};


unsigned long eaxBOX[4]  = {0x41CD80DC, 0x7D17C27E, 0x4ACA0D94, 0xD8772D0A};
unsigned long edx2BOX[4] = {0x3A3803A3, 0x8403C6C9, 0xB0882CD9, 0x41C6AF51};
unsigned long ebxBOX[256] = {
      0x5278D768, 0xBB167904, 0xC862C0EA, 0x3D2A74C7, 0x42494751, 0xD90BE783, 
      0x57A7CD31, 0x5E4567FF, 0x49B83ACA, 0x18E41D2D, 0xDA12D2B8, 0xC4A06AC9, 
      0xDC318226, 0xFE85E0F8, 0x5077A979, 0x3374E37D, 0xA888C9F9, 0xA464D25D, 
      0x58B7822B, 0x295760CF, 0x0CD6D069, 0xF74434DC, 0x30797989, 0x73D17BEE, 
      0x7CCA2A7C, 0xE732B742, 0x7422BCE5, 0x663ED894, 0x9732C258, 0x9DAD68CF, 
      0xEBCD0476, 0xE56EA394, 0x1B035F02, 0x27D9574E, 0xADDE9466, 0x97CE8D65, 
      0x0F5C2F4F, 0xDB44E778, 0x3F703E8F, 0x91FEC8CC, 0x03A58EBD, 0x8DA9D015, 
      0x7404CC9C, 0x45613FBF, 0x75495F7E, 0xF3FAC7E4, 0x06ADB02C, 0x8BC46395, 
      0x625BDAC2, 0x3D9F4233, 0xC70D6AB1, 0x9C5E439E, 0xF92E4C47, 0xADEB7BDF, 
      0x79CFDA63, 0x40720788, 0x1626E69F, 0xD3385F17, 0x22F33AC5, 0x92AFA1E2, 
      0x3A3803A3, 0x4F8BE4A3, 0xBDDEB1D6, 0x176B96D1, 0x3F21FD8D, 0x29C9F279, 
      0xD110733B, 0x13E3C9B8, 0x3A41D9E5, 0xF82D31A1, 0xA338369C, 0x25AAE543, 
      0x877F65E6, 0x4F21BD03, 0x393CB2A6, 0x8B311600, 0x275FA1DF, 0xAB893743, 
      0xB4E25C1C, 0x3FA2028C, 0x869860F2, 0x033F6E6F, 0xBD4CEE03, 0xE8ABDB53, 
      0x911597E5, 0x3B6D3108, 0xF3B06169, 0x78565B81, 0x8DB9DC26, 0x2F28B196, 
      0xEC5CFE99, 0xB0EF655E, 0x4ED57C6E, 0x5EA6A2F0, 0x45936BFB, 0xE44B75D4, 
      0xDB4BAB78, 0x76AB566C, 0xDCD46BC4, 0x18B3BCA5, 0xD445CBC2, 0xF0614D39, 
      0x8E7A56E1, 0xAF03AC0F, 0x257E6D04, 0xCCDAAC99, 0xFDBDBB5C, 0x81CB90B6, 
      0x256963D8, 0x343B7B18, 0x54375EE5, 0xAFE703C8, 0xAF181CA9, 0x55E927FD, 
      0xEC383391, 0xF08941C2, 0xED9BDF01, 0x19448D25, 0x20A01385, 0xFF301401, 
      0x9A61AC41, 0xAE4FDD66, 0x0BE0B80C, 0x0B5BD9AE, 0x8912CCB7, 0x8403C6C9, 
      0x5CEF5ACB, 0x4BF079D9, 0x64D41AE8, 0x0928B2E3, 0x2AD81923, 0x338BA9EE, 
      0x0C159FC2, 0xFCED28CB, 0xE8971A75, 0x0CAE4ADB, 0xB54CE64F, 0xCD212F65, 
      0x6D3D9DC7, 0x10981AF9, 0xDE089814, 0x5DC9A29B, 0xA4DFB3F0, 0x7E7A9C98, 
      0x84B54D4A, 0xD99CE362, 0xF155F34C, 0x20350FBE, 0x7EA54F22, 0xBEE7F6DA, 
      0x9465DDF8, 0x4BB49106, 0xEE5F6055, 0x0398122A, 0x8B3721E1, 0x700FFDA7, 
      0x0E8BB199, 0x4C2312EA, 0x1B49C45D, 0xE1E1E84D, 0xFAF0FD7F, 0x29360AE6, 
      0x6A5994F1, 0x0A207B64, 0xFD4C5DE6, 0x54FD5905, 0x5420B9D8, 0xD8359D58, 
      0x5563D9E6, 0x1EEA3C37, 0x321979DB, 0x1B812613, 0xE259DDBA, 0x6C25C744, 
      0x5E2BB4E5, 0x50D57CBC, 0x7DB3234D, 0x3791162C, 0x60578FD3, 0x4064DF86, 
      0xF85852D4, 0x05EBDA62, 0xFD0114AA, 0x3CD84826, 0x813CC5D4, 0x6FCA95A7, 
      0xF68280CD, 0x6C564755, 0xAC631453, 0xB73C9BBC, 0xB0882CD9, 0x01E23A6F, 
      0xA612C46A, 0xD598BBD8, 0xEDEE3085, 0x47704945, 0xDCBD15C9, 0x080AE86C, 
      0x1B470C7A, 0xDAE5305C, 0x2D2E9284, 0x2F84B9AA, 0xA254AF00, 0xCDD9390A, 
      0xDB63F1AA, 0xF2A00B52, 0x9D81E2E1, 0xD8BFF423, 0x62CFE56D, 0x11191275, 
      0xDF5B7CF7, 0x830AB240, 0x9507C43E, 0xEF7811E1, 0xF0E4AE12, 0x0F3DC457, 
      0x0AB65364, 0xE2224D0A, 0x926FF792, 0x76074B56, 0x503D8B3D, 0xC7B2CCDA, 
      0x76C3F829, 0x4B0712FE, 0x67112683, 0x753E4994, 0x46B7F3EC, 0x0FAF7469, 
      0xC4BC606C, 0x2A0182A2, 0x3C26A23F, 0x05199996, 0xB1CC8523, 0x3BE4EE24, 
      0x6C96BED4, 0xDF1FF27A, 0x2AF5580B, 0xB2B30F5D, 0xDA34CB4D, 0xA844F041, 
      0xD54769B3, 0x6969D4B9, 0xD86486A8, 0x6F48D7F3, 0x66D30BCF, 0x93D521A3, 
      0x67FFCCE2, 0xE81C6E5A, 0x075924CE, 0x03B6F007, 0x3F11F73E, 0x0E4C798F, 
      0xFF18A50B, 0xCC573F35, 0x63D09936, 0x41C6AF51
    };

unsigned long esiBOX[64] = {
      0x2C72F40E, 0xB3945E3E, 0x4AE073CF, 0x8621DD1C, 0x65B3DD7D, 0x8A4AD33C, 
      0x8150F9F5, 0xCF43C555, 0xDCDEABB3, 0xFCBB5DF1, 0x720BF4A3, 0x0E709E04, 
      0x44630130, 0x19A8646C, 0x3D0E2D3C, 0xBCAAED7E, 0xCC231C1B, 0xA347B0D1, 
      0x2D451211, 0xCE8E7E16, 0x3D347EC0, 0x837E9C2F, 0x7D0FF6E9, 0x49BE60DF, 
      0x1FCF50EA, 0x22B7A325, 0xFB92A805, 0x837A1724, 0x67D173CB, 0x581F2ABA, 
      0x0ADCF475, 0x4C864FCB, 0x067D7A51, 0x48FEC134, 0x7DFEED7E, 0x5CFBF379, 
      0x42404230, 0x56EC4F16, 0xDDCBEE9A, 0xD9B081B0, 0x3E58A872, 0x1D4F4BBF, 
      0xF558A1CE, 0x4939C3B7, 0x90FB040F, 0x6F38A3C6, 0xABDA7FBA, 0xB87E242C, 
      0xF6E3F9EE, 0x0CCFFD20, 0xC5B27D06, 0xB40BCBFD, 0xFD652DCE, 0x773976D5, 
      0x6866588C, 0x91AB938B, 0x35DEE3AD, 0x630525C1, 0x67067FB0, 0xCECAA9E3, 
      0x41CD80DC, 0x7D17C27E, 0x4ACA0D94, 0xD8772D0A};
/*
void decrypt_blocks(unsigned long v[8])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 64; i++)
		{
			v[0] = (bsw(ROL(v[4],  2) ^ v[0]) - DELTA) ^ esiBOX[i];
			v[1] = (bsw(ROL(v[5],  4) ^ v[1]) - DELTA) ^ esiBOX[i];
			v[2] = (bsw(ROL(v[6],  8) ^ v[2]) - DELTA) ^ esiBOX[i];
			v[3] = (bsw(ROL(v[7],  16) ^ v[3]) - DELTA) ^ esiBOX[i];

			v[0] = (bsw(~(v[0])) + edxBOX[j]) ^ esiBOX[i];
			v[1] = ~(ROL(v[1] - edxBOX[j], 7));
			v[2] = ROR(~(bsw(v[2]) + ebxBOX[64 * j + i]), 25);
			v[3] = bsw(~(v[3] ^ eaxBOX[j]) + ediBOX[i]) ^ edx2BOX[j];

			v[0] = bsw(~(esiBOX[i]) ^ v[0]) + ebxBOX[64 * j + i];
			v[1] = ~(ROL(ebxBOX[64 * j + i], 4) ^ v[1]);
			v[2] = ROL(v[2] - ediBOX[i], 7);
			v[3] = bsw(v[3] ^ ebxBOX[64 * j + i]) - ebxBOX[64 * j + i];

			v[0] = (~(v[0]) ^ ebxBOX[64 * j + i]) + ediBOX[i];
			v[1] = bsw(ROL(v[1] + ediBOX[i], 9) ^ esiBOX[i]);
			v[2] = ROR(v[2] - ~(ebxBOX[64 * j + i]), 7);
			v[3] = (bsw(v[3]) ^ esiBOX[i]) + ediBOX[i];

			v[0] = (bsw(v[0]) - ediBOX[i]) ^ esiBOX[i];
			v[1] = (~(v[1]) - ediBOX[i]) ^ esiBOX[i];
			v[2] = ROR(v[2] - ebxBOX[64 * j + i], 5) ^ esiBOX[i];
			v[3] = ROL(v[3] ^ ebxBOX[64 * j + i], 3) ^ esiBOX[i];

			v[0] = ~((v[0] - DELTA) ^ ebxBOX[64 * j + i]) ^ v[4];
			v[1] = ~((v[1] - DELTA) ^ ebxBOX[64 * j + i]) ^ v[5];
			v[2] = ~((v[2] - DELTA) ^ ebxBOX[64 * j + i]) ^ v[6];
			v[3] = ~((v[3] - DELTA) ^ ebxBOX[64 * j + i]) ^ v[7];
		}
	}
}
*/
void encrypt_blocks(unsigned long v[8])
{
	for (int j = 3; j >= 0; j--)
	{
		for (int i = 63; i >= 0; i--)
		{
			v[3] = (~(v[3] ^ v[7]) ^ ebxBOX[64 * j + i]) + DELTA;
			v[2] = (~(v[2] ^ v[6]) ^ ebxBOX[64 * j + i]) + DELTA;
			v[1] = (~(v[1] ^ v[5]) ^ ebxBOX[64 * j + i]) + DELTA;
			v[0] = (~(v[0] ^ v[4]) ^ ebxBOX[64 * j + i]) + DELTA;

			v[3] = ROR(v[3] ^ esiBOX[i], 3) ^ ebxBOX[64 * j + i];
			v[2] = ROL(v[2] ^ esiBOX[i], 5) + ebxBOX[64 * j + i];
			v[1] = ~((v[1] ^ esiBOX[i]) + ediBOX[i]);
			v[0] = bsw((v[0] ^ esiBOX[i]) + ediBOX[i]);

			v[3] = bsw((v[3] - ediBOX[i]) ^ esiBOX[i]);
			v[2] = ROL(v[2], 7) + ~(ebxBOX[64 * j + i]);
			v[1] = ROR(bsw(v[1]) ^ esiBOX[i], 9) - ediBOX[i];
			v[0] = ~((v[0] - ediBOX[i]) ^ ebxBOX[64 * j + i]);

			v[3] = bsw(v[3] +  ebxBOX[64 * j + i]) ^  ebxBOX[64 * j + i];
			v[2] = ROR(v[2], 7) + ediBOX[i];
			v[1] = ~(v[1]) ^ ROL(ebxBOX[64 * j + i], 4);
			v[0] = bsw(v[0] - ebxBOX[64 * j + i]) ^ (~(esiBOX[i]));

			v[3] = ~((bsw(v[3] ^ edx2BOX[j])) - ediBOX[i]) ^ eaxBOX[j];
			v[2] = bsw((~(ROL(v[2], 25))) - ebxBOX[64 * j + i]);
			v[1] = ROR(~v[1], 7) + edxBOX[j];
			v[0] = ~(bsw((v[0] ^ esiBOX[i]) - edxBOX[j]));

			v[3] = bsw((v[3] ^ esiBOX[i]) + DELTA) ^ ROL(v[7],  16);
			v[2] = bsw((v[2] ^ esiBOX[i]) + DELTA) ^ ROL(v[6],  8);
			v[1] = bsw((v[1] ^ esiBOX[i]) + DELTA) ^ ROL(v[5],  4);
			v[0] = bsw((v[0] ^ esiBOX[i]) + DELTA) ^ ROL(v[4],  2);
			
		}
	}
}
//-------------------------------------------------------

void main(INT ac, char * *av)
{
	mip = mirsys(2048, 16); 
	char buf[256], buf2[256], name[50];
	printf("Name: ");
	scanf("%s", name);

    unsigned long block1[8] = {0,0,0,0, 0x820E6467, 0x79AE25F0, 0x5BCB06E9, 0xDB98265C};
    unsigned long block2[8] = {0,0,0,0, 0x820E6467, 0x79AE25F0, 0x5BCB06E9, 0xDB98265C};

    // crc of name
    unsigned long crc = crc32((unsigned char *)name,strlen(name));
    // form first block
    unsigned __int64 dividend = (unsigned __int64)GetTickCount()<<32 | GetTickCount();


    block1[0] = crc;
    block1[1] = dividend % 0xD72A978F;
    block1[2] = dividend % 0xD73C1CB5;
    block1[3] = 0xD4804EB6;
    // encrypt it
    encrypt_blocks(block1);
    // form second block
    *(unsigned __int64 *)block2 = dividend;
    block2[2]=GetTickCount();
    block2[3]=block2[2]+1;
    // encrypt it
    encrypt_blocks(block2);

    // encode the blocks
    encode((unsigned char *)block1, 16, buf);
    strcat(buf, "+");
    encode((unsigned char *)block2, 16, buf+strlen(buf));
    printf("Serial: %s\n", buf);
	
	
	big alpha,y,x,p,e,q,r,k,m;
	alpha = mirvar(0);
	y = mirvar(0);
	x = mirvar(0);
	p = mirvar(0);
	e = mirvar(0);
	q = mirvar(0);
	r = mirvar(0);
	k = mirvar(0);
	m = mirvar(0);

	
	irand(GetTickCount());

	do{
	mip->IOBASE = 16;

	//Public key parameters

	cinstr(p,		"1EEAC785FB45C3F55"); // 35644997503173803861
	cinstr(q,		"18BBD2D195D16991"); // 1782249875158690193
	cinstr(x,		"07FC527A5AB7C963"); // 575425537858062691
	cinstr(alpha,	"A8EF6034CD90CA17"); // 12173054097709124119
	cinstr(y,		"64077FA05BA69A4E"); // 7207870055338908238

	bigdig(14,16,k); // random K
	sprintf(buf,"%08X",bsw(crc)); // CRC of name
	cinstr(m, buf);

	//alpha^-k mod p = r
	powmod(alpha, k, p, r); 
	xgcd(r,p,r,r,r); 
	
	//m*r mod p = e
	multiply(m,r,m);
	power(m,1,p,e);

	//x*e + k mod q = s
	multiply(x,e,x);
	add(x,k,x);
	power(x,1,q,x);

	cotstr(e, buf2);
	cotstr(x, buf2);

	mip->IOBASE = 10;
	cotstr(e,buf2);
	encode((unsigned char *)buf2, strlen(buf2), buf);
	strcat(buf,"+");
	cotstr(x,buf2);
	encode((unsigned char *)buf2, strlen(buf2), buf+strlen(buf));
	}
	while(strlen(buf) > 63); // If we get too long activation code, crackme-input-box wont handle it

	printf("Activation: %s\n", buf);

	mirkill(y);
	mirkill(x);
	mirkill(p);
	mirkill(e);
	mirkill(q);
	mirkill(r);
	mirkill(k);
	mirkill(m);

    printf("ctrl+C to quit!\n");
    while(1);

}

