#include <windows.h>
#include <stdio.h>

BOOL isCheckOk(INT i)
{
    // these are the indices within the table at 004018BB which
    // do NOT have entry 0E, which corresponds to the "skip instruction" for the VM
    if( i==(0x004018BB-0x004018BB) ||
        i==(0x004018D1-0x004018BB) ||
        i==(0x004018E2-0x004018BB) ||
        i==(0x004018F8-0x004018BB) ||
        i==(0x00401903-0x004018BB) ||
        i==(0x00401904-0x004018BB) ||
        i==(0x00401909-0x004018BB) ||
        i==(0x0040191F-0x004018BB) ||
        i==(0x00401930-0x004018BB) ||
        i==(0x00401946-0x004018BB) ||
        i==(0x00401957-0x004018BB) ||
        i==(0x0040196D-0x004018BB) ||
        i==(0x0040197E-0x004018BB) ||
        i==(0x00401994-0x004018BB)
        // valid indices after -0x11: 0x0,0x16,0x27,0x3D,0x48,0x49,0x4E,0x64,0x75,0x8B,0x9C,0xB2,0xC3,0xD9
        // valid indices before -0x11: 0x11,0x27,0x38,0x4E,0x59,0x5A,0x5F,0x75,0x86,0x9C,0xAD,0xC3,0xD4,0xEA
    )
        return 1;
    else
        return 0;
}

void main()
{
    DWORD area[14];

    // gp > for(i=0,127,print1(i^-1%60617,","))
    UINT64 x_inv[128]={0,1,30309,20206,45463,24247,10103,43298,53040,26941,42432,16532,
    35360,32640,21649,28288,26520,24960,43779,25523,21216,54844,8266,55346,17680,53343,
    16320,29186,41133,8361,14144,35197,13260,45922,12480,20783,52198,16383,43070,10880,
    10608,41397,27422,14097,4133,29635,27673,37402,8840,14845,56980,8320,8160,52611,
    14593,51800,50875,48919,34489,27740,7072,17887,47907,38487,6630,6528,22961,37094,
    6240,58860,40700,39273,26099,22420,38500,17781,21535,37000,5440,17648,5304,50140,
    51007,31404,13711,4992,37357,2787,32375,7492,45126,21982,44145,31938,18701,17228,
    4420,53118,37731,35513,28490,57016,4160,40019,4080,47339,56614,19828,37605,37260,
    25900,5461,55746,44524,54768,35316,47553,44038,13870,38204,3536,45588,39252,13799,
    54262,22792,49552,4773};

    for(INT x='!'; x<='~'; ++x)
        for(INT y='!'; y<='~'; ++y)
        {
            UINT64 q = ((UINT64)y * x_inv[x]) % 60617;
            CHAR r[128];
            sprintf(r,"%X",q);

            BOOL ok=1;
            for(INT i=0; i<strlen(r); ++i)
                if(!isdigit(r[i])) {ok=0; break;}
/*
            if(!ok)
                continue;
*/
            INT s=atoi(r);
            memset(area,0,14);
            area[0] = s%100;
            area[1] = (s/100)%100;
   
            INT check1 = area[0]-0x11;
            INT check2 = area[1]-0x11;
            INT check3 = ((area[0]*3 + area[1]*6) & 0xFF) - 0x11;
            //printf("%c%c has checks (%d,%d,0x%02X)\n", x, y, check1, check2, check3);
            //while(1);

            if(isCheckOk(check1) && isCheckOk(check2) && isCheckOk(check3))
                { printf("%c%c works\n", y, x); }

        }

}
