.orig x0000
LD R0, AA
LD R1, ZERO
LD R2, ZERO
INSERT R0
LD R1, BB
HALT

AA .fill x043B ; BRz TARGET
BB .fill 5
CC .fill 7
ZERO .fill 0

.end

.orig x0040
TARGET LD R2, CC
HALT

CC .fill 7
.end
; R0 = x043B, R1 = 0, R2 = 7, nzp = 0b001