;;=============================================================
;; CS 2110 - Fall 2021
;; Final Exam - Set Pixel
;;=============================================================
;; Name: Neil Kochhar
;;=============================================================

;; Pseudocode (see PDF for additional information)
;; 
;; offset = 0;
;; for (i = 0; i < ROW; i++) {
;;		offset += WIDTH;
;; }
;; offset += COL;
;; VIDEOBUFFER[offset] = COLOR

.orig x3000

;; YOUR CODE HERE




LD R0, ZERO ;load zero in R0 (offset)
LD R1, ZERO ; load zero in R1, (i)
STR R1, R5, 0 ;store zero in local variable

FOR
LDR  R2, R5, 0; load i into R2
NOT R2, R2 ;flip bits of R2
ADD R2, R2, 1 ;add 1 to R2
LD R3, ROW
ADD R2, R3, R2 ;add -i to ROW
BRp ENDFOR

LD R4, WIDTH
ADD R0, R0, R4 ;add width to the offset
ADD R1, R1, 1 ;add 1 to i
BRnzp FOR

ENDFOR
LD R4, COL
ADD R0, R0, R4 ; add column to the offset
LD R1, VIDEOBUFFER ;load videobuffer into R1
ADD R1, R1, R0 ;add offset to videobuffer
ST R1, COLOR ;store color at videobuffer[offset]


TEARDOWN
; save the value in R0 on the stack as our return value

    ; restore registers
    LDR R0, R6, 4
    LDR R1, R6, 3
    LDR R2, R6, 2
    LDR R3, R6, 1
    LDR R4, R6, 0

    ; restore return address, frame pointer, and move R6 to RV
    ADD R6, R6, 6
    LDR R5, R6, #0
    LDR R7, R6, 1
    ADD R6, R6, 2

HALT

COLOR .fill xFFFF
ROW .fill 1
COL .fill 1
ZERO .fill 0
ONE .fill 1

HEIGHT .fill 2
WIDTH .fill 2

VIDEOBUFFER .fill x4000

.end

.orig x4000
    .fill 2
    .fill 1
    .fill 1
    .fill 0
.end