;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - summation
;;=============================================================
;; Name: Nakul Kuttua
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;;    int result; (to save the summation of x)
;;    int x= 4; (given integer)
;;    int answer = 0;
;;    while (x > 0) {
;;        answer += x;
;;        x--;
;;    }
;;    result = answer;
.orig x3000
    ;; YOUR CODE HERE
    AND R0, R0, 0      ;; clear R0 to 0, consider R0 to be result
    AND R1, R1, 0      ;; clear R1 to 0, consider R1 to decrement operator
    LD R1, x           ;; LOAD the value of x into R1

    BRn NEGATIVE

    ISPOSITIVE             ;; Conditional that checks to see if R1 is positive, if it is, do R0 = R0 + R1 and R1--
        ADD R0, R0, R1
        ADD R1, R1, -1
    BRp ISPOSITIVE         ;; Loop back to ISPOSITIVE until the condition code reaches 010 (ZERO)

    NEGATIVE

    ST R0, result          ;; Store the value in R0 into the result LABEL
                  
HALT                   ;; Ensures that nothing gets run after this point
    x .fill 4          ;; Fill the label x with the integer 4
    result .blkw 1     ;; Reserves one memory address to hold the result
.end

