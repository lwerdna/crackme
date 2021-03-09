use warnings;
use strict;

use NTRU;

# this dude's from 0040C000 in the crackme
# notice df = 4 (there are (df) coeffs==1 and (df-1) coeffs==-1)
my @f = ( 0, 1, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,-1, 1, 0, 0, 0, 0, 1,-1, 0);
# and this one's from 0040C080
my @f_inv_3 = ( 0, 1, 0, 1, 2, 2, 1, 2, 1, 2, 2, 0, 0, 0, 0, 1, 2, 1, 0, 2, 1, 2, 2, 0, 0, 0, 2, 1, 2, 0, 1, 0);
# and this one we calculated
my @f_inv_32 = (-3, -15, 11, 13, 13, -2, -15, -8, 0, -14, -5, -1, -15, -15, -5, -1, -12, -11, 15, -11, -2, -14, 5, 6, -14, -11, -14, -11, 9, 13, 1, -14);

print "f * f^-1 (mod 3):\n";
$NTRU::g_modulus = 3;
my @r = NTRU::multiply(\@f, \@f_inv_3);
print "product: @r\n";

print "\n";

print "f * f^-1 (mod 32):\n";
$NTRU::g_modulus = 32;
@r = NTRU::multiply(\@f_inv_32, \@f);
print "product: @r\n";

