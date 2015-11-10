/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 3/8/2015
*   Last Modification Date:       3/8/2015
*   Filename:                     lab10.cpp
*
*   Overview:   This program can find the nth fibonacci number using non-recursive and
*               recursive functions. This program can also calculate the nth factorial
*               using non-tail recursive factorial and tail-recursive factorial functions.
*
*   Input:  The input shall consist of an integer of the nth fibonacci
*           or factorial to be calculated.
*
*   Output: The output of the program will be the fibonnaci value or factorial value
*           as well as the execution time of each function.
****************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::stringstream;
using std::numeric_limits;
using std::max;
using namespace std::chrono;

/*********************************************************************
** Function: FibonacciNR
** Description: Non-recursive function used to calculate fibonacci numbers.
** Parameters: unsigned long long int is the datatype of n (the nth fibonacci number)
** Pre-Conditions: user has entered value of n
** Post-Conditions: returns valid fibonacci number
*********************************************************************/
// design of this function came from:
// http://www.codeproject.com/Tips/109443/Fibonacci-Recursive-and-Non-Recursive-C
void FibonacciNR(unsigned long long int n);

/*********************************************************************
** Function: FibonacciR
** Description: Recursive function used to calculate fibonacci numbers.
** Parameters: unsigned long long int is the datatype of n (the nth fibonacci number)
** Pre-Conditions: user has entered value of n
** Post-Conditions: returns valid fibonacci number
*********************************************************************/
// design of this function came from:
// http://www.codeproject.com/Tips/109443/Fibonacci-Recursive-and-Non-Recursive-C
unsigned long long int FibonacciR(unsigned long long int n);

/*********************************************************************
** Function: NTRecursive
** Description: Not-Tail Recursive Function used to calculate factorial values
** Parameters: unsigned long long int is the datatype of n (n! factorial)
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
// design of this function came from lab10 assignment sheet
unsigned long long int NTRecursive(unsigned long long int n);

/*********************************************************************
** Function: TRecursiveHelper
** Description: Tail Recursive Function used to calculate factorial values
** Parameters: unsigned long long int is the datatype of n (n! factorial)
**              and also the factorial solution is also a parameter.
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
// design of this function came from lab10 assignment sheet
unsigned long long int TRecursiveHelper (unsigned long long int  n, unsigned long long int result);

/*********************************************************************
** Function: TRecursive
** Description: Function that calls on TRecursiveHelper to calculate factorial values
** Parameters: unsigned long long int is the datatype of n (n! factorial)
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
// design of this function came from lab10 assignment sheet
unsigned long long int TRecursive(unsigned long long int n);

/*********************************************************************
** Function: intCheck
** Description: Function used to check if input is valid integer between set min and max values
** Parameters: integers describing permissible min and max values for input.
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
//the design of this function was influenced by the discussion on
//http://r3dux.org/2011/11/how-to-get-valid-integer-input-in-c-a-stupidly-long-solution-to-a-stupidly-simple-problem/#comment-7175
int intCheck(int minRange, int maxRange);

int main()
{

bool menuOn = true;

do{
        cout <<  (double) std::chrono::high_resolution_clock::period::num
             / std::chrono::high_resolution_clock::period::den;

        cout << endl << "\t FIBONACCI AND FACTORIAL NUMBER GENERATOR\n" << endl

             << "Select which function you would like to execute.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     All 4 Function Types" << endl
             << "   2:     Iterative Fibonacci Function" << endl
             << "   3:     Recursive Fibonacci Function" << endl
             << "   4:     Non-Tail Recursive Factorial Function" << endl
             << "   5:     Tail Recursive Factorial Function" << endl
             << "   6:     EXIT" << endl << endl;

             cout << "Your Selection: ";

             int menuChoice;
             menuChoice = intCheck(1, 6);

             if(menuChoice == 6)
             {
                 cout << endl << "Exiting program..." << endl;
                 exit(1);
             }

             cout << endl << "Enter the nth fibonacci number OR factorial you would like to calculate." << endl;
             unsigned long long int fibNum;
             cin >> fibNum;

             cout << endl << endl;
             cout << "--------------------------------------------------------------------";
             cout << "------------" << endl;

//switch statement allows user to select which action they would like to execute.
switch(menuChoice)
             {
             case 1:
                 {
                    FibonacciNR(fibNum);

                    unsigned long long int rFibN;
                    high_resolution_clock::time_point t3 = high_resolution_clock::now();
                    rFibN = FibonacciR(fibNum);
                    high_resolution_clock::time_point t4 = high_resolution_clock::now();
                    auto duration2 = duration_cast<nanoseconds>(t4-t3).count();
                    cout << "The nth fibonacci number is " << rFibN << endl;
                    cout << endl << "The Recursive function runtime is: " << duration2 << endl << endl;

                     unsigned long long int rFibN2;
                     high_resolution_clock::time_point t5 = high_resolution_clock::now();
                     rFibN2 = NTRecursive(fibNum);
                     high_resolution_clock::time_point t6 = high_resolution_clock::now();
                     auto duration3 = duration_cast<nanoseconds>(t6-t5).count();
                     cout << fibNum << " factorial is " << rFibN2 << endl;
                     cout << endl << "The Non-Tail Recursive Factorial function runtime is: " << duration3 << endl << endl;

                     unsigned long long int rFibN3;
                     high_resolution_clock::time_point t7 = high_resolution_clock::now();
                     rFibN3 = TRecursive(fibNum);
                     high_resolution_clock::time_point t8 = high_resolution_clock::now();
                     auto duration4 = duration_cast<nanoseconds>(t8-t7).count();
                     cout << fibNum << " factorial is " << rFibN3 << endl;
                     cout << endl << "The Tail Recursive Factorial function runtime is: " << duration4 << endl << endl;
                 }
                break;
             case 2:
                FibonacciNR(fibNum);
                break;
             case 3:
                 {
                unsigned long long int rFibN;
                high_resolution_clock::time_point t3 = high_resolution_clock::now();
                rFibN = FibonacciR(fibNum);
                high_resolution_clock::time_point t4 = high_resolution_clock::now();
                auto duration2 = duration_cast<nanoseconds>(t4-t3).count();
                cout << "The nth fibonacci number is " << rFibN << endl;
                cout << endl << "The Recursive function runtime is: " << duration2 << endl << endl;
                 }
                break;
             case 4:
                 {
                     unsigned long long int rFibN2;
                     high_resolution_clock::time_point t5 = high_resolution_clock::now();
                     rFibN2 = NTRecursive(fibNum);
                     high_resolution_clock::time_point t6 = high_resolution_clock::now();
                     auto duration3 = duration_cast<nanoseconds>(t6-t5).count();
                     cout << fibNum << " factorial is " << rFibN2 << endl;
                     cout << endl << "The Non-Tail Recursive Factorial function runtime is: " << duration3 << endl << endl;
                 }
                break;
             case 5:
                {
                     unsigned long long int rFibN3;
                     high_resolution_clock::time_point t7 = high_resolution_clock::now();
                     rFibN3 = TRecursive(fibNum);
                     high_resolution_clock::time_point t8 = high_resolution_clock::now();
                     auto duration4 = duration_cast<nanoseconds>(t8-t7).count();
                     cout << fibNum << " factorial is " << rFibN3 << endl;
                     cout << endl << "The Tail Recursive Factorial function runtime is: " << duration4 << endl << endl;
                 }
                break;
             case 6:
                exit(1);
                break;
             }
}
while(menuOn);

return 0;

}

//function is based off design from:
//http://www.codeproject.com/Tips/109443/Fibonacci-Recursive-and-Non-Recursive-C
void FibonacciNR(unsigned long long int n)
{
    unsigned long long int first = 0;
   	unsigned long long int second = 1;
   	unsigned long long int counter = 2;
   	high_resolution_clock::time_point t1 = high_resolution_clock::now();
   	while(counter < n)
   	{
   		unsigned long long int temp = second;
   		second = first + second;
   		first = temp;
   		++counter;
   	}
   	unsigned long long int FibN = first + second;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(t2-t1).count();

   	if(n==0)
    {
        cout << "The nth fibonacci number is " << 0 << endl;
    }

   	else
    {
        cout << "The nth fibonacci number is " << FibN << endl;
    }

    cout << endl << "The Iterative function runtime is: " << duration << endl << endl;
}

//function is based off design from:
//http://www.codeproject.com/Tips/109443/Fibonacci-Recursive-and-Non-Recursive-C
unsigned long long int FibonacciR(unsigned long long int n)
{
    if(n == 0)
    {
        return 0;
    }

   	else if(n == 1)
    {
        return 1;
    }

    else
        {
        return FibonacciR(n-1) + FibonacciR(n-2);
        }
}

//function is based off design from lab10 assignment
unsigned long long int NTRecursive(unsigned long long int n)
{

if (n == 1)
{
    return 1;
}

else
{
    return n * NTRecursive(n-1);
}
}

//function is based off design from lab10 assignment
unsigned long long int TRecursiveHelper (unsigned long long int  n, unsigned long long int result) {
if (n == 1)
{
    return result;
}
else
{
    return TRecursiveHelper(n-1,n*result);
}
}

//function is based off design from lab10 assignment
unsigned long long int TRecursive(unsigned long long int n)
{
    return TRecursiveHelper(n,1);
}


//function to check if input is a valid integer between a minimum and maximum value.
//the design of this function was influenced by the discussion on
//http://r3dux.org/2011/11/how-to-get-valid-integer-input-in-c-a-stupidly-long-solution-to-a-stupidly-simple-problem/#comment-7175
int intCheck(int minRange, int maxRange)
{
	int input;

	while ( ( !(cin >> input) ) || (input < minRange) || (input > maxRange) || cin.peek() != '\n')
	{
		cout << "Please enter an integer between " << minRange << " and " << maxRange << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return input;
}
