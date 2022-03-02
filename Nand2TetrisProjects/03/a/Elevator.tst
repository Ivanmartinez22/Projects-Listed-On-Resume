// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/RightArithmeticBitshift.tst

//Important test Cases include:
// load = 0, in = 1, tick, tock, output shift by 1 bit
// load = 1, in = 0, tick, tock, output shift by 1 bit and MSB is replaced with 0
// load = 1, in = 1, tick, tock, output shift by 1 bit and MSB is replaced with 1
// load = 0, in = 0, tick, tock, output shift by 1 bit
// load = 1, in = 1, reset = 1, tick, tock, output becomes 0000

load Elevator.hdl,
output-file Elevator.out,
//compare-to RightArithmeticBitshift.cmp,
output-list u%B1.1.1 d%B1.1.1 ps%B1.1.1 n%B1.1.1 b%B1.1.1;


set u 0,
set d 0,
tick,
tock,
output;

set u 0,
set d 0,
tick,
tock,
output;


set u 0,
set d 1,
tick,
tock,
output;

set u 0,
set d 1,
tick,
tock,
output;

set u 1,
set d 0,
tick,
tock,
output;

set u 1,
set d 0,
tick,
tock,
output;

set u 1,
set d 1,
tick,
tock,
output;

set u 1,
set d 1,
tick,
tock,
output;