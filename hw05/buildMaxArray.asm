;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - buildMaxArray
;;=============================================================
;; Name: Nakul Kuttua
;;=============================================================


;; Pseudocode (see PDF for explanation)
;;
;;	int A[] = {1,2,3};
;;	int B[] = {-1, 7, 8};
;;	int C[3];
;;
;;	int i = 0;
;;
;;	while (i < A.length) {
;;		if (A[i] < B[i])
;;			C[i] = B[i];
;;		else
;;			C[i] = A[i];
;;
;;		i += 1;
;;	}


.orig x3000
	;; YOUR CODE HERE
	AND R0, R0, #0      ;; i
	AND R1, R1, #0      ;; Multi purpose
	AND R2, R2, #0      ;; for Array A
	AND R3, R3, #0      ;; for Array B

WHILE                   ;; i < LEN
	LD R1, LEN          ;; Load LEN into R1 so R1 = 4
	NOT R1, R1          ;; R1 = ~R1
	ADD R1, R1, #1      ;; R1 = -R1 = -LEN = -4
	ADD R1, R0, R1      ;; R1 = i + (-LEN)
	BRz ENDWHILE        ;; Branch out if R1 is zero (R1 can only equal -4, -3, -2, -1 so iterate 4 times) 

	AND R1, R1, #0      ;; Clear R1 so we can use it for A[i]
	LD R1, A            ;; Load the value of A (x3200) into R1
	ADD R1, R0, R1 	    ;; R1 = address of A[i] (not value, but the address of the value)
	LDR R2, R1, #0      ;; R2 = A[i] (the value now)

	AND R1, R1, #0      ;; Clear R1 so we can use it for B[i]
	LD R1, B            ;; Load the value of B (x3300) into R1
	ADD R1, R0, R1      ;; R1 = address of B[i] (not value, but the address of the value)
	LDR R3, R1, #0      ;; R3 = B[i] (the value now)

	NOT R3, R3          ;; R3 = ~R3
	ADD R3, R3, #1      ;; R3 = ~R3 + 1 = -R3 = -B[i]

	AND R1, R1, #0      ;; Clear R1 so we can use it to do R1 = A[i] + (-B[i])
	ADD R1, R2, R3      ;; R1 = A[i] + (-B[i])
	
	BRn BIsBigger       ;; If R1 is zero or positive, A[i] has to either be bigger than or equal to B[i] so branch to line 63m
		LD R1, C        ;; Load the value of C (memory address starting at x3400) into R1
		ADD R1, R0, R1  ;; R1 = mem[x3400 + i]
		STR R2, R1, 0
		BRnzp SKIPHERE  ;; This will skip setting mem[C[i]] = B[i]

	BIsBigger
		LD R1, C        ;; Load the value of C (memory address starting at x3400) into R1
		ADD R1, R0, R1  ;; R1 = mem[x3400 + i]
		NOT R3, R3      ;; R3 = ~R3
		ADD R3, R3, 1   ;; R3 = -R3
		STR R3, R1, 0
	SKIPHERE            ;; Branch here from line 67

	ADD R0, R0, 1       ;; i++
BRnzp WHILE

ENDWHILE

HALT

A 	.fill x3200
B 	.fill x3300
C 	.fill x3400
LEN .fill 4

.end

.orig x3200
	.fill -1
	.fill 2
	.fill 7
	.fill -3
.end

.orig x3300
	.fill 3
	.fill 6
	.fill 0
	.fill 5
.end

.orig x3400
	.blkw 4
.end


