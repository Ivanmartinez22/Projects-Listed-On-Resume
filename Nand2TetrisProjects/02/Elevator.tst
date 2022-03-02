// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/Add16.tst

load Elevator.hdl,
output-file Elevator.out,
//compare-to Add16.cmp,
output-list c%B1.2.1 r%B1.2.1 next%B1.2.1;

set c %B00,
set r %B10,
eval,
output;

set c %B00,
set r %B01,
eval,
output;

set c %B11,
set r %B10,
eval,
output;

set c %B11,
set r %B01,
eval,
output;

set c %B01,
set r %B00,
eval,
output;

set c %B10,
set r %B00,
eval,
output;
