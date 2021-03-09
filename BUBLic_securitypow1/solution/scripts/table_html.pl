use warnings;
use strict;

use NTRU;
$NTRU::g_modulus = 3;

sub pp_compact
{
    my @p = @{$_[0]};

    print $p[$_] foreach(0..$#p);
}

sub pp_html
{
    my @p = @{$_[0]};

    my $color = $p[0]*(255/3);
    $color = 256*$color + ($p[1] * 255/3);
    $color = 256*$color + ($p[2] * 255/3);
    $color = sprintf("#%06X", $color);

    print "<td bgcolor=$color>";
    print $p[$_] foreach(0..$#p);
    print "</td>";
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

print "<table>\n";
print "<tr>\n";
print "<th>+</th>\n";
foreach(0..26)
{
    print '<td><u>';
    pp_compact($polys[$_]);
    print "</u></td>\n";
}
print "</tr>\n";

foreach my $row(0..26)
{
    print "<tr>";

    print '<td><u>';
    pp_compact($polys[$row]);
    print "</u></td>\n";

    foreach my $col(0..26)
    {
        my @r = NTRU::add($polys[$row], $polys[$col]);
        pp_html(\@r);
    }

    print "</tr>\n";
}

print "</table>\n";

# intercession
print "<br><br>\n";

# multipl. table
print "Multiplication table:\n\n";

print "<table>\n";
print "<tr>\n";
print "<th>+</th>\n";
foreach(0..26)
{
    print '<td><u>';
    pp_compact($polys[$_]);
    print "</u></td>\n";
}
print "</tr>\n";

foreach my $row(0..26)
{
    print "<tr>";

    print '<td><u>';
    pp_compact($polys[$row]);
    print "</u></td>\n";

    foreach my $col(0..26)
    {
        my @r = NTRU::multiply($polys[$row], $polys[$col]);
        pp_html(\@r);
    }

    print "</tr>\n";
}

print "</table>\n";

