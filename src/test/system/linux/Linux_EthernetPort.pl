#!/usr/bin/perl

use strict;
use warnings;

my $className="Linux_EthernetPort.instance";
my $INST_FILE;

my $IN=$ARGV[0];

if(defined $IN) {
  if($IN =~ /-rm/) {
    unlink("$className");
    exit 0;
  }
}


my @out=`cat /proc/net/dev | grep eth | sed s/:/' '/`;


if( !open($INST_FILE,'>', "$className")) {
  print "can not open $className\n"; 
  exit 0;
}

foreach my $out (@out) {
  my @val = split(' ',$out);

  my $state = `/sbin/ifconfig | grep -c $val[0]`;
  if($state==1) { $state=2; }
  elsif($state==0) { $state=3; }

  print $INST_FILE "$val[0]\n";
  print $INST_FILE "$state\n";
  print $INST_FILE "$state\n";
  print $INST_FILE "\n";
}
