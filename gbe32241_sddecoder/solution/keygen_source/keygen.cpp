#define INFO    "KEYGEN for SDDecoder - Jan13_2010 andrewl\n\n" \
                "Thanks and love to my family for enduring this obsession...\n\n" \
                "Some keys do not have solutions! Solutions may take a while!\n" \
                "Best bet is to run a few of these until one finishes!\n"

#include <windows.h>
#include <stdio.h>

#include "bitvects.h"
#include "random.h"
#include "gf2.h"

#include "fevaluate.h"

VOID GetComponents(BitBasis *all_bases, Vect x, Vect *c1, Vect *c2, Vect *c3, Vect *c4, Vect *c5, Vect *c6, Vect *c7, Vect *c8)
{

    Vect temp;

    /*
    static Vect basis1_mask(0xFFFE000000000000, 0x0000000000000000);
    static Vect basis2_mask(0x0001FFFC00000000, 0x0000000000000000);
    static Vect basis3_mask(0x00000003FFF80000, 0x0000000000000000);
    static Vect basis4_mask(0x000000000007FFF0, 0x0000000000000000);
    static Vect basis5_mask(0x000000000000000F, 0xFFE0000000000000);
    static Vect basis6_mask(0x0000000000000000, 0x001FFFC000000000);
    static Vect basis7_mask(0x0000000000000000, 0x0000003FFF800000);
    static Vect basis8_mask(0x0000000000000000, 0x00000000007FFF00);
    */

    static Vect basis1_mask(0xFFFC000000000000, 0x0000000000000000); // 14
    static Vect basis2_mask(0x0003FFF800000000, 0x0000000000000000); // 15
    static Vect basis3_mask(0x00000007FFF00000, 0x0000000000000000);
    static Vect basis4_mask(0x00000000000FFFE0, 0x0000000000000000);
    static Vect basis5_mask(0x000000000000001F, 0xFFC0000000000000);
    static Vect basis6_mask(0x0000000000000000, 0x003FFF8000000000);
    static Vect basis7_mask(0x0000000000000000, 0x0000007FFF000000);
    static Vect basis8_mask(0x0000000000000000, 0x0000000000FFFF00); // 16

    temp = all_bases->SolveRowsFor(x);

    Vect component_1_rows = temp & basis1_mask;
    //component_1_rows.Print("component_1_rows");
    Vect component_2_rows = temp & basis2_mask;
    //component_2_rows.Print("component_2_rows");
    Vect component_3_rows = temp & basis3_mask;
    //component_3_rows.Print("component_3_rows");
    Vect component_4_rows = temp & basis4_mask;
    //component_4_rows.Print("component_4_rows");
    Vect component_5_rows = temp & basis5_mask;
    //component_5_rows.Print("component_5_rows");
    Vect component_6_rows = temp & basis6_mask;
    //component_6_rows.Print("component_6_rows");
    Vect component_7_rows = temp & basis7_mask;
    //component_7_rows.Print("component_7_rows");
    Vect component_8_rows = temp & basis8_mask;
    //component_8_rows.Print("component_8_rows");

    *c1 = all_bases->ChooseRows(component_1_rows);
    *c2 = all_bases->ChooseRows(component_2_rows);
    *c3 = all_bases->ChooseRows(component_3_rows);
    *c4 = all_bases->ChooseRows(component_4_rows);
    *c5 = all_bases->ChooseRows(component_5_rows);
    *c6 = all_bases->ChooseRows(component_6_rows);
    *c7 = all_bases->ChooseRows(component_7_rows);
    *c8 = all_bases->ChooseRows(component_8_rows);
}

INT main(INT ac, PCHAR *av)
{
    // private info from attack goes here!
    UINT64 bb_QRRRRRRR_vects[32] = { // dimension: 16
        0x5A5DFEF18E402B60, 0x84A0F9E1B1767289,
        0x9B4266BE34839610, 0x53496DD0CD808F70,
        0x1301C2A0CE4C1076, 0x3BC9C4A0308215C0,
        0x0AD3A25248E42CF4, 0x22812275776D3967,
        0x24B8B2029A9F6D3B, 0x4022FB985C962C39,
        0x01AF267F50332AB7, 0x4AF24586B0FAD76D,
        0x023E8D2D4D67F3C8, 0x0B0F9E03ED3328CF,
        0x008639F60BCBD436, 0x77BF4D084CF52E93,
        0x046AC796EFF318A3, 0x47248B48D849B060,
        0x00573A95C10A0F7A, 0x2ED838BC7B1742BA,
        0x003EE088DEF05621, 0xF3165DD80C257747,
        0x001CC1227D85D476, 0x16EE3B63743EC771,
        0x000D7F2ED6751AAA, 0x28D4211E45AD4582,
        0x0005A533D253B244, 0x4D1303831EC951AF,
        0x000112FCA3EC5429, 0x3F4DEA8183245A45,
        0x0002BD9FCC099323, 0x147DF25EE4495C6E,
    };
    BitBasis bb_QRRRRRRR;
    bb_QRRRRRRR.AddN(bb_QRRRRRRR_vects, 16);

    UINT64 bb_0QRRRRRR_vects[32] = { // dimension: 16
        0x49EC74F409231673, 0xAFD6E8B045527FA8,
        0xBBDC722112F5D3AC, 0xE09835929C8AE86C,
        0x19ADC0EA5A9228DD, 0xD547B9FD8E3736CC,
        0x290E1010BC3588B4, 0xBFF3B4FE4349E334,
        0x03E731DA78749CC0, 0xE8C954D41597C90A,
        0x00897E3F7A02AD80, 0xAA6E733320981FA6,
        0x0175B40BC78947F2, 0x58F4B385F7DE3977,
        0x0875ABEE1EF0D629, 0x3D208B0404B2ACC4,
        0x040C28F41A4412EB, 0x3E9486B507E0EA0A,
        0x006EF7E5FE0A72D7, 0xDA4E7D159A24D12F,
        0x00182DE6F05792B9, 0x2532898B55C903E5,
        0x000AFD90992492AA, 0xA4494E40B393F7E7,
        0x000587EE11A5231A, 0x551A73685E805B97,
        0x00031986CCB084F4, 0x95AAD6C1EB7F562F,
        0x0020E29324B96D73, 0xE433B4AE8719D4A8,
        0x0001F9DC84F0CF99, 0xD5E7107D1FE7690B,
    };
    BitBasis bb_0QRRRRRR;
    bb_0QRRRRRR.AddN(bb_0QRRRRRR_vects, 16);

    UINT64 bb_00QRRRRR_vects[32] = { // dimension: 16
        0x5F71E39BC34E7BAE, 0x99E23A70A386B4AA,
        0x82A7C9FA8E4ECC3F, 0xE7CC20A27207231B,
        0x3D210CE452CA417F, 0x5F52F34150ED9206,
        0x188B21860E17E2B8, 0xD30E02CDCF66CDAA,
        0x06CDAF146635487F, 0xD1212B988735A56E,
        0x01B1517B06130D3C, 0xA18770637A71560B,
        0x0AFE96930E680D53, 0x843D6B0CBDCB86B9,
        0x008E836A14CA01E7, 0x2FD88D807FDB2617,
        0x0046CA6503B6EBDA, 0x06910CC733389FFC,
        0x02354F12638E6296, 0x6AF133B632A90A63,
        0x0013088B57F208CF, 0xCF3FAF881CB37830,
        0x0028352FD324AC08, 0xF72E5D886FEDB98D,
        0x0001A75DD7F9DF00, 0x618330A79499195B,
        0x000EE440681F60AD, 0xB498943B4C5C623E,
        0x0000D12203A62013, 0x543B82909088D96C,
        0x00001341B7BC10D1, 0x9A4EAA1DFAFD01C9,
    };
    BitBasis bb_00QRRRRR;
    bb_00QRRRRR.AddN(bb_00QRRRRR_vects, 16);

    UINT64 bb_000QRRRR_vects[32] = { // dimension: 16
        0xFC6EA34411EF4905, 0x8D110D0F6105A0A4,
        0x317ABF897A4F5B1C, 0xCD7B05406DDC9B93,
        0x0442CD620C835ED4, 0xFE2E8CBA4DBD09D9,
        0x53985B32BC4F5D68, 0x4810F10C35A34849,
        0x03668E5CD389CF71, 0xEF6AB4CF9FE3568A,
        0x0867C0658734E9A3, 0x6FA6109D948D0193,
        0x1132834242A8D7B3, 0xB4CA7A7B2BA70109,
        0x01E03E5910D1F4C1, 0x18EE66D5A30F5D3F,
        0x008830DBF68EA9E4, 0xF081224F093BEC1B,
        0x007D1C44E95CF720, 0x698D8C08C33CBE69,
        0x001D1D4D2D730670, 0xA96BB4A11E619CA2,
        0x002A48F7560F691F, 0x8CBF84DFF5CE6097,
        0x000DDD44C501325D, 0x910F2F63D13BFBFE,
        0x0007070352A1CA50, 0x19D2937AC05D5018,
        0x00000B40732F65A6, 0x18C99A6DCDB65874,
        0x0001A181BDD1C41E, 0x2C6C17C7D0160E74,
    };
    BitBasis bb_000QRRRR;
    bb_000QRRRR.AddN(bb_000QRRRR_vects, 16);

    UINT64 bb_0000QRRR_vects[32] = { // dimension: 16
        0x44AC9207B5D310C2, 0x7F7217D6F79136F0,
        0x0AC5EC288BF868CC, 0xAA4CE79B198A14EB,
        0x2489A2C7DDE3CAA5, 0xC59750051F12442D,
        0x0542FD10921B6F2B, 0x901719A6AAA6803D,
        0x9260655B7892D7C9, 0xCBC06B6CB6A2EDBB,
        0x108B7143E09462BD, 0xA3F158313199A484,
        0x01D6828CF29CD181, 0x4E67DF99E92A194E,
        0x027E9C00D6F8EE52, 0x169DB84FC0222DAF,
        0x00AD9E852C16F5CA, 0x8E012CCB07477588,
        0x0071D9C11B4AA819, 0xD3D0580311C0E580,
        0x003A9AAF927105AB, 0xA28A32BED7E64F5D,
        0x0007ADDF3C1358EB, 0xDE66D1EE56B54902,
        0x0013C6C1A865EC3D, 0xB5F8AB5C4B33827F,
        0x0003CCD260C60018, 0x94ED968F003C1C43,
        0x0008CEEFB013045C, 0x976BD2FA0A1E9454,
        0x00007A7B1533CAAE, 0xC823319485D85CD4,
    };
    BitBasis bb_0000QRRR;
    bb_0000QRRR.AddN(bb_0000QRRR_vects, 16);

    UINT64 bb_00000QRR_vects[32] = { // dimension: 16
        0x43DDF036FA2B1BF0, 0x9F9AF52F109BBDEB,
        0x0A88C73B418FD44A, 0x93C435361DD97310,
        0x2734A0492088A58B, 0x7BA36D3D80C15C99,
        0x0481E404EAF75CC3, 0xFE909B074B4D4F46,
        0x923675A131F75E5A, 0xB688EEFC893623D2,
        0x12FC6AD8FA9E6F19, 0x73C24D6A19F60205,
        0x0122BA5C9DB446CC, 0xD7AB6D3CF1F73AF6,
        0x00C55852F93725F1, 0x83DF2B3BF0C514F0,
        0x005284608918EEF7, 0x2D3AA428B45B1516,
        0x0029F4B84D06A2D5, 0x42A4BEADD186FAFA,
        0x0000D46117F56009, 0x6CB3C12D3E46513F,
        0x00165318C346CD46, 0x9687CA9076956C10,
        0x020E6A1A71A64705, 0x6611206F17B0E0C1,
        0x000D1242DAB102A2, 0x0B5692CC341F323A,
        0x00016EEE19D831AA, 0x0FBA3A9AF6D1BC9A,
        0x0006130778290B8A, 0xCB755218C26D9D53,
    };
    BitBasis bb_00000QRR;
    bb_00000QRR.AddN(bb_00000QRR_vects, 16);

    UINT64 bb_000000QR_vects[32] = { // dimension: 16
        0x60C8C1C6AFBF5305, 0xC20E4E052FF5B6F7,
        0x11A312FD9E46FB0B, 0x74F19785102F33D5,
        0xA0D4E183247F8FDA, 0x6DD3A73ED9EA4399,
        0x014CED73D3631BFD, 0xABAD047A76DBB83B,
        0x26E8F881894EC525, 0x956C607E7B29C328,
        0x02F80C84C430BBC7, 0x882CB77BF2E2676D,
        0x0CE54796FF2F7772, 0x96B93FD7922D2D7C,
        0x04CDC0B9BE92071D, 0xBC35DC5F351E6B4C,
        0x001547B4C1DEB106, 0xF32D69B815347756,
        0x0006BA900645C0D0, 0x8FC1D7A070A71CF4,
        0x0082F2D45605CA2C, 0xCFF1A6439D42110E,
        0x002A53121EA05A6B, 0x377A5DFFEDB56C35,
        0x0043AFEA6BC46470, 0x6E313C652C4ECCB6,
        0x0003B3727947A69B, 0x95B30D410D9DC483,
        0x00013FA9275569ED, 0x3DF03E82D13502C9,
        0x000883FC3B4849E2, 0x81309C4BDAC0CFEB,
    };
    BitBasis bb_000000QR;
    bb_000000QR.AddN(bb_000000QR_vects, 16);

    UINT64 bb_0000000Q_vects[32] = { // dimension: 16
        0x237F63681532ABF1, 0x107B2152AFECDD5B,
        0x16F7A42CFA0694F5, 0x27B94B6ABD0C3FEB,
        0x0EB952B705A77B2A, 0x65BA1C46ECE5EFE3,
        0x0376AE4B183E2B58, 0x245AF54C0DE0C31F,
        0x81F08A810F811B73, 0x6EF29B46DC27CD81,
        0x4578BBCBF31B8AAB, 0x68828A29F2A436B7,
        0x04F38EFD67EE9A3C, 0x9700116285F239B9,
        0x010A3A88581853DF, 0xBF9BBA53EEF2CC1B,
        0x002910A97C9217B2, 0x32DE08182DFF4C37,
        0x0048873F8A3824E0, 0xF565AEF619649327,
        0x001295F33E2590E5, 0x8BE6856DAF9B6A44,
        0x00879F65226E7325, 0xC80DC017985195B1,
        0x000FF5F8FB7EFE9D, 0xA92133F473EC42A1,
        0x000080677CD125D0, 0xADE627162B7780B3,
        0x00057EB3F2933C1F, 0x9013C49DE2D9EEF4,
        0x00033E9C6F01E51A, 0x81681B047D9C4CB3,
    };
    BitBasis bb_0000000Q;
    bb_0000000Q.AddN(bb_0000000Q_vects, 16);

    UINT64 bb_final_QRRRRRRR_vects[28] = { // dimension: 14
        0x00AEF8B4430CB1AD, 0x85BBE71C2CE78C2B,
        0x005B4D5992DF990E, 0x83F4509C8E7C483E,
        0x001E6C77E28B57BD, 0xF53F0C1B2280A167,
        0x00226762828D6817, 0xB4FF2C5FA4EC6B44,
        0x000BC18731DD7D30, 0xF186A70448DDE85C,
        0x000175E30D625E24, 0x10368D7A2401DA09,
        0x0006320F80096D01, 0x091006A4017A407B,
        0x00027A9338E6600D, 0xEF1BDA724C73863D,
        0x00004203D2957043, 0xB348CD277F0E2996,
        0x00002C58DAE8CB4E, 0x85D59A55650B6640,
        0x00001ACA69F298F7, 0x71A855DED2EFD313,
        0x00000753A3A91059, 0xD1B4A6575F24B824,
        0x00000A7A66176C6B, 0x96C96D4D6612C5FF,
        0x000003CC70CE8286, 0x0702E2301C588A82,
    };
    BitBasis bb_final_QRRRRRRR;
    bb_final_QRRRRRRR.AddN(bb_final_QRRRRRRR_vects, 14);

    UINT64 bb_final_0QRRRRRR_vects[30] = { // dimension: 15
        0x00CEB16C4A6B0A28, 0xF4127629F80CEA11,
        0x002D18DEE1F898C1, 0xAA22F2747D1AFEEB,
        0x00182BFAC53B0FA7, 0xD67B6176C5F68BB6,
        0x00464BE1BE8CB914, 0xEFD0D70812306C21,
        0x000E07031BB866D0, 0xA53C8F4AACD46B8D,
        0x0002C9274C4B2CD6, 0x6FE636099DCFF9B3,
        0x00008C131E81494E, 0x05F1AACCA390011E,
        0x00006F5162F07574, 0x31A5B9CE9F5DC7CF,
        0x00011F988ABAB30C, 0x3C6EEE8A0F919639,
        0x000401FCF901046C, 0x5549E4FAE933694B,
        0x00000B3996AD4EE6, 0xB8299F76835FFD61,
        0x00001124D4D91209, 0x73AEF9350D0F7DD5,
        0x0000007262DCDADA, 0x255994DF80D50DBC,
        0x000000326D5550F7, 0xC039862DB090797C,
        0x0000028E77D64B17, 0xF5A25E057146F421,
    };
    BitBasis bb_final_0QRRRRRR;
    bb_final_0QRRRRRR.AddN(bb_final_0QRRRRRR_vects, 15);

    UINT64 bb_final_00QRRRRR_vects[30] = { // dimension: 15
        0x0098D3B8D2FA9813, 0x039BB794527BBF03,
        0x0047208E1BFEBADF, 0x986CF0E00C4D47E8,
        0x0029EB0EDA10B3DD, 0xB3FFD50F673CD7AB,
        0x00063DBDDF8C7543, 0x69F5DCBAE3002933,
        0x000372B644E7E602, 0x3D23EFCBD68CCB1D,
        0x0018D56A766DAC97, 0xA3CF2A9D0B63FD8D,
        0x0001627E5CAF0806, 0x3B73B33547E7528B,
        0x0000EEC6E4758B47, 0x19AC6186320EE63C,
        0x00087FA862A97179, 0xA601E6F3C496C3DD,
        0x00002256E0A9AFEC, 0x7304E815C5A367A2,
        0x000056E89EEEE756, 0xFA335B8AF168797F,
        0x000016F860B871E0, 0x68F3BC5F12950D78,
        0x000005BF7CDEC2B4, 0xE931C36D60D5D09F,
        0x00000BB6D3AC3A1B, 0x6C6AAB43441C5AB8,
        0x00000222C6322906, 0xD80852BA404076C4,
    };
    BitBasis bb_final_00QRRRRR;
    bb_final_00QRRRRR.AddN(bb_final_00QRRRRR_vects, 15);

    UINT64 bb_final_000QRRRR_vects[30] = { // dimension: 15
        0x009F756107886185, 0x54691808F7F885F8,
        0x005B79C2207ECAAF, 0x52DC32CA6C5DCFD5,
        0x00186EB02C449C0C, 0x3C0F38B1754C57A8,
        0x0002D6A7E22601B7, 0x388E0471A38D5C39,
        0x0008C503B2BADA74, 0x723F9EF8C39059C9,
        0x002135743C89A4D3, 0xA4148E54A059CCCA,
        0x0005DAF8D3041F8B, 0x6D965571779AA667,
        0x0000C6A251C8E36E, 0x58537D037D6717FD,
        0x00006BFC6AAD43A2, 0xAE86EECC3BA806D0,
        0x00002CA91549E146, 0xD71F5DF0EBF5631F,
        0x00000E63C2BA6017, 0x1407087B54D6F1C8,
        0x000114426161B5A6, 0x4AA7D89207956D08,
        0x000006D45C5791EC, 0xC9A5EE39639FB652,
        0x000003BD0E7CEC4F, 0xEC47691AB594445C,
        0x000000DE2C379D4C, 0x84B9F395E5DECD6B,
    };
    BitBasis bb_final_000QRRRR;
    bb_final_000QRRRR.AddN(bb_final_000QRRRR_vects, 15);

    UINT64 bb_final_0000QRRR_vects[30] = { // dimension: 15
        0x00BEF4F31A621DBD, 0x9701B70212FC2662,
        0x003D6EC91812EA78, 0xF03B7811D27247A9,
        0x00596CD2EC063A6A, 0xEC98524233F47368,
        0x000E4B917C039B76, 0xF1F4B75F0A4CD8ED,
        0x00039304641BBFFF, 0x602D099F7E7A3724,
        0x0014D999866BF8D0, 0xB61F0F7C17655672,
        0x0000FA5BD52020D0, 0x5B245CD6384B0500,
        0x00013F75BC8CD0C7, 0x1845103A5CC512CB,
        0x000034755E4B8C24, 0x863DE06841C720F3,
        0x00044C3CB8894E59, 0x353146FEDC58ABE0,
        0x000046521AC9728B, 0x69EB71E4F6D61ACF,
        0x0000190814644396, 0xA018D04AC06B43E0,
        0x0000038E332EF12D, 0x36DD0C23DAFB0CE3,
        0x00000170E2AEACF5, 0xBC348E7CB1BC2EC1,
        0x000008006ED7BC8D, 0x2F0BFC5EBF4B6524,
    };
    BitBasis bb_final_0000QRRR;
    bb_final_0000QRRR.AddN(bb_final_0000QRRR_vects, 15);

    UINT64 bb_final_00000QRR_vects[30] = { // dimension: 15
        0x00F7F8813B8E1BAB, 0x6D44B2720A0E981E,
        0x001A929EA7FD821F, 0xD050FDA1DCFE4388,
        0x0000AF78DE513697, 0x4CAB51999701EA06,
        0x002F4088F03782B8, 0x300C3C046F8C74E1,
        0x00022F61F6338A4C, 0xF861F9F38F87E50A,
        0x000D6D90A6E8EF7B, 0xF8E08E34344D9A63,
        0x00053670B1EDE34F, 0xD6D5E964EC59BAE7,
        0x00407AF54531562A, 0x8AF2D6304DEAD5A8,
        0x00006EEBF278F53F, 0x453C6558A202DCCF,
        0x000000497CC48A18, 0xDFEAEA6AA7F973D2,
        0x000023B50E567A73, 0xC082D851CBF4EE99,
        0x00010D1198072AC8, 0xEFC41E0EF4BFE67E,
        0x0000021944AE2B91, 0x168EE081191BDB4A,
        0x0000009CB0B9FD70, 0xEC73C1DD2566DC62,
        0x0000000E37D28710, 0x3C1EFD3601CFD3C9,
    };
    BitBasis bb_final_00000QRR;
    bb_final_00000QRR.AddN(bb_final_00000QRR_vects, 15);

    UINT64 bb_final_000000QR_vects[30] = { // dimension: 15
        0x0005265FC7721D09, 0x3FDE34CC467F06F3,
        0x00F862156AB23F15, 0x501E7A9772994DB7,
        0x0072A04B10F61620, 0x84C09CDFA5C926F2,
        0x0038C5787E381F62, 0x7589A35DB3FC1163,
        0x0000FF3B8C28DFCD, 0x5935D1DC75393CDB,
        0x001B078E4B6A6C3D, 0xF0464E4DC2C9E97C,
        0x000A6077DCBB7140, 0x6A0D00DCBF7EF085,
        0x000045BE0D230891, 0xC478AF3A02EC9D24,
        0x00030C83C61DE29A, 0x58A2B01E8579673E,
        0x00001628B6872B56, 0xE28DF246B145CA20,
        0x00012EF00EA7A1CD, 0x89FCEC9A7A985B2A,
        0x000006548718AD3F, 0xAACE74C461A68F52,
        0x000029EE45ED06E4, 0xE6F8EA753A5431C2,
        0x000002A5D738213C, 0x66131557CDAF5C6F,
        0x000000C0F605F962, 0xC28D1FE1CFD82BD2,
    };
    BitBasis bb_final_000000QR;
    bb_final_000000QR.AddN(bb_final_000000QR_vects, 15);

    UINT64 bb_final_0000000Q_vects[32] = { // dimension: 16
        0x00FE78EFAC0FE565, 0x5CA54263A03EF0C3,
        0x0000C3E92F1F8649, 0x8DFBF22CD50F520F,
        0x003E28685B6958B1, 0xD8AC6DD811E86DE0,
        0x004D0221C8B8BC94, 0x45D2E93DDCD468AE,
        0x0018683B74EF8AFB, 0x4148423FE0354B39,
        0x000E7BD66CA0B1FC, 0x26FC74E38B1E9DB2,
        0x000764176FBFF046, 0x7D52ED4427C0EABE,
        0x000007F91C493DA0, 0xDF2ED76A66BE6279,
        0x000350A7B7E175DA, 0x4161D2C4C46092E6,
        0x000033832CE6A9BF, 0xFDBB0A1315A1205E,
        0x000108000D9DF596, 0x30C69260570269C4,
        0x0000525F7FE44551, 0xE195C23797AA669D,
        0x00001206660B6A38, 0x12682F8A836854F1,
        0x000008045A02415E, 0xEBC451F24D57E081,
        0x000002953A5A8608, 0x47A9BF01E9F18150,
        0x000000FA7ADC457D, 0x6C87A1736002E6C5,
    };
    BitBasis bb_final_0000000Q;
    bb_final_0000000Q.AddN(bb_final_0000000Q_vects, 16);

    // ensure bb_QRRR, bb_0QRR, bb_00QR and bb_000Q are indeed independent
    BitBasis bb;
    for(INT i=0; i<16; ++i)
    {
        bb.AddFast(bb_QRRRRRRR.vects[i]);
        bb.AddFast(bb_0QRRRRRR.vects[i]);
        bb.AddFast(bb_00QRRRRR.vects[i]);
        bb.AddFast(bb_000QRRRR.vects[i]);
        bb.AddFast(bb_0000QRRR.vects[i]);
        bb.AddFast(bb_00000QRR.vects[i]);
        bb.AddFast(bb_000000QR.vects[i]);
        bb.AddFast(bb_0000000Q.vects[i]);
    }

    //printf("bb dimension: %d\n", bb.dimension);
    if(bb.dimension != 128)
        { printf("FFUCK!\n"); while(1); }

    printf("\n" INFO "\n");

    // get license id to search
    // 
    Vect id;
    if(ac < 2)
    {
        printf("generating license id randomly (you may specify 36-bit id as argument)\n");

        id.Random();
        id = id & Vect(0xFFFFFFFFF0000000, 0);
    }
    else
    {
        // decode argument
        //
        UINT64 x=0;

        PCHAR hex_string = av[1];

        UCHAR lookup[256];
        for(CHAR i='0'; i<='9'; ++i)
            lookup[i] = i-'0';
        for(CHAR i='A'; i<='G'; ++i)
            lookup[i] = i-'A'+10;

        while(*hex_string)
        {
            x <<= 4;
            x |= lookup[*hex_string++];
        }

        for(INT i=0; i<36; ++i)
            if(x & ((UINT64)1<<i))
                id.SetBit(127-i);
    }

    id.Print("will solve for license ID");

    // invert it!
    //
    Vect PRIMITIVE_POLY(0x8400000000000000, 0x0000080000000000); // x^84 + x^5 + 1 (hehe don't get confused by top 0x84..., coincidence)

    Vect parity = FieldInvert(id, PRIMITIVE_POLY);

    for(INT i=0; i<36; ++i)
        parity.Shr();

    // form ciphertext
    //
    Vect ciphertext = id | parity;

    // position at low 120 bits
    for(INT i=0; i<8; ++i)
        ciphertext.Shr();

    //ciphertext.PrintPari();

    ciphertext.Print("ciphertext");

    // k, must express target in terms of the bases QRRR, 0QRR, 00QR, 000Q
    //
    Vect target = ciphertext;

    BitBasis all_bases;
    all_bases.Join(bb_final_QRRRRRRR);
    all_bases.Join(bb_final_0QRRRRRR);
    all_bases.Join(bb_final_00QRRRRR);
    all_bases.Join(bb_final_000QRRRR);
    all_bases.Join(bb_final_0000QRRR);
    all_bases.Join(bb_final_00000QRR);
    all_bases.Join(bb_final_000000QR);
    all_bases.Join(bb_final_0000000Q);
    //all_bases.Print("all bases");

    Vect c1, c2, c3, c4, c5, c6, c7, c8;
    GetComponents(&all_bases, target, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8);
    c1.Print("c1");
    c2.Print("c2");
    c3.Print("c3");
    c4.Print("c4");
    c5.Print("c5");
    c6.Print("c6");
    c7.Print("c7");
    c8.Print("c8");

    printf("ensuring the components indeed add up to the target...\n");
    Vect zz;
    zz.Xor(c1);
    zz.Xor(c2);
    zz.Xor(c3);
    zz.Xor(c4);
    zz.Xor(c5);
    zz.Xor(c6);
    zz.Xor(c7);
    zz.Xor(c8);
    zz.Print("target (from bases)");

    // brute time!
    //
    Vect temp;
    Vect plaintext;
    Vect sol1, sol2, sol3, sol4, sol5, sol6, sol7, sol8;
    Vect cc1,cc2,cc3,cc4,cc5,cc6,cc7,cc8;
    //
    //
    bb_QRRRRRRR.SpanAllInit();
    while(bb_QRRRRRRR.SpanAllNext(&temp))
    {
        Vect r = f_evaluatev(temp);

        GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

        if(cc1 == c1)
        {
            sol1 = temp;
            sol1.Print("s1 passer");

            // S2
            //
            sol1.Print("into s2 with s1 solution");

            bb_0QRRRRRR.SpanAllInit();
            while(bb_0QRRRRRR.SpanAllNext(&temp))
            {
                Vect input = temp + sol1;
                Vect r = f_evaluatev(input);
                GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                if(cc1 == c1 && cc2 == c2)
                {
                    sol2 = input;
                    input.Print("s2 passer");

                    //
                    //
                    sol2.Print("into s3 with s2 solution");

                    bb_00QRRRRR.SpanAllInit();
                    while(bb_00QRRRRR.SpanAllNext(&temp))
                    {
                        Vect input = temp + sol2;
                        Vect r = f_evaluatev(input);
                        GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                        if(cc1 == c1 && cc2 == c2 && cc3 == c3)
                        {
                            sol3 = input;
                            input.Print("s3 passer");

                            //
                            //
                            sol3.Print("into s4 with s3 solution");

                            bb_000QRRRR.SpanAllInit();
                            while(bb_000QRRRR.SpanAllNext(&temp))
                            {
                                Vect input = temp + sol3;
                                Vect r = f_evaluatev(input);
                                GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                                if(cc1 == c1 && cc2 == c2 && cc3 == c3 && cc4 == c4)
                                {
                                    sol4 = input;
                                    input.Print("s4 passer");

                                    //
                                    //
                                    sol4.Print("into s5 with s4 solution");

                                    bb_0000QRRR.SpanAllInit();
                                    while(bb_0000QRRR.SpanAllNext(&temp))
                                    {
                                        Vect input = temp + sol4;
                                        Vect r = f_evaluatev(input);
                                        GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                                        if(cc1 == c1 && cc2 == c2 && cc3 == c3 && cc4 == c4 && cc5 == c5)
                                        {
                                            sol5 = input;
                                            input.Print("s5 passer");

                                            //
                                            //
                                            sol5.Print("into s6 with s5 solution");

                                            bb_00000QRR.SpanAllInit();
                                            while(bb_00000QRR.SpanAllNext(&temp))
                                            {
                                                Vect input = temp + sol5;
                                                Vect r = f_evaluatev(input);
                                                GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                                                if(cc1 == c1 && cc2 == c2 && cc3 == c3 && cc4 == c4 && cc5 == c5 && cc6 == c6)
                                                {
                                                    sol6 = input;
                                                    input.Print("s6 passer");

                                                    //
                                                    //
                                                    sol6.Print("into s7 with s6 solution");

                                                    bb_000000QR.SpanAllInit();
                                                    while(bb_000000QR.SpanAllNext(&temp))
                                                    {
                                                        Vect input = temp + sol6;
                                                        Vect r = f_evaluatev(input);
                                                        GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                                                        if(cc1 == c1 && cc2 == c2 && cc3 == c3 && cc4 == c4 && cc5 == c5 && cc6 == c6 && cc7 == c7)
                                                        {
                                                            sol7 = input;
                                                            input.Print("s7 passer");

                                                            //
                                                            //
                                                            sol7.Print("into s8 with s7 solution");


                                                            bb_0000000Q.SpanAllInit();
                                                            while(bb_0000000Q.SpanAllNext(&temp))
                                                            {

                                                                Vect input = temp + sol7;
                                                                Vect r = f_evaluatev(input);
                                                                GetComponents(&all_bases, r, &cc1, &cc2, &cc3, &cc4, &cc5, &cc6, &cc7, &cc8);

                                                                if(cc1 != c1 || cc2 != c2 || cc3 != c3 || cc4 != c4 || cc5 != c5 || cc6 != c6 || cc7 != c7)
                                                                    printf("wtf!\n");

                                                                if(cc1 == c1 && cc2 == c2 && cc3 == c3 && cc4 == c4 && cc5 == c5 && cc6 == c6 && cc7 == c7 && cc8 == c8)
                                                                {
                                                                    plaintext = input;
                                                                    goto all_done;
                                                                }

                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("no solutions!\n"); return 0;

    //
    //
    all_done:

    // encode plaintext in string
    // gbe skips top 3 bits, I assume to keep his serials short (5*5 chars * 5 bits == 125 bits == 3 bits shy of 128)
    PCHAR lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234967";
    CHAR serial[30];
    memset(serial, 0, 30);
    INT j=0;

    for(INT i=0; i<125; i+=5)
    {
        INT val = (plaintext.Bit(127-i) << 0) |
                    (plaintext.Bit(127-(i+1)) << 1) |
                    (plaintext.Bit(127-(i+2)) << 2) |
                    (plaintext.Bit(127-(i+3)) << 3) |
                    (plaintext.Bit(127-(i+4)) << 4);

        serial[j++] = lookup[val];

        if(i!=120 && !((i+5)%25))
            serial[j++] = '-';
    }
       
    printf("serial: %s\n", serial);

    printf("ctrl+C to quit!\n");
    while(1);

    return 0;
}
