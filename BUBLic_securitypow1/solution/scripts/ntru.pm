package NTRU;

use warnings;
use strict;

our $g_modulus = 3;

sub dotprod
{
    my @a = @{$_[0]};
    my @b = @{$_[1]};
    my $sum = 0;

    foreach(0..$#a)
    {
        $sum += $a[$_] * $b[$_];
    }

    return $sum;
}

sub multiply
{
    my @a = @{$_[0]};
    my @b = @{$_[1]};

    my $len = scalar(@a);
    #print "len is $len\n";

    my @r;
    my @t = reverse @b;

    foreach(0..$len-1)
    { 
        #print "@t ==rotate==> ";
        @t = ($t[$len-1], @t[0..$len-2]);
        #print "@t\n";
        #print join(',', @t), "\n";
        $r[$_] = dotprod(\@a, \@t) % $g_modulus;
    }

    return @r;
}

sub add
{
    my @a = @{$_[0]};
    my @b = @{$_[1]};

    my $len = scalar(@a);

    my @r;

    foreach(0..$len-1)
    { 
        $r[$_] = ($a[$_] + $b[$_]) % $g_modulus;
    }

    return @r;
}

1;

