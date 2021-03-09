use warnings;
use strict;

use NTRU;
$NTRU::g_modulus = 3;

sub pp_compact
{
    my @p = @{$_[0]};

    print $p[$_] foreach(0..$#p);
}

# i want to generate an addition and multiplication
# table for all NTRU polys with N=3 (max degree 2)
# and coefficients mod 3
#

# make all polys
my @polys;

foreach my $i(0..2)
{
    foreach my $j(0..2)
    {
        foreach my $k(0..2)
        {
            push(@polys, [$k, $j, $i]);
        }
    }
}

# addition table
print "Addition table:\n\n";

print "     "; # 5 spaces
foreach(0..26)
{
    print ' ';
    pp_compact($polys[$_]);
    print ' ';
}
print "\n     ";
print "-----" foreach(0..26);
print "\n";

foreach my $row(0..26)
{
    pp_compact($polys[$row]);
    print ' |';

    foreach my $col(0..26)
    {
        my @r = NTRU::add($polys[$row], $polys[$col]);
        print ' ';
        pp_compact(\@r);
        print ' ';
    }

    print "\n";
    print "    |\n";
}

# intercession
print "\n\n";

# multipl. table
print "Multiplication table:\n\n";

print "     "; # 5 spaces
foreach(0..26)
{
    print ' ';
    pp_compact($polys[$_]);
    print ' ';
}
print "\n     ";
print "-----" foreach(0..26);
print "\n";

foreach my $row(0..26)
{
    pp_compact($polys[$row]);
    print ' |';

    foreach my $col(0..26)
    {
        my @r = NTRU::multiply($polys[$row], $polys[$col]);
        print ' ';
        pp_compact(\@r);
        print ' ';
    }

    print "\n";
    print "    |\n";
}

#my @r = NTRU::multiply(\@a, \@b);
#my $s = NTRU::dotprod(\@a, \@b);

#print "r is: @r\n";
#print "s is: $s\n";
