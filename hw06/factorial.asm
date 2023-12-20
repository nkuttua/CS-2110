;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Factorial
;;=============================================================
;; Name: Nakul Kuttua
;;============================================================

;; In this file, you must implement the 'factorial' and "mult" subroutines.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'factorial' or 'mult' label.

;; Pseudocode

;; Factorial

;;    factorial(int n) {
;;        int ret = 1;
;;        for (int x = 2; x < n+1; x++) {
;;            ret = mult(ret, x);
;;        }
;;        return ret;
;;    }

;; Multiply
         
;;    mult(int a, int b) {
;;        int product = 0;
;;        while (b > 0):
;;            product += a;
;;            b--;
;;        return product;
;;    }

.orig x3000
    ;; you do not need to write anything here
HALT

factorial   ;; please do not change the name of your subroutine
    ;; insert your implementation for factorial subroutine
    ADD R6, R6, #-4 ;; make space for RV, RA, old FP, and LV1
    STR R5, R6, #1  ;; push R5 onto the stack
    STR R7, R6, #2  ;; push R7 onto the stack
    ADD R5, R6, 0   ;; R5 = R6 + 0 -> R5 = R6

    ADD R6, R6, #-5 ;; make space for the 5 registers R0-R4
    STR R4, R6, #0 ;; push current R4
    STR R3, R6, #1 ;; push current R3
    STR R2, R6, #2 ;; push current R2
    STR R1, R6, #3 ;; push current R1
    STR R0, R6, #4 ;; push current R0

    LDR R0, R5, #4  ;; R0 = n = 4
    AND R1, R1, 0   ;; clear R1
    ADD R1, R1, 1   ;; R1 = ret = 1
    AND R2, R2, 0   ;; clear R2
    ADD R2, R2, #2  ;; R2 = x = 2
    NOT R0, R0
    ADD R0, R0, 1   ;; n = -4
    ADD R0, R0, R2  ;; R0 = -n + x


    WHILE
        BRp ENDWHILE
        ADD R6, R6, #-2 ;; make space for 2 arguments
        STR R1, R6, 0   ;; push ret = 1
        STR R2, R6, 1   ;; push x = 2
        JSR mult        ;; mult(1, 2) = 2
        LDR R1, R6, 0   ;; load the product value (2) from mult into R1
        ADD R6, R6, #3  ;; decrement R6 to pop off the args (int a and b) from mult
        ADD R2, R2, 1   ;; x++
        ADD R0, R0, 1   ;; n++ 
        BR WHILE
    ENDWHILE
    STR R1, R5, #3
    BR TEARDOWN
    RET

mult        ;; please do not change the name of your subroutine
    ;; insert your implementation for mult subroutine

    ADD R6, R6, #-4 ;; make space for RV, RA, old FP, and LV1
    STR R5, R6, #1  ;; push R5 onto the stack
    STR R7, R6, #2  ;; push R7 onto the stack
    ADD R5, R6, 0   ;; R5 = R6

    ADD R6, R6, #-5 ;; make space for the 5 registers R0-R4
    STR R4, R6, #0 ;; push current R4
    STR R3, R6, #1 ;; push current R3
    STR R2, R6, #2 ;; push current R2
    STR R1, R6, #3 ;; push current R1
    STR R0, R6, #4 ;; push current R0

    AND R2, R2, 0  ;; product
    LDR R0, R5, #4  ;; load the first argument ret into R0 (a)
    LDR R1, R5, #5  ;; load the second argument x into R1 (b)

    WHILEMULT
        BRz ENDWHILEMULT
        ADD R2, R2, R0  ;; product += a
        ADD R1, R1, #-1 ;; b--
        BR WHILEMULT
    ENDWHILEMULT
    STR R2, R5, #3      ;; store the product into the mult subroutine return value
    BR TEARDOWN
    RET

TEARDOWN
    LDR R4, R6, #0   ;; restore old R0
    LDR R3, R6, #1   ;; restore old R1
    LDR R2, R6, #2   ;; restore old R2
    LDR R1, R6, #3   ;; restore old R3
    LDR R0, R6, #4   ;; restore old R4

    ADD R6, R5, #0		;; R6 = R5 + 0 = R5
	LDR R5, R6, #1		;; restores old frame pointer
	LDR R7, R6, #2		;; restores old return address 

	ADD R6, R6, #3
    RET

STACK .fill xF000
.end
