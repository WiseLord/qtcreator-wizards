#!/usr/bin/perl -w

use strict;
use Getopt::Long;
use IO::File;
use File::Copy;
use File::Basename;

my $optHelp = 0;
my $optDryRun = 0;
my $optProjectName = 'MyProject';
my $optDevName = 'STM32F0XX';

my $USAGE=<<EOF;
Usage: generate.pl [--help] | [--dry-run]
                   [--project-name=<project name>]
                   [--stm32-dev=<stm32 device>]

STM32 project generation script.

EOF

my $argCount = scalar(@ARGV);

if ($argCount == 0 ||
    !GetOptions("help" => \$optHelp,
                "dry-run" => \$optDryRun,
                "project-name:s" => \$optProjectName,
                "stm32-dev:s" => \$optDevName)
    ||  $optHelp != 0) {
    print $USAGE;
    exit (1);
}

if ($optDryRun) {
    print $optProjectName."/extra/ldscripts/".$optDevName."_FLASH.ld";
} else {
	mkdir($optProjectName."/extra/ldscripts");
	copy(dirname(__FILE__)."/project/extra/ldscripts/".$optDevName."_FLASH.ld",
	      $optProjectName."/extra/ldscripts/".$optDevName."_FLASH.ld");
}
