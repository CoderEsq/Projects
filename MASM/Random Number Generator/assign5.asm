TITLE Random Number Generator (assign5.asm)

; Author:				Alex Samuel
; Email:				samuelal@onid.oregonstate.edu 
; Date Created:			5/16/2015
; Date Modified:		5/19/2015
; Course:				CS 271-400
; Assignment:			Assignment 5
; Assignment Due Date:	5/24/2015
; Description:			Random number generator program which accepts an integer (n) and calculates
;                       and prints n random numbers between 100 and 999 and stores them in consecutive order.

INCLUDE Irvine32.inc

MINLIMIT = 10
MAXLIMIT = 200
LOWLIMIT = 100
HIGHLIMIT = 999

.data
programtitle        BYTE    "Random Number Generator by Alex Samuel", 0
instructions1       BYTE    "This program will generate and display a list of random numbers between the", 0
instructions2       BYTE    "values of 100 and 999. You may choose to display between 10 and 200 values.", 0
instructions3       BYTE    "Please select how many integers you would like to display: ", 0
err1				BYTE	"You did not enter a valid integer between 10 and 200.", 0
space3				BYTE	"   ", 0 	;used for spacing between random numbers
instructions5       BYTE    "The random numbers are as follows:", 0
endmsg              BYTE    "Thank you for using my program.", 0
exitmsg				BYTE	"Exiting Program...", 0
stitle				BYTE	"Sorted Array", 0
untitle				BYTE	"Unsorted Array", 0
medianval			BYTE	"The Median Value of the array is: ", 0

.data?

nthval              DWORD   ? 	;stores user input for n random numbers to print
rarray 				DWORD MAXLIMIT DUP(?)		;creates uninitialized array of size n

.code
main PROC
	call 	Randomize 		;Seeds random number generator

	;Calls procedure to display introductory message
	push 	OFFSET programtitle
	push 	OFFSET instructions1
	push 	OFFSET instructions2
	call	introduction
	
	;Calls procedure to obtain input from user
	push 	OFFSET instructions3
	push 	OFFSET nthval
	call 	getUserData

	;Calls procedure to fill array with random values
	push 	OFFSET rarray
	push 	nthval
	call 	fillArray

	;Calls procedure to display unsorted array of random values
	push 	OFFSET space3
	push 	nthval
	push 	OFFSET rarray
	push 	OFFSET untitle
	call 	display

	;Calls procedure to sort array
	push 	OFFSET rarray
	push 	nthval
	call 	sortList

	;Calls procedure to calculate median value of sorted array
	push 	OFFSET medianval
	push 	nthval
	push 	OFFSET rarray
	call	median

	;Calls procedure to display sorted array of random values
	call 	CrLf
	push 	OFFSET space3
	push 	nthval
	push 	OFFSET rarray
	push 	OFFSET stitle
	call 	display

	;Calls procedure to display terminating message
	push 	OFFSET endmsg
	push 	OFFSET exitmsg
	call 	farewell

	exit	; exit to operating system
main ENDP

;Description: Procedure to display introductory message
;Receives: programtitle, instructions1, instructions2 are global variables (strings)
;Returns: NONE
;Preconditions:  Input parameters must be null terminated strings
;Registers Changed: edx
introduction PROC

	push 	ebp
	mov 	ebp, esp

;Display programmer name and TITLE
	mov     edx, [ebp + 16]
	call    WriteString
	call    CrLf
	call    CrLf

;Display instructions
	mov     edx, [ebp + 12]
	call    WriteString
	call    CrLf

	mov     edx, [ebp + 8]
	call    WriteString
	call    CrLf
	call    CrLf

	pop 	ebp
	ret 	12
introduction ENDP

;Description: Procedure to get user input for number of random values to generate.
;Receives: nthval is a global variable to store the input value, instructions3 is a string
;Returns: User input value for global variable nthval
;Preconditions:  NONE
;Registers Changed: edx, ebx, eax
getUserData	PROC

	push 	ebp
	mov 	ebp, esp

;Ask user for how many numbers they want displayed and store value
	mov     edx, [ebp + 12]
	call    WriteString
	call 	ReadInt
	mov 	ebx, [ebp + 8]
	mov		[ebx], eax
	call    CrLf

;Calls validate procedure to check user input
	push nthval
	push OFFSET err1
	push OFFSET MINLIMIT
	push OFFSET MAXLIMIT
	call validate

	pop 	ebp
	ret 	8
getUserData	ENDP

;Description: Procedure to validate user input
;Receives: nthval (global variable to store user input), err1 (string containing error message), 
;MINLIMIT (constant containing value of minimum value permitted), MAXLIMIT (constant containing value of maximum value permitted)
;Returns: A valid number for nthval
;Preconditions:  NONE
;Registers Changed: eax, ebx, ecx, edx
validate PROC
	
	push 	ebp
	mov 	ebp, esp

	mov 	eax, [ebp + 20]
	mov 	ebx, [ebp + 12]
	mov 	ecx, [ebp + 8]
	cmp 	eax, ebx 	;checks that nth term is greater than 10
	jl 		ERROR
	cmp 	eax, ecx 	;checks that nth term is less than 200
	jg	 	ERROR
	jmp 	GOOD

;If nth term is invalid, error message printed and getUserData	procedure called
ERROR:
	mov     edx, [ebp + 16]
	call    WriteString
	call    CrLf
	call    CrLf
	push 	OFFSET instructions3
	push 	OFFSET nthval
	call 	getUserData

GOOD:
	pop 	ebp
	ret 	16 	
validate ENDP

;Description: Procedure to fill array with random values
;Receives: nthval (global variable to store number of elements in array), rarray (array to hold values)
;Returns: An array filled with unsorted random values.
;Preconditions:  NONE
;Registers Changed: ecx, eax, ebx
fillArray PROC
	push 	ebp
	mov 	ebp, esp

	mov 	ecx, [ebp + 8] 		;nthval serves as loop counter
	mov 	esi, [ebp + 12]
	mov 	ebx, 0 				;serves as array index, incremented each loop

;Loop to genereate and insert random values into array
INSERT:
	mov 	eax, 900
	call 	RandomRange
	add 	eax, 100	;Adds 100 to generated random value

	mov    	[esi + 4 * ebx], eax
	mov    	eax, [esi + 4 * ebx]
	inc 	ebx 		;Advances array index
	loop 	INSERT

	pop 	ebp
	ret 	8
fillArray ENDP

;Description: Procedure to print array of values
;Receives: space3 and title message are strings, nthval (global variable to store number of elements in array), 
;rarray (array to hold values)
;Returns: NONE
;Preconditions:  Array contains values
;Registers Changed: eax, ecx, ebx, edx
display PROC
	push 	ebp
	mov 	ebp, esp

	mov 	ecx, [ebp + 16]		;nthval serves as loop counter
	mov 	esi, [ebp + 12]
	mov 	ebx, 0 				;serves as array index, incremented each loop
	mov     edx, [ebp + 8]
	call    WriteString 		;Prints title of unsorted array
	call    CrLf
	call    CrLf

PRINT:
	mov    	eax, [esi + 4 * ebx]	;prints number to screen
	call 	WriteDec
	mov     edx, [ebp + 20] 	;inserts space after each number is printed
	call    WriteString
	inc 	ebx
	mov 	eax, ebx
	mov 	edi, 10
	mov 	edx, 0
	div 	edi
	cmp 	edx, 0 				;checks if 10th number has been printed
	je 		NEXTLINE
	loop 	PRINT
	jmp 	FINISH

NEXTLINE: 						;Inserts new line after every 10th number printed
	call    CrLf
	loop 	PRINT

FINISH:
	call    CrLf
	pop 	ebp
	ret 	12
display	ENDP

;The design for this Gnome Sort function was influenced by the
;discussion on http://www.miguelcasillas.com/?p=340
;Description: Procedure to sort random values within the array.
;Receives: nthval (global variable to store number of elements in array), 
;rarray (array to hold values)
;Returns: A sorted array
;Preconditions:  Array must contain values
;Registers Changed: ecx, eax, edx, ebx
sortList PROC
	push 	ebp
	mov 	ebp, esp

	mov 	ecx, [ebp + 8] 		;nthval serves as loop counter
	mov 	esi, [ebp + 12]
	mov 	eax, 0

BEGIN:
	cmp 	eax, ecx
	jge 	ENDL

	cmp 	eax, 0
	je 		ADVANCE

INNER:
	mov 	ebx, [esi] 			;points to later array element
	mov 	edx, [esi - 4]		;points to earlier array element
	cmp 	edx, ebx			;Compares whether earlier array element is larger than later element
	jge 	ADVANCE 			;If 1st element is larger, values are not switched

	push 	[esi]
	push 	[esi - 4]
	call 	exchange 			;Calls procedure to switch elements, only occurs if 2nd element is larger than 1st element

	sub 	esi, 4 				;Decrements esi pointer
	dec 	eax
	jmp 	BEGIN

ADVANCE:
	inc 	eax
	add 	esi, 4 				;increments esi pointer
	jmp 	BEGIN

ENDL:
	pop 	ebp
	ret 	8
sortList ENDP

;Description: Exchanges values at two consecutive positions within an unsorted array
;Receives: Memory adddresses of two consecutive array elements
;Returns: Array elements have been switched
;Preconditions:  NONE
;Registers Changed: ebx, edi
exchange PROC
	push 	ebp
	mov 	ebp, esp

	mov 	edi, [esi]
	mov 	ebx, [esi - 4]
	mov 	[esi], ebx
	mov 	[esi - 4], edi

	pop 	ebp
	ret 	8
exchange ENDP

;Description: Procedure to calculate median value of a sorted array of values.
;Receives: medianval (string), nthval (number of elements within array), rarray (sorted array of values)
;Returns: NONE
;Preconditions:  Array must contain values
;Registers Changed: edx, eax, ebx, ecx
median PROC
	push 	ebp
	mov 	ebp, esp

	mov 	eax, [ebp + 12]
	mov 	esi, [ebp + 8]
	mov 	ebx, 2

;Divides number of elements by 2 in order to determine whether there is an even or odd
;number of elements within the array.
	mov 	edx, 0
	div 	ebx
	cmp 	edx, 0
	je 		EVENARR
	jmp 	ODDARR

;If even number of elements, then 2 center-most elements must be averaged to calculate median
EVENARR:
	mov 	ecx, eax
	dec 	ecx
	mov    	eax, [esi + 4 * eax]
	add 	eax, [esi + 4 * ecx]
	mov 	edx, 0
	div  	ebx 		;eax contains average
	mov 	ecx, eax 	
	mov 	eax, edx  	;Now need to find 1st decimal place in order to determine rounding
	mov 	ebx, 10
	mul 	ebx
	mov 	ebx, 2
	mov 	edx, 0
	div 	ebx
	cmp 	eax, 5 		;If 1st decimal is < 5, quotient will be rounded down 
	jae 	ROUNDUP 	;If 1st decimal is >= 5, quotient will be rounded up
	jmp 	NOROUND

ROUNDUP:
	mov 	eax, ecx 
	inc 	eax
	jmp 	PRINTMED

NOROUND:
	mov 	eax, ecx
	jmp 	PRINTMED

;If there are an odd number of elements, the median value will be at an index equivalent
;to the quotient.
ODDARR:
	mov    	eax, [esi + 4 * eax]

;Prints the median value
PRINTMED:
	mov     edx, [ebp + 16]
	call    CrLf
	call    WriteString
	call 	WriteDec
	call    CrLf

	pop 	ebp
	ret 	12
median ENDP

;Description: Procedure to print ending messages
;Receives: endmsg and exitmsg are strings
;Returns: NONE
;Preconditions:  NONE
;Registers Changed: edx
farewell PROC

	push 	ebp
	mov 	ebp, esp

	call    CrLf
	call    CrLf
	mov     edx, [ebp + 12]
	call    WriteString
	call    CrLf
	call    CrLf
	mov     edx, [ebp + 8]
	call    WriteString
	call    CrLf
	call    CrLf

	pop 	ebp
	ret 	8
farewell ENDP

END main