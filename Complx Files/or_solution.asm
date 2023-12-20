.orig x3000 ; All of our programs will start at memory address x3000

; Our approach here is going to apply DeMorgan's Law:
; A|B = ~(~A & ~B)

; Since LD/ST take a PCOffset9 value, we can use labels instead to read from or write to those labels
LD R0, A         ; R0 = A
LD R1, B         ; R1 = B

; However, our approach actually needs the complement of A and B.
; So, we can use the NOT operation to get the complement of the values of these two registers:
NOT R2, R0       ; R2 = ~A
NOT R3, R1       ; R3 = ~B

; The last step of our calculation is to AND these two values and take the complement of the result:
AND R4, R2, R3   ; R4 = ~A & ~B
NOT R5, R4       ; R5 = ~(~A & ~B) == A|B

; Last but not least, we need to store this result back into memory
; We can just do the "reverse" of the LD operation we did before:
ST R5, RESULT 

HALT ; Stop execution

; We will store data after the instructions
A .fill b101010 ; == x2A == #42
B .fill b110011 ; == x33 == #51

; This will allocate one word of space for the result, but not store any specific value there
RESULT .blkw 1 
; Expected result: b111011 == x3B == #59

.end