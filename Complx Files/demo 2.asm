; int randRecursion(int arr1Address, int arr2Address, int index, int inc) {
;		if (index < 0) return 0
;		
;		int x = 5;
;		int y = x + inc;
;		arr2[index] = arr1[index] + y;
;		
;		return randRecursion(arr1Address, arr2Address, index - 1, inc) + arr2[index];
; }

.orig x3000

	LD R6, STACK		;; initialize SP
	LEA R0, ARR1 		;; initialize starting address for Array 1
	LD R1, ARR2			;; initialize starting address for Array 2
	LD R2, LEN			;; initialize length
	ADD R2, R2, #-1		;; get length - 1
	LD R3, INC

	ADD R6, R6, #-4		;; getting ready to push 4 arguments onto the stack
	STR R0, R6, #0		;; push arr1Address
	STR R1, R6, #1		;; push arr2Address
	STR R2, R6, #2		;; push index
	STR R3, R6, #3		;; push inc
	JSR FUNC 			;; call FUNC
	LDR R0, R6, #0		;; load return value
	ADD R6, R6, #5		;; finish popping stack
	ST R0, RESULT

	HALT

LEN 	.fill 3
INC 	.fill 4
STACK 	.fill xF000
RESULT 	.blkw 1

ARR1 	.fill 1
		.fill 2
		.fill 3

ARR2 	.fill x4000 ;; 10, 11, 12

.end

.orig x3100

FUNC

	;; Build the stack
	ADD R6, R6, #-4		;; decrementing stack pointer, making space for RV, old RA, old FP, and LV1
	STR R5, R6, #1		;; pushing old R5 (FP)
	STR R7, R6, #2		;; pushing old R7 (RA)
	ADD R5, R6, #0		;; R5 = R6 + 0 = R6

	ADD R6, R6, #-6		;; decrement stack pointer, make space for saving the 5 registers R0-R4
	STR R0, R6, #0		;; pushing current R0
	STR R1, R6, #1		;; pushing current R1
	STR R2, R6, #2		;; pushing current R2
	STR R3, R6, #3		;; pushing current R3
	STR R4, R6, #4		;; pushing current R4

	LDR R0, R5, #6 		;; load in index
	BRn RET0

	AND R0, R0, #0		;; clear R0
	ADD R0, R0, #5		;; R0 = 5
	STR R0, R5, #0		;; stores R0 as local variable or x
	;; blah blah happens here and for some reason my R0 changed

	LDR R0, R5, #0		;; load back LV1 = x to R0
	LDR R1, R5, #7		;; load inc into R1
	ADD R0, R0, R1 		;; R0 = x + inc
	STR R0, R5, #-1		;; store x + inc = y as LV2

	LDR R0, R5, #4		;; R0 = arr1Address
	LDR R1, R5, #6		;; R1 = index
	ADD R0, R0, R1 		;; R0 = address of arr1[index]
	LDR R0, R0, #0		;; R0 = mem[R0]
	LDR R1, R5, #-1		;; load back y into R1
	ADD R0, R0, R1 		;; R0 = arr1[index] + y

	LDR R1, R5, #5		;; R1 = arr2Address
	LDR R2, R5, #6		;; R2 = index
	ADD R1, R1, R2		;; R1 = address of arr2[index]

	STR R0, R1, #0		;; mem[R1 + 0] = R0 === mem[address of arr2[index]] = arr1[index] + y

	;; now we gotta be the caller

	LDR R0, R5, #4		;; R0 = arr1Address
	LDR R1, R5, #5		;; R1 = arr2Address
	LDR R2, R5, #6		;; R2 = index
	ADD R2, R2, #-1		;; R2 = index - 1
	LDR R3, R5, #7		;; R3 = inc

	;; push onto the stack as the caller
	ADD R6, R6, #-4
	STR R0, R6, #0
	STR R1, R6, #1
	STR R2, R6, #2
	STR R3, R6, #3
	JSR FUNC
	;; assume that the return value that we want is pointed to by R6
	LDR R0, R6, #0		;; loads in return value into R0
	ADD R6, R6, #5		;; complete teardown as caller's responsibility
	LDR R1, R5, #5		;; load arr2Address into R1
	LDR R2, R5, #6		;; R2 = index
	ADD R1, R1, R2		;; R1 = address of arr2[index]
	LDR R1, R1, #0		;; R1 = mem[R1 + 0] = arr2[index]
	ADD R0, R0, R1      ;; randRecursion(arr1Address, arr2Address, index - 1, inc) + arr2[index]
	STR R0, R5, #3		;; R0 gets stored to RV
	BR TEARDOWN			;; proceed to teardown

RET0

	AND R0, R0, #0		;; clear R0
	STR R0, R5, #3		;; save to return value slot
	BR TEARDOWN

TEARDOWN

	LDR R0, R6, #0		;; restoring R0
	LDR R1, R6, #1		;; restoring R1
	LDR R2, R6, #2		;; restoring R2
	LDR R3, R6, #3		;; restoring R3
	LDR R4, R6, #4		;; restoring R4

	ADD R6, R5, #0		;; R6 = R5 + 0 = R5
	LDR R5, R6, #1		;; restores old frame pointer
	LDR R7, R6, #2		;; restores old return address 

	ADD R6, R6, #3
	RET

.end

.orig x4000

	.blkw 3

.end