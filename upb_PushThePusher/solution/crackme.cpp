// push-the-pusher source with mods:
// - crc functionality ripped
// - rand ripped (so you're guaranteed to have same LCG PRNG params, despite your runtime)
// - signed comparison for FAF3CCCE made unsigned

#include <iostream>
#include <iomanip>
#include <string>

// <rip>
int g_rand_val = 0;

void rip_srand(int seed)
{
    g_rand_val = seed;
}

short int rip_rand()
{
    g_rand_val = (g_rand_val * 0x343FD) + 0x269EC3;
    return (g_rand_val >> 16) & 0x7FFF;
}

unsigned long crc_table[256] =
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

unsigned long crc32(unsigned char * p_input, unsigned int len, unsigned int crc)
{
    // stack picture:
    // (lo addresses)
    // 
    // old ebp                  <-- ebp+0
    // return                   <-- ebp+4
    // arg0 - pointer to buff   <-- ebp+8
    // arg1 - size of buff      <-- ebp+C
    // arg2 - initial CRC val   <-- ebp+10
    //
    // (hi addresses)

    // CRC register looks like this:

    // +---+---+---+---+
    // |msb|   |   |lsb|
    // +---+---+---+---+
    //  ^              ^
    //  |              |
    //  |              +---- holds x^24, x^25, ..., x^31 coefficients
    //  +------------------- holds x^0, x^1, ..., x^7 coefficients

    // since it reads the bytes left-to-right from the buffer, the input
    // buffer is actually this:

    // +-------+-------+-----
    // | byte0 | byte1 | ...
    // +-------+-------+-----
    // 
    // where byte0's bits represent ***MSB*** X^(N-7) + X^(N-6) + ... + X^(N) ***LSB***
    // and byte1's bits represent ***MSB*** X^(N-15) + X^(N-14) + ... + X^(N-8) ***LSB***
    // and so on (N is the degree of the polynomial of the input data)

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
// </rip>

char msgenc[] = {0x9b, 0x2f, 0x51, 0x95, 0x49, 0x3d, 0xec, 0xd7, 0xce, 0x23, 0x5b, 0x75, 0x12, 0x25, 0xb1, 0x7c,
0xf7, 0xef, 0x05, 0xfd, 0x6f, 0xea, 0xa7, 0x01, 0x7e, 0xa1, 0xe6, 0xd7, 0x69, 0x7f, 0xda, 0xd2, 0x66, 0x62, 0xb8,
0xac, 0x06, 0xea, 0xc9, 0x4c, 0x6c, 0x22, 0x25, 0xcd, 0x41, 0x55, 0xdc, 0x80, 0x7f, 0x4c, 0x58, 0x9b, 0x29
, 0x8e, 0xff, 0x86, 0xb2, 0xcf, 0x0b, 0x96, 0x9c, 0xae, 0xa9, 0xd9, 0xe9, 0x0f, 0x9e, 0xea, 0x00};

#define ROR(a, amt) ((a) >> (amt)) | ((a) << (8 - (amt)))

char buf[0x1000] = {0};

int main(int argc, char** argv)
{
	// previous bug:
    // if (argc % 0x5550423E == 0x50534852)
    if((unsigned int)argc % 0x5550423E == 0x50534852)
	{
		rip_srand(/*0xFAF3CCCE*/ argc);
		for (int i = 0; msgenc[i] != '\0'; ++i)
		{
			unsigned short r1 = rip_rand();
			unsigned short r2 = rip_rand();
			unsigned short r3 = rip_rand();

			unsigned char c = msgenc[i];
			c -= (unsigned char)(r3 >> 5);
			c ^= (unsigned char)(r2 >> 4);
			c = ROR(c, (unsigned char)((r1 >> 3) % 7));

			std::cout << c;
		}

		return argc + 1234;
	}

	if (argc+1 == 0)
	{
		unsigned short *cmd = (unsigned short*)argv;
		buf[cmd[0] ^ 0xFFFF] ^= 1 << (cmd[2] ^ 0xFFFF);
		return (int)cmd;
	}

	if (argc == 0x1001)
		exit(argc);

	if (argc != 0 && argc != 1)
	{
		std::cout << "invalid" << std::endl;
		main(0x1001, (char**)&argc);
	}

	memcpy(&buf, &msgenc, std::min(sizeof(buf), sizeof(msgenc)));
	std::string name, serial;

	std::cout << "upb's push the pusher crackme. hope it wont last as long as the previous one :P" << std::endl << "2006.12.23" << std::endl;
	std::cout << "name: ";
	std::getline(std::cin, name);

	std::cout << "serial: ";
	std::getline(std::cin, serial);

	if (serial.length() < 9 ||
		serial[4] != '-')
	{
		main(0x3, NULL);
	}

	for (int i = 0; i < name.length(); ++i)
		buf[i % std::min(sizeof(buf), name.length())] ^= (unsigned char)name[i];

	unsigned long firstpart = *(unsigned long*)serial.c_str();
	rip_srand(firstpart);

	for (int i = 0; i < sizeof(buf); ++i)
		buf[i] ^= (unsigned char)(rip_rand() >> 4);

	std::string cmds(serial.substr(5));

	for (int i = 0; i + 3 < cmds.length(); i += 4)
	{
		// FFTT - flips bits from FF to TT (inclusive)
		std::string hextab = "1234567890ABCDEF";
		int f1 =  hextab.find(cmds[i]);
		int f2 =  hextab.find(cmds[i + 1]);
		int t1 =  hextab.find(cmds[i + 2]);
		int t2 =  hextab.find(cmds[i + 3]);

		if (f1 == -1 || f2 == -1 || t1 == -1 || t2 == -1)
		{
			char *foo = (char*)hextab.c_str();
			main(2, &foo);
		}

		unsigned short f = (f1 << 4) | f2;
		unsigned short t = (t1 << 4) | t2;
		for (unsigned short i = std::min(f, t); i <= std::max(f, t); ++i)
		{
			unsigned short byteindex = (sizeof(buf) - (i / 8) + 1) % sizeof(buf);
			unsigned short bitindex = i % 8;
			unsigned short cmd[] = {byteindex ^ 0xFFFF, (unsigned short)buf[5], bitindex ^ 0xFFFF};
			char** foo = (char**)&cmd;

			main(0xFFFFFFFF, foo);
		}
	}

	unsigned long crc=0x21337455;
	crc = crc32((unsigned char*)buf, sizeof(buf), crc);
	main(crc, (char**)&buf);

	return 0;
}



