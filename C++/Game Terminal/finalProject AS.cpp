/*****************************************************
*   Author:                       Alex Samuel
*   Date Created:                 8/10/2014
*   Last Modification Date:       8/31/2014
*   Filename:                     finalProject.cpp
*
*   Overview:
*       This program allows the user to play different games.
*
*   Input:
*       The input will consist of integers and strings.
*
*   Output:
*       The output of this program will be a printout of the status of the game as it progresses.
*
***************************************************/

/*****************************************************
Assignment Reevaluation Component

1.  I would like my 2-Player Word Guess program(secretWord.cpp) to be re-evaluated from Assignment 4.
    The specific requirements from this project that I would like to be re-evaluated are that it
    actually displays the letters guessed correctly within the secret word (part 4 from assignment 4)
    and that a user can actually complete the game. My understanding of these requirements are
    demonstrated in my void secretWord() function which executes a 2-Player word guessing game (lines 624 - 739).

2.  I would like my 2-Player Word Guess program(secWordFun.cpp) to be re-evaluated from Assignment 5.
    The specific requirements from this project that I would like to be re-evaluated are that it
    uses a function to check if the secret word is a valid word (part c, from assignment 5),
    checks if the guess is a valid guess (part d.iii), and tells user whether they guessed the
    secret word or ran out of guesses (part e) and whether the victory condition can be met. My understanding
    of these requirements are demonstrated in my void secretWord() function which executes a 2-Player
    word guessing game (lines 624 - 739).

***************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;

/*----------------------------------------------------------------------
Requirement #21: Demonstrate use of at least one struct
----------------------------------------------------------------------*/
struct Person           //struct tag for struct containing name and age values.
{
    char name[100];
    int age;
};

/*----------------------------------------------------------------------
Requirement #22: Demonstrate use of one class and one object
----------------------------------------------------------------------*/
class Game_functions        //class containing different functions that each execute a separate game
{
public:
    void randNumGen();                  //function contains random number generation program
    void numGuess();                    // function contains 2-Player Number guess program
    string getWelcomeMsg();             //accessor function for private member welcome

private:
    string welcome;                     //private member that contains welcome message to user
};

typedef int* IntPtr;                    //defines IntPtr type which is the type for pointer variables that contain
                                        // contain pointers to int variables.

void commandlineGood(int userChoice);   //executed if user inputs valid command line arguments
void commandlineBad();                  //executed if user inputs invalid command line arguments
void commandlineEmpty();                //executed if user inputs no command line arguments and also
                                        //runs after user finishes game entered through commandline

int menuCheck(int menuInput);       //function used to check if user input when selecting game is valid
bool replayCheck(bool choice);      //function to check if user wants to replay game or return to menu
int intCheck();                     // function used to check if input is valid integer (no bounds)
int intCheck(int minRange, int maxRange);   //function used to check if input is valid integer between set min and max values

//functions used in Friend List Generator
void friendList();                  //function contains Friend List generator program
void set_person(Person &p);         //function that sets value within struct in each element of array

//functions used in Random Number Generator
int arraySize();                        //function used to obtain user input of number of random numbers to generate
void fillArray(int p[], int size);      //function used to fill dynamic array with random numbers
void printArray(int p[], int size);     //function used to print array of random numbers

//functions used in 2-Player Word Guessing Game
string wordCheck(string secretWord);    //function checks user input for secret word
char ltrCheck(char ltrGuess);           //function checks user input for guessed letter
void secretWord();                      //function contains 2-Player Word Guessing game

/*----------------------------------------------------------------------
Requirement #12: Demonstrate functional decomposition
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #20: Demonstrate at least 1 command line argument
----------------------------------------------------------------------*/
    int main(int argc, char *argv[])    //user may use command line arguments to select which sub-program to run.
    {
        int gameChoice;    //stores user selection
 /*----------------------------------------------------------------------
Requirement #04: Demonstrate conditional statement
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #05: Demonstrate logical operator ( == )
----------------------------------------------------------------------*/
        if (argc == 2)  //tests if user has inputted correct number of command line arguments
        {
            gameChoice = atoi(argv[1]); //converts char* into an integer

            //tests if input is valid menu selection
            if (gameChoice == 1 || gameChoice == 2 || gameChoice == 3 || gameChoice == 4 || gameChoice == 5){
            commandlineGood(gameChoice);  //passes input into function which executes switch statement containing program options
            }

            else {
                commandlineBad();   //if input is not valid integer within range, user will receive usage message
            }
        }

        else if(argc >= 3)
        {
            commandlineBad();   //prints out usage statement to user
        }

        commandlineEmpty();     //executes switch statement if user does not enter any command line arguments

        return 0;
    }

/*----------------------------------------------------------------------
Requirement #11: Demonstrate one function that is defined
----------------------------------------------------------------------*/
void commandlineGood(int userChoice)    //function is executed if command line arguments are valid
{                                       //will execute corresponding function to command line argument

    //userChoice = menuCheck(userChoice);    //checks user input to make sure game choice is valid
    Game_functions library;     //declares library class of type Game_functions

    switch(userChoice)     //the user's input is what the switch checks to execute the respective branch
    {
             case 1:
                 friendList();      //executes Friend List Generator program
                 break;

             case 2:
                 library.randNumGen();  //executes Random Number Generator program
                 break;

             case 3:
                 library.numGuess();    //executes 2-Player Number Guessing program
                 break;

             case 4:
                 secretWord();      //executes 2-Player Word Guessing program
                 break;

             case 5:
                 exit(1);       //exits program
                 break;
    }
}

//executes if user inputs invalid command line arguments (either too many arguments or args are non-integers)
void commandlineBad()
{
    cerr << "usage: " << "finalProject menuSelection" << endl   //prints out usage statement to user
         << "     menuSelection:  The integer corresponding to the menu item the user would like to execute." << endl;

    exit(1);
}

//executes if user does not input command line arguments
void commandlineEmpty()
{
        bool menuAgain = true;  //sets initial state, this will always be true so user always can access menu
/*----------------------------------------------------------------------
Requirement #07: Demonstrate loop ( while loop )
----------------------------------------------------------------------*/
        while (menuAgain == true){  //user will be able to repeatedly return to menu
/*----------------------------------------------------------------------
Requirement #01: Demonstrate simple output
----------------------------------------------------------------------*/
        cout << "\t WELCOME TO THE GAME TERMINAL!\n"    //menu displayed to user
             << "Select which game you would like to play from the choices below.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Friend List Program" << endl
             << "   2:     Random Number Generator" << endl
             << "   3:     2-Player Number Guessing Game" << endl
             << "   4:     2-Player Word Guessing Game" << endl
             << "   5:     EXIT GAME TERMINAL" << endl << endl;



             cout << "Your Selection: ";
             int gameChoice = intCheck(1, 5);    //checks user input to make sure game choice is valid integer between 1 and 5
             cout << endl;
             Game_functions library;     //declares library class of type Game_functions

// I chose to implement the menu with a switch statement. Each branch of the switch statement
// executes a different game and there is an option to completely exit the program. Users may
// move back and forth between each game and menu.
             switch(gameChoice)     //the user's input is what the switch checks to execute the respective branch
             {
             case 1:
                 friendList();      //executes Friend List Generator program
                 break;

             case 2:
                 library.randNumGen();  //executes Random Number Generator program
                 break;

             case 3:
                 library.numGuess();    //executes 2-Player Number Guessing program
                 break;

             case 4:
                 secretWord();      //executes 2-Player Word Guessing program
                 break;

             case 5:            //exits program
                 exit(1);
                 break;
             }

        }
}

/*----------------------------------------------------------------------
Requirement #15: Demonstrate function overloading (the function intCheck is overloaded)
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #17: Demonstrate some form of recursion (intCheck function is run again if input is not valid)
----------------------------------------------------------------------*/
int intCheck()   //function to check if input is a valid integer
{
    string Input;
    int funInt;
/*----------------------------------------------------------------------
Requirement #02: Demonstrate simple input
----------------------------------------------------------------------*/
    getline(cin, Input);    //takes input from user in the form of a string
    for(int i=0; i<Input.length(); i++)     //checks each character of string input to make sure it is a number
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

/*----------------------------------------------------------------------
Requirement #09: Demonstrate understanding of three general error categories
    Explanation: The compiler I used was very helpful in locating any syntax
    errors present. The types of syntax errors I commonly had were missing
    semi-colons or misspelled variable names. To prevent logic errors I tried to carefully
    read over my code to make sure the logic was sound. I did find and correct a few instances
    where functions were terminating earlier than expected and were not following the
    correct path. I did not run into any run-time errors but I designed my program in a way
    that would allow the user to receive a usage message if they input an incorrect
    command line argument. The program will also run if the user does not enter any
    command line arguments.
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #10: Demonstrate debugging trick (input verification, print statements)
    Explanation: I used print statements in the following function to help identify
    any problems with the logic of the function so I could see which branch the program
    was activating. This function is called to check the validity of user input to make
    sure that the user is inputting only a number between a designated minimum and maximum value.
----------------------------------------------------------------------*/
//function to check if input is a valid integer between a minimum and maximum value.
int intCheck(int minRange, int maxRange)
{
    //cout << "2" << endl;
    string Input;
    int funInt;
    //cout << "-1" << endl;
    getline(cin, Input);            //takes input from user in the form of a string
    for(int i=0; i<Input.length(); i++) //checks each character of string input to make sure it is a number
    {
        if(Input[i] == '0' || Input[i] == '1' ||  Input[i] == '2' ||  Input[i] == '3' ||  Input[i] == '4' ||
             Input[i] == '5' ||  Input[i] == '6' ||  Input[i] == '7' ||  Input[i] == '8' ||  Input[i] == '9' ||  Input[i] == '-')
        {
            //cout << "1" << endl;
            continue;
        }

        else    //if input is not a valid number, intCheck function is recursively called
        {
            cout << endl << "You did not enter a valid integer." << endl
                 << "Please enter an integer corresponding to your choice." << endl;
            cout << "Your Selection: ";
            i=0;
            return intCheck(minRange, maxRange);
            //cout << "2.5" << endl;
        }
    }
    funInt = atoi(Input.c_str( ));      //converts string of numbers into integer
    //cout << "3 & " << funInt << endl;

    if(funInt < minRange || funInt > maxRange)  //checks if user input is smaller or larger than defined min and max values
    {
        cout << "You entered " << funInt << "." << " This value is not between " << minRange << " and " << maxRange
        << ". Please try again." << endl;
        return intCheck(minRange, maxRange);    //if input is too large or too small, intCheck function is recursively called
    }

    else
    {
        //cout << "4" << endl;
        return funInt;          //returns user input to function as an integer
    }
}

/*----------------------------------------------------------------------
Requirement #13: Demonstrate how scope of variables work
(the variable replayInput is only accessible within this block of code)
----------------------------------------------------------------------*/
//this function asks if the user wants to replay the game they just finished or return to the menu.
bool replayCheck(bool choice)
{
    int replayInput;    //stores users selection
    cout << "Would you like to play again or would you like to return to the menu?" << endl
         << "Enter '1' if you would like to play again or " << endl
         << "Enter '2' if you would like to return to the menu." << endl << endl;
    cout << "Your Selection: ";
    replayInput = intCheck(1, 2);    //calls function to check validity of user input.
    cout << endl;


    if (replayInput == 1){  //checks which option user has selected
        choice = true;
        return choice;              //returns true value to game indicating user wants to play again.
    }
    else if(replayInput == 2){
        choice = false;
        return choice;              //returns false value to game indicating that user does not want to play again.
    }                               // Game then finishes and user is brought back to the menu screen.
}

void friendList() //Friend List program
{
    bool playAgain = true;
    while (playAgain == true)   //"playAgain" variable will change if user does not want to play again after running replayCheck function.
    {
        Person new_person;      //creates variable that stores struct of type Person
        Person *person_ptr;     //creates pointer to struct
/*----------------------------------------------------------------------
Requirement #14: Demonstrate passing mechanisms
----------------------------------------------------------------------*/
        person_ptr = &new_person;   //assigns pointer to struct reference
/*----------------------------------------------------------------------
Requirement #22: Demonstrate one class and one object
----------------------------------------------------------------------*/
        Game_functions friendL;     //generates object of class Game_functions
        Game_functions *friendPtr;   //creates pointer that can point to an object
        friendPtr = &friendL;   //sets pointer to object.

        cout << "The purpose of this program is to generate a list of your friends\n"
             << "and their respective ages." << endl << endl;

/*----------------------------------------------------------------------
Requirement #16: Demonstrate one std::string and one c-style string
(the private class member 'welcome' is a string in object friendL of class Game_functions
 and the struct member 'name' of the new_Person struct of type Person is a c-style string)
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #25: Demonstrate pointer to an object (friendPtr points to object friendL)
----------------------------------------------------------------------*/
//prints welcome message to user using pointer to private class member within accessor function
        cout << friendPtr->getWelcomeMsg() << endl;
        int numFriends;

        cout << "My name is: ";
        cin  >> new_person.name;    //name information input into c-style string

        cin.clear();
        cin.ignore(999, '\n');
        cout << "Please tell me your age?" << endl;
        new_person.age = intCheck();    //accepts and checks user input for age information

        cout << endl << "How many friends will be in your list?" << endl;
        numFriends = intCheck();
        cout << endl;

        Person friends[numFriends];  //creates an array of struct equal in size to the number of friends identified by user

//takes user input for each element within array of struct
        for(int i =0; i<numFriends; i++){
            cout << "Enter biographical information for friend # " << i+1 << "." << endl;
            set_person(friends[i]);     //calls function to fill in structs within array of structs
        }
/*----------------------------------------------------------------------
Requirement #24: Demonstrate at least one pointer to struct
----------------------------------------------------------------------*/
        cout << "Your name is: " << person_ptr->name << endl;   //accesses name value of struct through pointer
        cout << "Your age is: " << person_ptr->age << endl << endl;     //accesses age value of struct through pointer

        for(int i=0; i<numFriends; i++)      //prints member values of each struct array element
        {
            cout << "Friend number " << i+1 << "'s name is " << friends[i].name << "." << endl;
            cout << "His/Her Age is " << friends[i].age << " years old." << endl << endl;
        }

        playAgain = replayCheck(playAgain);     //calls replay function to check if user wants to rerun sub-program or return to menu
    }
}

//accessor function to private member value welcome
string Game_functions::getWelcomeMsg()
{
    welcome = "Please tell me your name so I may address you appropriately.";
    return welcome;
}

//fills in member values within array of structs (p is an array of struct)
void set_person(Person &p)
{
    cout << "Enter Name: ";
    cin >> p.name;

    cin.clear();
    cin.ignore(999, '\n');
    cout << "Enter Age: ";
	p.age = intCheck();
	cout << endl;
}

//Random Number Generator program
void Game_functions::randNumGen()
{
    bool playAgain = true;
    while (playAgain == true)       //"playAgain" variable will change if user does not want to play again after running replayCheck function.
    {
        cout << "The purpose of this program is to:" << endl
             << "1:  generate a list of random numbers" << endl
             << "2:  generate an array of random numbers; and" << endl
             << "3:  generate a list of results of bitwise operations" << endl
             << "    performed against the first element of the array of random numbers."
             << endl << endl;

        int numRand = arraySize();  //function asks user for number of random numbers to generate

        IntPtr p;   //creates pointer
/*----------------------------------------------------------------------
Requirement #23: Demonstrate at least one pointer to an array
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #19: Demonstrate dynamically declared array
    (the value of numRand is defined by the user)
----------------------------------------------------------------------*/
        p = new int[numRand];   //pointer points to dynamically declared array

        fillArray(p, numRand);  //calls function to fill up array pointed to by p
        printArray(p, numRand); //calls function to print array pointed to by p

        IntPtr *q = new IntPtr[numRand];
        for (int j = 0; j<numRand; j++){
            q[j] = new int[numRand];    //creates array of pointers
        }

        cout << endl << "Here is a " << numRand << "x" << numRand << " array of random numbers." << endl;

        for ( int j=0; j<numRand; j++){
            for(int k =0; k<numRand; k++){
/*----------------------------------------------------------------------
Requirement #08: Demonstrate random number
----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
Requirement #18: Demonstrate multi-dimensional array
----------------------------------------------------------------------*/
                q[j][k] = rand();   //assigns random numbers to each element of multidimensional array
            }
        }

        for ( int j=0; j<numRand; j++){
            for(int k =0; k<numRand; k++){
/*----------------------------------------------------------------------
Requirement #03: Demonstrate explicit type casting
----------------------------------------------------------------------*/
                double arrayRand = static_cast<double>(q[j][k]);    //casts int into double

//prints out each element value of the array of random numbers
                cout << "At position [" << j << "][" << k << "] the value stored within the array is " << arrayRand << ". " << endl;
            }
        }
/*----------------------------------------------------------------------
Requirement #06: Demonstrate bitwise operator
----------------------------------------------------------------------*/
        cout << endl << "The following is a list of results of various bitwise operations\n"
             << "performed on the first element([0,0] = " << q[0][0] << ") of the array of random numbers.\n";
        cout << q[0][0] << " & " << q[0][0] << " = " << ((q[0][0])&(q[0][0])) << endl;  //copies a bit to the result if it exists in both binary equivalent values
        cout << q[0][0] << " | " << q[0][0] << " = " << ((q[0][0])|(q[0][0])) << endl;  //copies a bit to the result if it exists in either binary equivalent value
        cout << q[0][0] << " ^ " << q[0][0] << " = " << ((q[0][0])^(q[0][0])) << endl << endl;  //copies a bit to the result if it exists in one but not the other binary equivalent value

//deletes array p
    delete [] p;

//deletes array q
    for ( int j=0; j<numRand; j++){
        delete[] q[j];
     }
    delete[] q;

    playAgain = replayCheck(playAgain);     //calls function to check if user wants to run Echo program again.
    }
}

//function that asks user for number of random numbers to generate
int arraySize()
{
    int numOfRandNums;
    cout << "How many random numbers would you like to generate?" << endl;

    numOfRandNums = intCheck();
    return numOfRandNums;
}

//function uses time function to seed random number generator
//and then fills array with random numbers
void fillArray(int p[], int size)
{
    srand (time(NULL));
    for(int i =0; i<size; i++){
        p[i] = rand();
    }
}

//function prints each element of 1D array of random numbers
void printArray(int p[], int size)
{
    cout << endl << "Here is a list of the random numbers you requested:" << endl;
    for(int i =0; i<size; i++){
        cout << p[i] << endl;
    }
    cout << endl;
}

//2 Player number guessing game
void Game_functions::numGuess()
{
    bool playAgain = true;
    while (playAgain == true)       //"playAgain" variable will change if user does not want to play again after running replayCheck function.
    {
        int secretNum;                          //secret number entered by player 1
        int guessLeft;                          //# of valid guesses remaining
        int guessDiff;                          //difference between guess and secret number


        cout << "The purpose of this program is to serve as a 2-player number guessing game.\n"
             << endl;


            int guessCounter = 0;               //# of guesses made by player 2
            int guessLimit = 5;                 //# of guesses player 2 is allowed to make
            int maxRange = 100;                 //maximum # that player 1 can choose as secret number
            int minRange = 0;                   //minimum # that player 1 can choose as secret number
            int newMaxRange = maxRange;         //maximum # that player 2 can choose as secret number
            int newMinRange = minRange;         //minimum # that player 2 can choose as secret number
            int guessNum = maxRange + 1;        //just a way to initialize the guess number
            int accurate = maxRange - minRange; //stores the value of how close player 2's closest guess was
            guessLeft = guessLimit;             //initially, # of guesses left is equal to the maximum number of guesses
            cout << "Player 1 - Please enter the secret number.\n"
                 << "You may choose a number between " << minRange << " and " << maxRange << endl;

            secretNum = intCheck(minRange, maxRange);   //asks for and checks Player 1 input to make sure secret number is integer and within valid range

            while(guessNum != secretNum && guessLeft != 0 ){
                cout << "Player 2 - Please enter your guess. You have " << guessLeft << " guesses remaining.\n"
                     << "You may choose a number between " << newMinRange << " and " << newMaxRange << endl;

                guessNum = intCheck(newMinRange, newMaxRange);  //checks Player 2 input to make sure guessed number is integer and within valid range

                if( guessNum > secretNum){                                  //checks if player 2's guess is larger than the secret number
                    cout << "Your guess was too high!\n" << endl;                   //informs player 2 that guess is too high
                    guessCounter++;                                         //increases the # of guesses by 1
                    guessLeft = guessLimit - guessCounter;                  //calculates the number of guesses remaining for player 2
                    newMaxRange = guessNum - 1;                                 //adjusts max range to the recent guess since the guess was larger than the secret number
                    guessDiff = guessNum - secretNum;                       //calculates how far off the guess was from the secret number
                    if( guessDiff < accurate){                              //if the guess was the most accurate one so far, the measure of how close it was is stored
                        accurate = guessDiff;
                    }
                }

                else if( guessNum < secretNum){                             //checks if player 2's guess is smaller than the secret number
                    cout << "Your guess was too low!\n" << endl;            //informs player 2 that guess is too low
                    guessCounter++;                                         //increases the # of guesses by 1
                    guessLeft = guessLimit - guessCounter;                  //calculates the number of guesses remaining for player 2
                    newMinRange = guessNum + 1;                                 //adjusts min range to the recent guess since the guess was smaller than the secret number
                    guessDiff = secretNum - guessNum;                       //calculates how far off the guess was from the secret number
                    if( guessDiff < accurate){                              //if the guess was the most accurate one so far, the measure of how close it was is stored
                        accurate = guessDiff;
                    }
                }
                else if( guessNum == secretNum || guessLeft == 0){          //escapes out of guessing loop (Victory condition or Loss condition has been met)
                    break;
                }
            }
            if(guessNum == secretNum){       //tests if guess was correct
                cout << "CONGRATULATIONS Player 2! You have guessed correctly!\n" << endl;
            }

            if(guessLeft == 0){     //tests if user has run out of guesses
                cout << "----------------- GAME OVER :( #sadface ---------------------" << endl << endl
                     << "Unfortunately Player 2, you did not guess the secret number\n"
                     << "in the alloted number of guesses.\n" << endl
                     << "The secret number was " << secretNum << "." << endl << endl
                     << "Your closest guess was " << accurate << " away from the secret number.\n" << endl
                     << "----------------------------------------------------" << endl << endl;
            }

        playAgain = replayCheck(playAgain);     //calls function to check if user wants to run Echo program again.
    }
}

//2-Player Word Guessing Game Program
void secretWord()
{
    bool playAgain = true;
    char ltrGuess;
    string secretWord;
    while (playAgain == true)       //"playAgain" variable will change if user does not want to play again after running replayCheck function.
    {
        string wordBank = "abcdefghijklmnopqrstuvwxyz";      //letter bank of letters available to be guessed
        cout << "The purpose of this program is to serve as a 2-player word guessing game.\n"
             << endl;

        cout << "Player 1 - Please enter the secret word.\n"
             << endl;
        cin >> secretWord;                          //stores user input of secret Word.
        secretWord = wordCheck(secretWord);         //checks Player 1 input for valid word

        string display = secretWord;                //sets displayed word equal to secret word
        int guessLimit = secretWord.length() + 5;       //number of guesses dependent on word length
        int guessLeft = guessLimit;                 //number of guesses left is initially equal to guessLimit
        int ltrsLeft = secretWord.length();         //number of letters in word left to be guessed

        for(int i=0; i < display.length(); i++){    //sets '?' for each letter within display
            display[i] = '?';
        }

//Tests for whether player 2 has guesses remaining or letters in secret word to be guessed
//which means victory or loss condition has not been met and game continues on
        while((guessLeft > 0) && (ltrsLeft > 0)){
                int correctFlag = 0;    //keeps track of whether last letter guess was correct
                int wrongFlag = 0;      //keeps track of whether last guess was incorrect
                cout << endl << "Player 2 - Please enter your guess.\n" << endl     //asks player 2 to guess letter in secret word.
                     << "You may select from the following letters: " << wordBank << endl
                     << display << " | You have " << guessLeft << " guesses remaining.\n" << endl;  //prints displayed word with unguessed letters and number of guesses remaining
                cin >> ltrGuess;
                ltrGuess = ltrCheck(ltrGuess);        //checks letter for valid type
                cin.clear();
                cin.ignore(999, '\n');

//if bank of letters contains guessed letter, then delete same letter within word bank
                if(wordBank.find(ltrGuess) != -1){
                    wordBank.erase(wordBank.find(ltrGuess), 1);
                }

//if secret word does not contain guessed letter, then set wrongFlag to true
// and print that guessed letter is not within the secret word
                if(secretWord.find(ltrGuess) == -1) {
                        wrongFlag = 1;
                        cout << ltrGuess << " is not in the word. " << endl << endl;
                    }

//if secret word does contain guessed letter, then set correctFlag to true
// and decrement value of number of letters remaining to be guessed within secretWord
                for(int i = 0; i < secretWord.length(); i++){
                    if(ltrGuess == secretWord[i]) {
                        display[i] = secretWord[i];     //updates displayed word to user 2, displays correctly guessed letters.
                        correctFlag = 1;
                        ltrsLeft--;
                    }
                }

//if last guess was correct and there are no more letters to be guessed within
//the secret word, victory condition has been met.
                if(correctFlag == 1)
                {
                    if(ltrsLeft == 0)
                    {
                        cout << "Congratulations Player 2! YOU ARE VICTORIOUS!!!" << endl;
                    }

//decrements number of guesses if last guess was correct but there are letters remaining to be guessed
                    guessLeft--;
                }

//if last guess was incorrect and there are no more letters to be guessed within
//the secret word, loss condition has been met.
                if(wrongFlag == 1)
                {
                    guessLeft--;
                    if(guessLeft == 0)
                    {
                        cout << "Congratulations Player 1! You beat Player 2!!!" << endl
                             << "Sorry, Player 2. You failed. The secret word was: " << secretWord << endl    //displays what secret word was.
                             << "You failed to guess the following letters: ";

                        for(int i = 0; i < secretWord.length(); i++){
                            if(display[i] == '?'){
                                cout << secretWord[i] << " ";
                            }
                        }
                        cout << endl << endl;
                    }
                }
        }
        playAgain = replayCheck(playAgain);     //calls function to check if user wants to run Echo program again.
    }
}

//tests player 1's input to make sure it only contains letters
string wordCheck(string secretWord)
{
    for( int i = 0; i < secretWord.length(); i++) {
        if ((secretWord.at(i) >= 'a' && secretWord.at(i) <= 'z'))
            {
            return secretWord;      //returns valid word to function
            }
        else {
            cout << "Player 1 - Your secret word may only contain lowercase letters.\n"
                 << endl
                 << "Please reenter your secret word.\n";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> secretWord;
            secretWord = wordCheck(secretWord);     //function calls itself if input is not valid word
        }
    }
}

//tests player 2's input to make sure it only contains a letter
char ltrCheck(char ltrGuess)
{
        if ((ltrGuess >= 'a' && ltrGuess <= 'z'))
            {
            return ltrGuess;    //returns valid letter to function
            }
        else {
            cout << "Player 2 - Your guess may only contain lowercase letters.\n"
                 << endl
                 << "Please reenter your guess.\n";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> ltrGuess;
            ltrGuess = ltrCheck(ltrGuess);  //function calls itself if input is not valid letter
        }
}

