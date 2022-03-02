// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Not16.tst

load ThreeOneDetector.hdl,
output-file ThreeOneDetector.out,
//compare-to ThreeOneDetector.cmp,
output-list a%B1.8.1 out%B1.1.1;

set a %B00011101,
eval,
output;

set a %B10101011,
eval,
output;

set a %B11110000,
eval,
output;

