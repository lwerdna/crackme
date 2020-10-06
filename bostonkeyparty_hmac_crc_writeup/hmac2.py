#!/usr/bin/env python

import sys

def to_bits(length, N):
  return [int(i) for i in bin(N)[2:].zfill(length)]

def from_bits(N):
  return int("".join(str(i) for i in N), 2)

# x^64 + x^63 + x^62 + x^61 + x^59 + x^58 + x^57 + x^56 + x^55 + x^54 + x^53 + 
# x^52 + x^50 + x^49 + x^46 + x^45 + x^44 + x^43 + x^42 + x^38 + x^37 + x^36 + 
# x^34 + x^33 + x^32 + x^31 + x^30 + x^28 + x^24 + x^21 + x^20 + x^19 + x^13 + 
# x^12 + x^10 + x^8 + x^7 + x^6 + x^5 + x^4 + x^2 + x + 1
# or
# 11110111111110110011111000111011111010001001110000011010111110111
CRC_POLY = to_bits(65, (2**64) + 0xeff67c77d13835f7)
# '0b1010101110101101110111101010110110111110111011110001110111101010'
# initial CRC result
CONST = to_bits(64, 0xabaddeadbeef1dea) # "a bad deadbeef idea"

def crc_rev():
   
  mesg += CONST
  shift = 0
  while shift < len(mesg) - 64:
    # if bit is set
    if mesg[shift]:
      # xor all 65 across
      for i in range(65):
        mesg[shift + i] ^= CRC_POLY[i]

    shift += 1
  return mesg[-64:]

def crc(mesg):
  #print "crc: ", mesg
  mesg += CONST
  shift = 0
  while shift < len(mesg) - 64:
    # if bit is set
    if mesg[shift]:
      # xor all 65 across
      for i in range(65):
        mesg[shift + i] ^= CRC_POLY[i]

    shift += 1
  return mesg[-64:]

INNER = to_bits(8, 0x36) * 8
OUTER = to_bits(8, 0x5c) * 8

def xor(x, y):
  return [g ^ h for (g, h) in zip(x, y)]

def hmac(h, key, mesg):
  #print "key: ", key
  #print "mesg: ", mesg
  return h(xor(key, OUTER) + h(xor(key, INNER) + mesg))

PLAIN_1 = "zupe zecret"
PLAIN_2 = "BKPCTF"

def str_to_bits(s):
  return [b for i in s for b in to_bits(8, ord(i))]

def bits_to_hex(b):
  return hex(from_bits(b)).rstrip("L")

if __name__ == "__main__":
#  print str_to_bits(PLAIN_1)
#  print INNER
#  print OUTER
#  print CONST
#  print CRC_POLY
#  sys.exit(-1)
  with open("key.txt") as f:
    KEY = to_bits(64, int(f.read().strip("\n"), 16))
  print PLAIN_1, "=>", bits_to_hex(hmac(crc, KEY, str_to_bits(PLAIN_1)))
  print "BKPCTF{" + bits_to_hex(hmac(crc, KEY, str_to_bits(PLAIN_2))) + "}"
