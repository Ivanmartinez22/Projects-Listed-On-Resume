// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Not16.tst

load OnesCounter.hdl,
output-file OnesCounter.out,
//compare-to OnesCounter.cmp,
output-list in%B1.3.1 out%B1.2.1;

set in %B010,
eval,
output;

set in %B101,
eval,
output;

set in %B000,
eval,
output;

set in %B111,
eval,
output;

set in %B110,
eval,
output;

set in %B001,
eval,
output;

set in %B011,
eval,
output;

set in %B100,
eval,
output;

