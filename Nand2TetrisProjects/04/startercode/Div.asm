// File: Div.asm
// Author: Ivan Martinez
// Date: 10/14/2021
// Section: 505 
// E-mail: ivanattexas@tamu.edu 
// Description:
// The content of this file implements division in hack assembly


// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Div.asm

// Divides R0 by R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// R0=2, R1=2, Div.asm file should store R2=1


// Put your code here.
//Goal: R0/R1 -> R2
//R2 = 0
//While(R0 > R1)
//  R0  = R0 - R1
//  R2  = R2 + 1
//In this program I used R0 and R1 as counters but for this test script the RAM0 and RAM1 were reset to their previous values 
//But the values could be saved in other RAMS such as RAM 4 and 5 and the values of RAM0 and RAM1 reset through the use of RAM 4 and 5
@2 // A = 2
M = 0 // setting R2 to zero 

@1 // A = 1
// setting register D to the value of R1
D = M

(LOOP)
	@0 // A = 0
	D = M 
	@END 
	D;JEQ // if R0 == 0 goto END
	@1 // A = 1
	D = M  // Setting D to the value of R1
	@0 // A = 0
	M = M - D // R0  = R0 - R1
	@2 // A = 2
	M = M + 1 // R2 = R2 + 1 
	@0 // A = 0
	D = D - M // R1 = R1 - R0
	@END 
	D;JGT // if R1 > 0 goto END 
	@1 // A = 1
	D = M  // Setting D to the value of R1
	@LOOP
	0;JMP // Goto LOOP
(END)
	@END
	0;JMP // Infinite loop

