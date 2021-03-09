// 2008 andrewl

// os
#include <windows.h>

// openssl
#include "idiotopenssl.h"
#include "crypto\bn\bn.h"
#include "crypto\hmac\hmac.h"

typedef ULONG (*PFN_TRANSFORM_USER0)(PUCHAR, ULONG);
typedef void (*PFN_TRANSFORM_PREFIX0)(PCHAR, PUCHAR);

// from misc rips
extern UCHAR transform_user0[];
extern UCHAR index_in_wagalphabet[];
extern UCHAR transform_prefix0[];
extern CHAR wagalphabet[];

void fixup_rips()
{
    // fixup the reference to wagalphabet in index_in_wagalphabet()
    *(ULONG *)(index_in_wagalphabet + 0x1D + 3)=(ULONG)wagalphabet;

    // fixup the calls to index_in_wagalphabet() in transform_prefix()
    *(ULONG *)(transform_prefix0 + 0xD3)=(ULONG)(index_in_wagalphabet - (transform_prefix0 + 0xD3 + 4));
    *(ULONG *)(transform_prefix0 + 0x124)=(ULONG)(index_in_wagalphabet - (transform_prefix0 + 0x124 + 4));
    *(ULONG *)(transform_prefix0 + 0x180)=(ULONG)(index_in_wagalphabet - (transform_prefix0 + 0x180 + 4));
}

//
// this is to emulate the code at 0x00107691
//
INT funky_GCD(BIGNUM * hash, BIGNUM * factor)
{
    INT ret=1;

    // init a context
    BN_CTX * ctx;
    ctx = BN_CTX_new();

    // constants
    BIGNUM *two=0, *three=0, *four=0, *five=0, *eight=0;
    BN_dec2bn(&two, "2");
    BN_dec2bn(&three, "3");
    BN_dec2bn(&four, "4");
    BN_dec2bn(&five, "5");
    BN_dec2bn(&eight, "8");

    BIGNUM calc1, calc2;
    BN_init(&calc1);
    BN_init(&calc2);

    BIGNUM temp1, temp2, temp3;
    BN_init(&temp1);
    BN_init(&temp2);
    BN_init(&temp3);

    BN_copy(&calc1, hash);
    BN_copy(&calc2, factor);

    while(!BN_is_zero(&calc1))
    {
        if(!BN_is_odd(&calc1))
        {
            BN_div(&calc1, &temp1, &calc1, two, ctx); // calc1 = calc1/2
            BN_div(0, &temp2, &calc2, eight, ctx); // temp2 = calc1 %8
            
            if( (BN_cmp(&temp2, three)==0) ||
                (BN_cmp(&temp2, five)==0)   )
            {
                ret=-ret;
            }
        }
        else
        {
            BN_copy(&temp1, &calc1);
            BN_copy(&calc1, &calc2);
            BN_copy(&calc2, &temp1);

            BN_div(0, &temp2, &calc1, four, ctx);   // temp2 = calc1 % 4
            BN_div(0, &temp3, &calc2, four, ctx);   // temp3 = calc2 % 4
            
            if( (BN_cmp(&temp2, three)==0) && 
                (BN_cmp(&temp3, three)==0) )
            {
                ret=-ret;
            }

            BN_div(0, &calc1, &calc1, &calc2, ctx); // calc1 = calc1 % calc2;
        }
    }

    if(calc2.top != 1)
        ret=0;
    else if(*calc2.d!=1)
        ret=0;
    else if(*calc2.d==1)
        if(calc2.neg!=0)
            ret=0;
    
    // free stuff!
    BN_free(two);
    BN_free(three);
    BN_free(four);
    BN_free(five);
    BN_free(eight);
    BN_free(&calc1);
    BN_free(&calc2);
    BN_free(&temp1);
    BN_free(&temp2);
    BN_free(&temp3);

    return ret;
}

void transform_username(char * username, BIGNUM * result)
{
    // temp to play around with
    BIGNUM BN_temp;
    BN_init(&BN_temp);
    BIGNUM BN_temp2;
    BN_init(&BN_temp2);

    // init a context
    BN_CTX * pctx_BN;
    pctx_BN = BN_CTX_new();

    BIGNUM *const1=0, *factor1=0, *factor2=0;
    BN_dec2bn(&factor1, "56314315727265148662503030763343660191795076067");
    BN_dec2bn(&factor2, "57375460067007762984026787123334422029973026987");
    BN_dec2bn(&const1, "3231059773210568767339731308062401168932613017316655150232323931789052315453509684929908820129");

    //
    // take HMAC of username
    //

    ULONG ulen=strlen((char *)username);
    UCHAR buff[256]={0};
    UINT hashLen=0;
    HMAC_CTX ctx;
    HMAC_Init(&ctx, "GAGANONO\0\x01", 10, EVP_ripemd160());
    HMAC_Update(&ctx, (PUCHAR)username, strlen(username));
    HMAC_Final(&ctx, (UCHAR *)buff, &hashLen);
    // for(i=0; i<hashLen; ++i)
    //    printf("%02X ", 0xFF & buff[i]);
    BIGNUM BN_userhash;
    BN_init(&BN_userhash);
    BN_bin2bn(buff, 20, &BN_userhash);
    printf("username HMAC: %s\n", BN_bn2hex(&BN_userhash));

    //
    // get dword transform of username
    //
    PFN_TRANSFORM_USER0 pfn0=(PFN_TRANSFORM_USER0)(void *)transform_user0;
    ULONG uxform1=pfn0((PUCHAR)username, ulen);
    __asm { 
            push eax; 
            mov eax, [uxform1]; 
            bswap eax; 
            mov [uxform1], eax; 
            pop eax; 
            };
    BIGNUM BN_userdword;
    BN_init(&BN_userdword);
    BN_bin2bn((unsigned char *)&uxform1, 4, &BN_userdword);
    printf("username DWORD: %s\n", BN_bn2hex(&BN_userdword));

    //
    // calculate HMAC ^ DWORD % const1
    //
    BIGNUM BN_calc1;
    BN_init(&BN_calc1);
    BN_mod_exp(&BN_calc1, &BN_userhash, &BN_userdword, const1, pctx_BN);
    printf("HMAC ^ DWORD %% const1=%s\n", BN_bn2hex(&BN_calc1));
    printf("in dec: %s\n", BN_bn2dec(&BN_calc1));

    //
    // possibly modify it
    //
    char chlen=strlen(username);
    BIGNUM userlen;
    BN_init(&userlen);
    BN_bin2bn((PUCHAR)&chlen, 1, &userlen);

    printf("The length of the username is %s\n", BN_bn2dec(&userlen));

    while(1)
    {
        if( (funky_GCD(&BN_calc1, factor1) != 1) ||
            (funky_GCD(&BN_calc1, factor2) != 1))
        {
            BN_add(&BN_calc1, &BN_calc1, &userlen);
        }
        else
            break;
    }

    //
    // return result
    //
    BN_copy(result, &BN_calc1);


}
