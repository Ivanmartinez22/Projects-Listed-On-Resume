// File: lcd.asm
// Author: Ivan Martinez
// Date: 10/14/2021
// Section: 505 
// E-mail: ivanattexas@tamu.edu 
// Description:
// The content of this file implements the lcd program


//Using Euclidean algorithm to find the larget common divisor of two positive integers
//Assuming RAM[R0] stores the first integer and RAM[R1] stores the second integer
//RAM[R2] stores the result
//See the lcd.cmp,lcd.tst file to understand the input and output structure
//Put your code here
@0
D = M // Setting D to value of RAM0
@2 
M = D // Setting M at 2 to D
@1
D = M // Setting D to value of RAM1
@2
D = M + D // if A and B == 0 return 0
@107
D;JEQ // if D == 0 goto end of program
// if A and B == 0 return 0
//base case
@1
D = M// Setting D to value of RAM1
@2
M = D// Setting M at 2 to D
@0
D = M // Setting D to value of RAM0
@107
D;JEQ // if R0 == 0 goto end of program 
//If A = 0 then GCD(A,B)=B, since the GCD(0,B)=B, and we can stop. from khan academy
//base case
@0
D = M// Setting D to value of RAM0
@2
M = D// Setting M at 2 to D
@1
D = M // Setting D to value of RAM1
@107
D;JEQ // if R0 == 0 goto end of program
//If B = 0 then GCD(A,B)=A, since the GCD(A,0)=A, and we can stop. from khan academy
//base case
@0
D = M // setting D = M at 0
@3
M = D // storing value of RAM0 in RAM3 for later use 
@1
D = M // setting D = M at 1
@4
M = D // storing value of RAM0 in RAM4 for later use
@0
D = M //setting D = M at 0
@5
M = D // setting RAM5 to D
@1
D = M // D set to M at 1
@5 // register used to check if value at RAM0 is less than RAM1
M = M - D // operation used to check if value at RAM0 is less than RAM1
@5 
D = M 
// storing RAM0 and RAM1 in RAM4 and RAM5 for later use 
@49 // see if variables need flipping 
// variables need to be flipped to ensure b can subtract from a
D;JLT
@60 // if no need to flip skip onto later operations i.e. regular cases 
0;JMP
@49 // Flipping variables to  make sure b can always subract from a 
@3 // using value stored in RAM3 to flip RAM1 to value of RAM0
D = M // Setting D to M at 3
@1 
M = D // setting RAM1 to D 
@4// using value stored in RAM4 to flip RAM0 to value of RAM1
D = M // Setting D to M at 4
@0
M = D // setting RAM0 to D 
@60
0;JMP
@60//remainder finding operations loop
//loop pseudo code:
//very similar to logic of mod.asm 
//While(R0 > R1)
//  if(R0 < R1)
//     R2 = R0
//     Break
//  R0  = R0 - R1
//loop is used to find remainder
(LOOP)
	@1 // A = 1
	D = M  // Setting D to the value of R1
	@0 // A = 0
	M = M - D // R0  = R0 - R1
	@0
	D = M 
	@2 // A = 2
	M = D// M is set to R0
	@1 // A = 1
	D = M  // Setting D to the value of R1
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
//variables are then switched to be sent through the remainder finding loop
//i.e. RAM0 is set to the value of RAM1 from previous loop and RAM1 is set to the remainder from previous loop
@1 
D = M // D is set to M at 1
@0
M = D // RAM0 is set to D
@2 // remainder storage 
D = M // D is set to M at 2
@1 
M = D // RAM1 is set to D
@1
D = M // D is set to M at 1
@94//if RAM1 == 0 the base case has been reached and the lcd has been found
//feeding loop is exited 
D;JEQ
@60
0;JMP
@94 // output handling 
//since the values of RAM0 and RAM1 were changed by the loops they must be changed back to their original values for their correct values to be outputted 
@0//holds value of lcd
D = M // D is set to M at 0
@2//lcd must go here 
M = D // writing lcd into M at 2
@3 
D = M // D is set to M at 3
@0 // changing RAM0 to original value 
M = D // RAM0 is set to D
@4
D = M // D is set to M at 4
@1 // changing RAM1 to original value 
M = D // RAM1 is set to D
@107//jump point for base cases aka end of program 
0;JMP // Infinite loop
