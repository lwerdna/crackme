#!/usr/bin/python

# rsa1 verifies serials by testing that decrypt(serial) == name
#
# to decrypt, only PUBLIC information necessary stored in rsa1 
#
# only private key holder can produce serial = encrypt(name)
#
# you must break this cryptosystem (parameter n is easily factorable) to forge serials

import sys

# public rsa parameters
d = 65537
n = 152415787532388368909312594615759791673

# how big is the multiplicative group Z_n ?
#
# it is exactly the quantity of numbers coprime to n
#
# but we cannot know what is coprime without knowing divisors of n 
#
# so factor n = 12345678901234567891 * 12345678901234568003

p = 12345678901234567891
q = 12345678901234568003

# every multiple of p is NOT coprime (of which there are q-1)
# every multiple of q is NOT coprime (of which there are p-1)
# there are thus (n-1) - (q-1) - (p-1) coprime numbers
#
# = (pq-1) - (q-1) - (p-1)
# = pq - 1 - q + 1 -p + 1
# = pq - q - p + 1
# = (p-1)(q-1)

group_size = 152415787532388368884621236813290655780

# since we know the group size, we can easily calculate multiplicative inverse
#
# e = d^1 (mod group_size)

e = 121073071683722759420379046775102789873

# and you should test that these are inverses by verifying d * e (Mod group_size) = 1
#
# now encryption is simple: treat name as member of group, exponentiate by e

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

# encrypt
print pow(m, e, n)

