// solution to NeoN's 192 bits keygenme
// 9/22/2007 andrewl

// compile: cl keygen.cpp /EHsc /O2 /link ntl.lib

// NTL lib (http://www.shoup.net/ntl)
//
#include "NTL/zz.h"

using namespace std;
using namespace NTL;

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
			printf("enter name as argument\n");
			return -1;
	}

    // initialize modulus
	
	/*
    unsigned char bytes_modulus[] = {	0x69, 0xbd, 0x92, 0x18, 0xa7, 0x41, 0xec, 0x6e,
	    								0xed, 0x29, 0x70, 0xd2, 0x72, 0xef, 0xf8, 0xc4,
										0xc3, 0xdd, 0xbf, 0x63, 0x8f, 0x3f, 0xc8, 0xb0	};

    ZZ modulus = ZZFromBytes(bytes_modulus, 24);
	*/

	// at offset 00403237 you find prime: 4334687418001776494064519822354979895306094686353721834857
	ZZ factor1 = to_ZZ("56820299132471488072643744243");
	ZZ factor2 = to_ZZ("76287655717824315207331163699");
	ZZ phi_n = (factor1-1) * (factor2-1);
	ZZ modulus = factor1 * factor2;

	cout << "phi_n is: " << phi_n << endl;
	cout << "modulus: " << modulus << endl;
	cout << "product: " << modulus << endl;

	ZZ encrypt = to_ZZ("65537");
	ZZ decrypt;

	// find decrypt
	for(ZZ i = to_ZZ("1"); ; i++)
	{
			ZZ temp = (phi_n * i) / encrypt + 1;

			if(to_ZZ("1") == MulMod(encrypt, temp, phi_n))
			{
					decrypt = temp;
					break;
			}
	}

	cout << "decrypt: " << decrypt << endl;

	//cout << "I wonder what decrypt * encrypt  mod modulus are! " << MulMod(encrypt, decrypt, phi_n) << endl;
	//cout << " I wonder what their products are " << encrypt * decrypt << endl;

    // initilize name "asdf"
	
    //unsigned char bytes_name[] = {	0x61, 0x73, 0x64, 0x66	};

    ZZ name = ZZFromBytes((unsigned char *)argv[1], strlen(argv[1]));

	ZZ key = PowerMod(name, decrypt, modulus);

//	ZZ key_copy = key;
//	ZZ key_copy2 = key;

	cout << "key: (as integer) " << key << endl;

	unsigned char answer[30] = {0};

	BytesFromZZ(answer, key, 30);

	cout << "key: (to enter) ";

	for(int i=0; i<24; ++i)
			printf("%02X", 0x000000FF & answer[i]);

	cout << endl;

	return 0;
/*

	printf("\n");

	for(int i=0; i<16; i++)
	{
		key = MulMod(key, key, modulus);
		BytesFromZZ(answer, key, 30);

		for(int i=0; i<24; ++i)
			printf("%02X ", 0x000000FF & answer[i]);

		printf("\n");
	}

	printf("lala-\n");
	key_copy = MulMod(key_copy, key, modulus);

	BytesFromZZ(answer, key_copy, 30);

	for(int i=0; i<24; ++i)
			printf("%02X ", 0x000000FF & answer[i]);

	printf("\n");

	printf("Could I raise the origingal key to the 65537'th power to get it?\n");

	key_copy2 = PowerMod(key_copy2, 65537, modulus);

	BytesFromZZ(answer, key_copy2, 30);

	for(int i=0; i<24; ++i)
			printf("%02X ", 0x000000FF & answer[i]);

	printf("\n");
*/


}



