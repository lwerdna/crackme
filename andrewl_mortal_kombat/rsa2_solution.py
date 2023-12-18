#!/usr/bin/python

import sys

# public rsa parameters
d = 65537
n = 1881676372353657811661123145248487672842656756506225389209

# again we seek the mult. group size (number of coprimes)
#
# we can't test if a number is coprime until we know n's factors
#
# n = 12345678901234567891 * 12345678901234568003 * 12345678901234568033

p = 12345678901234567891
q = 12345678901234568003
r = 12345678901234568033

# uh oh! three factors instead of two? do we run scared? 
#
# no, continue with getting the group size...
#
# every p'th number is NOT coprime and NOT a group elem, so 1/p of n is eliminated
# every q'th number is "   "       "   "   " "     "   , "  1/q "  " "  "
# every r'th number is "   "       "   "   " "     "   , "  1/r "  " "  "
#
# leaving n*(1-1/p)*(1-1/q)*(1-1/r)
#
# see "Euler's product formula" at http://en.wikipedia.org/wiki/Euler's_totient_function

group_size = 1881676372353657811203875782651322564028299238350304024960

# find d's inverse... e = d^-1 (Mod group_size)

e = 1198367463101713073897605435346459269991198156923035680513

# again, verifying inverse relationship is good idea here
# indeed, e*d = 1 (Mod group_size)

# and like before, treat the plaintext as an element and exponentiate to encrypt

# args?
if len(sys.argv) != 2:
    print "usage: ", sys.argv[0], " <name>";
    quit()

# convert name to number eg: "AAAA" -> 0x41414141
m = 0;
for char in sys.argv[1]:
    m = m*256 + ord(char);

if m > n:
    m = m % n;

# calculate, print
print pow(m, e, n)
