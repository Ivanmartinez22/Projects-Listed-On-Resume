// File: mod.asm
// Author: Ivan Martinez
// Date: 10/14/2021
// Section: 505 
// E-mail: ivanattexas@tamu.edu 
// Description:
// The content of this file implements the mod program


//This asm computes the modular of two numbers
//Assuming R0 stores the number a and R1 stores the number n
//so in normal programming language, the goal is to compute RAM[R0]%RAM[R1]
//The result will be put to R2
//Assuming RAM[R1] is positive integer and RAM[R0] is non-negative integer

//See the mod.cmp,mod.tst file to understand the input and output structure

//Put your code here

// Put your code here.
//Goal: R0%R1 -> R2
//Base case1: if a = b return 0
//Base case2: if a < b return a
//Base case3; if a == 0 return 0
//LOOP PSEUDO CODE FOR MAIN CASES
//R2 = 0
//While(R0 > R1)
//  if(R0 < R1)
//     R2 = R0
//     Break
//  R0  = R0 - R1

//RAM3 and RAM4 serve as stores for the original values of RAM0 and RAM1
@0
D = M // D = R0

@2 // A = 2
M = D // setting R2 to R0
//For use in base case

@0
D = M // D = R0

@3 // storing value of R0 in R3
M = D

@1
D = M 

@4 // storing value of R1 in R4
M = D 

@1 // A = 1
// setting register D to the value of R1
D = M

@0 // seeing if R0 < R1 
D = M - D



@END 
D;JLT // if R0 < 0 goto END
//base case 

@2
M = 0

@END
D;JEQ // if R0 == R1 goto End
//base case


(LOOP)
//using RAM3 to not modify RAM0
	@0 // A = 0
	D = M 

	@END 
	D;JEQ // if R0 == 0 goto END
	//Base case

	@1 // A = 1
	D = M  // Setting D to the value of R1

	@3 // A = 0
	M = M - D // R0  = R0 - R1

	@3
	D = M 


	@2 // A = 2
	M = D// M is set to R0

	@1 // A = 1
	D = M  // Setting D to the value of R1

	@3 // A = 0
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

