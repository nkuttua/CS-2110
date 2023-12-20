;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - fourCharacterStrings
;;=============================================================
;; Name: Nakul Kuttua
;;=============================================================


;; Pseudocode (see PDF for explanation)
;;
;; int count = 0;
;; int chars = 0;
;; int i = 0;
;;
;;  while(str[i] != '\0') {
;;      if (str[i] != ' ') 
;;          chars++;
;;      
;;      else {
;;          if (chars == 4) 
;;              count++;   
;;          chars = 0;
;;      }
;;      i++;
;;  }
;; ***IMPORTANT***
;; - Assume that all strings provided will end with a space (' ').
;; - Special characters do not have to be treated differently. For instance, strings like "it's" and "But," are considered 4 character strings.
;;

.orig x3000
	;; YOUR CODE HERE
	AND R0, R0, 0 ;; R0 = i
	AND R1, R1, 0 ;; R1 = chars
	AND R2, R2, 0 ;; R2 = count
	AND R4, R4, 0

	WHILE
		AND R3, R3, 0
		LD R3, STRING           ;; Load the string into R3
		ADD R3, R3, R0          ;; Go to the address of the current character
		LDR R4, R3, 0           ;; R4 is given the value of the memory address in R3
		BRz ENDWHILE            ;; Escape the while loop once we reach the null terminator (ASCII value of 0 hence the z in BRz)
		AND R3, R3, 0           ;; Clear R3 so we can set it equal to SPACE
		LD R3, SPACE            ;; Load the value of SPACE (-32) into R3
        ADD R4, R4, R3          ;; We subtract 32 from R4 and if the value is positive (NOT ZERO) then we know the character is not a space

		BRp ISACHAR             ;; If the value in R4 is zero, branch to line 54 because R4 is not a space
			AND R3, R3, R0       ;; Clear R3 to 0 so we can use it for another purpose
			ADD R3, R1, #-4     ;; Here we are testing if chars == 4 by doing chars - 4 == 0
			BRnp INCREMENTCOUNT ;; If the chars == 4, lines 51-52 will execute
				ADD R2, R2, 1   ;; count++
				AND R1, R1, 0   ;; chars goes back to 0
			BRnzp OUTOFHERE
		ISACHAR
			ADD R1, R1, 1       ;; chars++
			BRnzp OUTOFHERE
		INCREMENTCOUNT
			AND R1, R1, 0       ;; Reset R1 to 0 since the chars was not 4 long
		OUTOFHERE
		ADD R0, R0, 1           ;; Increment i
		BRnzp WHILE             ;; Go back and loop again

	ENDWHILE

	ST R2, ANSWER
	HALT


SPACE 	.fill #-32
STRING	.fill x4000
ANSWER .blkw 1

.end ;;end


.orig x4000

.stringz "dazz "

.end
