.orig x3000

	LD R6, STACK	;; puts the vlaue xF000 into R6
	LD R0, NUM		;; puts the value 4 into R0

	ADD R6, R6, #-1 ;; decrementing stack pointer
	STR R0, R6, #0  ;; pushing R0/n onto the stack
	JSR SUM			;; save current PC into R7 AND Jump to SUM
	LDR R0, R6, #0	;; load return value into R0
	ADD R6, R6, #2
	ST R0, RESULT

	HALT

STACK	.fill xF000
NUM		.fill 4
RESULT	.blkw 1

.end

.orig x3100

SUM

	ADD R6, R6, #-4		;; decrementing stack pointer, making space for RV, old RA, old FP, and LV1
	STR R5, R6, #1		;; pushing old R5 (FP)
	STR R7, R6, #2		;; pushing old R7 (RA)
	ADD R5, R6, #0		;; R5 = R6 + 0 = R6

	ADD R6, R6, #-5		;; decrement stack pointer, make space for saving the 5 registers R0-R4
	STR R0, R6, #0		;; pushing current R0
	STR R1, R6, #1		;; pushing current R1
	STR R2, R6, #2		;; pushing current R2
	STR R3, R6, #3		;; pushing current R3
	STR R4, R6, #4		;; pushing current R4

	LDR R0, R5, #4		;; puts the value of the first argument (n) into R0
	ADD R1, R0, #-1		;; R1 = R0 - 1
	BRp ELSE
	;AND R1, R1, #0		;; R1 = 0
	;ADD R1, R1, #1		;; R1 = 1
	STR R0, R5, #3		;; stores the return value to RV slot
	BR TEARDOWN

ELSE

	ADD R6, R6, #-1		;; decrement stack pointer to make space for R1
	STR R1, R6, #0		;; pushes (n - 1) onto the stack
	JSR SUM				;; recursive call
	LDR R1, R6, #0		;; load the return value into R1
	ADD R6, R6, #2		;; pops the remaining of the stack and makes it look like nothing ever happened
	ADD R1, R0, R1		;; R1 = n + sum(n - 1)
	STR R1, R5, #3		;; stores the return value to RV slot (n + sum(n - 1))

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