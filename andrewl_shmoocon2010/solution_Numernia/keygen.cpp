#define PRIMITIVE_POLY 0xA348FCCD93AEA5A7
#define QWORD unsigned __int64
#define RADER 64
#define KOLS  65

QWORD V[64] = {
0xAD458DFA930E7758, 0xF10FC3F820C929F1, 0xF00B0B657B4D94A9, 0x6DE1598414A517A6,
0x9B991A0E314C1E44, 0xB1382BF2E3CDA5E1, 0xC16FF86AE8F4653A, 0x237748675547C4BF,
0xE960CFF49C1A8946, 0xDB062207E72995EA, 0x66DB5BDF2AB4F6E8, 0x83784C90CD235412,
0x4A1C881DEC7EBBB2, 0x0B52BA8EFD33B9B3, 0xF12D03725E251905, 0x3085E423EDC121CF,
0xEB94E62E6055D5E0, 0x62367B5F39D560C0, 0x52906FB8C9492CF1, 0x035AFD2D7798B999,
0x65069945E2FA15E6, 0xBE7C73357C22AB67, 0x56922905F46124C9, 0x12E40CF6282DB94A,
0x9AB1D0AA6563F126, 0x181B2A1156AC1362, 0xFAC9155379F4B6C1, 0x7CC8A69D25DC3FA9,
0x3486DAE2772FC829, 0xFC1CB668F8CF072E, 0xE4C6D4AF5882F4B8, 0xBA3ECDABACAB06D3,
0xA69C01579EAE3907, 0xA30168A0C083E3F0, 0x04C9BCCAE603EA44, 0x81C5F65F675E7475,
0xAA1C9C9EA6D88051, 0xC51760AF7B132D43, 0x9D76ED84BB7D9C4C, 0x623D7A0632326993,
0xA759A86799AA809C, 0xC5DBE04375045249, 0xB77EFBD73113D8F7, 0xF7D967450A939C9A,
0xBEA34737BB98A3A2, 0xD5F41E7C3D9A753D, 0x443A6C32B29B7B36, 0x30443726895B5FD3,
0x101ABAD636A6AA7D, 0xF721FC4F40178F70, 0xC948EDCC3F35C769, 0x4E8E9AA3A94080CC,
0xE0A1D1D2E036DCF4, 0x1BEC7F6071E649A5, 0xDC875AABD5F0ED20, 0xCB001EEFA902FDEF,
0xCB1E9A37FA062738, 0x1778159F2F97B255, 0xC98C7390409472B1, 0x90FE940558F42F8B,
0xBF9DC6C13E0FB878, 0xCDC1551E825C7E4C, 0x55E1784B37A34219, 0xB8315E039D3C214D};

QWORD GaussEliminationGF2(int a[100][100], QWORD V[65], QWORD y)
{
	int s=0, i=0, j=0, k=0, p=0, temp=0;
	QWORD tp;
	/* Init phase, zero memory */
	for (i = 0; i < 100; i++){
		for (j = 0; j < 100; j++){
			a[i][j] = 0;
		}
	}

	/* Build table, convert V to binary and store in matrix */
	for (i = 0; i < RADER; i++)
	{
		tp = V[i];
		for (j = 0; j < RADER; j++)
		{
			a[i][63-j] = tp & 1;
			tp >>= 1;
		}
	}
	tp = y; //This is the answer matrix
   
	for (j = 0; j < RADER; j++)
	{
		a[63-j][RADER] = tp & 1;
		tp >>= 1;
	}

  
	/* Begin Gauss Elimination over GF(2)*/
	for (k = 0; k < KOLS; k++)
	{
		s = k;
		while(a[s][k] == 0 && s <= KOLS){
			s++;}
		for (p = 0; p < KOLS; p++){ //exchange rows
			temp = a[k][p];
			a[k][p] = a[s][p];
			a[s][p] = temp;
		}
		for (i = 0; i < RADER; i++){
			if( (i != k) && (a[i][k] == 1) ){
				for (j = k-1; j < KOLS; j++){
					a[i][j] = a[i][j] ^ a[k][j]; //
				}
			}
		}
	}
	/* Build the X(answer) vector to a number for returning. */
	tp = 0;
	for (p = 0; p < RADER; p++){
		if(a[p][KOLS-1]==1){
			tp |= (QWORD)1<<(63-p);
		}

	   
	}
   return tp;
}

QWORD FieldMul(QWORD multiplicand, QWORD multiplier, QWORD modulus)
{
    QWORD d_mask;
    QWORD result;

    // measure the degree of the modulus
    d_mask = (QWORD)1 << 63;
	

    while(!(d_mask & modulus))
        d_mask >>= (QWORD)1;

    // calculate the product
    result = 0;
	
    while(multiplier)
    {
        // if the current coeff of the muliplier is set
        //   then add the multiplicand to the result
        if(multiplier & (QWORD)1)
            result ^= multiplicand;

        multiplier >>= (QWORD)1;

        multiplicand <<= (QWORD)1;
		

        // if degree(multiplicand) >= degree(modulus)
        //   then subtract the modulus
        if(multiplicand & d_mask)
            multiplicand ^= modulus;
    }


    return result;
}

QWORD FieldAdd(QWORD addend_a, QWORD addend_b)
{
    return addend_a ^ addend_b;
}

QWORD FieldDivide(QWORD dividend, QWORD divisor, QWORD *remainder)
{
    QWORD quotient = 0;
    INT degree = 63;

    while(!(divisor & 0x8000000000000000))
    {
        divisor <<= (QWORD)1;
        degree--;
    }

    quotient = 0;

    for(INT bit = 63; bit >= degree; --bit)
    {
		
        if(dividend & ((QWORD)1<<bit))
        {
            quotient |= ((QWORD)1<<(bit-degree));

            dividend ^= divisor;
        }

        // slide the divisor to the right across the dividend
        divisor >>= (QWORD)1;
    }

    *remainder = dividend;


    return quotient;
}

QWORD FieldEGCD(QWORD a, QWORD b, QWORD primitive, QWORD *r, QWORD *s)
{
    QWORD sum;
    QWORD product;
    QWORD quotient;
    QWORD remainder;

    QWORD gcd = 0;

    QWORD r_a = 1, s_a = 0; // a = 1*a + 0*b
    QWORD r_b = 0, s_b = 1; // b = 0*b + 1*a

    while(a && b)
    {
        if(a > b)
        {
            quotient = FieldDivide(a, b, &remainder);
            a = remainder;

            product = FieldMul(quotient, r_b, primitive);
            r_a = FieldAdd(r_a, product);       // r_a = r_a - quotient * (r_b);

            product = FieldMul(quotient, s_b, primitive);
            s_a = FieldAdd(s_a, product);       // s_a = s_a - quotient * (s_b);
        }
        else
        {
            quotient = FieldDivide(b, a, &remainder);
            b = remainder;

            product = FieldMul(quotient, r_a, primitive);
            r_b = FieldAdd(r_b, product);       // r_a = r_a - quotient * (r_a);

            product = FieldMul(quotient, s_a, primitive);
            s_b = FieldAdd(s_b, product);       // s_b = s_b - quotient * (s_a);
        }
    }

    if(a)
    {
        *s = s_a;
        *r = r_a;
        return a;
    }
    else
    {
        *s = s_b;
        *r = r_b;
        return b;
    }
}

QWORD FieldInvert(QWORD a, QWORD primitive)
{
    QWORD r, s;
    FieldEGCD(a, primitive, primitive, &r, &s);
    return r;
}
//#########################################################

void Generate(HWND hwnd) 
{
	int matrix[100][100];
	QWORD name_dw = 0;
	char name[50]={0}, serial[20];
	int len = GetDlgItemText(hwnd,IDC_EDIT2,name,50);
	
	if (len > 8)
	{
		name[8] = 0;
		SetDlgItemText(hwnd,IDC_EDIT2,name);
	}
	else if (len <= 1){
		return;}

	for (int i = 0; i < len; i++)
		name_dw |= ((QWORD)name[i] << (QWORD)(8 * i));

	//crypto1
	QWORD serial_cm1 = GaussEliminationGF2(matrix,V,name_dw);
	wsprintfA(serial,"%I64X", serial_cm1);
	SetDlgItemText(hwnd,IDC_EDIT1,serial);
	
	//crypto2
	QWORD serial_cm2 = FieldInvert(name_dw, PRIMITIVE_POLY);
	wsprintfA(serial,"%I64X", serial_cm2);
	SetDlgItemText(hwnd,IDC_EDIT3,serial);

	//crypto3
	QWORD serial_cm3 = powmod64(name_dw, 0x7181F6EA6026F297, 0x7FBF89F8CD4152C5);
	wsprintfA(serial,"%I64X", serial_cm3);
	SetDlgItemText(hwnd,IDC_EDIT4,serial);

	//crypto5
	unsigned long sn2 = rand()*rand();
	unsigned long sn1 = powmod32(sn2,0xB00BEEE5,0xFFFFFFFB);
	sn1 = (sn1 * (name_dw % 0xFFFFFFFB)) % 0xFFFFFFFB;

	wsprintfA(serial,"%08X%08X",sn1,sn2);
	SetDlgItemText(hwnd,IDC_EDIT5,serial);
}