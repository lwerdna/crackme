my $info = "Keygen to BUBlic's Security Pow-1 ... andrewl ... 1/26/2009";

use warnings;
use strict;
use NTRU;
use Digest::MD5 qw(md5);

# POLYNOMIAL FROM HASH OF USER
my $name = $ARGV[0] || 'BUBlic'; 
my $md5_raw = md5($name);
my @md5_bytes = unpack('C16', $md5_raw);
my @poly_hash;
foreach(@md5_bytes)
{
    push(@poly_hash, $_ & 1);
    push(@poly_hash, ($_ >> 4) & 1);
}

# ADD TO THE POLY HASH
$NTRU::g_modulus = 32;
my @poly_serial = NTRU::add(\@poly_hash, [23, 19, 1, 7, 7, 26, 19, 8, 0, 22, 17, 29, 19, 19, 17, 29, 28, 31, 13, 31, 26, 22, 15, 18, 22, 31, 22, 31, 27, 7, 3, 22]);

# MAKE SERIAL
my $serial;
my @alphabet = split(//, '0123456789ABCDEFGHIJKLMNOPQRSTUV');
foreach(@poly_serial)
  { $serial .= $alphabet[$_]; }

# OUTPUT
print "\n$info\n\n";
print "   name: $name\n";
print " serial: $serial\n";

