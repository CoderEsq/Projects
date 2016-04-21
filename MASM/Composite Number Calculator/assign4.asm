TITLE Composite Number Calculator Program (assign4.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			5/11/2015
; Date Modified:		5/11/2015
; Course:				CS 271-400
; Assignment:			Assignment 4
; Assignment Due Date:	5/10/2015
; Description:			Composite number program which accepts an integer (n) and calculates
;                       and prints the composite numbers up to and including the nth term.

INCLUDE Irvine32.inc

UPRLIMIT = 400
LWRLIMIT = 1

.data
programtitle        BYTE    "Composite Number Calculator by Alex Samuel", 0
instructions1       BYTE    "This program will calculate and display all of the composite numbers", 0
instructions2       BYTE    "up to, and including, the nth term that you choose to enter.", 0
instructions3       BYTE    "Please Enter an integer between 1 and 400: ", 0
err1				BYTE	"You did not enter a valid integer between 1 and 400.", 0
space5				BYTE	"     ", 0 	;used for spacing between composite numbers
instructions5       BYTE    "The composite numbers are as follows:", 0
endmsg              BYTE    "Thank you for using my program.", 0
exitmsg				BYTE	"Exiting Program...", 0

TWO             	DWORD   2 	;stores value of 2
TEN             	DWORD   10 	;stores value of 10
nthprint            DWORD   0 	;stores nth number printed
testval 			DWORD 	4	;stores current number being tested whether it is composite
divval 				DWORD 	2	;stores the current divisor

.data?
nthval              DWORD   ? 	;stores user input for n composite numbers to print
tencounter 			DWORD 	?	;counts the number of digits in the composite number
halftest 			DWORD 	?

.code
main PROC
	pushad
	call	introduction
	popad

	pushad
	call 	getUserData
	popad

	pushad
	call 	showComposites
	popad

	pushad
	call 	farewell
	popad

	exit	; exit to operating system
main ENDP

;Description: Procedure to display introduction
;Receives: NONE
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: edx
introduction	PROC

;Display programmer name and TITLE
	mov     edx, OFFSET programtitle
	call    WriteString
	call    CrLf
	call    CrLf

;Display instructions
	mov     edx, OFFSET instructions1
	call    WriteString
	call    CrLf

	mov     edx, OFFSET instructions2
	call    WriteString
	call    CrLf
	call    CrLf

	ret
introduction	ENDP

;Description: Procedure to get user data.
;Receives: NONE
;Returns: User input value for global variable nthval
;Preconditions:  NONE
;Registers Changed: edx, eax
getUserData	PROC

;Ask user for how many numbers they want displayed and store value
	mov     edx, OFFSET instructions3
	call    WriteString
	call 	ReadInt
	call    CrLf
	mov 	nthval, eax

;Calls validate procedure to check user input
	pushad
	call validate
	popad

	ret
getUserData	ENDP

;Description: Procedure to validate user input
;Receives: NONE
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: edx
validate PROC

	cmp 	nthval, LWRLIMIT 	;checks that nth term is greater than 1
	jl 		ERROR
	cmp 	nthval, UPRLIMIT 	;checks that nth term is lower than 400
	jg	 	ERROR
	jmp 	GOOD

;If nth term is invalid, error message printed and getUserData	procedure called
ERROR:
	mov     edx, OFFSET err1
	call    WriteString
	call    CrLf
	call    CrLf
	pushad
	call 	getUserData
	popad
GOOD:
	ret
validate	ENDP

;Description: Procedure to validate user input
;Receives: NONE
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: ecx, eax, ebx, edx
showComposites PROC

	mov 	ecx, nthval

;Calculates half the value of the tested number
CALC:
	mov 	eax, testval
	mov 	ebx, TWO
	mov 	edx, 0
	div 	ebx
	mov 	halftest, eax
	inc 	halftest
	mov 	eax, testval 	

;Divides the test value by the current divisor
CALC2:
	mov 	edx, 0
	div 	divval
	cmp 	edx, 0
	je 		PRINT
	jmp 	INCDIV

;If divisor results in a remainder, then tested value is not composite.
INCDIV:
	inc 	divval
	mov 	ebx, halftest
	cmp 	divval, ebx
	jge 	NOTCOMP
	jmp 	CALC

RANGE:
;This serves as a LOOP range extender (otherwise target would have been
;out of memory range of later occurring loop)
	jmp 	CALC

;Prints composite numbers
PRINT:
	pushad
	call 	isComposite
	popad
	jmp 	NEXT

;If tested value is not composite, testvalue is incremented
NOTCOMP:
	inc 	testval
	jmp 	CALC

;Loop will execute after tested value is found to be composite
;or prime.
NEXT:
	loop 	RANGE
	ret
showComposites	ENDP

;Description: Procedure to print composite values
;Receives: NONE
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: eax, edx
isComposite PROC
	mov 	eax, testval
	call 	WriteDec
	inc 	testval
	mov 	divval, 2
	inc 	nthprint
	mov 	eax, nthprint
	mov 	edx, 0
	div 	TEN
	cmp 	edx, 0
	je 		PRINTLINE

	mov     edx, OFFSET space5
	call    WriteString
	ret

PRINTLINE:
	call CrLF
	ret

isComposite	ENDP

;Description: Procedure to print ending messages
;Receives: NONE
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: edx
farewell PROC
	call    CrLf
	call    CrLf
	mov     edx, OFFSET endmsg
	call    WriteString
	call    CrLf
	call    CrLf
	mov     edx, OFFSET exitmsg
	call    WriteString
	call    CrLf
	call    CrLf
	ret
farewell	ENDP

END main