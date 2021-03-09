#define INFO "Keygen to death's \"Saddam crackme\" - andrewl - dec21_2009\n\n"

#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "crypt32.lib")

#define ERR(A) { MessageBox(0,(A),"Error",MB_OK); goto cleanup; }

BOOL DesEncrypt(BYTE block[8], BYTE key[8])
{
    BOOL fRet=0;
    DWORD dwRet;
    BYTE text[16]; // +8 for padding

    // get provider
    //
    HCRYPTPROV hProv=0;
    if(!CryptAcquireContext(&hProv,0,MS_DEF_PROV,PROV_RSA_FULL,0))
        if(!CryptAcquireContext(&hProv,0,MS_DEF_PROV,PROV_RSA_FULL,CRYPT_NEWKEYSET))
            ERR("CryptAcquireContext()");

    // setup key
    //
    typedef struct _KEY_STRUCT
    {
        PUBLICKEYSTRUC pks;
        DWORD key_size;
        BYTE key_bytes[8];
    } KEY_STRUCT, *PKEY_STRUCT;

    KEY_STRUCT ks;
    ks.pks.bType=PLAINTEXTKEYBLOB;
    ks.pks.bVersion=CUR_BLOB_VERSION;
    ks.pks.reserved=0;
    ks.pks.aiKeyAlg=CALG_DES;
    ks.key_size=8;
    memcpy(&ks.key_bytes,key,8);

    HCRYPTKEY hKey;
    if(!CryptImportKey(hProv,(PBYTE)&ks,sizeof(ks),0,0,&hKey))
        ERR("CryptImportKey()");

    // encrypt
    //
    dwRet=8;
    memcpy(text,block,8);
    if(!CryptEncrypt(hKey, 0, 1, 0, text, &dwRet, 16))
        ERR("CryptEncrypt()");
    
    // return encrypted value
    //
    memcpy(block,text,8);

    fRet=1;

    cleanup:

    if(hProv) 
        CryptReleaseContext(hProv, 0);

    return fRet;
}



DWORD DoHash(unsigned char * str1)  
{ 
    #define BSWAP(A) (((A)>>24) | (((A)>>8)&0xFF00) | (((A)<<8)&0xFF0000) | ((A)<<24))
	
    // found this succinct SHA1 code from:
    // http://www.hoozi.com/post/a93ye/secure-hash-algorithm-sha-1
    #define rotateleft(x,n) ((x<<n) | (x>>(32-n)))  
    #define rotateright(x,n) ((x>>n) | (x<<(32-n)))  
    unsigned long int h0,h1,h2,h3,h4,a,b,c,d,e,f,k,temp;  
   
    h0 = 0x67452301;  
    h1 = 0xEFCDAB89;  
    h2 = 0x98BADCFE;  
    h3 = 0x10325476;  
    h4 = 0xC3D2E1F0;  
   
    unsigned char * str;  
    str = (unsigned char *)malloc(strlen((const char *)str1)+100);  
    strcpy((char *)str,(const char *)str1);  
   
    int current_length = strlen((const char *)str);  
    int original_length = current_length;  
    str[current_length] = 0x80;  
    str[current_length + 1] = '\0';  
   
    char ic = str[current_length];  
    current_length++;  
   
    int ib = current_length % 64;  
    if(ib<56)  
        ib = 56-ib;  
    else  
        ib = 120 - ib;  
  
    int i;
    for(i=0;i < ib;i++)  
    {  
        str[current_length]=0x00;  
        current_length++;  
    }  
    str[current_length + 1]='\0';  
   
    for(i=0;i<6;i++)  
    {  
        str[current_length]=0x0;  
        current_length++;  
    }  
    str[current_length] = (original_length * 8) / 0x100 ;  
    current_length++;  
    str[current_length] = (original_length * 8) % 0x100;  
    current_length++;  
    str[current_length+i]='\0';  
   
    int number_of_chunks = current_length/64;  
    unsigned long int word[80];  
    for(i=0;i<number_of_chunks;i++)  
    {  
        int j;
        for(j=0;j<16;j++)  
        {  
            word[j] = str[i*64 + j*4 + 0] * 0x1000000 + str[i*64 + j*4 + 1] * 0x10000 + str[i*64 + j*4 + 2] * 0x100 + str[i*64 + j*4 + 3];  

	    // modmod!
	    word[j] = BSWAP(word[j]);

        }  
        for(j=16;j<80;j++)  
        {  
            word[j] = rotateleft((word[j-3] ^ word[j-8] ^ word[j-14] ^ word[j-16]),1);  
        }  
   
        a = h0;  
        b = h1;  
        c = h2;  
        d = h3;  
        e = h4;  
   
        for(int m=0;m<80;m++)  
        {  
            if(m<=19)  
            {  
                f = (b & c) | ((~b) & d);  
                k = 0x5A827999;  
            }  
            else if(m<=39)  
            {  
                f = b ^ c ^ d;  
                k = 0x6ED9EBA1;  
            }  
            else if(m<=59)  
            {  
                f = (b & c) | (b & d) | (c & d);  
                k = 0x8F1BBCDC;  
            }  
            else  
            {  
                f = b ^ c ^ d;  
                k = 0xCA62C1D6;   
            }  
   
            temp = (rotateleft(a,5) + f + e + k + word[m]) & 0xFFFFFFFF;  
            e = d;  
            d = c;  
            c = rotateleft(b,30);  
            b = a;  
            a = temp;  
   
        }  
   
        h0 = h0 + a;  
        h1 = h1 + b;  
        h2 = h2 + c;  
        h3 = h3 + d;  
        h4 = h4 + e;  
   
    }  
  
    // mod mod!
    h0 = BSWAP(h0);
    h1 = BSWAP(h1);
    h2 = BSWAP(h2);
    h3 = BSWAP(h3);
    h4 = BSWAP(h4);

    return h0+h1+h2+h3+h4;
}  


int main(int ac, PCHAR *av)
{
    DWORD dwRet;
    BYTE key[8];
    BYTE text[8];

    // user input
    //
    CHAR strName[128];
    CHAR strKey[128];

    printf(INFO);

    printf("enter challenge key (provided by crackme): ");
    gets(strKey);

    if(strlen(strKey) != 16)
        ERR("challenge key should be 64-bit value in HEX format!");

    printf("enter name: ");
    gets(strName);

    dwRet=8;
    if(!CryptStringToBinary(strKey,16,CRYPT_STRING_HEX,key,&dwRet,0,0))
        ERR("challenge key should be 64-bit value in HEX format!");

    for(INT i=0; i<4; ++i)
        { BYTE t=key[i]; key[i]=key[7-i]; key[7-i]=t; }

    printf("key bytes: ");
    for(INT i=0; i<8; ++i)
        printf("%02X ", key[i]);
    printf("\n");

    DWORD hash;
    hash = DoHash((PUCHAR)strName);
    printf("hash(name): %08X\n", hash);

    // form plaintext
    //
    DWORD permute_seeds[18] = {
	  0x0A20D521, 0x1800F711, 0x25E11901, 0x33C13AF1, 
	  0x41A15CE1, 0x4F817ED1, 0x5D61A0C1, 0x6B41C2B1, 
	  0x7921E4A1, 0x87020691, 0x94E22881, 0xA2C24A71, 
	  0xB0A26C61, 0xBE828E51, 0xCC62B041, 0xDA42D231, 
	  0xE822F421, 0xF6031611
    };

    DWORD permute_seed = permute_seeds[GetTickCount()%18]; 

    printf("chose permute seed: %08X\n", permute_seed);

    *(PDWORD)(text) = permute_seed ^ hash;
    *(PDWORD)(text+4) = 'krmS' ^ hash;
 
    printf("left block: %08X ^ %08X == %08X\n", permute_seed, hash, *(PDWORD)text);
    printf("right block: %08X ^ %08X == %08X\n", 'krmS', hash, *(PDWORD)(text+4));
 
    printf("plain text: ");
    for(INT i=0; i<8; ++i)
        printf("%02X ", text[i]);
    printf("\n"); 

    // encrypt
    //
    if(!DesEncrypt(text, key))
        ERR("DesEncrypt()");

    printf("ciphertext: ");
    for(INT i=0; i<8; ++i)
        printf("%02X ", text[i]);
    printf("\n");

    // encode
    //
    dwRet=32;
    CHAR serial[32];
    if(!CryptBinaryToString(text, 8, CRYPT_STRING_BASE64|CRYPT_STRING_NOCRLF, serial, &dwRet))
        ERR("CryptStringToBinary()");

    printf("serial: %s\n", serial);

    printf("ctrL+C to quit!\n");
    while(1);

    cleanup:

    return 0; 
}

