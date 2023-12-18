#!/usr/bin/python

# Diffie Hellman challenge
#
# the challenge simulations a Diffie-Hellman key exchange
#
# you play the part of Alice, having secret key a (encoded in the serial)
#
# you and Bob must arrive at the same shared key (encoded in the name)
#

import sys

# global parameters

prime = 1223334444555556666667777783
generator = 3
bobs_message = 814779647738427315424653119

# remember that Bob's message to you is generator^b, where b is his secret
#
# let's find b by asking the question:
#
# "to what power must the generator be raised to equal Bob's message?"
#
# this is the discrete logarithm problem (DLP) and is difficult in this group
# 
# you can use any number of tools or implement any number of algorithms to
# solve this, a good starting point is: http://en.wikipedia.org/wiki/Discrete_logarithm

b = 8675309

# you should of course verify that generator^b = bobs_message (Mod p)

# now, you are trying to provide a so that:
#
# bobs_message ^ a = shared_secret 
#
# substitute in bobs_message and shared_secret:
#
# (generator^b) ^ a = (generator^name)
# generator ^ (ab) = generator ^ name
#
# equating exponents:
#
# ab = name (Mod p-1)
#
# isolating a:
#
# a = b^-1 * name (Mod p-1)
#
# so we reduced key generation to a simple multiply!

b_inverse = 694146710323678502410938469

# args?
if len(sys.argv) != 2:
    print "usage: ", sys.argv[0], " <name>";
    quit()

# convert name to number eg: "AAAA" -> 0x41414141
name = 0;
for char in sys.argv[1]:
    name = name*256 + ord(char);

# generate, print serial
print (b_inverse * name) % (prime-1)
