
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/FullAdder.tst

load LeftLogicBitshift.hdl,
output-file LeftLogicBitshift.out,
//compare-to FullAdder.cmp,
output-list x%B1.16.1 y%B1.16.1 out%B1.16.1;

set x %B0000000001000100,
set y %B0000000000000001,
eval,
output;

//set c 1,
//eval,
//output;
//
//set b 1,
//set c 0,
//eval,
//output;
//
//set c 1,
//eval,
//output;
//
//set a 1,
//set b 0,
//set c 0,
//eval,
//output;
//
//set c 1,
//eval,
//output;
//
//set b 1,
//set c 0,
//eval,
//output;
//
//set c 1,
//eval,
//output;
