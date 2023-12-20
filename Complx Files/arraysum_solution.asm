;; Compute the sum of the given array and store the sum at the RESULT label.
;;
;; Pseudocode:
;;
;;   i = 0;
;;   sum = 0;
;;   while (i < LENGTH) {
;;       element = ARRAY[i];
;;       sum = sum + element;
;;       i++;
;;   }
;;   RESULT = sum;

.orig x3000

        AND     R0, R0, #0      ; i = R0
        AND     R2, R2, #0      ; sum = R2

WHILE   LD      R3, LENGTH
        NOT     R3, R3
        ADD     R3, R3, #1      ; R3 = -length
        ADD     R3, R0, R3      ; R3 = i + (-length)
        BRzp    ENDWHILE        ; if (i - length >= 0), break out of the loop

        LEA     R3, ARRAY       ; R3 = address of the array
        ADD     R3, R0, R3      ; R3 = address of array[i]
        LDR     R4, R3, #0      ; R4 = array[i]

        ADD     R2, R2, R4      ; sum = sum + array[i]
        ADD     R0, R0, #1      ; i++

        BR   WHILE           ; go back and loop again

ENDWHILE
        ST      R2, RESULT      ; store the result

        HALT

LENGTH  .fill 5  ; the length of the array below

ARRAY   .fill 1 ; index 0
        .fill 2 ; index 1
        .fill 3 ; index 2
        .fill 4 ; index 3
        .fill 5 ; index 4

RESULT  .blkw 1  ; store the sum here!

.end

