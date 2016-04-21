TITLE Negative Average Calculator Program (assign3.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			4/28/2015
; Date Modified:		5/3/2015
; Course:				CS 271-400
; Assignment:			Assignment 3
; Assignment Due Date:	5/3/2015
; Description:			Calculates the average value of a series of negative
;						integers input by the user.

INCLUDE Irvine32.inc

UPRLIMIT = -1
LWRLIMIT = -100
NEGLIMIT = 0

.data
programtitle        BYTE    "Negative Integers Average Calculator by Alex Samuel", 0
instructions1       BYTE    "Please Enter your name: ", 0
greeting1			BYTE	"Hello, ", 0
greeting2			BYTE	" it is a pleasure to meet you.", 0
instructions2       BYTE    "This program will calculate and display the average of a series of", 0
instructions3       BYTE    "negative integers that you choose to enter. When you would like", 0
instructions4		BYTE	"to calculate the average value, simply enter a non-negative value.", 0
instructions5       BYTE    "Please Enter an integer between -100 and -1: ", 0
err1				BYTE	"ERROR: You did not enter a valid integer between -100 and -1.", 0
ecprompt1 		 	BYTE 	"**EC: Number the lines during user input.", 0
specialmsg			BYTE	"Since you did not enter any negative values, the program will terminate.", 0
numnegmsg1          BYTE    "You entered ", 0
numnegmsg2          BYTE    " valid numbers.", 0
sumnegmsg          	BYTE    "The sum of your valid numbers is ", 0
avgnegmsg          	BYTE    "The rounded average is ", 0
decmsg				BYTE	".", 0
linespace			BYTE	":     ", 0
endmsg              BYTE    "Thank you for using my program, ", 0
exitmsg				BYTE	"Exiting Program...", 0


nameinput			BYTE	26	DUP(0) 	;stores user's name
negcounter          DWORD   0 			;counter for number of values entered by user
negval              DWORD   0 			;stores user input
negsum              DWORD   0 			;stores sum of values
linecounter 		DWORD	0			;stores line counter

.data?
negavg 				DWORD 	? 	;stores value of quotient of avg
negremainder 		DWORD 	? 	;stores value of remainder of average
newremainder		DWORD 	?	;stores remainder from each division operation
newdiv				DWORD	?	;stores new numerator for each division operation
decimal1			DWORD	?	;stores value of first decimal



.code
main PROC

; Display programmer name and program title
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET programtitle 	
	call    WriteString
	call    CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET ecprompt1
	call    WriteString
	call    CrLf
	call    CrLf

; Ask user for name
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET instructions1
	call    WriteString
	mov 	edx, OFFSET nameinput
	mov 	ecx, SIZEOF nameinput
	call	ReadString
	call    CrLf

;Read name from user and print greeting
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET greeting1
	call    WriteString
	mov     edx, OFFSET nameinput
	call    WriteString
	mov     edx, OFFSET greeting2
	call    WriteString
	call    CrLf
	call    CrLf

;Print instructions to user
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET instructions2
	call    WriteString
	call    CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET instructions3
	call    WriteString
	call    CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET instructions4
	call    WriteString
	call    CrLf

GETN:
;Prompt user and read in input for negative values
	call    CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter
	mov     edx, OFFSET instructions5
	call    WriteString
	call 	ReadInt
	call    CrLf
	mov 	negval, eax

	cmp 	negval, NEGLIMIT 	;ensures that input is less than 0
	jge 	AVG
	cmp 	negval, LWRLIMIT 	;ensures that input is greater than -100
	jl 		ERROR
	cmp 	negval, UPRLIMIT 	;ensures that input is lower than -1
	jg	 	ERROR
	jmp 	ACCUM

ERROR:
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 		
	mov     edx, OFFSET err1
	call    WriteString
	jmp 	GETN

ACCUM:
	mov 	eax, negval
	add 	eax, negsum
	mov 	negsum, eax
	inc 	negcounter
	jmp 	GETN

;Calculates average value
AVG:
	mov 	eax, negcounter
	cmp 	eax, 0
	je 		DISPLAY
	mov 	eax, negsum
	cdq
	mov 	ebx, negcounter
	idiv 	ebx
	mov 	negavg, eax
	mov 	negremainder, edx

;Division operations used to calculate decimal
;Checks if remainder=0
	mov 	eax, negremainder
	cmp 	eax, 0
	je 		DISPLAY

;First decimal value is calculated
	mov 	ebx, 10
	mul 	ebx
	mov 	negremainder, eax

	mov 	eax, negremainder
	cdq
	mov 	ebx, negcounter
	idiv 	ebx
	mov 	decimal1, eax
	mov 	newremainder, edx

;Rounds quotient
ROUND:
;Sets 1st decimal value to 0
	mov 	eax, decimal1
	cmp 	eax, -5
	jge 	DISPLAY

;Rounds quotient up 1
	mov 	eax, negavg
	add 	eax, 1
	mov 	negavg, eax

;Displays number of values entered, sum, and rounded average if neg values entered
DISPLAY:
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET numnegmsg1
	call    WriteString
	mov 	eax, negcounter
	call 	WriteDec
	mov     edx, OFFSET numnegmsg2
	call    WriteString
	call 	CrLf
	cmp 	eax, 0
	je 		SPECIAL
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET sumnegmsg
	call    WriteString
	mov 	eax, negsum
	call 	WriteInt
	call 	CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET avgnegmsg
	call    WriteString
	mov 	eax, negavg
	call 	WriteInt
	call 	CrLf
	jmp 	GOODBYE

;Prints special message in case no neg values were entered
SPECIAL:
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET specialmsg
	call    WriteString
	call 	CrLf
	call 	CrLf

;Prints terminating messages to user.
GOODBYE:
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter
	mov     edx, OFFSET endmsg
	call    WriteString
	mov     edx, OFFSET nameinput
	call    WriteString
	mov     edx, OFFSET decmsg
	call    WriteString
	call 	CrLf
	call 	CrLf
	mov 	eax, linecounter
	call 	WriteDec
	mov     edx, OFFSET linespace
	call    WriteString
	inc 	linecounter 
	mov     edx, OFFSET exitmsg
	call    WriteString
	call    CrLf
	call    CrLf

	exit	; exit to operating system
main ENDP

END main