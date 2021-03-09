// keygen j0sh's_Crackme1


#include <stdio.h>

void main(int argc, char * argv[])
{
	int i=0, len=0, serial=0;

	if(argc < 2)
		return;

	len = strlen(argv[1]);

	for(;i<len; ++i)
		serial += argv[1][i];

	serial = serial * 0x1337 * len;

	printf("serial: %u\n", serial);
}	
