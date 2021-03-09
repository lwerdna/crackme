
#include <idc.idc>

static main() {
	auto i,b,k;
	auto pStart, nCodeLen;

	auto c,d;
	auto bFound;
	auto j;
	for(j=0;j<=7;j++){
		pStart=0x405020;
		i=pStart;
		while ( i<0x41D687 ) {
			b=Byte(i+0x03);
			if(b==j){
				k=Byte(i+0x0E);
				if(k==1){
					k=Byte(i+0x09);
					// Message("0%02Xh\n",k);
					bFound=1;
					
					for(c=i;c<0x41D687;c=c+0x41){
						d=Byte(c+0x03);
						if(d!=b)continue;
						d=Byte(c+0x09);
						if(d!=k)continue;
						d=Byte(c+0x0E);
						if(d==0){bFound=0;break;}
					}
					if(bFound==1){
						Message("FOUND %d:%c\n",j,k);
					}
				}
			}
			i=i+0x41;
		} // while ( i<0x41D687 ) {
	} // for(j=0;j<=7;j++){

}
