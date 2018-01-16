#!/usr/bin/perl

use Tk;
use Socket;
use IO::Socket::INET;
use Thread;
use Fcntl;

$|=1;

my($socket,$data);

$socket=new IO::Socket::INET(
PeerAddr=>'127.0.0.1:15000',
Proto=>'udp')
 or die "error";
$flags|=O_NONBLOCK;
fcntl($socket,F_SETFL,$flags);

$mw=MainWindow->new();

$mw->title("Scale");
$mw->minsize(150,350);
my $a;
print $a;



$scale=$mw->Scale(	-orient=>"v",-length=>300,-width=>100,-from=>1000,-to=>5,
				-variable=>\$a,-command => \&fgv)
				->pack();

MainLoop();

sub fgv
{

print $a."\n";
#$data=<>;
$data=$a;

chomp($data);
$socket->send($data);

$data=<$socket>;
print "rec.data:$data\n";

#print "end";
#$socket->close();

}









