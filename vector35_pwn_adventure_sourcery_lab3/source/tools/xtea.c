#include <stdint.h>
#include <stdio.h>

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

void decipher(uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*371;
    for (i=0; i < 371; i++) {
    	printf("key[%d]\n", (sum>>11)&3);
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        sum -= delta;
    	printf("key[%d]\n", (sum&3));
    	printf("--\n");
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    v[0]=v0; v[1]=v1;
}

void decipher2(uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1];
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x28B7BD67 + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x8A8043AE + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x8A8043AE + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xEC48C9F5 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xEC48C9F5 + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x4E11503C + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x4E11503C + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xAFD9D683 + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xAFD9D683 + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x11A25CCA + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x11A25CCA + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x736AE311 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x736AE311 + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xD5336958 + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xD5336958 + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x36FBEF9F + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x36FBEF9F + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x98C475E6 + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x98C475E6 + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xFA8CFC2D + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xFA8CFC2D + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x5C558274 + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x5C558274 + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xBE1E08BB + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xBE1E08BB + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x1FE68F02 + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x1FE68F02 + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x81AF1549 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x81AF1549 + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xE3779B90 + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xE3779B90 + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x454021D7 + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x454021D7 + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xA708A81E + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xA708A81E + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x08D12E65 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x08D12E65 + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x6A99B4AC + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x6A99B4AC + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xCC623AF3 + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xCC623AF3 + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x2E2AC13A + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x2E2AC13A + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x8FF34781 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x8FF34781 + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xF1BBCDC8 + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xF1BBCDC8 + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x5384540F + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x5384540F + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xB54CDA56 + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xB54CDA56 + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x1715609D + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x1715609D + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x78DDE6E4 + key[0]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x78DDE6E4 + key[0]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0xDAA66D2B + key[3]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0xDAA66D2B + key[1]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x3C6EF372 + key[2]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x3C6EF372 + key[2]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x9E3779B9 + key[1]);
	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (0x9E3779B9 + key[3]);
	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (0x00000000 + key[0]);
	v[0]=v0; v[1]=v1;
}

void decipher3(uint32_t v[2]);

int main()
{
	char ptext[8] = "CSAWHAHA";
	uint32_t v[2];
	uint32_t k[4] = {0xDEADBEEF, 0xCAFEBABE, 0x8BADF00D, 0xC0D3D00D};

	v[0] = *(uint32_t *)(ptext+0);
	v[1] = *(uint32_t *)(ptext+4);

	printf("v: %08X-%08X\n", v[0], v[1]);
	encipher(v, k);
	printf("v: %08X-%08X\n", v[0], v[1]);
	//decipher(v, k);
	decipher3(v);
	printf("v: %08X-%08X\n", v[0], v[1]);

	return 0;
}
