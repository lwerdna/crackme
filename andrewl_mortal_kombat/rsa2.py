#!/usr/bin/python

# rsa challenge: small variation
# 
# example name/serial pairs:
#
# knowledge/257014932647022476629105944633281615089141156845896379995
#        is/1329069310718104464780466755268688813797593879660919420348
#     power/534076957670713822340842061309354377305560973801889229849
#    Mortal/1087928536645949014695914711277849014560566619636186179555
#    Kombat/463667786161528797874335174690684435030139371861878224217

import sys

# globals
d = 65537
n = 1881676372353657811661123145248487672842656756506225389209

# args?
if len(sys.argv) != 3:
    print "usage: ", sys.argv[0], " <name> <serial>";
    quit()

# convert name to number eg: "AAAA" -> 0x41414141
m = 0;
for char in sys.argv[1]:
    m = m*256 + ord(char);

if m > n:
    m = m % n;

# convert serial to number eg: "1234" -> 1234
c = int(sys.argv[2], 10);

# process, check
if pow(c, d, n) == m:
    print "good"
else:
    print "bad"
