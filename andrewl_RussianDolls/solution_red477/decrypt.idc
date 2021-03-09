
#include <idc.idc>

static main() {
	auto i,b,k;
	auto pStart, nCodeLen;

	pStart=0x40501D;
	// nCodeLen=0x01866A;
	while(pStart<=0x40501D+0x01866A)
	{
        Message("Processing 0x%08X\n",pStart);
		i=pStart;
		k=Byte(pStart-7);
		nCodeLen=Dword(pStart-0x0D);
		while(i<pStart+nCodeLen){
			b=Byte(i);
			b=b^k;
			PatchByte(i,b);
			i++;
		}
		for(;;)
		{
			// if "call $+5 / pop esi / add esi,15" instructions pair found
			if ((Dword(pStart)==0x000000E8) && (Dword(pStart+4)==0xC6815E00)){
				if(Dword(pStart+8)==0x0015){
					break;
				}
			}
			pStart++;
            if(pStart>=0x40501D+0x01866A)break;
		}
		pStart=pStart+0x1A;
		// if (pStart>=0x40501D+0x01866A)break;
	}
}
