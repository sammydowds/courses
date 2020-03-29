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

//Psuedo code
//Loop
//Check if keyboard register is null, if so jump back to top of loop
//if keyboard is not null, then output screen completely black

@8192 //words (16bits) in MAP
D=A
@words
M=D

(KBDFEED)
  @i
  M=0  //setting counter to zero
  @KBD
  D=M   //reading kbd memory
  @WHITE
  D;JEQ //if kbd mem is 0 make screen white
  @BLACK
  0;JMP

(BLACK)
  @i
  D=M
  @words
  D=D-M   //if this is 0, then have looped through all registers in screen map
  @KBDFEED
  D;JGE
  @i
  D=M
  @SCREEN
  A=A+D
  M=-1   //saving location of screen + i to black

  @i
  M=M+1  //incrementing i
  @BLACK
  0;JMP  //goto loop

(WHITE)
  @i
  D=M
  @words
  D=D-M   //if this is 0, then have looped through all registers in screen map
  @KBDFEED
  D;JGE

  @i
  D=M
  @SCREEN
  A=A+D
  M=0   //saving location of screen + i to black

  @i
  M=M+1  //incrementing i
  @WHITE
  0;JMP  //goto loop
