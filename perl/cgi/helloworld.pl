#!/usr/bin/env perl

use strict;
use warnings;
use Env;

my $key;
my $val;
my $res;
my $buffer;

foreach $key (sort keys %ENV) {
  $val = join(" = ", $key, $ENV{$key});
  $res = join("    ", $res, "<p>$val</p>\n");
}

read (STDIN, $buffer, $ENV{'CONTENT_LENGTH'});


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

  <div>
    <h2>CGI Environment</h2>
$res
  </div>
  <div>
     <h2>CGI Data</h2>
$buffer
  </div>
</body>
</html>
END
