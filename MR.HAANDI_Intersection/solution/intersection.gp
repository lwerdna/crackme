\\ these values come from replacing GetTickCount() with xor eax, eax; dec eax
\\ and having "MR.HAANDI" default name
p = 4294967291;
m = (+0401877261*x^0 +0319151251*x^1 +1522639780*x^2 +0373083325*x^3 +0135070006*x^4 +2072661367*x^5 +0000000001*x^6 ) * Mod(1,p);
order = 6277101691541631771514589274364601047755112573811991434000;
DLP_old = 53525920154607081292323834060017845652241272953839788991535352592015460708129232383406001784565224127295383978899153;
DLP = 314159265;

\\ derived from hash of name
zzMd5Name=2418411290696412;
\\ derived from serial number
serial=18225923690521628478004036645069549649647;
\\ derived from first exponentiation
zzMd5PointA=5619858642284813;
\\ from GetTickCount() == 0xFFFFFFFF == 4294967295
elemFromGTC = (+3010928169*x^5 +3910405806*x^4 +2879497108*x^3 +1009877983*x^2 +0568316934*x^1 +2289504861*x^0) * Mod(1,p);


GenerateAB(k) = {
    local(irred, SeedA, SeedB, PointA, PointB);

    irred = (x^6 +2072661367*x^5 +0135070006*x^4 +0373083325*x^3 +1522639780*x^2 +0319151251*x^1 +0401877261*x^0) * Mod(1,p);

    SeedA = [
        (+2447134460*x^5 +0871167555*x^4 +0338177802*x^3 +0370371326*x^2 +3152113581*x^1 +2218130420*x^0) * Mod(1,p),
        (+0970958055*x^5 +1661846692*x^4 +2615174668*x^3 +2687502417*x^2 +2539672687*x^1 +2585604584*x^0) * Mod(1,p),
        (+2090499100*x^5 +3586500530*x^4 +0534184351*x^3 +2169583335*x^2 +3452718476*x^1 +4090110644*x^0) * Mod(1,p),
        (+1672623231*x^5 +1924900927*x^4 +2628290729*x^3 +1426685279*x^2 +3777830547*x^1 +1900306940*x^0) * Mod(1,p)
    ];

    SeedB = [
        (+2943798197*x^5 +0843145904*x^4 +3020622304*x^3 +3097671584*x^2 +2515596009*x^1 +3326296572*x^0) * Mod(1,p),
        (+4077598163*x^5 +0698704803*x^4 +4259079522*x^3 +3473322830*x^2 +1492737774*x^1 +2314264621*x^0) * Mod(1,p),
        (+0326530814*x^5 +1927248595*x^4 +0302635456*x^3 +1656396964*x^2 +3392538410*x^1 +0412491626*x^0) * Mod(1,p),
        (+0577721219*x^5 +3979886956*x^4 +3905696031*x^3 +3091627353*x^2 +1583157487*x^1 +3853647145*x^0) * Mod(1,p)
    ];

    PointA = vector(4);
    PointA[1] = (SeedA[1] * k) % irred;
    PointA[2] = (SeedA[2] * k) % irred;
    PointA[3] = (SeedA[3] * k) % irred;
    PointA[4] = (SeedA[4] * k) % irred;

    PointB = vector(4);
    PointB[1] = (SeedB[1] * k) % irred;
    PointB[2] = (SeedB[2] * k) % irred;
    PointB[3] = (SeedB[3] * k) % irred;
    PointB[4] = (SeedB[4] * k) % irred;

    return([PointA, PointB]);
}

IsIdentity(p) = {
    local(d_inv, r);

    r = vector(4);

    d_inv = Mod(p[4], m);
    d_inv = d_inv^-1;
    d_inv = lift(d_inv);

    for(i=1,4,
        r[i] = lift(lift( (p[i] * d_inv)%m ));    
    );

    if(r[1]==0 && r[2]==1 && r[3]==1 && r[4]==1,
        return(1);
    ,
        return(0);
    );
}

PrintPointNormalized(p) = {
    local(d_inv);

    d_inv = Mod(p[4], m);
    d_inv = d_inv^-1;
    d_inv = lift(d_inv);

    for(i=1,3,
        print(lift(lift((p[i] * d_inv)%m)));    
    );
}

PrintPoint(p) = {
    for(i=1,4,
        print(lift(p[i]));
    );

    print("-(normalized:)-");
    PrintPointNormalized(p);
    print();
}

PrintPointM(msg,p) = {
    print(msg);
    PrintPoint(p);
}

PointDouble(p) = {
	local(A,B,C,D);

	A=p[1]; B=p[2]; C=p[3]; D=p[4];

	p[1] = 2*A*B*C*D % m;
	p[2] = ( + (B*C)^2 + (B*D)^2 - (C*D)^2 ) % m;
	p[3] = ( + (B*C)^2 - (B*D)^2 + (C*D)^2 ) % m;
	p[4] = ( - (B*C)^2 + (B*D)^2 + (C*D)^2 ) % m;

	return(p);
}

PointAdd(p1,p2) = {
    local(r,X1,Y1,Z1,T1,X2,Y2,Z2,T2);

    r=vector(4);

    X1=p1[1]; Y1=p1[2]; Z1=p1[3]; T1=p1[4];
    X2=p2[1]; Y2=p2[2]; Z2=p2[3]; T2=p2[4];

    r[1] = (T1*Y2*X1*Z2 + Z1*X2*Y1*T2) % m;
    r[2] = (T1*Y2*Y1*T2 - Z1*X2*X1*Z2) % m;
    r[3] = (T1*Z1*T2*Z2 - 2951558829*X1*Y1*X2*Y2) % m;
    r[4] = ((T1*Y2)^2 + (Z1*X2)^2) % m;

    return(r);
}

PointAddBug(p1,p2) = {
    local(r,X1,Y1,Z1,T1,X2,Y2,Z2,T2);

    r=vector(4);

    X1=p1[1]; Y1=p1[2]; Z1=p1[3]; T1=p1[4];
    X2=p2[1]; Y2=p2[2]; Z2=p2[3]; T2=p2[4];

    r[1] = (T1*Y2*X1*Z2 + Z1*X2*Y1*T2) % m;
    r[2] = (T1*Y2*Y1*T2 - Z1*X2*X1*Z2) % m;
    r[3] = (T1*Z1*T2*Z2 - 2951558829*X1*Y1*X2*Y2) % m;
    r[4] = ((T1*Y2)^2 + (Z1*X2)^2) % m;

    return(r);
}

PointMul(p, coeff) = {
    local(runner,result);

    runner=p;

    \\ it is written in this non-intuitive order to mirror the generated
    \\ code for easier tracing
    
    if(coeff % 2,
        result=p;
    ,
        result=[0,1,1,1];
    );

    coeff >>= 1;

    while(coeff,
        \\print("coeff is: ", coeff);
        \\print("--");

        runner = PointDouble(runner);

        if(coeff % 2,
            \\print("adding to current result:");
            \\printPoint(result);
            \\print("--");

            result = PointAdd(runner, result);
            \\print("new result:");
            \\printPoint(result);
            \\print("--");

        );

        coeff = coeff >> 1;
    );

    return(result);
}

EmulateCrackme() = {
    local(r,s,t,u,v2);

    \\ generate the points
    \\
    v2 = GenerateAB(elemFromGTC);
    PointA = v2[1];
    PointB = v2[2];

    print("PointA:");
    PrintPoint(PointA);

    print("PointB:");
    PrintPoint(PointB);

    \\ for GetTickCount() returning 0xFFFFFFFF, we should get:
    \\PointA = [ \
    \\((+2842271803*x^5 +0131690647*x^4 +4156969949*x^3 +3746455294*x^2 +0628579242*x^1 +2361017629*x^0)*Mod(1,p))%m, \
    \\((+4016367385*x^5 +2329238747*x^4 +2260841201*x^3 +3385008325*x^2 +3614064443*x^1 +0117428241*x^0)*Mod(1,p))%m, \
    \\((+3437718441*x^5 +1450895703*x^4 +3918476104*x^3 +2086868649*x^2 +1638612588*x^1 +1441414064*x^0)*Mod(1,p))%m, \
    \\((+2995270019*x^5 +3695742188*x^4 +4144697843*x^3 +2445042676*x^2 +1982063046*x^1 +0998991137*x^0)*Mod(1,p))%m \
    \\];
    \\
    \\PointB = [ \
    \\((+3989364853*x^5 +0115724639*x^4 +0284217963*x^3 +3664906030*x^2 +4104504421*x^1 +1908119556*x^0)*Mod(1,p))%m, \
    \\((+0419593291*x^5 +0142358558*x^4 +1719332116*x^3 +0853685456*x^2 +2600068677*x^1 +0043331810*x^0 )*Mod(1,p))%m, \
    \\((+1919090511*x^5 +3817636701*x^4 +3326742980*x^3 +1380461678*x^2 +2832482354*x^1 +2782252193*x^0 )*Mod(1,p))%m, \
    \\((+1777791494*x^5 +2792368212*x^4 +1862492839*x^3 +2006547967*x^2 +4096141700*x^1 +2286909155*x^0 )*Mod(1,p))%m \
    \\];

    r = PointMul(PointA, zzMd5Name);

    print("to_ZZ(MD5(name)) * PointA:");
    PrintPoint(r);

    s = PointMul(PointA, serial^3);

    print("to_ZZ(serial)^3 * PointA:");
    PrintPoint(s);

    t = PointMul(PointB, zzMd5PointA);

    print("MD5(MD5(...)) * PointB:");
    PrintPoint(t);

    u = PointAdd(s, t);
    print("sum:");
    PrintPoint(u);

    print("Notice that the sum is equal to ZZ(MD5(name)) * PointA, accepted serial!");
}




