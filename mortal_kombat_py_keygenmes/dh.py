#!/usr/bin/python

# Diffie Hellman challenge
#
# example name/serial pairs:
#
# knowledge/507214045860688507569039621
#        is/676757930239709232931683761
#     power/677520530474024396858850188
#    Mortal/686817964136950007668570596
#    Kombat/1099087011704959736789579354

import sys

# global parameters
prime = 1223334444555556666667777783
generator = 3
bobs_message = 814779647738427315424653119

# args?
if len(sys.argv) != 3:
    print "usage: ", sys.argv[0], " <name> <serial>";
    quit()

# convert name to number eg: "AAAA" -> 0x41414141
name = 0;
for char in sys.argv[1]:
    name = name*256 + ord(char);
shared_secret = pow(generator, name, prime) 

# convert serial to number eg: "1234" -> 1234
a = int(sys.argv[2], 10);

# process, check
if pow(bobs_message, a, prime) == shared_secret:
    print "good"
else:
    print "bad"
