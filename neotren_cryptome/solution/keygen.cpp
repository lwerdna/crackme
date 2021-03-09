#define INFO "keygen to neotren's \"cryptome\" - mar29_2010 andrewl\n"

#include <windows.h>
#include <stdio.h>
extern "C" {
#include <miracl.h>
}

#include <stdio.h>

//-------------------------------------------------------------------------
//
// STRUCTS SHOW KEY FILE STRUCTURE
//
//-------------------------------------------------------------------------
#pragma pack(push, 1)

typedef struct _MESSAGE
{
    CHAR name[65];
    CHAR flags[16];
} MESSAGE, *PMESSAGE;

typedef struct _SIGNEDMESSAGE
{
    CHAR marker[4];
    CHAR e[4];
    CHAR s[7];
    MESSAGE m;
} SIGNEDMESSAGE, *PSIGNEDMESSAGE;

typedef struct _LICENSEFILE
{
    CHAR marker[16];
    CHAR separator[1];
    CHAR signedmessage_encrypted[255]; // RSA_encrypt(SIGNEDMESSAGE)
    CHAR aes_key[128];
} LICENSEFILE, *PLICENSEFILE;

//-------------------------------------------------------------------------
//
// FUNCTIONS
//
//-------------------------------------------------------------------------

VOID printbig(PCHAR label, big b)
{
    CHAR buff[1024];
    INT n = cotstr(b, buff);
    printf("%s = h2d( \\\n", label);
    
    printf("    \"");
    for(INT i=0; i<n; ++i)
    {
        printf("%c", buff[i]);
        if(!((i+1)%64))
            printf("\" \\\n    \"");
    }

    if(n%64)
        printf("\"");

    printf(");\n");
}

#define pb(X) printbig(#X,X);

int main(INT ac, PCHAR *av)
{
    PCHAR name = "neotren";
    CHAR buff[1024];
    INT i, j;

    printf("\n\n%s\n", INFO);

    if(ac > 1)
        name = av[1];
    else
        printf("(you may override default name with command line arg!\n");

    printf("using name: %s\n", name);

    //-------------------------------------------------------------------------
    //
    // INIT MIRACL, IMPORTANT NUMBERS
    //
    //-------------------------------------------------------------------------
    miracl *mip=mirsys(256, 0);

    mip->IOBASE=10;
    big o1 = mirvar(0);
    cinstr(o1, "1014193");
    big o2 = mirvar(0);
    cinstr(o2, "1057282879");
    big o3 = mirvar(0);
    cinstr(o3, "1072288894901647");
    big dlp = mirvar(0);
    cinstr(dlp, "564030902046214");
    big rsa_e = mirvar(0);
    cinstr(rsa_e, "828223770366743458091986315735554352098688768822605387441673443268090509853232621627480891769757450423390643407035547779482786383915746604194881833222979388262668897125975128891195302726010103446004608828234361391092950379019472390978041304452241748698481394573710285395386056382978789936997153233242258428473660895493566362399582475132870988921167897519679370718952200130048226838361310726334291739122144504216583353210418727097258857009675844941328518013227691833850519651938655056315983501288527982697595315550053749884312156239315208524953449349754158187847974767102103192721864805968023445833236031319879873");
    big rsa_p = mirvar(0);
    cinstr(rsa_p, "8659900789654913469567658198567758695469201478039994980815792383316851012380235422437795119658214806214285548366357636127306398351875353150086163499555917446566711669651199392508717287375296894140680819630870474463350581807304309127240007448474255618126328765096444847531784218358908620745278532582719520241");

    mip->IOBASE=16;
    big n = mirvar(0);
    cinstr(n, "021C02B83B55B322BDB134C133894A39DED270A01785F1FE760F0BAEF71783CB5AE67B2208E363B8E60A2B6C0153BA5B8E2B05CBBBBF54F9A7D741D3F337E8052E77379902487E7A9FEFEC17C86AF4917172F92E39434A0258D9E850A454784E8622E579C3B8CF44F47864A745CF086396B4E92A7B0FF8F068FB3A81A3E0725FCEFEB2DA03EF32F1E3B5C4280A2252AF5FB3C8900A5F2DE9EBF669237BBC9080614F1509C979FCAF00CA409A15A239A9748A5C61C96F141E403D02B40961CDA8E62E5EF536F165A1B99AFEA582C3169DBF32B91B903A75DFA315DB95B3F181D4A5992F7ED1572446B091E9EBCACDDD57B6216DA3876671EEFDACB86DFB503F");
    big g = mirvar(0);
    cinstr(g, "017A1EB581E9B0719167D77ABC3542A690B4B7F8A9C6BC5535B658F6AC0577432EB3084B0F07D1D8FD8E98A06BCA6DF9DAA8796D5A40FB09D942ED6E3473A7D9838A8771BB4BA1C4248EC07E36C82963DE3575C5FD95BFBD7F4795DBC4585E3286BA22AD8529F2E59A39B14970D0534B1F576101FEE9BCBCFEB22BC922DF5E7F5150C18FA87E02AF7415838BADD7B992EA58B3D888D520A0E935B5A7379BC19E5749C9E21306E970BA90C66F9D7B76AF322086D154F2E7A612C0A508D74E46DC2BC9429B7D53ABCF839A191474EC0E9141CCDEC4E4A3E2A7E4A961DA8D77C1005969F2257F9A5781BC618A8081B81E36A05C0244A200FD3FD9B96E500DB7F4");
    big y = mirvar(0);
    cinstr(y, "016B2835C93F302F1A281E0FC6C3C270674C5A7E23D3EB08F44E44AF963F1931F2A2EDC636065FAD79763B57F62C4561310AD6ECD703F480517F8609AFA57806CD7743899D7930B00D129A0C048BA4361AF30C93A0653528EBA39DF287477E2BCF12A4FED60558AF4C1397F73D456E46805A96D5FDD389DE12E2E302CC6F3215E26126388191144E014F9539FA78A668CDD44501A6AE84425D9437DEDC773FFA62DEE277CAA2BF448BE97F6961F67F6A63D8B3A764CA00C7A61B036FFA4E4527778D8DBF25FEC02F7C8B36AE1A723B32108A6E3D6CE16890CA1833A21267AA238E52419BB434B839D96424BE8EF9C181E1A405A91B3B86500D7B484B8C1081");
    big f = mirvar(0);
    cinstr(f, "FABF1234");

    irand(GetTickCount());

    //-------------------------------------------------------------------------
    //
    // MAKE MESSAGE
    //
    //-------------------------------------------------------------------------
    MESSAGE m;
    memset(&m, 0, sizeof(m));
    strcpy((PCHAR)&m, name); // don't overflow me!
    strcpy((PCHAR)&(m.flags), "111111111111111");

    //-------------------------------------------------------------------------
    //
    // SIGN MESSAGE
    //
    //-------------------------------------------------------------------------
    // m
    big big_m = mirvar(0);
    bytes_to_big(sizeof(m), (PCHAR)&m, big_m);
    pb(big_m);

    // k random: [0,1072288894901647]
    big k = mirvar(1);
    bigbits(49, k); // roughly 
    pb(k);

    // r = g^k (mod n)
    big r = mirvar(0);
    powmod(g, k, n, r);
    pb(r);

    // e = hash(name || r) % 0xFABF1234
    big e = mirvar(0);
    CHAR digest[20];
    sha context;
    shs_init(&context);
    j = strlen(name);
    for(i=0; i<j; ++i)
        shs_process(&context, name[i]);
    j = big_to_bytes(0, r, buff, 0);
    for(i=0; i<j; ++i)
        shs_process(&context, buff[i]);
    shs_hash(&context, digest);
    bytes_to_big(20, digest, e);
    printbig("bignum(hash(name || r))", e);
    divide(e, f, f);
    pb(e);

    // s = k - dlp*e (mod o3)
    big s = mirvar(0);
    multiply(dlp, e, s);
    subtract(k, s, s);
    //divide(s, o3, o3);
    powmod(s, mirvar(1), o3, s);
    pb(s);

    // fill struct
    SIGNEDMESSAGE sm;
    memset(&sm, 0, sizeof(sm));
    memcpy(&sm.marker, "\x80\xAA\x80\xAA", 4);
    big_to_bytes(sizeof(sm.e), e, sm.e, 1);
    big_to_bytes(sizeof(sm.s), s, sm.s, 1);
    big_to_bytes(sizeof(sm.m), big_m, (PCHAR)&sm.m, 1);

    //-------------------------------------------------------------------------
    //
    // ENCRYPT MESSAGE INTO KEY FILE
    //
    //-------------------------------------------------------------------------
    big ciphertext = mirvar(0);
    bytes_to_big(sizeof(SIGNEDMESSAGE), (PCHAR)&sm, ciphertext);
    powmod(ciphertext, rsa_e, n, ciphertext);
    pb(ciphertext);

    LICENSEFILE lf;
    memset(&lf, 0, sizeof(LICENSEFILE));
    strcpy((PCHAR)&lf.marker, ">Keygenme6  Key<");
    lf.separator[0] = 0xFF;
    big_to_bytes(sizeof(lf.signedmessage_encrypted), ciphertext, lf.signedmessage_encrypted, 1);
    big_to_bytes(sizeof(lf.aes_key), rsa_p, lf.aes_key, 1);

    //-------------------------------------------------------------------------
    //
    // WRITE TO KEY FILE, QUIT
    //
    //-------------------------------------------------------------------------
    FILE *fp = fopen("keyfile.bin", "wb+");
    fwrite((PVOID)&lf, 1, sizeof(LICENSEFILE), fp);
    fclose(fp);

    // done
    //
    printf("tried to write keyfile...check if it's there :)\n");
    printf("ctrl+c to quit!\n");
    while(1);
}

