#!/usr/bin/python

# XTEA challenge
#
# example name/serial pairs:
#
# knowledge/4965306580672701350
#        is/7280703883267641400
#     power/9946186638386043440
#    Mortal/13205294812230278731
#    Kombat/725838670719994951

import sys

def xtea_encrypt(v):
    k = [0xDEADBEEFL, 0xCAFEBABEL, 0xFACEFEEDL, 0xD15EA5EDL]

    for i in range(1000):
        k[i % 4] ^= k[(i+1) % 4]

    sum, delta, mask = 0L, 0x9e3779b9L, 0xffffffffL
    for i in range(32):
        v[0] = (v[0] + (((v[1]<<4 ^ v[1]>>5) + v[1]) ^ (sum + k[sum & 3]))) & mask
        sum = (sum + delta) & mask
        v[1] = (v[1] + (((v[0]<<4 ^ v[0]>>5) + v[0]) ^ (sum + k[sum>>11 & 3]))) & mask
  
# args?
if len(sys.argv) != 3:
    print "usage: ", sys.argv[0], " <name> <serial>";
    quit()

# convert name to a block
temp = 0;
for char in sys.argv[1]:
    temp = temp*256 + ord(char);
name_L = (temp >> 32) & 0xFFFFFFFF
name_R = (temp & 0xFFFFFFFF)

# convert serial to block 
temp = int(sys.argv[2], 10);
serial_L = (temp >> 32) & 0xFFFFFFFF
serial_R = (temp & 0xFFFFFFFF)

# process, check
block = [serial_L, serial_R]
xtea_encrypt(block)

if block[0] == name_L and block[1] == name_R: 
    print "good"
else:
    print "bad"
