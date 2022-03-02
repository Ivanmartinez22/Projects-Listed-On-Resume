// File: mod.asm
// Author: Ivan Martinez
// Date: 10/14/2021
// Section: 505 
// E-mail: ivanattexas@tamu.edu 
// Description:
// The content of this file implements the mod program
@3
D = A

@0
M = D

@6
D = A

@1
M = D

@35
D = A

@2
M = D 

@0
D = M 
@a
M = D

@1
D = M 

@d
M = D

@2
D = M
@n
M = D 

@a
D = M 
@3
M = D

@n
D = M - 1

@END
D;JEQ

@n
M = M - 1

@d
D = M 
@END
D;JEQ

@counter 
M = 0

(LOOP)
	@counter
	M = M + 1
	@d
	D = M
	@3
	M = M + D
	@n
	D = M 
	@counter
	D = D - M
	@END
	D;JEQ
	@LOOP
	0;JMP
(END)
0;JMP

