// solution to luxor's Keygenme I v1.0
// 9/6/2007 andrewl and ilkhomd

// credit to Mr. Haandi's tutorial on luxor's Keygenme III which showed to use
// NTL lib (http://www.shoup.net/ntl) to solve equation 
//

// compile: cl keygen.cpp /EHsc /O1 /link ntl.lib

#include <NTL/ZZ_pXFactoring.h>

using namespace std;
using namespace NTL;

void de_hash_serial(__int64 serial_hash, char * result)
{
    char lookup[] = "CDFHKMPQTVX23468";

    int i;

    memset(result, 'Z', 19);
    result[19] = '\0';

    int char_loc = 18;

    for(i=19; i>0; --i)
    {
        unsigned char nibble = 0;

        nibble = serial_hash & 0xF;

        result[char_loc--] = lookup[nibble];

        serial_hash >>= 4;
    }

    result[19] = '\0';
}

__int64 get_hash_name(unsigned char * name)
{
    unsigned __int64 hash_name = -1;
    unsigned __int64 table[256] = {0};

    // INIT TABLE OF 256 SIXTY-FOUR BIT NUMBERS
    {
        int i, j;
        unsigned __int64 var = 0;

        for(i=0; i<256; ++i)
        {
            var = i;

            for(j=0; j<8; ++j)
                if(var % 2 == 0)
                    var = (var >> 1);
                else
                    var = (var >> 1) ^ 0x95AC9329AC4BC9B5;

            table[i] = var;
        }
    }

    // USE TABLE TO GET HASH OF USERNAME
    {
        unsigned char * cur_char;
        unsigned int index;

        for(cur_char = name; *cur_char; ++cur_char)
        {
            index = *cur_char ^ (unsigned char)hash_name;

            hash_name = (hash_name >> 8) ^ table[index];
        }
    }

    return hash_name;
}

unsigned __int64 zzp_to_int64(ZZ_p & num_mod)
{
    unsigned char bytes[8];

    ZZ num = rep(num_mod);

    BytesFromZZ(bytes, num, 8);

    return *(__int64 *)bytes;
}

ZZ int64_to_zzp(__int64 num)
{
    return ZZFromBytes((unsigned char *)&num, 8);
}

int main(int argc, char * argv[])
{
    char charhash[20] = {'\0'};
    unsigned __int64 hash_name;

    if(argc < 2)
    {
        printf("Enter name as argument.\n");
        return -1;
    }

    hash_name = get_hash_name((unsigned char *)argv[1]);

    printf("hashed your name to: %016I64x (%I64u)\n", hash_name, hash_name);

    ZZ modulus = to_ZZ("18446744073709551616");
    ZZ_p::init(modulus);

    ZZ_pX polynomial;
    ZZ_p root;

    if(hash_name & 1)
    {
        //SetCoeff(polynomial, 0, to_ZZ_p(to_ZZ("-3932672073523589310"))); // X^0
        SetCoeff(polynomial, 0, to_ZZ_p(to_ZZ("14514072000185962306"))); // X^0
        SetCoeff(polynomial, 1, to_ZZ_p(to_ZZ("0"))); // X^1
        SetCoeff(polynomial, 2, to_ZZ_p(int64_to_zzp(hash_name))); // X^2
        SetCoeff(polynomial, 3, to_ZZ_p(to_ZZ("1"))); // X^3
    }
    else
    {
        SetCoeff(polynomial, 0, to_ZZ_p(int64_to_zzp(hash_name))); // X^0
        SetCoeff(polynomial, 1, to_ZZ_p(to_ZZ("0"))); // X^1
        SetCoeff(polynomial, 2, to_ZZ_p(to_ZZ("10785157014839085493"))); // X^2
        SetCoeff(polynomial, 3, to_ZZ_p(to_ZZ("1"))); // X^3
    }

    FindRoot(root, polynomial);

    unsigned __int64 temp = zzp_to_int64(root);
    de_hash_serial(temp, charhash);
    printf("key: %s\n", charhash);
}

