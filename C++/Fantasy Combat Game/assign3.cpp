/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 2/12/2015
*   Last Modification Date:       2/12/2015
*   Filename:                     assign3.cpp
*
*   Overview:   This program is a fantasy combat game.
*
*
*   Input:  The input shall consist of integers to select different creatures.
*
*
*   Output: The output of the program will be combat between two selected creatures.
*
*
****************************************************************************************/


#include "Creature.h"
#include "Barbarian.h"
#include "ReptilePeople.h"
#include "TheShadow.h"
#include "Goblin.h"
#include "BlueMen.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <istream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::streamsize;

/*********************************************************************
** Function: goFirst
** Description: Function used to see which player will be able to attack first.
** Parameters: integers of each players' dice rolls.
** Pre-Conditions: each user has rolled a dice
** Post-Conditions: returns valid integer that designates which player will attack first
*********************************************************************/
int goFirst(int rollp1, int rollp2);

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

bool menuOn = true;
vector<Creature *> fighters;

do{
        cout << endl << "\t WELCOME TO FIGHT CLUB!\n" << endl

             << "PLAYER 1 - Please select which creature you would like to choose.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Goblin" << endl
             << "   2:     Barbarian" << endl
             << "   3:     Reptile People" << endl
             << "   4:     Blue Men" << endl
             << "   5:     The Shadow" << endl
             << "   6:     EXIT" << endl << endl;

             cout << "PLAYER 1 Selection: ";

             int p1Choice = intCheck(1, 6);

             cout << endl << endl;
             cout << "--------------------------------------------------------------------";
             cout << "------------" << endl;

//switch statement allows 1st player to select which race they would like to play as.
switch(p1Choice)
             {
             case 1:
                 fighters.push_back(new Goblin());  //creates new Goblin class and inserts it into end of vector
                 break;
             case 2:
                 fighters.push_back(new Barbarian());
                 break;
             case 3:
                 fighters.push_back(new ReptilePeople());
                 break;
             case 4:
                 fighters.push_back(new BlueMen());
                 break;
             case 5:
                 fighters.push_back(new TheShadow());
                 break;
             case 6:
                 exit(1);
                 break;
             }

        cout << endl << "\t WELCOME TO FIGHT CLUB!\n" << endl

             << "PLAYER 2 - Please select which creature you would like to choose.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Goblin" << endl
             << "   2:     Barbarian" << endl
             << "   3:     Reptile People" << endl
             << "   4:     Blue Men" << endl
             << "   5:     The Shadow" << endl
             << "   6:     EXIT" << endl << endl;

             cout << "PLAYER 2 Selection: ";

             int p2Choice = intCheck(1, 6);

             cout << endl << endl;
             cout << "--------------------------------------------------------------------";
             cout << "------------" << endl;

//switch statement allows 2nd player to select which race they would like to play as.
switch(p2Choice)
             {
             case 1:
                 fighters.push_back(new Goblin());
                 break;
             case 2:
                 fighters.push_back(new Barbarian());
                 break;
             case 3:
                 fighters.push_back(new ReptilePeople());
                 break;
             case 4:
                 fighters.push_back(new BlueMen());
                 break;
             case 5:
                 fighters.push_back(new TheShadow());
                 break;
             case 6:
                 exit(1);
                 break;
             }

    cout << "PLAYER 1 has selected " << fighters[0]->getName() << "." << endl << endl;
    cout << "PLAYER 2 has selected " << fighters[1]->getName() << "." << endl << endl;
    cout << "Press ENTER to continue..." << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

    cout << "Now we need to determine which player attacks first." << endl;
    cout << "The player with the highest dice roll(1d6) will get to attack first." << endl << endl;

    cout << "PLAYER 1 press ENTER to roll your dice." << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

    fighters[0]->DiceRoll(1, 6);    //calls DiceRoll function of derived class
    int p1roll = fighters[0]->getdiceTotal();   //gets DiceRoll total from derived class
    cout << "PLAYER 1 has rolled a " << p1roll << "." << endl << endl;

    cout << "PLAYER 2 press ENTER to roll your dice." << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    fighters[1]->DiceRoll(1, 6);
    int p2roll = fighters[1]->getdiceTotal();
    cout << "PLAYER 2 has rolled a " << p2roll << "." << endl << endl;

    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

//dice roll totals from player 1 and player 2 are passed to function to determine winner
    int pWinner = goFirst(p1roll, p2roll);
    int pLoser = 5;
    if(pWinner == 0){pLoser = 1;} //winner indicator is assigned to player who won
    if(pWinner == 1){pLoser = 0;}


    // calls and stores starting strengthpoints from class
    double p1SP = fighters[pWinner]->getstrengthPoints();
    int p1ID = fighters[pWinner]->getID();  //obtains ID num of race


    double p2SP = fighters[pLoser]->getstrengthPoints();
    int p2ID = fighters[pLoser]->getID();

    //these flags are used to indicate whether Goblin's Special has been activated
    int achillesFlagp1 = 0;
    int achillesFlagp2 = 0;


    while ( (p1SP > 0) || (p2SP > 0) )
    {
        double p1dmg;
        double p2dmg;

        cout << "PLAYER " << pWinner + 1 << " attacks... " << endl;
        fighters[pWinner]->Attack(p2ID);    //winner's attack member function is executed

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        cout << "PLAYER " << pLoser + 1 << " defends... " << endl;
        fighters[pLoser]->Defense();    //loser's defense member function is executed

        //IF statement compares IDs to see if Goblin is facing nonGoblin and whether Goblin Special Flag
        //has not already been turned on and also that Goblin has rolled a 12.
        if ( p1ID == 1 && p2ID != 1 && achillesFlagp1 == 0 && fighters[pWinner]->getdiceTotal() == 12 )
        {
            achillesFlagp1 = 1; //if conditions are met, this flag is activated for remainder of game.
            cout << "OUCH!!! Goblin has sliced " << fighters[pLoser]->getName() << "'s Achilles Tendon!" << endl;
            cout << fighters[pLoser]->getName() << "'s Attack has been reduced by 50% for the remainder of the fight!" << endl << endl;
        }

        //If Goblin Attack Special has been activated, this modified damage calculation will occur
        if ( achillesFlagp2 == 1 )
        {
            p2dmg = ( static_cast<double>(( fighters[pWinner]->getdiceTotal() )) / 2.0 ) - ( fighters[pLoser]->getdiceTotal() ) - ( fighters[pLoser]->getArmor() );
        }

        //this is the normal damage calculation that will run if Goblin Special is not active
        else {
        p2dmg = ( fighters[pWinner]->getdiceTotal() ) - ( fighters[pLoser]->getdiceTotal() ) - ( fighters[pLoser]->getArmor() );
        }

        //changes damage incurred to 0 if actually negative number so strengthpoints
        //are not increased from particularly strong defense roll
        if(p2dmg <= 0){ p2dmg = 0;}

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        p2SP = p2SP - p2dmg;

        //checks if victory condition has been met after player's Attack round
        if(p2SP <= 0)
            { p2SP = 0;
            cout << "PLAYER " << pLoser + 1 << " receives " << p2dmg << " Damage and now has " << p2SP << " strength points remaining." << endl;
            cout << "PLAYER " << pWinner + 1 << " IS VICTORIOUS IS COMBAT!!!" << endl << endl;
            break;
            }

        cout << "PLAYER " << pLoser + 1 << " receives " << p2dmg << " Damage and now has " << p2SP << " strength points remaining." << endl;

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        //2nd Player to move begins their attack round
        cout << "PLAYER " << pLoser + 1 << " attacks... " << endl;
        fighters[pLoser]->Attack(p2ID);

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        //1st player to move has their defensive roll
        cout << "PLAYER " << pWinner + 1 << " defends... " << endl;
        fighters[pWinner]->Defense();

        //IF statement compares IDs to see if Goblin is facing nonGoblin and whether Goblin Special Flag
        //has not already been turned on and also that Goblin has rolled a 12.
        if ( p2ID == 1 && p1ID != 1 && achillesFlagp2 == 0 && fighters[pLoser]->getdiceTotal() == 12 )
        {
            achillesFlagp2 = 1;
            cout << "OUCH!!! Goblin has sliced " << fighters[pWinner]->getName() << "'s Achilles Tendon!" << endl;
            cout << fighters[pWinner]->getName() << "'s Attack has been reduced by 50% for the remainder of the fight!" << endl << endl;
        }

        //If Goblin Attack Special has been activated, this modified damage calculation will occur
        if ( achillesFlagp1 == 1 )
        {
            p1dmg = ( static_cast<double>(( fighters[pLoser]->getdiceTotal() )) / 2.0 ) - ( fighters[pWinner]->getdiceTotal() ) - ( fighters[pWinner]->getArmor() );
        }

        //this is the normal damage calculation that will run if Goblin Special is not active
        else {

        p1dmg = ( fighters[pLoser]->getdiceTotal() ) - ( fighters[pWinner]->getdiceTotal() ) - ( fighters[pWinner]->getArmor() );

        }

        if(p1dmg <= 0){ p1dmg = 0;}

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

        p1SP = p1SP - p1dmg;

        if(p1SP <= 0)
            { p1SP = 0;
            cout << "PLAYER " << pWinner + 1 << " receives " << p1dmg << " Damage and now has " << p1SP << " strength points remaining." << endl;
            cout << "PLAYER " << pLoser + 1 << " IS VICTORIOUS IS COMBAT!!!" << endl << endl;
            break;
            }

        cout << "PLAYER " << pWinner + 1 << " receives " << p1dmg << " Damage and now has " << p1SP << " strength points remaining." << endl;

        cout << "Press ENTER to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    }

    //Destroys created objects
    fighters[0]->~Creature();
    fighters[1]->~Creature();

    cout << "Would you like to play again?" << endl;
    cout << "Enter 1 if you would like to play again " << endl
         << "or Enter 2 if you would like to exit the program." << endl << endl;

    cout << "Your Selection: ";

    int playAgain = intCheck(1, 2);

    cout << endl << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;

//checks if users want to play again or exit program
switch(playAgain)
             {
             case 1:
                 fighters.clear(); //clears vector of pointers to objects and allows it to be refilled
                 continue;
                 break;

             case 2:
                 exit(1);
                 break;
             }
}

while(menuOn);

return 0;
}

//function used to determine which player will go first
int goFirst(int rollp1, int rollp2)
{
    int temp1 = rollp1;
    int temp2 = rollp2;
    int flag1 = 1;
    int pWinner;
    do {

    if(temp1 > temp2)
    {
        cout << "PLAYER 1 has won the dice roll." << endl << endl;
        flag1 = 2;
        pWinner = 0;
        return pWinner;
    }

    else if(temp2 > temp1)
    {
        cout << "PLAYER 2 has won the dice roll." << endl << endl;
        flag1 = 2;
        pWinner = 1;
        return pWinner;
    }

    //function will run until 1 player rolls a dice number larger than the other
    else if(temp1 == temp2)
    {
        cout << "...you both rolled the same value." << endl;
        cout << "Automatically rerolling a larger dice on your behalves." << endl << endl;
        temp1 = rand();
        temp2 = rand();
        cout << "PLAYER 1 has rolled a " << temp1 << "." << endl << endl;
        cout << "PLAYER 2 has rolled a " << temp2 << "." << endl << endl;
    }

    }while(flag1 == 1);

    return 5;
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
