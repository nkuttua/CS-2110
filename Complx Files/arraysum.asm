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

        ; Let R0 = i and R2 = sum

WHILE   LD      R3, LENGTH
        NOT     R3, R3          ; R3 = -length
        ADD     R3, R0, R3      ; R3 = i + (-length)
        BRn     ENDWHILE        ; if (i - length >= 0), break out of the loop

        LEA     R3, ARRAY       ; R3 = address of the array
        ADD     R3, R0, R3      ; R3 = address of array[i]
        LDR     R4, R4, #0      ; R4 = array[i]

        ADD     R2, R2, R4      ; sum = sum + array[i]
        ADD     R0, R0, #1      ; i++

        BRnzp   WHILE           ; go back and loop again

ENDWHILE
        STI     R2, RESULT      ; store the result

        HALT

LENGTH  .fill 5  ; the length of the array below

ARRAY   .fill 1
        .fill 2
        .fill 3
        .fill 4
        .fill 5

RESULT  .blkw 1  ; store the sum here!

.end

