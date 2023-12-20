.orig x0000

LD R0, AA
LD R1, BB
LD R2, BB
SETCC R0
BRz TARGET
LD R1, CC
LD R2, CC
TARGET NOP
HALT

AA .fill 0
BB .fill 5
CC .fill 2

.end
; R0 = 0, R1 = 5, R2 = 5, nzp = 0b010