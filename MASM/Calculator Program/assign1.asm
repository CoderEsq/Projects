TITLE Calculator Program (assign1.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			4/3/2015
; Date Modified:		4/5/2015
; Course:				CS 271-400
; Assignment:			Assignment 1
; Assignment Due Date:	4/12/2015
; Description:			Calculator program which accepts two values and calculates
;                       the results of various mathematical operations.

INCLUDE Irvine32.inc

.data

programTitle        BYTE    "Calculator Program by Alex Samuel", 0
instructions1       BYTE    "Enter two positive integers and this program will calculate the", 0
instructions2       BYTE    "sum, difference, product, quotient, and remainder of the two integers. ", 0
ECprompt1			BYTE	"**EC: Program repeats until the user chooses to quit.", 0
ECprompt2			BYTE	"**EC: Program validates the second number to be less than the first.", 0
ECprompt3			BYTE	"**EC: Program displays quotient as floating-point number (rounded to 0.001).", 0
instructions3		BYTE	"Please make sure to enter the largest value first.", 0
prompt1       		BYTE    "Please enter the first positive integer: ", 0
prompt2       		BYTE    "Please enter the second positive integer: ", 0
err1				BYTE	"You did not enter the largest integer first.", 0

addmsg       		BYTE    " + ", 0
submsg       		BYTE    " - ", 0
mulmsg       		BYTE    " X ", 0
divmsg       		BYTE    " / ", 0
remaindermsg       	BYTE    " remainder ", 0
equalmsg       		BYTE    " = ", 0
decmsg				BYTE	".", 0

endmsg              BYTE    "Thank you for using my program.", 0
playAgain			BYTE	"Would you like to run another calculation?", 0
choice1				BYTE	"Enter 1 if you would like to make another calculation", 0
choice2				BYTE	"or Enter 2 if you would like to exit the program.", 0
selection			BYTE	"Your Selection: ", 0
exitmsg				BYTE	"Exiting Program...", 0

.data?

value1              DWORD   ?   ;1st value entered by user
value2              DWORD   ?   ;2nd value entered by user
sum                 DWORD   ?   
difference          DWORD   ?
product             DWORD   ?
quotient            DWORD   ?
fpuquotient			REAL4	?
remainder1          DWORD   ?
replay				DWORD	?	;stores user's choice to rerun program
newremainder		DWORD 	?	;stores remainder from each division operation
newdiv				DWORD	?	;stores new numerator for each division operation
decimal1			DWORD	?	;stores value of first decimal
decimal2			DWORD	?	;stores value of 2nd decimal
decimal3			DWORD	?	;stores value of 3rd decimal
decimal4			DWORD	?	;stores value of 4th decimal

.code
main PROC

START:
; Display programmer name and program title
	mov     edx, OFFSET programTitle
	call    WriteString
	call    CrLf
	call    CrLf

; Display instructions to user
	mov     edx, OFFSET instructions1
	call    WriteString
	call    CrLf

	mov     edx, OFFSET instructions2
	call    WriteString
	call    CrLf

	mov     edx, OFFSET ECprompt1
	call    WriteString
	call    CrLf

	mov     edx, OFFSET ECprompt2
	call    WriteString
	call    CrLf

	mov     edx, OFFSET ECprompt3
	call    WriteString
	call    CrLf
	call    CrLf

INPUT:

	mov     edx, OFFSET instructions3
	call    WriteString
	call    CrLf
	call    CrLf

; prompt user to enter two numbers and reads input
	mov     edx, OFFSET prompt1
	call    WriteString
	call 	ReadInt
	mov 	value1, eax

	mov     edx, OFFSET prompt2
	call    WriteString
	call 	ReadInt
	mov 	value2, eax
	call    CrLf

;Checks if user entered smaller number first
	mov 	eax, value1
	cmp 	eax, value2
	jae 	CALCS		;If large number is first, error message skipped
	jb 		ERRMSG

ERRMSG:
;Prints out Error message if user did not enter smaller number first  (Extra Crdit Option 2) 
;Reprompts user to enter numeric values
	mov     edx, OFFSET err1
	call    WriteString
	call    CrLf
	call    CrLf
	cmp 	eax, value2
	jb 		INPUT

CALCS:
;calculate sum
	mov 	eax, value1
	add 	eax, value2
	mov 	sum, eax

;calculate difference
	mov 	eax, value1
	sub 	eax, value2
	mov 	difference, eax

;calculate product
	mov 	eax, value1
	mov 	ebx, value2
	mul 	ebx
	mov 	product, eax

;calculate quotient and remainder
	mov 	eax, value1
	mov 	ebx, value2
	div 	ebx
	mov 	quotient, eax
	mov 	remainder1, edx

;Division operations used to calculate FPU quotient (Extra Crdit Option 3) 
;Checks if remainder=0, if so then decimal 1,2,3 = 0
	mov 	eax, remainder1
	cmp 	eax, 0
	je 		NOREMAINDER

	mov 	eax, remainder1
	mov 	ebx, 10
	mul 	ebx
	mov 	newdiv, eax

;First decimal value is calculated
	mov 	eax, newdiv
	mov 	ebx, value2
	div 	ebx
	mov 	decimal1, eax
	mov 	newremainder, edx

;If no remainder, then remaining decimals = 0
	mov 	eax, newremainder
	cmp 	eax, 0
	je 		DEC1

	mov 	eax, newremainder
	mov 	ebx, 10
	mul 	ebx
	mov 	newdiv, eax

;Calculates 2nd decimal value and remainder
	mov 	eax, newdiv
	mov 	ebx, value2
	div 	ebx
	mov 	decimal2, eax
	mov 	newremainder, edx

;If no remainder, then remaining decimals = 0
	mov 	eax, newremainder
	cmp 	eax, 0
	je 		DEC2

	mov 	ebx, 10
	mul 	ebx
	mov 	newdiv, eax

;Calculates 3rd decimal value and remainder
	mov 	eax, newdiv
	mov 	ebx, value2
	div 	ebx
	mov 	decimal3, eax
	mov 	newremainder, edx

;If no remainder, then no remaining decimals need to be calculated
	mov 	eax, newremainder
	cmp 	eax, 0
	je 		DISPLAY

	mov 	ebx, 10
	mul 	ebx
	mov 	newdiv, eax

;Calculates 4th decimal value
	mov 	eax, newdiv
	mov 	ebx, value2
	div 	ebx
	mov 	decimal4, eax

;If 4th decimal value is >= 5, then 3rd decimal needs to be rounded up.
	mov 	eax, decimal4
	cmp 	eax, 5
	jae 	ROUND3
	jmp 	DISPLAY

;Rounds 3rd decimal value
ROUND3:
	mov 	eax, decimal3
	add 	eax, 1
	mov 	decimal3, eax

;If 3rd decimal value = 10, 2nd decimal value needs to be rounded up
	cmp 	eax, 10
	je 		ROUND2
	jmp 	DISPLAY

;Rounds 2nd decimal value
ROUND2:
;Sets 3rd decimal value to 0
	mov 	eax, 0
	mov 	decimal3, eax

;Rounds 2nd decimal value up 1
	mov 	eax, decimal2
	add 	eax, 1
	mov 	decimal2, eax

;If 2nd decimal value = 10, 1st decimal value needs to be rounded up
	cmp 	eax, 10
	je 		ROUND1
	jmp 	DISPLAY

;Rounds 1st decimal value
ROUND1:
;Sets 2nd decimal value to 0
	mov 	eax, 0
	mov 	decimal2, eax

;Rounds 1st decimal value up 1
	mov 	eax, decimal1
	add 	eax, 1
	mov 	decimal1, eax

;If 1st decimal value = 10, quotient value needs to be rounded up
	cmp 	eax, 10
	je 		ROUND
	jmp 	DISPLAY

;Rounds quotient
ROUND:
;Sets 1st decimal value to 0
	mov 	eax, 0
	mov 	decimal1, eax

;Rounds quotient up 1
	mov 	eax, quotient
	add 	eax, 1
	mov 	quotient, eax
	jmp 	DISPLAY

;If quotient has no remainder, all decimal places = 0
NOREMAINDER:
	mov 	eax, 0
	mov 	decimal1, eax
	mov 	decimal2, eax
	mov 	decimal3, eax
	mov 	decimal4, eax	
	jmp 	DISPLAY

;If after 1st decimal no remainder, remaining decimal places = 0
DEC1:
	mov 	eax, 0
	mov 	decimal2, eax
	mov 	eax, 0
	mov 	decimal3, eax
	mov 	eax, 0
	mov 	decimal4, eax	
	jmp 	DISPLAY

;If after 2nd decimal no remainder, remaining decimal places = 0
DEC2:
	mov 	eax, 0
	mov 	decimal3, eax
	mov 	eax, 0
	mov 	decimal4, eax	
	jmp 	DISPLAY

DISPLAY:
;displays sum
	mov 	eax, value1
	call 	WriteDec
	mov     edx, OFFSET addmsg
	call    WriteString
	mov 	eax, value2
	call 	WriteDec
	mov     edx, OFFSET equalmsg
	call    WriteString
	mov 	eax, sum
	call 	WriteDec
	call    CrLf

;displays difference
	mov 	eax, value1
	call 	WriteDec
	mov     edx, OFFSET submsg
	call    WriteString
	mov 	eax, value2
	call 	WriteDec
	mov     edx, OFFSET equalmsg
	call    WriteString
	mov 	eax, difference
	call 	WriteDec
	call    CrLf

;displays product
	mov 	eax, value1
	call 	WriteDec
	mov     edx, OFFSET mulmsg
	call    WriteString
	mov 	eax, value2
	call 	WriteDec
	mov     edx, OFFSET equalmsg
	call    WriteString
	mov 	eax, product
	call 	WriteDec
	call    CrLf

;displays quotient and remainder
	mov 	eax, value1
	call 	WriteDec
	mov     edx, OFFSET divmsg
	call    WriteString
	mov 	eax, value2
	call 	WriteDec
	mov     edx, OFFSET equalmsg
	call    WriteString
	mov 	eax, quotient
	call 	WriteDec
	mov     edx, OFFSET remaindermsg
	call    WriteString
	mov 	eax, remainder1
	call 	WriteDec
	call    CrLf

;displays FPU quotient
	mov 	eax, value1
	call 	WriteDec
	mov     edx, OFFSET divmsg
	call    WriteString
	mov 	eax, value2
	call 	WriteDec
	mov     edx, OFFSET equalmsg
	call    WriteString
	mov 	eax, quotient
	call 	WriteDec
	mov     edx, OFFSET decmsg
	call    WriteString
	mov 	eax, decimal1
	call 	WriteDec
	mov 	eax, decimal2
	call 	WriteDec
	mov 	eax, decimal3
	call 	WriteDec
	call    CrLf
	call    CrLf

;display terminating message
	mov     edx, OFFSET endmsg
	call    WriteString
	call    CrLf
	call    CrLf

;ask user if they want to rerun program
	mov     edx, OFFSET playAgain
	call    WriteString
	call    CrLf
	mov     edx, OFFSET choice1
	call    WriteString
	call    CrLf
	mov     edx, OFFSET choice2
	call    WriteString
	call    CrLf
	call    CrLf
	mov     edx, OFFSET selection
	call    WriteString
	call 	ReadInt
	mov 	replay, eax

;If user selected to rerun, program starts at beginning (Extra Crdit Option 1) 
	mov 	eax, replay
	cmp 	eax, 1
	je 		START

;If user did not select to rerun, program exits
	mov     edx, OFFSET exitmsg
	call    WriteString
	call    CrLf
	call    CrLf

	exit	; exit to operating system
main ENDP

END main