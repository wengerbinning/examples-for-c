#!/usr/bin/env perl

use strict;
use warnings;
use Env;

my $key;
my $val;
my $res;

foreach $key (sort keys %ENV) {
  $val = join(" = ", $key, $ENV{$key});
  $res = join("    ", $res, "<p>$val</p>\n");
}
 
# print $res;

print <<END;
Status: 200
Content-type: text/html

<!doctype html>
<html>
<head>
    <tilte>Perl CGI Result</title>
</head>

<body>

$res
 
</body>
</html>
END
