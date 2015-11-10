/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 1/28/2015
*   Last Modification Date:       2/1/2015
*   Filename:                     assign2.cpp
*
*   Overview:   This program is a grocery list program. Users may import, edit, and
*               export their grocery list.
*
*
*   Input:  The input shall consist of string and integers that the user may enter.
*           The user may enter item name, unit type, quantity, and price information
*           for each grocery list item. The user may also import a grocery list file.
*
*   Output: The output of the program will be a display of the grocery list. The user
*           may also write the grocery list to a  file.
*
****************************************************************************************/

#include <iostream>
#include "item.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::vector;

/*********************************************************************
** Function: fillList
** Description: Function that will generate a grocery list and ask
**          user to input class member variable values for each item.
** Parameters: Vector containing classes.
** Pre-Conditions: NONE
** Post-Conditions: Grocery list vector containing classes has been created.
*********************************************************************/
void fillList(vector<Item>&);

/*********************************************************************
** Function: printList
** Description: Function that will print the grocery list to the screen.
** Parameters: Vector containing classes.
** Pre-Conditions: Vector exists.
** Post-Conditions: Vector elements have been printed to the screen.
*********************************************************************/
void printList(vector<Item>&);

/*********************************************************************
** Function: editList
** Description: Function used to Add/Edit grocery list.
** Parameters: Vector containing classes.
** Pre-Conditions: Vector exists.
** Post-Conditions: Element has been added to vector or modified.
*********************************************************************/
void editList(vector<Item>&);

/*********************************************************************
** Function: removeItem
** Description: Function used to remove classes from vector.
** Parameters: Vector containing classes.
** Pre-Conditions: Vector exists and contains at least 1 element.
** Post-Conditions: Element has been removed from vector.
*********************************************************************/
void removeItem(vector<Item>&);

/*********************************************************************
** Function: readList
** Description: Function used to open and read input file,
**      and then close file.
** Parameters: Vector containing classes.
** Pre-Conditions: Vector exists and file exists.
** Post-Conditions: Grocery list has been read into program.
*********************************************************************/
void readList(vector<Item>&);

/*********************************************************************
** Function: writeList
** Description: Function used to open output file, write list to file,
**      and then close file.
** Parameters: Vector containing classes.
** Pre-Conditions: Vector exists.
** Post-Conditions: Grocery list has been written to output file.
*********************************************************************/
void writeList(vector<Item>&);

/*********************************************************************
** Function: intCheck
** Description: Function used to check if input is valid integer.
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

/*********************************************************************
** Function: doubleCheck
** Description: Function used to check if input is valid double
** Parameters: NONE
** Pre-Conditions: user has entered input
** Post-Conditions: returns valid double
*********************************************************************/
double doubleCheck();

int main()
{

bool menuOn = true;
vector<Item> myList;
do{
        cout << endl << "\t WELCOME TO YOUR GROCERY LIST!\n" << endl

             << "Select which action you would like to do from the choices below.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Read in new grocery list from a file." << endl
             << "   2:     Create a new grocery list." << endl
             << "   3:     Add/Edit Item in List." << endl
             << "   4:     Remove Item from List." << endl
             << "   5:     Save grocery list to a file." << endl
             << "   6:     EXIT" << endl << endl;

             cout << "Your Selection: ";

             int menuChoice = intCheck(1, 6);

             cout << endl << endl;
             cout << "--------------------------------------------------------------------";
             cout << "------------" << endl;

//switch statement allows user to select which action they would like to execute.
switch(menuChoice)
             {
             case 1:
                 readList(myList);
                 printList(myList);
                 break;

             case 2:
                 fillList(myList);
                 printList(myList);
                 break;
             case 3:
                 editList(myList);
                 break;
             case 4:
                 removeItem(myList);
                 break;
             case 5:
                 writeList(myList);
                 break;
             case 6:
                 exit(1);
                 break;
             case 7: //exists solely for testing purposes
                 printList(myList);
                 break;
             }
}
while(menuOn);

return 0;
}

//Function that will generate a grocery list and ask user to input class
//member variable values for each item.
void fillList(vector<Item>& newList){
    //declares member variables
    string name;
    string type;
    double amount;
    double price;

    cout << "How many items do you want to add to your grocery list? Please enter an integer." << endl;
    int numList = intCheck();

    for(int i = 1; i <= numList; i++){
        //ignores characters until newline so that getline doesn't inadvertantly read in unwanted data.
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout << endl << "Enter the name of Item #" << i << ": ";
        getline(cin, name);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout <<  endl << "Enter the unit type (i.e cans, grams, lbs) of Item #" << i << ": ";
        getline(cin, type);
        cout <<  endl << "Enter the number of " << type << " of " << name << " you plan to purchase: ";
        amount = doubleCheck();
        cout <<  endl << "Enter the price per unit of Item #" << i << " (in dollars): ";
        price = doubleCheck();
        cout << endl;

        //creates class using constructor function to pass in member variable data
        Item gList(name, type, amount, price);

        //class is added to end of vector of classes
        newList.push_back(gList);

    }
}

//Function that will print the grocery list to the screen.
void printList(vector<Item>& newList){

    double totalPrice = 0;
    cout << "MY GROCERY LIST" << endl << endl;
    //for loop through every element of vector.
    for(unsigned int i = 0; i < newList.size(); i++){
        //for each element, class member variable information is printed to screen
        cout << "Item #" << i+1 << ": " << newList[i].getName() << endl;
        cout << "Unit Type: " << newList[i].getType() << endl;
        cout << fixed << setprecision(2);
        cout << "Quantity: " << newList[i].getNum() << endl;
        cout << "Price per Unit: $" << newList[i].getPrice() << endl;
        cout << "Subtotal: $" << newList[i].getsubTotal() << endl << endl;
    }

        for(unsigned int i = 0; i < newList.size(); i++){
        //adds up all subtotal member variables in entire vector
        totalPrice += newList[i].getsubTotal();

    }
    cout << "TOTAL PRICE: $" << totalPrice << endl << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;
}

//Function used to Add/Edit grocery list.
void editList(vector<Item>& newList){
    int runAgain = 1;
    while (runAgain == 1){
    string name;
    string type;
    double amount;
    double price;
    printList(newList);
    cin.clear();
    cout << "If you would like to simply add another item to your list, Enter 1." << endl
         << "If you would like to edit an existing item in your list, Enter 2." << endl
         << "Or If you would like to return to the Main Menu, Enter 0." << endl
         << "Your Choice: ";

    int addChoice = intCheck(0, 2);
    cout << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

    if(addChoice == 0){
        return;
    }

    if(addChoice == 1){
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout << endl << "Enter the name of the item: ";
        getline(cin, name);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout <<  endl << "Enter the unit type (i.e cans, grams, lbs) of the item: ";
        getline(cin, type);
        cout <<  endl << "Enter the number of " << type << " of " << name << " you plan to purchase: ";
        amount = doubleCheck();
        cout <<  endl << "Enter the price per unit of the item (in dollars): ";
        price = doubleCheck();
        cout << endl;

//creates class using constructor function to pass in member variable data
        Item gList(name, type, amount, price);

        // classes is appended to end of vector
        newList.push_back(gList);

    }

    if(addChoice == 2){
        if(newList.empty()){
        cout << "Your grocery list is currently empty and therefore you cannot edit an item" << endl
        << "in your list." << endl << endl;
        cout << "--------------------------------------------------------------------";
        cout << "------------" << endl << endl;
        return;
    }

    cout << "Enter the integer corresponding to the Item you would like to edit."
         << endl << "Or if you would not like to edit any items, Enter 0." << endl
         << "Your Choice: ";

    int itemChoice = intCheck(0, newList.size());
    cout << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

    if(itemChoice == 0){
        return;
    }

    //setter functions used to edit member variables for a particular class within the vector
    itemChoice = itemChoice - 1;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cout << endl << "Enter the name of Item #" << itemChoice+1 << ": ";
    getline(cin, name);
    newList[itemChoice].setName(name);
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cout <<  endl << "Enter the unit type (i.e cans, grams, lbs) of Item #" << itemChoice+1 << ": ";
    getline(cin, type);
    newList[itemChoice].setType(type);
    cout <<  endl << "Enter the number of " << type << " of " << name << " you plan to purchase: ";
    amount = doubleCheck();
    newList[itemChoice].setNum(amount);
    cout <<  endl << "Enter the price per unit of Item #" << itemChoice+1 << " (in dollars): ";
    price = doubleCheck();
    newList[itemChoice].setPrice(price);
    cout << endl;
    }

    printList(newList);
    cin.clear();
    cout << "Would you like to edit another item or would you like to return to the menu?" << endl
         << "Enter '1' if you would like to edit another item or " << endl
         << "Enter '2' if you would like to return to the menu." << endl << endl;
    cout << "Your Selection: ";
    runAgain = intCheck(1, 2);    //calls function to check validity of user input.
    cout << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

    }
}

//Function used to remove classes from vector.
void removeItem(vector<Item>& newList){

    int runAgain = 1;
    while (runAgain == 1){
    printList(newList);
    cin.clear();
    cout << "Enter the integer corresponding to the Item # you would like to remove from your list."
         << endl << "Or if you would not like to remove any items, Enter 0." << endl
         << "Your Choice: ";

    int itemChoice = intCheck(0, newList.size()+1);
    cout << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

    if(itemChoice == 0){
        return;
    }

    itemChoice = itemChoice - 1;

    if(newList.empty()){
        cout << "Your grocery list is currently empty and therefore you cannot remove an item" << endl
        << "from your list." << endl << endl;
        cout << "--------------------------------------------------------------------";
        cout << "------------" << endl << endl;
        return;
    }

    //erases particular class from vector
    newList.erase(newList.begin()+itemChoice);
    printList(newList);

    cin.clear();
    cout << "Would you like to remove another item or would you like to return to the menu?" << endl
         << "Enter '1' if you would like to remove another item or " << endl
         << "Enter '2' if you would like to return to the menu." << endl << endl;
    cout << "Your Selection: ";
    runAgain = intCheck(1, 2);    //calls function to check validity of user input.
    cout << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

}
}

//Function used to open and read input file and then close file.
void readList(vector<Item>& newList){
    string input;
    string name;
    string type;
    string stringAmount;
    string stringPrice;
    double amount;
    double price;
    string filename1;
    cout << "Please enter the name of the input file: ";
    cin >> filename1;
    ifstream inStream(filename1);

    //checks if input file opened correctly.
    if(inStream) {
            cout << filename1 << " has been opened successfully." << endl;}
    else{
            cout << "Can't open input file, " << filename1 << endl;
        }

    while(getline(inStream, input)){
    stringstream ss;
    ss << input;
    getline(ss, name, '|');
    getline(ss, type, '|');
    ss >> amount;
    ss >> price;

    Item gList(name, type, amount, price);
    newList.push_back(gList);
    }

    //closes input file
    inStream.close();

    //checks if input file was successfully closed
    if(inStream.is_open()) {
        cout << "Can't close " << filename1 << " ." << endl;
    }

    if(!inStream.is_open()) {
        cout << endl << filename1 << " has been successfully closed." << endl << endl;
    }
}

//Function used to open output file, write list to file, and then close file.
void writeList(vector<Item>& newList){
        string oFilename = " ";
        cout << "Please enter the name of the output file: ";
        cin >> oFilename;
        ofstream outputFile(oFilename);

        //checks if outfile has been opened successfully
        if(outputFile) {
        cout << oFilename << " has been opened successfully." << endl << endl;
        }
        else{
                cout << "Can't open " << oFilename << " ." <<endl;
                }

    for(unsigned int i = 0; i < newList.size(); i++){
        outputFile << newList[i].getName() << "|" << newList[i].getType() << "|";
        outputFile << newList[i].getNum() << " " << newList[i].getPrice() << endl;

    }

        //closes output file
        outputFile.close();

        //checks if output file has been successfully closed
        if(outputFile.is_open()) {
                cout << "Can't close output file, " << oFilename << endl;
                }

        if(!outputFile.is_open()) {
                cout << oFilename << " has been closed." << endl;
                }

        return;
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

//design of this function influenced by discussion thread:
// http://stackoverflow.com/questions/17750872/validating-a-double-in-c
double doubleCheck()
{
    double input;
    cin >> input;
    while(cin.fail() || (cin.peek() != '\r' && cin.peek() != '\n'))
    {
        cout << "You did not enter a valid numerical value. Please input a numerical value." << endl;
        cin.clear();
        while( cin.get() != '\n' );
        cin >> input;
    }
    return input;
}
