; int randRecursion(int arr1Address, int arr2Address, int index, int inc) {
;   if (index < 0) {
;       return 0;
;   }
;
;    int x = 5;
;    int y = x + inc;
;    arr2[index] = arr1[index] + y;
;
;    return randRecursion(arr1Address, arr2Address, index - 1, inc) + arr2[index];
;
;}

.orig x3000

    LD R6, STACK                 ;; initialize SP
    LEA R0, ARR1                 ;; initialize starting address for Array 1
    LD R1, ARR2                  ;; initialize starting address for Array 2
    LD R2, LEN                   ;; initialize length
    ADD R2, R2, -1               ;; get length - 1
    LD R3, INC

    ADD R6, R6, #-4              ;; getting ready to push 4 arguments onto the stack
    STR R0, R6, 0 ;; push arr1Address
    STR R1, R6, 1 ;; push arr2Address
    STR R2, R6, #2 ;; push index
    STR R3, R6, #2 ;; push inc
    JSR FUNC ;; call FUNC

    HALT

LEN .fill 3
INT .fill 4
STACK .fill xF000
RESULT .blkw 1

ARR1 .fill 1
     .fill 2
     .fill 3

ARR2 .fill x4000

.orig x3100

FUNC

    ADD R6, R6, -4 ;; make space for the 4 arguments
    STR R5, R6, 1 ;; push old R5
    STR R7, R6, #2 ;; push old R7
    ADD R5, R6, 0 ;; R5 = R6

    ADD R6, R6, #-6 ;; decrement stack pointer
    STR R0, R6, 0 ;; push old R0
    STR R1, R6, 1 ;; push old R1
    STR R2, R6, #2 ;; push old R2
    STR R3, R6, #2 ;; push old R3

    LDR R0, R5, #6 ;; load in index
    BRn RET0

    AND R0, R0, 0 ;; clear R0
    ADD R0, R0, 5 ;; R0 = 5 x = 5
    STR R0, R5, 0 ;; stores R0 as local variable x

    LDR R0, R5, 0 ;; load back local var 1 = x to R0
    LDR R1, R5, #7 ;; load inc into R1
    ADD R0, R0, R1 ;; R0 = x + inc
    STR R0, R5, -1 ;; store x + inc = y as local var 2

RET0    

    AND R0, R0, 0 ;; clear R0
    STR R0, R5, #3 ;; save to return value slot
    BR TEARDOWN

TEARDOWN

.end

.end

.orig x4000

    .blkw 3

.end