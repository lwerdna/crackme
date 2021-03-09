#!/usr/local/bin/perl

use warnings;
use strict;

use CGI;
my $cgi = CGI->new();
print $cgi->header;

print "<html>\n";
my $msg = $cgi->param('liwfEIJFkefji3');

if($msg)
{
	open(FP, ">>log.txt")
		or die("Error writing to log.txt");

	print FP "$^T $msg\n";

	close(FP);

	print "<p>Yo, just logged -$^T $msg-</p>\n";
}
else
{

	print "<html>\n";
	print "<img src=astigmata.png style=\"float: right\">\n";
	print "<font color=red>It found it! At around 8:30AM Christmas eve the bruter reported 94240657. This is the value after translation from the ascii that the user types. You must enter \"76449502\".</font>\n";
	print "<h2>Live Astigmata Brute-Forcer Stats</h2>\n";

	print "<p>(<a href=\"http://crackmes.de/users/astigmata/bruteforceme1_astigmata/\">crackme link</a>)</p>\n";

	open(FP, "<log.txt")
		or die("Error opening log.txt");
	my @lines = <FP>;
	close(FP);

	shift @lines if($lines[0] =~ m/^$/);
	pop @lines if($lines[$#lines] =~ m/^$/);

	my $t0 = 0;
	my $t1 = 0;
	my $tN = 0;
	$lines[$#lines] =~ m/^(\d+)/;
	$t0 = $1;
	$lines[$#lines-1] =~ m/^(\d+)/;
	$t1 = $1;
	$lines[0] =~ m/^(\d+)/;
	$tN = $1;

	#print "t0: ".localtime($t0)."<br>\n";
	#print "t1: ".localtime($t1)."<br>\n";
	#print "tN: ".localtime($tN)."<br>\n";
	#print "line0: ".$lines[0]."<br>\n";


	my $spt = ($t0-$t1)/12288;
	my $tps = $spt ? 1/$spt : -1;
	printf "<h3>Last batch speed: %.04f seconds/trial (%04f trials/second)</h3>\n", $spt, $tps;

	$spt = ($t0-$tN)/ (12288 * scalar(@lines));
	$tps = $spt ? 1/$spt : -1;;
	printf "<h3>Average speed: %.04f seconds/trial (%04f trials/second)</h3>\n", $spt, $tps;

	my $total_done = 12288 * scalar(@lines);
	my $percent_done = ($total_done / 1000000);
	my $work_remaining = 100000000 - $total_done;
	my $percent_remaining = $work_remaining / 1000000;
	my $time_remaining = int($spt * $work_remaining);

	print "<h3>Trials completed: $total_done / 100000000 ($percent_done\%)</h3>\n";
	print "<h3>Trials remaining: $work_remaining ($percent_remaining\%)</h3>\n";
	print "<h3>Time remaining at average rate: $time_remaining seconds (target date: ".localtime($^T + $time_remaining).")</h3>\n";	

	print "<h3>Last 50 updates:</h3>\n";
	
	foreach my $line(reverse @lines)
	{
		next if $line =~ m/^$/;
		$line =~ m/^(\d+) (.*)$/;
		#print "line is: <b>$line</b><br>\n";
		print "<p>".localtime($1)." $2</p>\n";
	}

	close(FP);
}

print "</html>\n";


