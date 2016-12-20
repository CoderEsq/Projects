TITLE Low-Level I/O Calculator (assign6.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			5/26/2015
; Date Modified:		6/6/2015
; Course:				Computer Architecture & Assembly
; Assignment:			Assignment 6 Option A
; Assignment Due Date:	6/7/2015
; Description:			Low-Level I/O Calculator

INCLUDE Irvine32.inc

MAXDIGITS = 12
TEN = 10
HUNDRED = 100
K1 = 1000
K10 = 10000
K100 = 100000
M1 = 1000000
M10 = 10000000
M100 = 100000000
B1 = 1000000000

getString	MACRO	instruct, buffer
	push	edx
	push 	ecx
	push 	ebx

	displayString instruct

	mov 	edx, buffer
	mov 	ecx, MAXDIGITS
	call 	ReadString

	pop ebx
	pop	ecx
	pop edx
ENDM

displayString 	MACRO	stringloc
	push	edx
	mov		edx, stringloc
	call	WriteString
	pop edx
ENDM

.data
programtitle        BYTE    "Low-Level I/O Calculator by Alex Samuel", 0
instructions1       BYTE    "This program will read in 10 unsigned numbers and calculate the sum and", 0
instructions2       BYTE    "average value.", 0


instructions3       BYTE    "Please enter an unsigned number: ", 0
err1				BYTE	"ERROR: You did not enter an unsigned number or your number was too large.", 0

instructions5       BYTE    "You entered the following numbers: ", 0
spacer       		BYTE    ", ", 0
sumval				BYTE	"The Sum of these numbers is: ", 0
avgval				BYTE	"The Average of these numbers is: ", 0

endmsg              BYTE    "Thank you for using my program.", 0
exitmsg				BYTE	"Exiting Program...", 0
holder 				DWORD 	11 DUP(?)
array 				DWORD 	11 DUP(?)
tarray 				DWORD 	11 DUP(?)

testr				BYTE	10, 20, 30, 0

.data?


.code
main PROC

	;Calls macro to display introductory message
	displayString OFFSET programtitle
	call 	CrLf
	call 	CrLf

	;Calls macro to display instructions
	displayString OFFSET instructions1
	call 	CrLf

	;Calls macro to display instructions
	displayString OFFSET instructions2
	call 	CrLf

	;Pushes values onto stack and calls procedure to read in user data  and valdiate
	push 	OFFSET avgval
	push 	OFFSET holder
	push 	OFFSET instructions3
	push 	OFFSET sumval
	push 	OFFSET err1
	push 	OFFSET array
	call 	ReadVal

	displayString OFFSET instructions5
	push 	OFFSET array
	push 	OFFSET spacer
	call 	WriteVal

	;Calls macro to display ending message
	displayString OFFSET endmsg
	call 	CrLf
	call 	CrLf

	;Calls macro to display exit message
	displayString OFFSET exitmsg
	call 	CrLf
	call 	CrLf

	exit	; exit to operating system
main ENDP


;Description: Procedure to read and validate user input
;Receives: avgval, instructions3, sumval, err1 (all strings), and array and holder (arrays)
;Returns: array contains user input in numerics
;Preconditions:  NONE
;Registers Changed: ecx, edx, eax, ebx, ebp, esp, esi, edi
ReadVal PROC
	
	push 	ebp
	mov 	ebp, esp
	mov 	ecx, 10

GETVAL:
;Saves value of ecx
	push 	ecx

;Reads in user information and stores into array
	getString	[ebp + 20], [ebp + 24]
	cld
	mov 	esi, [ebp + 24]
	mov 	edi, [ebp + 8]
	INVOKE Str_length, esi

;Checks that the length of the array containing user input
;is not larger than 11 digits (limit of 32-bit register)
	cmp 	eax, 11
	jae 	FAILR

;Stores number of digits in ecx and ebx
	mov 	ecx, eax
	mov 	ebx, ecx
	xor 	eax, eax

;Takes the first character and checks whether its ASCII value is between
; 0 and 9.
DIGCHECK:
	lodsb
	cmp 	al, '0'
	jb 		FAILR
	cmp 	al, '9'
	ja	 	FAILR

;If character passes, hex value of 30h is subtracted to convert to numeric
PASSR:
	sub 	al, 30h

;Digit is then pushed onto the stack and next digit is checked
	push 	eax
	loop 	DIGCHECK

;Number of total digits in user input is copied to ecx to be used as
;loop counter
	mov 	ecx, ebx
	dec  	ecx

;Last digit entered by user is popped off stack and added to ebx which will keep running total
	pop 	eax
	mov 	ebx, 0
	add 	ebx, eax
	jmp 	PRINTR

;If user input invalid character, error message printed
FAILR:
	call 	CrLf
	displayString [ebp + 12]
	call 	CrLf
	jmp 	GETVAL

PRINTR:
;If number of digits is 1, value doesnt need to be processed
	cmp 	ecx, 0
	je 		GOOD

;If value contains 2 digits total, value in tens place
;needs to be multiplied by 10.
	cmp 	ecx, 1
	je 		DIG2

;Ten's digit is popped off stack and is multiplied by 10
;then added to running total in ebx
DIG2:
	pop 	eax
	mov 	edx, TEN
	mul 	edx
	add 	ebx, eax

;Checks if user entered string longer than 2 digits
	cmp 	ecx, 2
	jae 	DIG3
	jmp 	GOOD

;Hundreds digit is popped off stack and is multiplied by 100
;then added to running total, process is repeated for each digit position
DIG3:
	pop 	eax
	mov 	edx, HUNDRED
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 3
	jae 	DIG4
	jmp 	GOOD

DIG4:
	pop 	eax
	mov 	edx, K1
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 4
	jae		DIG5
	jmp 	GOOD

DIG5:
	pop 	eax
	mov 	edx, K10
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 5
	jae 	DIG6
	jmp 	GOOD

DIG6:
	pop 	eax
	mov 	edx, K100
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 6
	jae 	DIG7
	jmp 	GOOD

DIG7:
	pop 	eax
	mov 	edx, M1
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 7
	jae		DIG8
	jmp 	GOOD

DIG8:
	pop 	eax
	mov 	edx, M10
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 8
	jae 	DIG9
	jmp 	GOOD

DIG9:
	pop 	eax
	mov 	edx, M100
	mul 	edx
	add 	ebx, eax

	cmp 	ecx, 9
	jae 	DIG10
	jmp 	GOOD

DIG10:
	pop 	eax
	cmp 	eax, 4
	ja 		FAILR
	mov 	edx, B1
	mul 	edx
	add 	ebx, eax
	jc 		FAILR
	jmp 	GOOD

;LOOP jump range extender
JMPGATE:
	jmp 	GETVAL

GOOD:
;Value of ecx is restored
	pop 	ecx
	mov 	edx, 10
	sub 	edx, ecx
	mov 	esi, 0
	mov 	esi, [ebp + 8]

;Running total (numeric value user entered) is stored in array
;user is prompted for next value
	mov 	[esi + 4 * edx], ebx
	cdq
	loop 	JMPGATE

	mov 	ecx, 0
	mov 	eax, 0

;Calculates total value of all values entered by user
SUM:
	add 	eax, [esi + 4 * ecx]
	inc 	ecx
	cmp 	ecx, 10
	jb 		SUM
	call 	CrLf
	displayString [ebp + 16]
	call 	WriteDec
	call 	CrLf

;Calculates average of all values entered by user
	mov 	ebx, 10
	div 	ebx
	displayString [ebp + 28]
	call 	WriteDec
	call 	CrLf

	pop 	ebp
	ret 	24

ReadVal ENDP

;Description: Procedure to write a numeric value to screen.
;Receives: array (array containing numeric values), instructions5 (string)
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: eax, ecx, esi, ebp
WriteVal PROC
	
	push 	ebp
	mov 	ebp, esp
	mov 	esi, [ebp + 12]
	mov 	ecx, 0

PRINTL:
	mov 	eax, [esi + 4 * ecx]
	inc 	ecx
	call 	WriteDec
	displayString [ebp + 8]
	cmp 	ecx, 10
	jne 	PRINTL
	call 	CrLf
	pop 	ebp
	ret 	8
WriteVal ENDP

END main