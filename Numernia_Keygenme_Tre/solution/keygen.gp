info = "keygen to Numernia's \"Keygenme Tre\"\njan27_2009 andrewl/crackmes.de\n";

\\ this is a script for PARI/GP Version 2.3.4 (released) (http://pari.math.u-bordeaux.fr/)
\\ you can run this several ways:
\\ 1) on command line with: gp <path to keygen.gp>
\\ 2) within gp, use command: \r <path to keygen.gp>
\\ 3) within gp, just copy paste this entire text

\\ want to just know the output and test some keys?
\\ ADC8DC-3173-68E9-B65-1849-63BB-39A-NM
\\ CB3591-1A23-5375-F20-0042-B8A5-A74-NM
\\ E275F7-19A4-EDD2-046-158A-BAD6-5C8-NM
\\ 8EE073-1885-9863-FD9-0B0F-B72B-EC8-NM
\\ BA7E1C-0975-8E24-BDA-2C91-BECB-66C-NM
\\ C56607-2715-07D4-A9A-1420-7412-621-NM
\\ 9F5702-1D65-FD71-C5D-2A73-C846-B08-NM
\\ C557C5-2F4B-B523-285-214F-116C-350-NM
\\ 933BFF-0C3D-D8EC-3A2-16F3-855C-B3F-NM
\\ 8265B5-1C32-1CB8-96E-2358-D338-A72-NM
\\ 3D2CA0-21B8-2DB0-2FC-0C24-9E66-7EA-NM
\\ E43645-1D44-4A35-A33-0EE6-3F7B-692-NM
\\ 3B2C67-1EEE-FACF-5C4-304B-8444-9DA-NM
\\ 97891C-229B-9588-594-2A24-0617-A4E-NM
\\ BDDB25-28A6-1283-163-0A82-5630-52B-NM
\\ D3B713-08DD-DE06-CC5-2AC8-28C2-B77-NM

\\ ------------------------------------------------------------
\\ STRING FUNCTIONS
\\ ------------------------------------------------------------

Substring(s,a,b) =
{
    local(y="",t);

    t=vecextract(Vec(s),Str(a,"..",b));

    for(i=1,#t,
        y = concat(y,t[i]);
    );

    y;
}

\\ ------------------------------------------------------------
\\ CONVERSIONS
\\ ------------------------------------------------------------

\\ binary vector to hex
binvect2hex(V)=
{
    local(W,nibl,answ,lookup);

    lookup=["0","1","2","3","4","5","6","7",
            "8","9","A","B","C","D","E","F"];

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

\\ binary vector to decimal number
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

\\ ------------------------------------------------------------
\\ GLOBALS
\\ ------------------------------------------------------------

\\ curve params
a = 621;
b = 645;                        
p = 3410286041003;

\\ ECNR params
G = [1926452604425, 1986356512487]; \\ generator
Y = [0291423732751, 0437711818455]; \\ public key = xG
x = 2408408535581;                  \\ private key
o = 3410284165198;                  \\ group order

\\ ------------------------------------------------------------
\\ KEYGEN FUNCTIONS
\\ ------------------------------------------------------------

GenMessage() =
{
    \\ generate random 3-byte message
    while(1,
        m = binary(random(2^24));
        if(!m,next);

        \\ ensure that msb bit is on an odd index (crackme rule)
        for(i=1,#m,
            if(m[i], \\ first set bit found!
                if((#m-i)%2==0,
                    next(2);
                ,
                    break(2);
                );
            );
        );
    );

    \\ pad message bit vector to 24 bits
    m = concat(vector(24-#m),m);
    binvect2dec(m);
}

GenKey() =
{
    \\ we sign a random message:
    \\
    \\ signing:
    \\ --------
    \\ r = x_coord(k*G) + message
    \\ s = k - x*r (mod order)
    \\ 
    \\ verification: (Crackme does this)
    \\ ------------
    \\ r - x_coord(s*G + r*Y) =
    \\ r - x_coord((k - x*r)*G + r*(x*G)) =
    \\ r - x_coord(k*G - x*r*G + r*x*G) =
    \\ r - x_coord(k*G) = 
    \\ (x_coord(k*G) + message) - x_coord(k*G) =
    \\ message

    m = GenMessage();
    \\print("m: ", m);

    k = 1 + random(o-1);
    \\print("k: ", k);

    E = ellinit([0,0,0,Mod(a,p),Mod(b,p)]);
    
    r = lift(ellpow(E,G,k));    \\ kG
    r = r[1];                   \\ x_coord(kG)
    r = (r + m) % o;            \\
    s = (k - x*r) % o;

    \\print("r: ", r);
    \\print("s: ", s);

    \\ pad bits, convert to hex
    m = binary(m);
    m = binvect2hex(concat(vector(24-#m),m));
    r = binary(r);
    r = binvect2hex(concat(vector(44-#r),r));
    s = binary(s);
    s = binvect2hex(concat(vector(44-#s),s));

    \\ build final serial string
    serial = concat(m, "-");
    serial = concat(serial, Substring(r,1,4));
    serial = concat(serial, "-");
    serial = concat(serial, Substring(r,5,8));
    serial = concat(serial, "-");
    serial = concat(serial, Substring(r,9,11));
    serial = concat(serial, "-");
    serial = concat(serial, Substring(s,1,4));
    serial = concat(serial, "-");
    serial = concat(serial, Substring(s,5,8));
    serial = concat(serial, "-");
    serial = concat(serial, Substring(s,9,11));
    serial = concat(serial, "-NM");
    serial;
}

\\ ------------------------------------------------------------
\\ main() 
\\ ------------------------------------------------------------

print(info);
print("Generating 16 random keys...");
for(i=1,16,print(GenKey()));

