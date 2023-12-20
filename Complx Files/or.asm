.orig x3000 ; All of our programs will start at memory address x3000


HALT ; Stop execution

; We will store data after the instructions
A .fill b101010 ; == x2A == #42
B .fill b110011 ; == x33 == #51

; This will allocate one word of space for the result, but not store any specific value there
RESULT .blkw 1 
; Expected result: b111011 == x3B == #59

.end