;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Quick Sort
;;=============================================================
;; Name: Nakul Kuttua
;;============================================================

;; In this file, you must implement the 'quicksort' and 'partition' subroutines.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'quicksort' or 'partition' label.


;; Pseudocode:

;; Partition

;;    partition(int[] arr, int low, int high) {
;;        int pivot = arr[high];
;;        int i = low - 1;
;;        for (j = low; j < high; j++) {
;;            if (arr[j] < pivot) {
;;                i++;
;;                int temp = arr[j];
;;                arr[j] = arr[i];
;;                arr[i] = temp;
;;            }
;;        }
;;        int temp = arr[high];
;;        arr[high] = arr[i + 1];
;;        arr[i + 1] = temp;
;;        return i + 1;
;;    }
        
;; Quicksort

;;    quicksort(int[] arr, int left, int right) {
;;        if (left < right) {
;;            int pi = partition(arr, left, right);
;;            quicksort(arr, left, pi - 1);
;;            quicksort(arr, pi + 1, right);
;;        }
;;    }


.orig x3000
    ;; you do not need to write anything here
HALT

partition   ;; please do not change the name of your subroutine
    ;; insert your implementation for partition subroutine

    ADD R6, R6, #-4 ;; make space for RV, RA, old FP, and LV1
    STR R5, R6, #1  ;; push R5 onto the stack
    STR R7, R6, #2  ;; push R7 onto the stack
    ADD R5, R6, #0   ;; R5 = R6

    ADD R6, R6, #-13 ;; make space for the 5 registers R0-R4 and 8 Local Vars
    STR R4, R6, #0 ;; push current R0
    STR R3, R6, #1 ;; push current R1
    STR R2, R6, #2 ;; push current R2
    STR R1, R6, #3 ;; push current R3
    STR R0, R6, #4 ;; push current R4

    LDR R0, R5, #4 ;; arr
    LDR R1, R5, #5 ;; low
    LDR R2, R5, #6 ;; high

    ADD R0, R0, R2 ;; address of pivot
    LDR R3, R0, #0  ;; arr[high]
    STR R3, R5, #0  ;; pivot
    ADD R3, R1, #-1 ;; i
    STR R3, R5, #-1
    AND R3, R3, #0
    ADD R3, R3, R1 ;; j
    AND R4, R4, #0
    ADD R4, R4, R2
    NOT R4, R4
    ADD R4, R4, #1
    STR R1, R5, #-2 ;; high
    STR R2, R5, #-3 ;; low
    ADD R4, R4, R3

    LOOP
    BRz CEASE

        LDR R1, R5, #0 ;; pivot
        ADD R0, R0, R3
        AND R2, R2, #0
        LDR R2, R0, #0  ;; arr[j]
        NOT R1, R1
        ADD R1, R1, #1  ;; -pivot
        ADD R1, R2, R1

        BR PIVOTNOTBIGGER

            AND R1, R1, #0
            LDR R1, R5, #-1
            ADD R1, R1, #1
            STR R1, R5, #-1
            AND R1, R1, #0 ;; temp
            ADD R1, R2, R1 ;; temp = arr[j]

        PIVOTNOTBIGGER

        STR R4, R5, #-4
        AND R2, R2, #0
        ADD R0, R0, R4
        LDR R2, R0, #0
        ADD R0, R0, R3
        STR R2, R0, #0
        ADD R0, R0, R4
        STR R1, R0, #0
        AND R1, R1, #0
        AND R4, R4, #0
        LDR R4, R5, #-4
        ADD R4, R4, #1

        BR LOOP
        CEASE

        AND R2, R2, #0
        LDR R2, R5, #-3
        AND R3, R3, #0
        ADD R0, R0, R2
        LDR R3, R0, #0
        ADD R1, R1, R3
        AND R2, R2, #0
        AND R4, R4, #0
        LDR R4, R5, #-1
        ADD R4, R4, #1
        ADD R0, R0, R4
        LDR R2, R0, #0
        ADD R0, R0, R4
        STR R3, R0, #0
        AND R1, R1, #0
        LDR R1, R5, #-3
        ADD R0, R0, R1
        STR R2, R0, #0
        STR R4, R5, #3

    BR TEARDOWN

    RET

quicksort   ;; please do not change the name of your subroutine
    ;; insert your implementation for quicksort subroutine
    
    ADD R6, R6, #-4 ;; make space for RV, RA, old FP, and LV1
    STR R5, R6, #1  ;; push R5 onto the stack
    STR R7, R6, #2  ;; push R7 onto the stack
    ADD R5, R6, #0   ;; R5 = R6

    ADD R6, R6, #-5 ;; make space for the 5 registers R0-R4
    STR R4, R6, #0 ;; push current R0
    STR R3, R6, #1 ;; push current R1
    STR R2, R6, #2 ;; push current R2
    STR R1, R6, #3 ;; push current R3
    STR R0, R6, #4 ;; push current R4

    LDR R0, R5, #4 ;; arr
    LDR R1, R5, #5 ;; left
    LDR R2, R5, #6 ;; right
    AND R3, R3, #0
    NOT R3, R2
    ADD R3, R3, #1  ;; R3 = -right
    ADD R3, R1, R3 ;; R3 = left + (-right)
    
    BRzp RIGHTISNOTBIGGER

        ADD R6, R6, #-3
        STR R0, R6, #0
        STR R1, R6, #1
        STR R2, R6, #2
        JSR partition

        LDR R3, R6, #0
        ADD R3, R3, #-1
        ADD R6, R6, #-3
        STR R0, R6, #0
        STR R1, R6, #1
        STR R3, R6, #2
        JSR quicksort

        ADD R3, R3, #2
        ADD R6, R6, #-3
        STR R0, R6, #0
        STR R3, R6, #1
        STR R2, R6, #2
        JSR quicksort

        BR TEARDOWN
    RIGHTISNOTBIGGER
        BR TEARDOWN
    RET

TEARDOWN
    LDR R4, R6, #0   ;; restore old R0
    LDR R3, R6, #1   ;; restore old R1
    LDR R2, R6, #2   ;; restore old R2
    LDR R1, R6, #3   ;; restore old R3
    LDR R0, R6, #4   ;; restore old R4

    ADD R6, R5, #0		;; R6 = R5 + 0 = R5
	LDR R5, R6, #1		;; restores old frame pointer
	LDR R7, R6, #2		;; restores old return address 

	ADD R6, R6, #3
    RET

STACK .fill xF000
.end


;; Assuming the array starts at address x4000, here's how the array [1,3,2,5] represents in memory
;; Memory address           Data
;; x4000                    1
;; x4001                    3
;; x4002                    2
;; x4003                    5
