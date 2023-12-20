.orig x0000
LD R0, AA
LDN R1, R0

HALT

AA .fill xFFFB ; xFFFB = ~4
BB .fill 5
.end
; R0 = xFFFB, R1 = 5, nzp = 0b001

