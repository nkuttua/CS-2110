.orig x0000

LD R1, MYLABEL
LDR R2, R1, 0
LDR R3, R1, 1

HALT

MYLABEL .fill x0005

.fill x0006
.fill x0012

.end

;; R1: x0005, R2: x0006, R3: x0012, PC: x0004, CC: b001, Instructions executed: 3, LC3 Cycles: 
