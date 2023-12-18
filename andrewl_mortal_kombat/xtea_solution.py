#!/usr/bin/python

import sys

# the challenge just encrypt's the serial to see that it equals the name:
#
# encrypt(serial) = name
#
# thus, to generate the serial, we compute decrypt(name), so the equation becomes:
#
# encrypt(decrypt(name)) = name
# name = name
#

# notice that there is no key parameter, it is calculated on the fly
#
# you may replicate this on-the-fly calculation when implementing the
# xtea decrypt function, or discover the resulting calculation with a
# print statement: 
#
# def xtea_encrypt(v):
#     k = [0xDEADBEEF, 0xCAFEBABE, 0xFACEFEED, 0xD15EA5ED]
# 
#     for i in range(1000):
#         k[(3*i) % 4] ^= k[(5*i) % 4]
# 
#     print map(lambda x: hex(x), k) # <------ !!!! INSERTED PRINT !!!!
#     ....
#
# and we find that the effective key was:

k = [0xee9dfabcL, 0xe16ee1beL, 0x3fc35f51L, 0xf53de5efL]

# now just grab an implementation of XTEA_encrypt (http://en.wikipedia.org/wiki/XTEA)
# 
def xtea_decrypt(v):
    delta, mask, sum = 0x9e3779b9L, 0xffffffffL, 0xc6ef3720L
    for i in range(32):
        v[1] = (v[1] - (((v[0]<<4 ^ v[0]>>5) + v[0]) ^ (sum + k[sum>>11 & 3]))) & mask
        sum = (sum - delta) & mask
        v[0] = (v[0] - (((v[1]<<4 ^ v[1]>>5) + v[1]) ^ (sum + k[sum & 3]))) & mask

# args?
if len(sys.argv) != 2:
    print "usage: ", sys.argv[0], " <name>";
    quit()

# convert name to a block
temp = 0;
for char in sys.argv[1]:
    temp = temp*256 + ord(char);
name_L = (temp >> 32) & 0xFFFFFFFF
name_R = (temp & 0xFFFFFFFF)

# process
block = [name_L, name_R]
xtea_decrypt(block)

# print as a decimal number
print (block[0] * (2**32) + block[1])
