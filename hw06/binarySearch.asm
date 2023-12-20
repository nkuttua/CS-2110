;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Binary Search
;;=============================================================
;; Name: Nakul Kuttua
;;============================================================

;; In this file, you must implement the 'binarySearch' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'binarySearch' label.


;; Pseudocode:

;; Nodes are blocks of size 3 in memory:

;; The data is located in the 1st memory location
;; The node's left child address is located in the 2nd memory location
;; The node's right child address is located in the 3rd memory location

;; Binary Search

;;    binarySearch(Node root (addr), int data) {
;;        if (root == 0) {
;;            return 0;
;;        }
;;        if (data == root.data) {
;;            return root;
;;        }
;;        if (data < root.data) {
;;            return binarySearch(root.left, data);
;;        }
;;        return binarySearch(root.right, data);
;;    }

.orig x3000
    ;; you do not need to write anything here
HALT

binary_search   ;; please do not change the name of your subroutine
    ;; insert your implementation for binarySearch subroutine

    ADD R6, R6, #-4		;; decrementing stack pointer, making space for RV, old RA, old FP, and LV1
	STR R5, R6, #1		;; pushing old R5 (FP)
	STR R7, R6, #2		;; pushing old R7 (RA)
	ADD R5, R6, #0		;; R5 = R6 + 0 = R6

	ADD R6, R6, #-5		;; decrement stack pointer, make space for saving the 5 registers R0-R4
	STR R4, R6, #0		;; pushing current R0
	STR R3, R6, #1		;; pushing current R1
	STR R2, R6, #2		;; pushing current R2
	STR R1, R6, #3		;; pushing current R3
	STR R0, R6, #4		;; pushing current R4

	LDR R1, R5, #5      ;; load the second arg (data) into R1
	LDR R0, R5, #4      ;; load the first arg (root) into R0

	BRz ROOTISZERO
	LDR R2, R0, 0       ;; R2 = root.data
	NOT R2, R2
	ADD R2, R2, 1       ;; R2 = -root.data
	ADD R2, R1, R2      ;; R2 = R1 + R2 = data + (-root.data)
	BRz DATAISROOTDATA  ;; data == root.data
	BRn DATAISLESS      ;; data < root.data
	BRp DATAISMORE      ;; data > root.data

		DATAISROOTDATA
			STR R0, R5, #3 ;; return root
			BR ESCAPE
		DATAISLESS
			ADD R6, R6, #-2 ;; make space for 2 args
			LDR R3, R0, 1   ;; R3 = root.left.data
			STR R3, R6, 0   ;; push arg1
			STR R1, R6, 1   ;; push arg2
			JSR binary_search
			LDR R1, R6, 0
			STR R1, R5, #3
			ADD R6, R6, #3  ;; decrement R6 to pop off the args from mult
			BR ESCAPE

		DATAISMORE
			ADD R6, R6, #-2 ;; make space for 2 args
			LDR R3, R0, 2   ;; R3 = root.right.data
			STR R3, R6, 0   ;; push arg1
			STR R1, R6, 1   ;; push arg2
			JSR binary_search
			LDR R1, R6, 0
			STR R1, R5, #3
			ADD R6, R6, #3  ;; decrement R6 to pop off the args from mult
			BR ESCAPE

		ROOTISZERO
			AND R0, R0, 0  ;; clear R0
			STR R0, R5, #3 ;; return 0
	ESCAPE
	BR TEARDOWN
    RET

TEARDOWN

	LDR R4, R6, #0		;; restoring R0
	LDR R3, R6, #1		;; restoring R1
	LDR R2, R6, #2		;; restoring R2
	LDR R1, R6, #3		;; restoring R3
	LDR R0, R6, #4		;; restoring R4

	ADD R6, R5, #0		;; R6 = R5 + 0 = R5
	LDR R5, R6, #1		;; restores old frame pointer
	LDR R7, R6, #2		;; restores old return address 

	ADD R6, R6, #3
	RET

STACK .fill xF000
.end

;; Assuming the tree starts at address x4000, here's how the tree (see below and in the pdf) represents in memory
;;
;;              4
;;            /   \
;;           2     8 
;;         /   \
;;        1     3 
;;
;; Memory address           Data
;; x4000                    4
;; x4001                    x4004
;; x4002                    x4008
;; x4003                    Don't Know
;; x4004                    2
;; x4005                    x400C
;; x4006                    x4010
;; x4007                    Don't Know
;; x4008                    8
;; x4009                    0(NULL)
;; x400A                    0(NULL)
;; x400B                    Don't Know
;; x400C                    1
;; x400D                    0(NULL)
;; x400E                    0(NULL)
;; x400F                    Dont't Know
;; x4010                    3
;; x4011                    0(NULL)
;; x4012                    0(NULL)
;; x4013                    Dont't Know
;;
;; *note: 0 is equivalent to NULL in assembly