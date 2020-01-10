#!/usr/bin/perl

use strict;
use warnings;

my $className="Linux_IPProtocolEndpoint.instance";
my $INST_FILE;

my $IN=$ARGV[0];

if(defined $IN) {
  if($IN =~ /-rm/) {
    unlink("$className");
    exit 0;
  }
}


my @out=`cat /proc/net/dev | grep -E 'eth|lo|tr|sit' | sed s/:/' '/`;


if( !open($INST_FILE,'>', "$className")) {
  print "can not open $className\n"; 
  exit 0;
}

foreach my $out (@out) {
  my @val = split(' ',$out);
  my $ip='NULL';
  my $mask='NULL';

  my $state = `/sbin/ifconfig | grep -c $val[0]`;
  if($state==1) { $state=2; }
  elsif($state==0) { $state=3; }

  my $line = `/sbin/ifconfig $val[0] | grep 'inet addr'`;
  my @addr = split(' ',$line);
  foreach my $addr (@addr) {
    my @sv = split(':',$addr);
    $ip = $sv[1] if($addr =~ /addr/i);
    $mask = $sv[1] if($addr =~ /mask/i);
  }

  print $INST_FILE "IPv4_$val[0]\n";
  print $INST_FILE "$state\n";
  print $INST_FILE "$state\n";
  print $INST_FILE "$ip\n";
  print $INST_FILE "$mask\n";
  print $INST_FILE "\n";
}
