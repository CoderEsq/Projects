/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 2/15/2015
*   Last Modification Date:       2/15/2015
*   Filename:                     lab6.cpp
*
*   Overview:   This program is a search and sort program.
*
*
*   Input:  The input shall consist of a file containing data.
*
*
*   Output: The output of the program will be a printout of the locations of the target
*   value as well as a file containing a set of sorted values.
*
*
****************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::stringstream;
using std::ios;

int intCheck(int minRange, int maxRange);
void lSearch(vector<int> &numbers);
void sortFile(vector<int> &numbers);
void bSearch(vector<int> &numbers);

int main()
{

vector<int> values;
ifstream input;
ofstream output;

bool menuOn = true;
do{
        cout << endl << "\t FILE SEARCH & SORT PROGRAM\n" << endl

             << "Select which search or sort option you would like to apply from the choices below.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Search for target value (linear search)" << endl
             << "   2:     Sort a set of values" << endl
             << "   3:     Search for a target value (binary search)" << endl
             << "   4:     EXIT" << endl << endl;

             cout << "Your Selection: ";

             int menuChoice = intCheck(1, 5);

             cout << endl << endl;
             cout << "--------------------------------------------------------------------";
             cout << "------------" << endl;

//switch statement allows user to select which action they would like to execute.
switch(menuChoice)
             {
             case 1:
                lSearch(values);
                break;
             case 2:
                sortFile(values);
                break;
             case 3:
                bSearch(values);
                break;
             case 4:
                exit(1);
                break;
             }
}
while(menuOn);

return 0;
}

void lSearch(vector<int> &numbers)
{
    int runAgain;
    string filename1;

    vector<int> location;
    cout << "Please enter the name of the file you would like to search: ";
    cin >> filename1;
    ifstream inStream (filename1);

    //checks if input file opened correctly.
    if(inStream) {
            cout << endl << filename1 << " has been opened successfully." << endl << endl;
            }
    else{
            cout << "Can't open input file, " << filename1 << endl << endl;
            exit(1);
        }

    int data;
    while (inStream >> data)
    {
        cout << data << endl;
        numbers.push_back(data);
    }

    int value;

    do{
    cout << endl <<  "What value are you looking for?" << endl;
    cin >> value;
    cout << endl << endl;
    int index = 0; // Used as a subscript to search vector
    int position = -1; // Used to record position of search value
    bool found = false; // Flag to indicate if the value was found

    //design based on example in book located at pg. 597
    for(unsigned int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == value) // If the value is found
        {
            found = true; // Set the flag
            position = index; // Record the value's subscript
            location.push_back(i);
        }

    }

        if(location.empty())
        {
            cout << "The number does not exist in the list of values." << endl;
        }

        else {
        for(unsigned int i = 0; i < location.size(); i++){

        cout << "That value is located at position " << location[i]+1 << endl; // Return the position, or -1
        }
        }
    location.clear();

    cout << endl << "Would you like to search for another number within the file or would you like to return to the menu?" << endl
         << "Enter '1' if you would like to search for another number or " << endl
         << "Enter '2' if you would like to return to the menu." << endl << endl;
    cout << "Your Selection: ";
    runAgain = intCheck(1, 2);    //calls function to check validity of user input.

    }while(runAgain == 1);

    numbers.clear();
    inStream.close();
    //checks if input file was successfully closed
    if(inStream.is_open()) {
        cout << "Can't close " << filename1 << " ." << endl << endl;
    }

    if(!inStream.is_open()) {
        cout << endl << filename1 << " has been successfully closed." << endl << endl;
    }

    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

}

void sortFile(vector<int> &numbers)
{
    string filename1;
    //ifstream inStream;


    vector<int> location;
    cout << "Please enter the name of the file you would like to sort: ";
    cin >> filename1;
    ifstream inStream (filename1);

    //checks if input file opened correctly.
    if(inStream) {
            cout << endl << filename1 << " has been opened successfully." << endl << endl;
            }
    else{
            cout << "Can't open input file, " << filename1 << endl << endl;
            exit(1);
        }

    string oFilename = " ";
    cout << "Please enter the name of the output file where you would like to store the sorted values: ";
    cin >> oFilename;
    ofstream outStream(oFilename);

    //checks if outfile has been opened successfully
    if(outStream) {
        cout << endl << oFilename << " has been opened successfully." << endl << endl;
        }
    else{
            cout << "Can't open " << oFilename << " ." << endl << endl;
    }

    int data;
    cout << "Here are the unsorted values:" << endl << endl;
    while (inStream >> data)
    {
        cout << data << endl;
        numbers.push_back(data);
    }

    cout << endl << endl;

    int temp;
    bool swap;

    //design based on example located in pg. 618 of the textbook (Bubble Sort)
    do
    { swap = false;
    for (unsigned count = 0; count < numbers.size()-1; count++)
    {
        if (numbers[count] > numbers[count + 1])
        {
        temp = numbers[count];
        numbers[count] = numbers[count + 1];
        numbers[count + 1] = temp;
        swap = true;
        }
    }
    } while (swap);

    cout << "Here are the sorted values:" << endl << endl;

    for(unsigned int i = 0; i < numbers.size(); i++)
    {
        int temp2 = numbers[i];
        outStream << temp2 << endl;
        cout << numbers[i] << endl;
    }

    numbers.clear();

    inStream.close();
    //checks if input file was successfully closed
    if(inStream.is_open()) {
        cout << "Can't close " << filename1 << " ." << endl << endl;
    }

    if(!inStream.is_open()) {
        cout << endl << filename1 << " has been successfully closed." << endl << endl;
    }

    outStream.close();
    //checks if output file has been successfully closed
    if(outStream.is_open())
        {
            cout << "Can't close output file, " << oFilename << endl << endl;
        }

    if(!outStream.is_open())
        {
            cout << oFilename << " has been closed." << endl << endl;
        }

    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

}

void bSearch(vector<int> &numbers)
{

    int runAgain;
    string filename1;

    vector<int> location;
    cout << "Please enter the name of the file you would like to search: ";
    cin >> filename1;
    ifstream inStream (filename1);

    //checks if input file opened correctly.
    if(inStream) {
            cout << endl << filename1 << " has been opened successfully." << endl << endl;
            }
    else{
            cout << "Can't open input file, " << filename1 << endl << endl;
            exit(1);
        }

    int data;
    while (inStream >> data)
    {
        cout << data << endl;
        numbers.push_back(data);
    }

    int value;
    int vSize = numbers.size();

    do{
    cout << endl <<  "What value are you looking for?" << endl;
    cin >> value;
    cout << endl << endl;
    int position = -1; // Used to record position of search value
    bool found = false; // Flag to indicate if the value was found

    //design based on example in book located at pg. 601
    int first = 0;
    int last = vSize - 1;
    int middle;

    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if ( numbers[middle] == value)
        {
            found = true;
            position = middle;
            location.push_back(position);
        }
        else if ( numbers[middle] > value)
        {
            last = middle - 1;
        }
        else {
            first = middle + 1;
        }

    }

    if(location.empty())
        {
            cout << "The number does not exist in the list of values." << endl;
        }

    else {
        for(unsigned int i = 0; i < location.size(); i++){

        cout << "That value is located at position " << location[i]+1 << endl; // Return the position, or -1
    }
    }

    location.clear();

    cout << endl << "Would you like to search for another number within the file or would you like to return to the menu?" << endl
         << "Enter '1' if you would like to search for another number or " << endl
         << "Enter '2' if you would like to return to the menu." << endl << endl;
    cout << "Your Selection: ";
    runAgain = intCheck(1, 2);    //calls function to check validity of user input.

    }while(runAgain == 1);

    numbers.clear();
    inStream.close();
    //checks if input file was successfully closed
    if(inStream.is_open()) {
        cout << "Can't close " << filename1 << " ." << endl << endl;
    }

    if(!inStream.is_open()) {
        cout << endl << filename1 << " has been successfully closed." << endl << endl;
    }

    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

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
