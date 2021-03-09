g = h2d("017A1EB581E9B0719167D77ABC3542A690B4B7F8A9C6BC5535B658F6AC0577432EB3084B0F07D1D8FD8E98A06BCA6DF9DAA8796D5A40FB09D942ED6E3473A7D9838A8771BB4BA1C4248EC07E36C82963DE3575C5FD95BFBD7F4795DBC4585E3286BA22AD8529F2E59A39B14970D0534B1F576101FEE9BCBCFEB22BC922DF5E7F5150C18FA87E02AF7415838BADD7B992EA58B3D888D520A0E935B5A7379BC19E5749C9E21306E970BA90C66F9D7B76AF322086D154F2E7A612C0A508D74E46DC2BC9429B7D53ABCF839A191474EC0E9141CCDEC4E4A3E2A7E4A961DA8D77C1005969F2257F9A5781BC618A8081B81E36A05C0244A200FD3FD9B96E500DB7F4");
N = h2d("021C02B83B55B322BDB134C133894A39DED270A01785F1FE760F0BAEF71783CB5AE67B2208E363B8E60A2B6C0153BA5B8E2B05CBBBBF54F9A7D741D3F337E8052E77379902487E7A9FEFEC17C86AF4917172F92E39434A0258D9E850A454784E8622E579C3B8CF44F47864A745CF086396B4E92A7B0FF8F068FB3A81A3E0725FCEFEB2DA03EF32F1E3B5C4280A2252AF5FB3C8900A5F2DE9EBF669237BBC9080614F1509C979FCAF00CA409A15A239A9748A5C61C96F141E403D02B40961CDA8E62E5EF536F165A1B99AFEA582C3169DBF32B91B903A75DFA315DB95B3F181D4A5992F7ED1572446B091E9EBCACDDD57B6216DA3876671EEFDACB86DFB503F");
subgroup_size = 2^56;
counter = 1;
\\ cache this
toplog = log(subgroup_size);
\\ largest factor of 2^56 is capped here
limit = ceil(sqrt(subgroup_size));
p=2;
while(p<limit, \
	degree = ceil(toplog/log(p)); \
	g = PowMod(g,p^degree,N); \
	if(!(counter%100000),print("on prime: ",p)); \
	counter = counter+1; \
	p = nextprime(p+1); \
); \
print(g);

