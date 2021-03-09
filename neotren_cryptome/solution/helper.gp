\\ hex to decimal
h2d(s) =
{
    local(v=Vec(s), a=10,b=11,c=12,d=13,e=14,f=15,
            A=10,B=11,C=12,D=13,E=14,F=15, h);

    \\ remove leading "0x" if it exists
    if(#v >= 2,
        if(v[1]=="0" && v[2]=="x",
            \\print("v before: ", v);
            v = vecextract(v,concat("3..",#v));
            \\print("new v: ", v);
        );
    );

    for(i=1,#v,
        h = (h<<4) + eval(v[i])
    );
    
    h
}

\\ binary vector to hex
binvect2hex(V)=
{
    local(W,nibl,answ,lookup);

    lookup=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

    answ="";

    W=V;
    if(#W%4,
        W=concat(vector(4-(#W%4)),W);
    );

    forstep(i=1,#W,4,
        nibl=8*W[i]+4*W[i+1]+2*W[i+2]+W[i+3];
        answ=concat(answ,lookup[nibl+1]);
    );

    answ;
}

\\ binary vector to hex
binvect2dec(V)=
{
    local(y=0);

    for(i=1,#V,
        y = y << 1;
        y = y + V[i];
    );

    y;
}

\\ decimal to hex
d2h(n) =
{
    binvect2hex(binary(n))
}

\\
\\ fast exponenentiation
\\
PowMod(b,e,m) =
{
    local(runner,result);

    result=1;
    runner=b;

    while(e,
        if(e % 2,
            result = (result * runner) % m;
        );

        runner = (runner * runner) % m;
        e >>= 1;
    );

    result;
}

\\ alternative to expand()
\\from pari/gp faq
\\
polmonomials(v)=
{ local(w);

    if (type(v) != "t_POL",
            if(v, [v], [])
            ,
            w = [];
            for(n=0, poldegree(v),
                w = concat(w, variable(v)^n * polmonomials(polcoeff(v,n)))
               ); w
       )
}

