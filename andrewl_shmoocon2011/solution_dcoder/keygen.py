
import sys
import math

rotor0 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~1akuEOY"
rotor1 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~2blvFPZ9hqz"
rotor2 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~3cmwGQ10irAIQ"
rotor3 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~4dnxHR2ajsBJRY6cj"
rotor4 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~5eoyIS3bktCKSZ7dkqw"
rotor5 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~6fpzJT4cluDLT18elrxCHMR"
rotor6 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~7gqAKU5dmvEMU29fmsyDINSW159cgkoswAEIM"
rotor7 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~8hrBLV6enwFNV30gntzEJOTX260dhlptxBFJNQTWZ"
rotor8 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~9isCMW7foxGOW4ahouAFKPUY37aeimquyCGKORUX13579ac"
rotor9 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnopqrstuvwxyz{|}~0jtDNX8gpyHPX5bipvBGLQVZ48bfjnrvzDHLPSVY24680bdef"

def xgcd(u, v):
  u1 = 1
  u2 = 0
  u3 = u
  v1 = 0
  v2 = 1
  v3 = v
  while v3 != 0:
    q = u3 / v3
    t1 = u1 - q * v1
    t2 = u2 - q * v2
    t3 = u3 - q * v3
    u1 = v1
    u2 = v2
    u3 = v3
    v1 = t1
    v2 = t2
    v3 = t3
  return u1, u2, u3

def inverse_mod(a, p):
  u1,v1,d = xgcd(a, p)
  return u1 if u1 > 0 else u1+p
  
def crt(n,p):
  r = len(p)
  L = reduce(lambda x,y: x*y, p)
  li = [L / x for x in p]
  vi = [inverse_mod(li[i], p[i]) for i in range(r)]
  return reduce(lambda x,y: x+y, map(lambda x,y,z: x*y*z, n,li,vi)) % L
    
def ec_add(P,Q,a,b,p):
  Px = P[0]
  Py = P[1]
  Qx = Q[0]
  Qy = Q[1]
  if P == [0,1]:
    return Q
  if Q == [0,1]:
    return P
  if P == Q:
    s = ((3*Px**2 + a)*inverse_mod(2*Py, p)) % p
    Rx = (s**2 - 2*Px)%p
    Ry = (-P[1] + s*(Px-Rx)) % p
    return [Rx,Ry]
  else:
    s = (Qy - Py)*inverse_mod(Qx - Px, p) % p
    Rx = (s**2 - Px - Qx)%p
    Ry = (s*(Px - Rx) - Py)%p
    return [Rx,Ry]

def ec_mul(P,e,a,b,p):
  Q = [0,1]
  for i in range(int(math.ceil(math.log(e,2)))):
    if e%2:
      Q = ec_add(Q,P,a,b,p)
    P = ec_add(P,P,a,b,p)
    e >>= 1
  return Q

def warmup(name):
  if len(name) > 10:
    name = name[0:10]
  else:
    while len(name) < 10:
      name = name + 'S'
  
  rotors = [rotor0,rotor1,rotor2,rotor3,rotor4,
      rotor5,rotor6,rotor7,rotor8,rotor9]
  
  rot = range(10)
  for i in range(10):
    rot[i] = rotors[i].find(name[i])
  
  serial = crt(rot, [len(rotors[i]) for i in range(10)])
  return serial
  
def crypto1(name):
  d = 65537
  n = 1821668788150059822966422307930288186476927434330004078983325993614616857
  e = 174725878413998504300527427786354881690797517767573630493566745566969857
  m = 0;
  for char in name:
    m = m*256 + ord(char);
  
  if m > n:
    m = m % n;
  
  return pow(m, e, n)
  
def crypto2(name):
  name_num = 0
  for char in name:
      name_num = name_num*256 + ord(char)

  name_num &= 2**64-1
  state = name_num
  for i in range(65537):
      state = (state >> 1) | ( (state&1) ^ (state >> 1)&1 ^ (state >> 3)&1 ^ (state >> 4)&1 ^ 1) << 63

  return state
  
def crypto3(name):
  order = 18446693477654742300
  dlog  = 1449402469971139457
  name_num = 0
  for char in name:
    name_num = name_num*256 + ord(char);
  return (dlog * name_num)%order

def crypto4(name):
  p =  6277101735386680763835789423207666416102355444459739541047
  a =  0
  b =  3
  o =  6277101735386680763835789423061264271957123915200845512077
  k = inverse_mod(13, o)
  
  name_x = 0;
  for char in sys.argv[1]:
    name_x = name_x*256 + ord(char)
  while 1:
    quadres = (name_x**3 + 3)%p
    name_y = pow(quadres, (p+1)/4, p)
    if pow(name_y, 2, p) == quadres:
      break;
    name_x += 1
  P1 = [name_x, name_y]
  P2 = ec_mul(P1,k,a,b,p)
  return "%d-%d" % (P2[0],P2[1])
  
def crypto5(name):
  a = 0
  b = 13
  p = 9524793152874449521
  x = 1223334444333221111
  o = 9524793149788155121
  g1 = [1,4577206343548535956]
  
  name_c = 0;
  for char in sys.argv[1]:
    name_c = name_c*256 + ord(char)
  S = ec_mul(g1, (x*name_c)%o, a,b,p)
  return "%d-%d" % (S[0],S[1])

if(len(sys.argv) != 2):
	print "Usage: ", sys.argv[0], " <name>"
	quit()
  
print "Warmup  : ", warmup(sys.argv[1])
print "Crypto 1: ", crypto1(sys.argv[1])
print "Crypto 2: ", crypto2(sys.argv[1])
print "Crypto 3: ", crypto3(sys.argv[1])
print "Crypto 4: ", crypto4(sys.argv[1])
print "Crypto 5: ", crypto5(sys.argv[1])