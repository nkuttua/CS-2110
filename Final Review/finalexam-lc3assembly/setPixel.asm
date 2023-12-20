;;=============================================================
;; CS 2110 - Fall 2021
;; Final Exam - Set Pixel
;;=============================================================
;; Name: 
;;=============================================================

;; Pseudocode (see PDF for additional information)
;; 
;; offset = 0;
;; for (i = 0; i < ROW; i++) {
;;		offset += WIDTH;
;; }
;; offset += COL;
;; VIDEOBUFFER[offset] = COLOR

.orig x3000

;; YOUR CODE HERE

HALT

COLOR .fill xFFFF
ROW .fill 1
COL .fill 1

HEIGHT .fill 2
WIDTH .fill 2

VIDEOBUFFER .fill x4000

.end

.orig x4000
    .fill 2
    .fill 1
    .fill 1
    .fill 0
.end