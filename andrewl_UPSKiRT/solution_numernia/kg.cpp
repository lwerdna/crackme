
void FillZeros(char *a)
{
	strrev(a);
	for(;;)
	{
		if(strlen(a)==24)
			break;
		strcat(a,"0");
	}
	strrev(a);
}
		

void Generate(HWND hWnd)
{
	srand(GetTickCount());
	char AlfaKey[] = "#cRaCkInG4NeWbIeS", serial[100];
	BYTE PermuTable[20]={0}, try1 = 0;

	big m, p1, p2, k, n, s2, s3, key, h, l;

	m = mirvar(0);
	p1 = mirvar(0);
	p2 = mirvar(0);
	k = mirvar(0);
	n = mirvar(0);
	key = mirvar(0);
	h = mirvar(0);
	l = mirvar(0);

	s2 = mirvar(0);
	s3 = mirvar(0);
	
	mip->IOBASE = 16;
	char seed[24], s[200] = {0};

	//install the seed buffer
	for (int i = 0; i < 20; i++)
		PermuTable[i]=0xFF;
	
	PermuTable[0]=9;
	PermuTable[12]=4;

	//fix the seed
	for (int j = 0; j < 17; j++)
	{
NewTry:
		try1 = rand()%17;
		for (int r = 0; r < 17; r++){
			if(try1 == PermuTable[r]){
				goto NewTry;
			}
		}
		if((j!=0)&&(j!=12)){
			PermuTable[j] = try1;}
			
		seed[j]=AlfaKey[PermuTable[j]];
		
	}
	for (int j = 0; j < 7; j++){
		seed[j+17] = 0x41 + rand()%26;}
	seed[24]=0;

	strcpy(serial,seed);
	strcat(serial,"-");

	for (int i = 0; i < 12; i++)
		seed[i] ^= (seed[i+12] << 4);

	bytes_to_big(12,seed,m);


	cinstr(key,"5F94CF4E06C11B198137892");
	cinstr(p1,"19FBD41D69AA3D86009A968D");
	cinstr(p2,"1B6F141F98EEB619BC036051");

	//(p2+m)*key
	add(p2,m,h);
	multiply(h,key,h);
	
	//([h/p2]+1)*p2
	copy(h,l);
	divide(h,p2,n);
	copy(l,h);
	incr(n,1,n);
	multiply(n,p2,n);
	
	//(p2+m)*key - ([h/p2]+1)*p2
	subtract(n,h,s2);
	
	cotstr(s2,s);
	if(strlen(s)!=24){
		FillZeros(s);}
	strcat(serial,s);
	strcat(serial,"-");

	//((s2*p1)+m)/p2=s3
	multiply(s2,p1,h);
	add(h,m,h);
	divide(h,p2,s3);

	cotstr(s3,s);
	if(strlen(s)!=24){
		FillZeros(s);}
	strcat(serial,s);
	SetDlgItemText(hWnd,IDC_EDIT1,serial);
	
	mirkill(h);
	mirkill(l);
	mirkill(key);
	mirkill(m);
	mirkill(p1);
	mirkill(p2);
	mirkill(k);
	mirkill(n);
	mirkill(s2);
	mirkill(s3);
	
}