// File: Fill.asm
// Author: Ivan Martinez
// Date: 10/14/2021
// Section: 505 
// E-mail: ivanattexas@tamu.edu 
// Description:
// The content of this file implements the fill program

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@0 // beginning of listening loop
@15
M = 0 // RAM15 is used for counting offset for screen reset to 0 on this line 
@KBD //Keyboad register or memory map
D = M 
@10
D;JGT // if key is pressed fill screen
@0
0;JMP // end of listening loop. loop back to listening loop or @0
@10 
// fill screen loop 
D = 0 // D set to zero used for offset
(LOOP2)
	@16384 // starting address of screen 
	A = A + D // incrementing with D 
	M = -1 // using complement to set bits to 11111...1111 i.e. writing black pixel
	D = D + 1 //D++ to change to next pixels
	@15 // storing offset 
	M = D
	@8193 // max offset for D or last valid screen map for writing to screen
	D = D - A // See if D == A
	@END2 // exit loop if D == A
	D;JEQ
	@15 // set D back to Offset
	D = M
	@LOOP2
	0;JMP // Goto LOOP
(END2)
@END2
@27 //Begining of listening loop
@15 // offset set to 0
M = 0
@KBD // Checking for keyboard release
D = M // D is set to M 
@36 // if no key is pressed jump to clear loop
D;JEQ
@27 //end of listening loop
0;JMP // loop back to listening loop or @27
@36
//Clear screen loop
D = 0 // D set to zero used for offset
(LOOP3)
	@16384// starting address of screen 
	A = A + D // incrementing with D 
	M = 0 // setting bits to 0 i.e. writing white
	D = D + 1 //D++ to change to next pixels
	@15// storing offset 
	M = D
	@8193 // max offset for D or last valid screen map for writing to screen
	D = D - A// See if D == A
	@END3// exit loop if D == A
	D;JEQ
	@15
	D = M // set D back to Offset
	@LOOP3
	0;JMP // Goto LOOP
(END3)
@END3
@0 //jump back to beginning since screen is clear to listen for a key press to fill
0;JMP
