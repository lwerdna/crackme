// Keygen to MR.HAANDI's "INTERSECTION #1.0"
// March 16, 2010 andrewl
//
// compile/link with:
// cl keygen.cpp /Zi /c /EHsc /Ic:\temp\WinNTL-5_5_2\include
// link keygen.obj /DEBUG c:\temp\WinNTL-5_5_2\src\ntl552.lib advapi32.lib crypt32.lib user32.lib

#include <windows.h>

#include <stdio.h>

#include <string>
#include <iostream>

#define NTL_NO_MIN_MAX
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>

using namespace std;
using namespace NTL;

// macros/defines
#define ERR(A) { printf("ERROR: %s\n",A); goto cleanup; }

// globals
ZZ_pX *m;

//-----------------------------------------------------------------------------------------
//
// HASH/HASH CONVERSION FUNCTIONS
//
//-----------------------------------------------------------------------------------------

BOOL MD5_data(BYTE * pbBuffer, UINT dwBufferLen, PBYTE sr)
{
    BOOL bRet=0;
    HCRYPTPROV hProv=0;
    HCRYPTHASH hHash=0;
    DWORD cbHash=0;

    if(!CryptAcquireContext(&hProv,0,MS_DEF_PROV,PROV_RSA_FULL,0))
        if(!CryptAcquireContext(&hProv,0,MS_DEF_PROV,PROV_RSA_FULL,CRYPT_NEWKEYSET))
            ERR("CryptAcquireContext()");

    if(!CryptCreateHash(hProv,CALG_MD5,0,0,&hHash)) 
        ERR("CryptCreateHash()");

    if(!CryptHashData(hHash,pbBuffer,dwBufferLen,0)) 
        ERR("CryptHashData()");

    cbHash = 20;

    if(!CryptGetHashParam(hHash, HP_HASHVAL, (BYTE *)sr, &cbHash, 0))
        ERR("CryptGetHashParam()");

    bRet=1;
    
    cleanup:

    if(hHash) 
        CryptDestroyHash(hHash);
    if(hProv) 
        CryptReleaseContext(hProv, 0);
            
    return bRet;
}

BOOL MD5_to_ZZ(BYTE * md5, ZZ *out)
{
    string decimal = "";

    for(INT i=0; i<16; ++i)
    {
        BYTE b = md5[i];
        b = b % 10;
        CHAR c = (CHAR)(b + 0x30);
        decimal += c;
    }

    //cout << "decimal: " << decimal << endl;

    *out = to_ZZ(decimal.c_str());

    return 1;
}


//-----------------------------------------------------------------------------------------
//
// ECC POINT OPERATIONS
//
//-----------------------------------------------------------------------------------------

vec_ZZ_pX PointDouble(vec_ZZ_pX P)
{
    vec_ZZ_pX r;
    r.SetLength(4);

	r[0] = (2*P[0]*P[1]*P[2]*P[3]) % *m;
	r[1] = ((P[1]*P[2])*(P[1]*P[2]) + (P[1]*P[3])*(P[1]*P[3]) - (P[2]*P[3])*(P[2]*P[3])) % *m;
	r[2] = ((P[1]*P[2])*(P[1]*P[2]) - (P[1]*P[3])*(P[1]*P[3]) + (P[2]*P[3])*(P[2]*P[3])) % *m;
	r[3] = (-(P[1]*P[2])*(P[1]*P[2]) + (P[1]*P[3])*(P[1]*P[3]) + (P[2]*P[3])*(P[2]*P[3])) % *m;

	return(r);
}

vec_ZZ_pX PointAdd(vec_ZZ_pX P, vec_ZZ_pX Q)
{
    vec_ZZ_pX r;
    r.SetLength(4);

    r[0] = (P[3]*Q[1]*P[0]*Q[2] + P[2]*Q[0]*P[1]*Q[3]) % *m;
    r[1] = (P[3]*Q[1]*P[1]*Q[3] - P[2]*Q[0]*P[0]*Q[2]) % *m;
    r[2] = (P[3]*P[2]*Q[3]*Q[2] - to_ZZ_p(to_ZZ("2951558829"))*P[0]*P[1]*Q[0]*Q[1]) % *m;
    r[3] = ((P[3]*Q[1])*(P[3]*Q[1]) + (P[2]*Q[0])*(P[2]*Q[0])) % *m;

    return(r);
}

vec_ZZ_pX PointMul(vec_ZZ_pX P, ZZ coeff)
{
    vec_ZZ_pX runner = P;

    vec_ZZ_pX result;

    if((coeff % to_ZZ(2)) == to_ZZ(1))
        result = P;
    else 
    {
        result.SetLength(4);
        SetCoeff(result[0], 0, 0);
        SetCoeff(result[1], 0, 1);
        SetCoeff(result[2], 0, 1);
        SetCoeff(result[3], 0, 1);
    }

    coeff >>= 1;


    while(coeff != ZZ::zero())
    {
        runner = PointDouble(runner);

        if((coeff % to_ZZ(2)) == to_ZZ(1))
        {
            result = PointAdd(runner, result);
        }

        coeff >>= 1;
    }

    return result;
}

vec_ZZ_pX PointNormalize(vec_ZZ_pX P)
{
    ZZ_pX tInv = P[3];
    tInv = InvMod(tInv, *m);

    for(INT i=0; i<4; ++i)
        P[i] = (P[i] * tInv) % *m;

    return P;
}

//-----------------------------------------------------------------------------------------
//
// ECC POINT OUTPUT FUNCTIONS
//
//-----------------------------------------------------------------------------------------

VOID PrintPoly(ZZ_pX p)
{
    for(INT i=deg(p); i>=0; --i) 
    {
        if(i<deg(p))
            cout << " + ";

        cout << coeff(p, i);

        if(i>0)
        {
            cout << "*x";

            if(i>1)
                cout << "^" << i;
        }
    }
    cout << endl;
}


VOID PrintPoint(string msg, vec_ZZ_pX P)
{
    // 4-coord output
    cout << msg << ":\n";
    for(INT i=0; i<4; ++i)
        PrintPoly(P[i]);

    // 3-coord normalized output
    cout << "--(normalized:)--\n";

    P = PointNormalize(P);
    for(INT i=0; i<3; ++i)
        PrintPoly(P[i]);

    cout << endl;
}

//-----------------------------------------------------------------------------------------
//
// POLYNOMIAL SOLVING FUNCTIONS
//
//-----------------------------------------------------------------------------------------

BOOL SolveCubic(ZZ_pX cubic, ZZ_p *root)
{
    BOOL fRet = 0;

    vec_pair_ZZ_pX_long factors;

    CanZass(factors, cubic);

    for(INT i=0; i<factors.length(); ++i)
    {
        // some vec_pair_ZZ_pX
        // .a = [34 0 0] is ZZ_pX polynomial factor
        // .b = is long degree
        if(deg(factors[i].a) == 1)
        {
            // if (X - k) is a factor, k is a root
            *root = coeff(factors[i].a, 0);
            *root *= to_ZZ_p(to_ZZ(-1));
            fRet = 1;
            break;
        }
    }

    return fRet;
}

//-----------------------------------------------------------------------------------------
//
// MAIN LOGIC
//
//-----------------------------------------------------------------------------------------

int main(int argc, char * argv[])
{
    // decide on name
    //
    PCHAR name = "MR.HAANDI";
    if(argc>1)
        name = argv[1];
    printf("using name: %s\n", name);
    printf("(supply argument to change name)\n");

    // initialize extension field modulus as global
    // m = (+0401877261*x^0 +0319151251*x^1 +1522639780*x^2 +0373083325*x^3 +0135070006*x^4 +2072661367*x^5 +0000000001*x^6 ) * Mod(1,p);
    //
    ZZ_p::init(to_ZZ("4294967291"));

    m = new ZZ_pX(6,1);
    SetCoeff(*m, 0, to_ZZ_p(to_ZZ("401877261")));
    SetCoeff(*m, 1, to_ZZ_p(to_ZZ("319151251")));
    SetCoeff(*m, 2, to_ZZ_p(to_ZZ("1522639780")));
    SetCoeff(*m, 3, to_ZZ_p(to_ZZ("373083325")));
    SetCoeff(*m, 4, to_ZZ_p(to_ZZ("135070006")));
    SetCoeff(*m, 5, to_ZZ_p(to_ZZ("2072661367")));

    cout << "m: " << m << "\n\n";

    // initialize the extension field elements
    //
    vec_ZZ_pX PointA;
    PointA.SetLength(4);
    ZZ_pX temp(5,1);
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("2447134460")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("871167555")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("338177802")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("370371326")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("3152113581")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("2218130420")));
    PointA[0] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("970958055")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("1661846692")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("2615174668")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("2687502417")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("2539672687")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("2585604584")));
    PointA[1] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("2090499100")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("3586500530")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("534184351")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("2169583335")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("3452718476")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("4090110644")));
    PointA[2] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("1672623231")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("1924900927")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("2628290729")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("1426685279")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("3777830547")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("1900306940")));
    PointA[3] = temp;

    PrintPoint("PointA", PointA);
    printf("\n");

    vec_ZZ_pX PointB;
    PointB.SetLength(4);
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("2943798197")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("843145904")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("3020622304")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("3097671584")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("2515596009")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("3326296572")));
    PointB[0] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("4077598163")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("698704803")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("4259079522")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("3473322830")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("1492737774")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("2314264621")));
    PointB[1] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("326530814")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("1927248595")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("302635456")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("1656396964")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("3392538410")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("412491626")));
    PointB[2] = temp;
    SetCoeff(temp, 5, to_ZZ_p(to_ZZ("577721219")));
    SetCoeff(temp, 4, to_ZZ_p(to_ZZ("3979886956")));
    SetCoeff(temp, 3, to_ZZ_p(to_ZZ("3905696031")));
    SetCoeff(temp, 2, to_ZZ_p(to_ZZ("3091627353")));
    SetCoeff(temp, 1, to_ZZ_p(to_ZZ("1583157487")));
    SetCoeff(temp, 0, to_ZZ_p(to_ZZ("3853647145")));
    PointB[3] = temp;

    PrintPoint("PointB", PointA);
    printf("\n");
   
    // get ZZ(MD5(name)) * PointA
    //
    BYTE digest[16];
    if(!MD5_data((PBYTE)name, strlen(name), digest))
        return 0;

    printf("MD5(name): ");
    for(INT i=0; i<16; ++i)
        printf("%02X",digest[i]);
    printf("\n\n");

    ZZ zzMd5Name;
    MD5_to_ZZ(digest, &zzMd5Name);
    cout << "ZZ(MD5(name)): " << zzMd5Name << endl << endl;

    vec_ZZ_pX PointTemp = PointMul(PointA, zzMd5Name);
    PrintPoint("ZZ(MD5(name)) * PointA", PointTemp);
    printf("\n");

    // second coefficient comes from some hashing of the coefficients
    // of the normalized result, careful....
    PointTemp = PointNormalize(PointTemp);

    UINT buff[18];
    for(INT i=0; i<3; ++i)
        for(INT j=0; j<6; ++j)
            buff[6*i + j] = to_uint(rep(coeff(PointTemp[i],j)));

    printf("hash input:\n");
    for(INT i=0; i<18; ++i)
    {
        printf("%08X ", buff[i]);
        if(!((i+1)%4))
            printf("\n");
    }
    printf("\n");

    BYTE digest2[16];
    MD5_data((PBYTE)buff, 18*sizeof(UINT), digest2);
    printf("MD5(ZZ(MD5(name)) * PointA): ");
    for(INT i=0; i<16; ++i)
        printf("%02X", digest2[i]);
    printf("\n");

    MD5_data(digest2, 16, digest);
    printf("MD5(MD5(ZZ(MD5(name)) * PointA)): ");
    for(INT i=0; i<16; ++i)
        printf("%02X", digest[i]);
    printf("\n");

    ZZ zzMd5PointA;
    MD5_to_ZZ(digest, &zzMd5PointA);
    cout << "ZZ(MD5(MD5(ZZ(MD5(name)) * PointA))): " << zzMd5PointA << endl;
    printf("\n");

    // now, we have this situation:
    //
    // serial^3 * PointA + zzMd5PointA * PointB = zzMd5Name * PointA
    //
    // we know k, where B = A*k (from having solved the DLP), so equation is now:
    // 
    // serial^3 * PointA + zzMd5PointA * k * PointA = zzMd5Name * PointA
    //
    // and thus:
    //
    // serial^3 + zzMd5PointA * k = zzMd5Name (mod order(curve))
    //
    // thus the final keygenning step is solving this cubic!

    /* fail :( "ZZ_p: division by non-invertible element"
    ZZ order = to_ZZ("6277101691541631771514589274364601047755112573811991434000");
    ZZ k = to_ZZ("5352592015460708129232383406001784565224127295383978899153");
    ZZ_p::init(order);
    ZZ_pX cubic(3,1);
    SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
    ZZ_p root;
    FindRoot(root, cubic);
    */
    ZZ order_curve = to_ZZ("6277101691541631771514589274364601047755112573811991434000");
    ZZ order_subgroup = to_ZZ("1073750771");
    ZZ dlp = to_ZZ("314159265");

    ZZ_pX cubic(3,1);

    ZZ_p root16, root125, root43, root349, root619, root1453, root13877, root161911, root224671873, root1073750771, root428997622167797533;
  
    for(INT i=0; 1; ++i)
    {
        ZZ k = dlp + to_ZZ(i) * order_subgroup;

        if(!(i%65536))
        {
            printf("on solve try %d\n", i);
            cout << "k: " << k << endl;
        }

        // brute root 16
        ZZ_p::init(to_ZZ("16"));
        for(LONG i=0; i<16; ++i)
        {
            root16 = to_ZZ_p(to_ZZ(i));
            if(root16 * root16 * root16 + to_ZZ_p(zzMd5PointA) * to_ZZ_p(k) == to_ZZ_p(zzMd5Name))
                break;
        }
        //cout << "root (mod 16) is: " << root16 << endl;

        // brute root 125
        ZZ_p::init(to_ZZ("125"));
        for(LONG i=0; i<125; ++i)
        {
            root125 = to_ZZ_p(to_ZZ(i));
            if(root125 * root125 * root125 + to_ZZ_p(zzMd5PointA) * to_ZZ_p(k) == to_ZZ_p(zzMd5Name))
                break;
        }
        //cout << "root (mod 125) is: " << root125 << endl;

        ZZ_p::init(to_ZZ(43));
        //SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        SetCoeff(cubic, 0, to_ZZ_p(to_ZZ(16)));
        vec_pair_ZZ_pX_long factors;
        if(!SolveCubic(cubic, &root43)) continue;
        //cout << "root (mod 43) is: " << root43 << endl;

        ZZ_p::init(to_ZZ(349));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root349)) continue;
        //cout << "root (mod 349) is: " << root349 << endl;

        ZZ_p::init(to_ZZ("619"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root619)) continue;
        //cout << "root (mod 619) is: " << root619 << endl;

        ZZ_p::init(to_ZZ("1453"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root1453)) continue;
        //cout << "root (mod 1453) is: " << root1453 << endl;

        ZZ_p::init(to_ZZ("13877"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root13877)) continue;
        //cout << "root (mod 13877) is: " << root13877 << endl;

        ZZ_p::init(to_ZZ("161911"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root161911)) continue;
        //cout << "root (mod 161911) is: " << root161911 << endl;

        ZZ_p::init(to_ZZ("224671873"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root224671873)) continue;
        //cout << "root (mod 224671873) is: " << root224671873 << endl;

        ZZ_p::init(to_ZZ("1073750771"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root1073750771)) continue;
        //cout << "root (mod 1073750771) is: " << root1073750771 << endl;

        ZZ_p::init(to_ZZ("428997622167797533"));
        SetCoeff(cubic, 0, to_ZZ_p(zzMd5PointA * k - zzMd5Name));
        if(!SolveCubic(cubic, &root428997622167797533)) continue;
        //cout << "root (mod 428997622167797533) is: " << root428997622167797533 << endl;
        
        break;
    }

    // now combine the results using the CRT
    printf("combining results....\n");
    ZZ root = to_ZZ(0);
    ZZ mod = to_ZZ(1);
    CRT(root, mod, rep(root16), to_ZZ(16));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root125), to_ZZ(125));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root43), to_ZZ(43));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root349), to_ZZ(349));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root619), to_ZZ(619));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root1453), to_ZZ(1453));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root13877), to_ZZ(13877));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root161911), to_ZZ(161911));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root224671873), to_ZZ("224671873"));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root1073750771), to_ZZ("1073750771"));
    cout << "root:" << root << " mod:" << mod << endl;
    CRT(root, mod, rep(root428997622167797533), to_ZZ("428997622167797533"));
    cout << "root:" << root << " mod:" << mod << endl; // this last mod should be the total group order

    if(root < ZZ::zero())
        root = root + order_curve;

    // encode serial
    string serial = "";
    PCHAR lookup = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx";

    while(root != ZZ::zero())
    {
        ZZ r = root % to_ZZ(60);
        serial = string(lookup+to_int(r), 1) + serial;
        root = root / to_ZZ(60);
    }
   
    cout << endl << endl;
    cout << "-----------------------------------------------------\n";
    cout << "  name: " << name << endl;
    cout << "serial: " << serial << endl;
    cout << "-----------------------------------------------------\n";
    cout << endl;
    
    printf("ctrL+c to quit!!\n");
    while(1);

    cleanup:
    return 0;
}

