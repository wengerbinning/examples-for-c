#!/usr/bin/env ruby
# -*- coding: UTF-8 -*-

# Global Variable
$fixnum_min = -2**30
$fixnum_max =  2**30 - 1
$fixnum = $fixnum_max + 1

$bignum_min = -2**62
$bignum_max =  2**62 - 1
$bignum = $bignum_max + 1

$bin = 0b101010
$oct = 012
$dec = 1_012
$hex = 0x0a0a
$chr = "a".ord

$float = 123.456
$float_e = 1.0E6
$float_e_1 = 1.0E-6



puts "min fixnum: #$fixnum_min, max fixnum: #$fixnum_max, fixnum #$fixnum;"
puts "min bignum: #$bignum_min, max bignum: #$bignum_max, bignum #$bignum;"

puts "bin #$bin, oct #$oct, dec #$dec, hex #$hex, chr #$chr"

puts "float #$float, float_e #$float_e, float_e_1 = #$float_e_1"




# +, -, *, /, ** 
