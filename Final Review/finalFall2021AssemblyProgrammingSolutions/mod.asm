;;=======================================
;; CS 2110 - Fall 2021
;; Final Exam - Modulo
;;=======================================
;; Name: Neil Kochhar
;;=======================================

;; In this file, you must implement the 'mod' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'mod' label.


.orig x3000
HALT

mod
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of mod: integer a, positive integer b
;;
;; Pseudocode:
;; 
;; mod(a, b) {
;;     if (a < 0) {
;;         return mod(a + b, b);
;;     }
;;
;;     if (a < b) {
;;         return a;
;;     }
;;
;;     return mod(a - b, b);
;; }
;;
    
    
    ;; YOUR CODE HERE
ADD R6, R6, -4 ;Allocate space
STR R7, R6, 2 ;Save Ret Address
STR R5, R6, 1 ;Save Old FP
ADD R5, R6, 0 ;Copy SP to FP
ADD R6, R6, -5 ;make room for saved regs
STR R0, R6, 4 ;save R0
STR R1, R6, 3;save R1
STR R2, R6, 2 ;save R2
STR R3, R6, 1 ;save R3
STR R4, R6, 0 ;save R4




LDR R0, R5, 4 ;load a into R0
LDR R1, R5, 5 ;load b into R1

ADD R2, R0, 0 ;add a to 0
BRn ANEGATIVE


CONTINUE
LDR R2, R5, 5 ;load b into R2
NOT R2, R2
ADD R2, R2, 1 ;flip bits and add 1 to get ~b
ADD R2, R0, R2 ;add ~b and a
BRn ALESSTHAN
BRzp CONTINUE2


ANEGATIVE
ADD R6, R6, -2

ADD R3, R0, R1 ;add a + b 

STR R3, R6, 0 ;pass in parameters
STR R1, R6, 1
JSR mod
LDR R3, R6, 0 ;load return value in R3
ADD R6, R6, 3
BRnzp CONTINUE


ALESSTHAN
LDR R0, R6, 0 ;load return value in R3
BRnzp TEARDOWN

CONTINUE2
NOT R2, R1
ADD R2, R2, 1 ;flip bits and add 1 to get ~b
ADD R2, R0, R2 ;add a to ~b

STR R2, R6, 0 ;pass in parameters
STR R1, R6, 1
JSR mod
LDR R3, R6, 0 ;load return value in R3
ADD R6, R6, 3






TEARDOWN
; save the value in R0 on the stack as our return value

    ; restore registers
    LDR R0, R6, 4
    LDR R1, R6, 3
    LDR R2, R6, 2
    LDR R3, R6, 1
    LDR R4, R6, 0
    

    ; restore return address, frame pointer, and move R6 to RV
    ADD R6, R5, 0
    ADD R6, R6, 1
    ;ADD R6, R6, 6
    LDR R5, R6, #0
    LDR R7, R6, 1
    ADD R6, R6, 2



RET

;; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end