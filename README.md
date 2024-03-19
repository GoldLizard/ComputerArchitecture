# ComputerArchitecture
Another class

Given an .asm file with assembly code, this program will generate machine code for a mano machine.

Instruction set:
     I=0  I=1
AND  0xxx 8xxx  AND memory word to AC
AND  1xxx 9xxx  Add memory word to AC
LDA  2xxx Axxx  Load memory word to AC
STA  3xxx Bxxx  Store content of AC in memory
BUN  4xxx Cxxx Branch unconditionally
BSA  5xxx Dxxx Branch and save return address
ISA  6xxx Exxx Increment and skip if zero
----------------------------------
CLA  7800  Clear AC
CLE  7400  Clear E
CMA  7200  Complement AC
CME  7100  Complement E
CIR  7080  Circulate right AC and E
CIL  7040  Circulate left AC and E
INC  7020  Increment AC
SPA  7010  Skip next isntruction if AC positive
SNA  7008  Skip next instruction if AC negative
SZA  7004  Skip next instruction if AC zero
SZE  7002  Skip next instruction if E is 0
HLT  7001  Halt computer
-----------------------------------
INP  F800  Input character to AC
OUT  F400  Output character from AC
SKI  F200  Skip on input flag
SKO  F100  Skip on output flag
ION  F080  Interrupt on
IOF  F040  interrupt off




