;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - binaryStringToInt
;;=============================================================
;; Name: Nakul Kuttua
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;;    int result = x4000; (given memory address to save the converted value)
;;    String binaryString= "01000000"; (given binary string)
;;    int length = 8; (given length of the above binary string)
;;    int base = 1;
;;    int value = 0;
;;    while (length > 0) {
;;        int y = binaryString.charAt(length - 1) - 48;
;;        if (y == 1) {
;;            value += base;
;;        }     
;;            base += base;
;;            length--;
;;    }
;;    mem[result] = value;
.orig x3000
    ;; YOUR CODE HERE
    AND R0, R0, 0            ;; Clear R0 and R0 = i
    LD R0, length            ;; Load length into R0
    ADD R0, R0, -1
    AND R1, R1, 0            ;; Clear R1
    AND R2, R2, 0            ;; Clear R2, and R2 = base
    ADD R2, R2, 1            ;; base = 1
    AND R3, R3, 0            ;; Clear R3, and R3 = value
    WHILE
        BRn ENDWHILE         ;; Branch to ENDWHILE if the CC from R0 is negative (once we reach the end of the binary string)
        LD R1, binaryString  ;; Load the binaryString into R1
        ADD R1, R0, R1       ;; R1 = R1 + R0 = mem[binaryString] + length (we are at the address of the value we want)
        LDR R1, R1, 0        ;; Load the value of the address in R1 into R1 (go from the address of the value to the value itself in the same register)
        ADD R1, R1, #-16     ;; Convert from char to decimal
        ADD R1, R1, #-16     ;; Convert from char to decimal
        ADD R1, R1, #-16     ;; Convert from char to decimal
        BRz VALUEISZERO      ;; If the CC is 010, then do not execute the below lines
            ADD R3, R3, R2   ;; value += base
        VALUEISZERO
        ADD R2, R2, R2       ;; base += base
        ADD R0, R0, -1       ;; length--
        BRnzp WHILE          ;; Go back and loop again
    ENDWHILE

    LD R0, result
    STR R3, R0, 0
    
    HALT

    binaryString .fill x5000
    length .fill 8
    result .fill x4000
.end 

.orig x5000
    .stringz "00000011" ;; 5000 5001 5002 5003 5004 5005 5006 5007
.end
