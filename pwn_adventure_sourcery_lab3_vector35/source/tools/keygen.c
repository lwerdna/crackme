#include <stdio.h>
#include <stdint.h>
void encipher(uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;
    for (i=0; i < 371; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    }
    v[0]=v0; v[1]=v1;
}
int main()
{
	uint32_t v[2];
	uint32_t k[4] = {0xDEADBEEF, 0xCAFEBABE, 0x8BADF00D, 0xC0D3D00D};
	v[0] = 0x57415343; // CSAW
	v[1] = 0x41484148; // HAHA
	encipher(v, k);
	printf("%08X-%08X\n", v[0], v[1]);
	return 0;
}

