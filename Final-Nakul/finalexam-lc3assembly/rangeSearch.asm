;;=============================================================
;; CS 2110 - Spring 2022
;; Final Exam - Range Search
;;=============================================================
;; Name: Nakul Kuttua
;;=============================================================

;; Pseudocode (see PDF for additional information)
;;     int list = [2, 1, 1, 0, 4, 2, 9, 0];
;;     int size = 8;
;;     int target = 10;
;;     int range = 2;
;;     int answer;
;;
;;     int element = -1;
;;     for (int i = 0; i < size; i++) {
;;         if (target - range <= list[i] <= target + range) {
;;             element = list[i];
;;             break;
;;         }
;;     }
;;
;;     while (size > 0) {
;;         if (target - range <= list[i] <= target + range) {
;;             element = list[i];
;;             break;
;;         }
;;          size--;
;;      }
;;     answer = element;
;;     
;; 
.orig x3000

LD R1, SIZE
LD R2, TARGET
LD R3, RANGE
AND R6, R6, 0 ;; i to increment
AND R4, R4, 0 ;; R4 WILL BE ELEMENT
ADD R4, R4, #-1 ;; R4 = ELEMENT = -1

WHILE ;; SIZE IS POSITIVE

    BRz ENDWHILE ;; ONLY DO THIS LINE ONCE SIZE == 0

    ;;CODE
    NOT R3, R3
    ADD R3, R3, #1 ;; -R3 = -RANGE
    ADD R5, R2, R3 ;; R5 = R2 + (-R3) = TARGET - RANGE
    LD R0, LIST    
    ADD R0, R0, R6 ;; GETS THE ADDRESS OF LIST[I]
    LDR R0, R0, 0  ;; GET LIST[I] VALUE
    NOT R0, R0
    ADD R0, R0, #1 ;; -LIST[I]
    ADD R5, R5, R0 ;; R5 = R5 + (-R0) = TARGET-RANGE - LIST[I]
    BRnz CASE1
    BR SKIPCASE1

    CASE1
        ;;CODE
        NOT R0, R0
        ADD R0, R0, #1 ;; TURN LIST[I] BACK TO POSITIVE
        NOT R3, R3
        ADD R3, R3, #1 ;; TURN RANGE BACK INTO POSITIVE (LINE 48)
        ADD R5, R2, R3 ;; R5 = R2 + R3 = TARGET + RANGE
        NOT R5, R5
        ADD R5, R5, #1 ;; -(TARGET + RANGE)
        ADD R5, R0, R5 ;; R5 = R0 + (-R5) = LIST[I] + -(TARGET + RANGE)
        BRnz CASE2
        BR SKIPCASE2

            CASE2
                ;;CODE
                ADD R4, R0, 0 ;; R4 = R0 + 0 = R0 = LIST[I] OR ELEMENT = LIST[I]
                BR ENDWHILE

    SKIPCASE1
    SKIPCASE2
    ADD R6, R6, #1  ;; i++
    ADD R1, R1, #-1 ;; SIZE--

    BR WHILE

ENDWHILE

LD R7, ANSWER ;; R7 = ANSWER SPOT
STR R4, R7, 0 ;; ANSWER = R4
;; YOUR CODE HERE


HALT

LIST    .fill x4000
SIZE    .fill 8
TARGET  .fill 10
RANGE   .fill 2
ANSWER  .blkw 1

.end

.orig x4000
    .fill 2
    .fill 1
    .fill 1
    .fill 0
    .fill 4
    .fill 2
    .fill 9
    .fill 0
.end