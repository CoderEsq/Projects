TITLE Fibonacci Number Program (assign2.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			4/13/2015
; Date Modified:		4/18/2015
; Course:				Computer Architecture & Assembly
; Assignment:			Assignment 2
; Assignment Due Date:	4/19/2015
; Description:			Fibonacci number program which accepts an integer (n) and calculates
;                       and prints the Fibonacci numbers up to and including the nth term.

INCLUDE Irvine32.inc

UPRLIMIT = 46
LWRLIMIT = 1

.data
programtitle        BYTE    "Fibonacci Number Program by Alex Samuel", 0
instructions1       BYTE    "Please Enter your name: ", 0
greeting1			BYTE	"Hello, ", 0
greeting2			BYTE	" it is a pleasure to meet you.", 0
instructions2       BYTE    "This program will calculate and display all of the Fibonacci numbers", 0
instructions3       BYTE    "up to, and including, the nth term that you choose to enter.", 0
instructions4       BYTE    "Please Enter an integer between 1 and 46: ", 0
err1				BYTE	"You did not enter a valid integer between 1 and 46.", 0
ecprompt1 		 	BYTE 	"**EC: Program displays the numbers in aligned columns.", 0
ecprompt2 		 	BYTE 	"**EC: Program does something incredible.", 0
space15				BYTE	"              ", 0 	;used for spacing between fib numbers
onespace			BYTE	" ", 0 					;used for spacing between fib numbers
instructions5       BYTE    "The Fibonacci Numbers are as follows:", 0
endmsg              BYTE    "Thank you for using my program.", 0

playAgain			BYTE	"Would you like to run another calculation?", 0
choice1				BYTE	"Enter 1 if you would like to make another calculation", 0
choice2				BYTE	"or Enter 2 if you would like to see something incredible", 0
choice3				BYTE	"or Enter 3 if you would like to exit the program.", 0
selection			BYTE	"Your Selection: ", 0
exitmsg				BYTE	"Exiting Program...", 0


nameinput			BYTE	26	DUP(0) 	;stores user's name
fibone				DWORD	1			;value of 1st fibonacci seed
fibtwo				DWORD 	1			;value of 2nd fibonacci seed
pcounter            DWORD   2			;stores the number of fib num values that have been printed on a line
fiverr            	DWORD   5			;stores the number of fib numbers to be printed on a line
tenrr            	DWORD   10			;used to calculate number of digits
standardlength 		DWORD 	15 			;stores the number of characters between the 1st digits of subsequent fib numbers printed

;Rows of print statements used to generate picture
l1        BYTE    "###############################################################################", 0
l2        BYTE    "##############(         /#########.        .#####/      ####(      ############", 0
l3        BYTE    "############,              #####              ###/      ####(      ############", 0
l4        BYTE    "###########                 ###                ##/      ####(      ############", 0
l5        BYTE    "###########      *###(      (#       ####       #/      ####(      ############", 0
l6        BYTE    "###########      #####      /#       ####       #/      ####(      ############", 0
l7        BYTE    "###########      #####      /#       ####       #/      ####(      ############", 0
l8        BYTE    "###########      #####      /#       ####(((((((#/      ####(      ############", 0
l9        BYTE    "###########      #####      /##       (##########/      ####(      ############", 0
l10        BYTE    "###########      #####      /##(        #########/      ####(      ############", 0
l11        BYTE    "###########      #####      /####        /#######/      ####(      ############", 0
l12        BYTE    "###########      #####      /######        ######/      ####(      ############", 0
l13        BYTE    "###########      #####      /#######(        ####/      ####(      ############", 0
l14        BYTE    "###########      #####      /#########        (##/      ####(      ############", 0
l15        BYTE    "###########      #####      /###########       ##/      ####(      ############", 0
l16        BYTE    "###########      #####      /#       ####       #/      ####(      ############", 0
l17        BYTE    "###########      #####      /#       ####       #/      ####(      ############", 0
l18        BYTE    "###########      #####      /#       ####       #/      ####(      ############", 0
l19        BYTE    "###########      ,###/      (#       ####       #(      /###,      ############", 0
l20        BYTE    "###########                 ###                ###                 ############", 0
l21        BYTE    "############/             ,#####              #####,             /#############", 0
l22        BYTE    "###############.        ##########/        (##########        .################", 0
l23        BYTE    "###############################################################################", 0

.data?
fibnum				DWORD	?			;temporarily stores value of calculated fib number
nthval              DWORD   ? 			;stores user input for n fibonacci terms to print
tencounter 			DWORD 	?			;counts the number of digits in fib number
spacecounter		DWORD 	? 			;stores the number of spaces actually printed between fib numbers
numspace			DWORD 	?			;stores the number of spaces to be printed between fib numbers
replay				DWORD	?			;stores user's choice to rerun program

.code
main PROC

START:
; introduction
; Display programmer name and program title
	mov     edx, OFFSET programtitle
	call    WriteString
	call    CrLf
	call    CrLf

	mov     edx, OFFSET ecprompt1
	call    WriteString
	call    CrLf
	mov     edx, OFFSET ecprompt2
	call    WriteString
	call    CrLf
	call    CrLf

; Ask user for name
	mov     edx, OFFSET instructions1
	call    WriteString
	mov 	edx, OFFSET nameinput
	mov 	ecx, SIZEOF nameinput
	call	ReadString
	call    CrLf

;Read name from user and print greeting
	mov     edx, OFFSET greeting1
	call    WriteString
	mov     edx, OFFSET nameinput
	call    WriteString
	mov     edx, OFFSET greeting2
	call    WriteString
	call    CrLf
	call    CrLf

;userInstructions
;Print instructions to user
	mov     edx, OFFSET instructions2
	call    WriteString
	call    CrLf
	mov     edx, OFFSET instructions3
	call    WriteString
	call    CrLf
	call    CrLf

GETN:
;getUserData
;Prompt user and read in input for nth term
	mov     edx, OFFSET instructions4
	call    WriteString
	call 	ReadInt
	call    CrLf
	mov 	nthval, eax

	cmp 	nthval, LWRLIMIT 	;checks that nth term is greater than 0
	jl 		GETN
	cmp 	nthval, UPRLIMIT 	;checks that nth term is lower than 47
	jg	 	GETN

;Subtracts 2 from nth term and sets loop counter
	mov 	eax, nthval
	sub 	eax, 2
	mov 	ecx, eax

;Checks whether user entered 1 or larger
	cmp 	nthval, 1
	je 		PRINTN1
	jg 		PRINTN1N2

;displayFibs
PRINTN1:
;Print 1st Fibonacci Number and skip algorithm
	mov 	eax, fibone
	call    WriteDec
	call    CrLf
	jmp 	LABEL1

PRINTN1N2:
;Print 1st and 2nd Fibonacci Number
	mov 	eax, fibone
	call    WriteDec
	mov     edx, OFFSET space15
	call    WriteString

	mov 	eax, fibtwo
	call    WriteDec
	mov     edx, OFFSET space15
	call    WriteString

;If nth term is equal to 2, skip algorithm
	cmp 	nthval, 2
	je 		LABEL1

CALCFIB:
;Calculates fibonacci number
	mov 	eax, 0
	mov 	spacecounter, eax
	mov 	tencounter, eax
	mov 	eax, fibone			
	add 	eax, fibtwo
	mov 	fibnum, eax

	mov 	eax, fibtwo
	mov 	fibone, eax

	mov 	eax, fibnum				
	mov 	fibtwo, eax
	call    WriteDec

CALCSPACE:
;Counts the digits in the most recently printed fib number
	mov     edx, 0
	div 	tenrr
	inc 	tencounter
	cmp 	eax, 1
	jge 	CALCSPACE
	jl  	SPACEPRINT

RANGE:
;This serves as a JMP/LOOP range extender (otherwise target would have been
;out of memory range of later occurring loops)
	loop 	CALCFIB
	jmp 	LABEL1

SPACEPRINT:
;Calculates the number of spaces to print between fib numbers
	mov 	eax, 15
	sub 	eax, tencounter
	mov 	numspace, eax

SPACEPRINT2:
;Prints spacing between fib numbers (larger numbers with more digits require fewer spaces between them)
;(Extra Credit Option 1)
	mov     edx, OFFSET onespace
	call    WriteString
	inc 	spacecounter
	mov 	eax, spacecounter
	cmp 	eax, numspace
	jl 		SPACEPRINT2
	jge 	CALCFIB2

CALCFIB2:
;Counts how many fib numbers have been printed on the same line
;and moves to next line if 5 numbers have been printed
 	inc		pcounter
 	mov 	eax, pcounter
	mov     edx, 0
	div 	fiverr
	cmp 	edx, 0
	je 		NEXTLINE
	jmp 	RANGE

NEXTLINE:
	call    CrLf
	jmp 	RANGE

LABEL1:
;farewell - resets counters and displays terminating message
	mov 	eax, 1
	mov 	fibone, eax
	mov 	fibtwo, eax
	mov 	eax, 2
	mov 	pcounter, eax
	call    CrLf
	call    CrLf
	mov     edx, OFFSET endmsg
	call    WriteString
	call    CrLf
	call    CrLf

PROMPT:
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
	mov     edx, OFFSET choice3
	call    WriteString
	call    CrLf
	call    CrLf
	mov     edx, OFFSET selection
	call    WriteString
	call 	ReadInt
	mov 	replay, eax
	call    CrLf
	call    CrLf

;If user selected to rerun, program starts at beginning 
	mov 	eax, replay
	cmp 	eax, 1
	je 		START

;If user selected to see something incredible 
	cmp 	eax, 2
	je 		INCREDIBLE

;If user selected to exit, program prints terminating message and ends 
	cmp 	eax, 3
	je 		ENDING
	jmp 	PROMPT

INCREDIBLE:
;Prints ASCII image (Extra Credit Option 2)
	mov 	eax, white + (lightRed * 16)
	call 	SetTextColor
	mov     edx, OFFSET l1
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l2
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l3
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l4
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l5
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l6
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l7
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l8
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l9
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l10
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l11
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l12
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l13
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l14
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l15
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l16
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l17
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l18
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l19
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l20
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l21
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l22
	call    WriteString
	call    CrLf
	mov     edx, OFFSET l23
	call    WriteString
	call    CrLf
	mov 	eax, lightgray + (black * 16)
	call 	SetTextColor
	call    CrLf
	jmp 	PROMPT

ENDING:
;If user did not select to rerun, program exits
	call    CrLf
	mov     edx, OFFSET exitmsg
	call    WriteString
	call    CrLf
	call    CrLf

	exit	; exit to operating system
main ENDP

END main