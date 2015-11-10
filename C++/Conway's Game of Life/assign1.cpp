/*****************************************************
*   Author:                       Alex Samuel
*   Date Created:                 1/11/2015
*   Last Modification Date:       1/18/2015
*   Filename:                     assign1.cpp
*
*   Overview:   This program is an implementation of Conway's
*   Game of Life. Users may run simulations of four different
*   patterns.
*
*
*   Input:  The input shall consist of integers to select
*   options and to enter coordinates.
*
*
*   Output: The output of the program will be a display
*   of the pattern.
*
***************************************************/

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;


/*********************************************************************
** Function: displayBoard
** Description: Function used to display pattern on screen.
** Parameters: string array, integer array, and integer
** Pre-Conditions:  int array must contain state of cells
** Post-Conditions: string array must be updated and printed to screen
*********************************************************************/
void displayBoard(string cellSym[][100], int cellNum[][100], int rows);

/*********************************************************************
** Function: brain
** Description: Function used to determine how cells are born and die (implement rules
** of game).
** Parameters: integer array and integer
** Pre-Conditions: integer array must contain values describing current cell state
** Post-Conditions: integer array must contain values describing next cell state
** after rules have been applied.
*********************************************************************/
void brain(int cellNum[][100], int rows);

/*********************************************************************
** Function: intCheck
** Description: Function used to check if input is valid integer (no bounds).
** Parameters: NONE
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
int intCheck();

/*********************************************************************
** Function: intCheck
** Description: Function used to check if input is valid integer between set min and max values
** Parameters: integers describing permissible min and max values for input.
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid integer
*********************************************************************/
int intCheck(int minRange, int maxRange);


int main()
{
string cells[100][100];     //creates array of cells
int cellVal[100][100];      //creates array off cell's state (alive or dead)
const string alive = "O";   //used to test various display options for live cells
const string dead = " ";    //used to test various display options for dead cells

bool menuAgain = true;
while (menuAgain == true){ //user will be able to repeatedly return to menu
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            cells[x][y] = dead;
            cellVal[x][y] = 0;

            /*
            The following was used to test possible border options
            cells[0][y] = border;
            cells[xSize-1][y] = border;
            cells[x][0] = border;
            cells[x][ySize-1] = border;
            */
        }
    }

        //menu displayed to user
        cout << endl << "\t WELCOME TO CONWAY'S GAME OF LIFE!\n" << endl
             << "   The simulation will be displayed on a grid 80 cells wide and 22 cells tall." << endl

             << "Select which pattern you would like to run from the choices below.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Simple Oscillator" << endl
             << "   2:     Glider" << endl
             << "   3:     Gosper Glider Gun" << endl
             << "   4:     Clock" << endl
             << "   5:     EXIT" << endl << endl;



             cout << "Your Selection: ";

//checks user input to make sure pattern choice is valid integer between 1 and 5
             int patChoice = intCheck(1, 5);
             cout << endl;

             if (patChoice == 5)    //checks if user chooses to exit program
                {
                    exit(1);
                }

            cout << "Would you like to specify a specific starting location for the pattern?" << endl
                 << "Enter the integer corresponding to your choice."
                 << endl << endl
                 << "   1:     No, place the pattern at the center of the display." << endl
                 << "   2:     Yes." << endl << endl
                 << "Your Selection: ";

 //checks user input to make sure choice is valid integer between 1 and 2
             int posChoice = intCheck(1, 2);
             cout << endl;

//traditional x-y coordinate system is equivalent to [row][column] system in C++.
             int xCen;      //stores y-coordinate of where pattern should be centered
             int yCen;      //stores x-coordinate of where pattern should be centered

             if (posChoice == 1)    //[21][50] is center of display
                {
                    xCen = 21;
                    yCen = 50;
                }

             if (posChoice == 2)
                {
            cout << "Please enter the X coordinate as an integer where you would like the " << endl
                 << "pattern centered. The X-values increase from left to right. The center " << endl
                 << "of the display is set at X = 40." << endl
                 << "You may enter a value between 0 and 80." << endl << endl
                 << "X coordinate: ";

             yCen = intCheck(0, 80) + 10;    //checks input, must be integer between 0 and 80
             cout << endl;

            cout << "Please enter the Y coordinate as an integer where you would like the " << endl
                 << "pattern centered. The Y-values increase from bottom to top. The center " << endl
                 << "of the display is set at Y = 11." << endl
                 << "You may enter a value between 0 and 22." << endl << endl
                 << "Y coordinate: ";

             xCen = 32 - intCheck(0, 22);    //checks if input is valid integer between 0 and 22
             cout << endl;
                }

//sets the initial state based on pattern choice
//coordinate information for each pattern was obtained from conwaylife.com
             switch(patChoice)
             {
             case 1:
                 // simple oscillator
                 cellVal[xCen][yCen] = 1;
                 cellVal[xCen][yCen - 1] = 1;
                 cellVal[xCen][yCen + 1] = 1;
                 break;

             case 2:
                // pure glider generator
                cellVal[xCen][yCen] = 1;
                cellVal[xCen + 1][yCen] = 1;
                cellVal[xCen][yCen - 1] = 1;
                cellVal[xCen][yCen + 1] = 1;
                cellVal[xCen - 2][yCen - 5] = 1;
                cellVal[xCen - 2][yCen - 6] = 1;
                cellVal[xCen - 2][yCen - 7] = 1;
                cellVal[xCen - 3][yCen - 5] = 1;
                cellVal[xCen - 4][yCen - 5] = 1;
                cellVal[xCen + 2][yCen + 5] = 1;
                cellVal[xCen + 2][yCen + 6] = 1;
                cellVal[xCen + 2][yCen + 7] = 1;
                cellVal[xCen + 3][yCen + 5] = 1;
                cellVal[xCen + 4][yCen + 5] = 1;
                break;

             case 3:
                // glider gun
                cellVal[xCen - 4][yCen + 6] = 1;
                cellVal[xCen - 3][yCen + 4] = 1;
                cellVal[xCen - 3][yCen + 6] = 1;
                cellVal[xCen - 2][yCen - 6] = 1;
                cellVal[xCen - 2][yCen - 5] = 1;
                cellVal[xCen - 2][yCen + 2] = 1;
                cellVal[xCen - 2][yCen + 3] = 1;
                cellVal[xCen - 2][yCen + 16] = 1;
                cellVal[xCen - 2][yCen + 17] = 1;
                cellVal[xCen - 1][yCen - 7] = 1;
                cellVal[xCen - 1][yCen - 3] = 1;
                cellVal[xCen - 1][yCen + 2] = 1;
                cellVal[xCen - 1][yCen + 3] = 1;
                cellVal[xCen - 1][yCen + 16] = 1;
                cellVal[xCen - 1][yCen + 17] = 1;
                cellVal[xCen][yCen - 18] = 1;
                cellVal[xCen][yCen - 17] = 1;
                cellVal[xCen][yCen - 8] = 1;
                cellVal[xCen][yCen - 2] = 1;
                cellVal[xCen][yCen + 2] = 1;
                cellVal[xCen][yCen + 3] = 1;
                cellVal[xCen + 1][yCen - 18] = 1;
                cellVal[xCen + 1][yCen - 17] = 1;
                cellVal[xCen + 1][yCen - 8] = 1;
                cellVal[xCen + 1][yCen - 4] = 1;
                cellVal[xCen + 1][yCen - 2] = 1;
                cellVal[xCen + 1][yCen - 1] = 1;
                cellVal[xCen + 1][yCen + 4] = 1;
                cellVal[xCen + 1][yCen + 6] = 1;
                cellVal[xCen + 2][yCen - 8] = 1;
                cellVal[xCen + 2][yCen - 2] = 1;
                cellVal[xCen + 2][yCen + 6] = 1;
                cellVal[xCen + 3][yCen - 7] = 1;
                cellVal[xCen + 3][yCen - 3] = 1;
                cellVal[xCen + 4][yCen - 6] = 1;
                cellVal[xCen + 4][yCen - 5] = 1;
                break;

             case 4:
                // clock
                cellVal[xCen][yCen - 2] = 1;
                cellVal[xCen - 2][yCen - 1] = 1;
                cellVal[xCen][yCen - 1] = 1;
                cellVal[xCen - 1][yCen] = 1;
                cellVal[xCen + 1][yCen] = 1;
                cellVal[xCen - 1][yCen + 1] = 1;
                break;
             }

    cout << "Please enter the number of generations as an integer "
         << "you would like the simulation to run." << endl << endl
         << "Number of generations: ";

             int genNum = intCheck();    //checks user input to make sure choice is valid integer
             cout << endl;

    for (int t = 1; t <= genNum + 1; t++)

        {
            displayBoard(cells, cellVal, 100);  //calls function which prints pattern to screen
            //Idea to use carriage return came from http://stackoverflow.com/questions/1337529/
            cout << "\r" << "Generation #: " << t - 1 << endl; //displays current generation
            brain(cellVal, 100);    //calls function to change pattern based on rules
        }

    cout << endl << "Would you like to run another simulation?" << endl
         << "Enter the integer corresponding to your choice."
         << endl << endl
         << "   1:     Yes." << endl
         << "   2:     No, exit the program." << endl << endl
         << "Your Selection: ";

 //checks user input to make sure choice is valid integer, either 1 or 2
    int replayChoice = intCheck(1, 2);
    cout << endl;

    switch(replayChoice)
    {
        case 1:
            break;  //will rerun program from menu screen

        case 2:
            exit(1);
            break;
    }
}

return 0;

}

void displayBoard(string cellSym[][100], int cellNum[][100], int rows)
{
    const int xSize = 22;
    const int ySize = 80;
    for (int x = 5; x < 95; x++)
    {
        for (int y = 5; y < 95; y++)
        {
            if (cellNum[x][y] == 1){
                cellSym[x][y] = "O";
            }
            else if (cellNum[x][y] == 0){
                cellSym[x][y] = " ";
            }
        }
    }

for (int x = 10; x < xSize + 10; x++)
    {
        for (int y = 10; y < ySize + 10; y++)
        {
            cout << cellSym[x][y];
        }
    }
}

void brain(int cellNum[][100], int rows)
{
int newcellVal[100][100];
for (int x = 5; x < 95; x++)
    {
        for (int y = 5; y < 95; y++)
        {
            int cellSum = (cellNum[x-1][y-1] + cellNum[x-1][y] + cellNum[x-1][y+1] +
                cellNum[x][y-1] + cellNum[x][y+1] + cellNum[x+1][y-1] +
                cellNum[x+1][y] + cellNum[x+1][y+1]);

            if (cellNum[x][y] == 1 && cellSum < 2)
                {
                    newcellVal[x][y] = 0;
                }

            if (cellNum[x][y] == 1 && (cellSum == 2 || cellSum == 3))
                {
                    newcellVal[x][y] = 1;
                }

            if (cellNum[x][y] == 1 && cellSum > 3)
                {
                    newcellVal[x][y] = 0;
                }

            if (cellNum[x][y] == 0 && cellSum == 3)
                {
                    newcellVal[x][y] = 1;
                }
        }
    }

for (int x = 5; x < 95; x++)
    {
        for (int y = 5; y < 95; y++)
        {
        cellNum[x][y] = newcellVal[x][y];
        }
    }
}

//function to check if input is a valid integer between a minimum and maximum value.
//This function is being reused from CS 161.
int intCheck(int minRange, int maxRange)
{
    string Input;
    int funInt;
    getline(cin, Input);            //takes input from user in the form of a string
    for(unsigned int i=0; i<Input.length(); i++) //checks each character of string input to make sure it is a number
    {
        if(Input[i] == '0' || Input[i] == '1' ||  Input[i] == '2' ||  Input[i] == '3' ||  Input[i] == '4' ||
             Input[i] == '5' ||  Input[i] == '6' ||  Input[i] == '7' ||  Input[i] == '8' ||  Input[i] == '9' ||  Input[i] == '-')
        {
            continue;
        }

        else    //if input is not a valid number, intCheck function is recursively called
        {
            cout << endl << "You did not enter a valid integer." << endl
                 << "Please enter an integer corresponding to your choice." << endl;
            cout << "Your Selection: ";
            i=0;
            return intCheck(minRange, maxRange);
        }
    }
    funInt = atoi(Input.c_str( ));      //converts string of numbers into integer

    if(funInt < minRange || funInt > maxRange)  //checks if user input is smaller or larger than defined min and max values
    {
        cout << "You entered " << funInt << "." << " This value is not between " << minRange << " and " << maxRange
        << ". Please try again." << endl;
        return intCheck(minRange, maxRange);    //if input is too large or too small, intCheck function is recursively called
    }

    else
    {
        return funInt;          //returns user input to function as an integer
    }
}

//function to check if input is a valid integer
//This function is being reused from CS 161.
int intCheck()
{
    string Input;
    int funInt;
    getline(cin, Input);    //takes input from user in the form of a string
    for(unsigned int i=0; i<Input.length(); i++)     //checks each character of string input to make sure it is a number
    {
        if(Input[i] == '0' || Input[i] == '1' ||  Input[i] == '2' ||  Input[i] == '3' ||  Input[i] == '4' ||
             Input[i] == '5' ||  Input[i] == '6' ||  Input[i] == '7' ||  Input[i] == '8' ||  Input[i] == '9' ||  Input[i] == '-')
        {
            continue;
        }

        else    //if input is not a valid number, intCheck function is recursively called
        {
            cout << endl << "You did not enter a valid integer." << endl
                 << "Please enter an integer corresponding to your choice." << endl;
            cout << "Your Selection: ";
            return intCheck();
        }
    }
    funInt = atoi(Input.c_str( ));  //converts string of numbers into integer
    return funInt;                  //returns user input to function as an integer
}
