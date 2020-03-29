// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Psuedo code
//for loop which runs R[1] number of times
//R[2] = R[2] + R[0]

@i  //creating i for loop
M=0 //setting i = 1

@R2
M=0 //zeroing out Register 2

(LOOP)
  @i
  D=M //D=i
  @R1
  D=D-M //if D-M is neg or zero, continue to run
  @END
  D;JGE
  @R0
  D=M //register 0 saved as D
  @R2
  M=M+D //add R0 + R2, run for R1 loops
  @i
  M=M+1
  @LOOP
  0;JMP //goto Loop
(END)
  @END
  0;JMP //infinite loop
