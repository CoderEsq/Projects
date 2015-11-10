/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 2/25/2015
*   Last Modification Date:       3/1/2015
*   Filename:                     assign4.cpp
*
*   Overview:   This program is a fantasy combat game.
*
*
*   Input:  The input shall consist of integers to select teams of different fighters as
*           as well as names of the fighters.
*
*
*   Output: The output of the program will be combat between two teams of selected creatures.
*
****************************************************************************************/

#include "Creature.h"
#include "Goblin.h"
#include "Barbarian.h"
#include "ReptilePeople.h"
#include "TheShadow.h"
#include "BlueMen.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <istream>
#include <limits>
#include <algorithm>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::streamsize;
using std::setw;
using std::rotate;
using std::numeric_limits;
using std::max;

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
//the design of this function was influenced by the discussion on
//http://r3dux.org/2011/11/how-to-get-valid-integer-input-in-c-a-stupidly-long-solution-to-a-stupidly-simple-problem/#comment-7175
int intCheck(int minRange, int maxRange);

/*********************************************************************
** Function: sortBykills
** Description: Function used to sort vector of all fighters by their number of kills
** Parameters: Creature pointers
** Pre-Conditions: Vector contains pointers to base class objects
** Post-Conditions: Vector contains pointers to base class objects sorted by number of kills.
*********************************************************************/
//design of this function influenced by discussion on: http://www.cplusplus.com/articles/NhA0RXSz/
bool sortBykills(Creature *lhs, Creature *rhs) { return lhs->getkills() > rhs->getkills(); }

/*********************************************************************
** Function: sortBydmg
** Description: Function used to sort vector of all fighters by the amount of damage inflicted.
** Parameters: Creature pointers
** Pre-Conditions: Vector contains pointers to base class objects
** Post-Conditions: Vector contains pointers to base class objects sorted by the amount of damage inflicted.
*********************************************************************/
//design of this function influenced by discussion on: http://www.cplusplus.com/articles/NhA0RXSz/
bool sortBydmg(Creature *lhs, Creature *rhs) { return lhs->gettotaldmg() > rhs->gettotaldmg(); }

int main()
{
srand(time(NULL));
bool menuOn = true;

do{
        vector<Creature *> fighters;
        vector<Creature *> team1;
        vector<Creature *> team2;
        vector<Creature *> losers1;
        vector<Creature *> losers2;

        int tSize;
        cout << endl << setw(50) << "WELCOME TO FIGHT CLUB!\n" << endl << endl
             << "How many fighters would you like on each team?" << endl;
        tSize = intCheck(1, 1000);
        cout << endl;

        int p1Choice;
        for(int i = 0; i < tSize; i++)
            {

             cout << "PLAYER 1 - Please select Fighter #" << i+1 << " you would like to add to your team.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Goblin" << endl
             << "   2:     Barbarian" << endl
             << "   3:     Reptile People" << endl
             << "   4:     Blue Men" << endl
             << "   5:     The Shadow" << endl
             << "   6:     EXIT GAME" << endl << endl;

             cout << "PLAYER 1 Selection: ";

             //cin >> p1Choice;
             p1Choice = intCheck(1, 6);

//switch statement allows 1st player to select which race they would like to play as.
switch(p1Choice)
             {
             case 1:
                 team1.push_back(new Goblin(1));  //creates new Goblin class and inserts it into end of vector
                 break;
             case 2:
                 team1.push_back(new Barbarian(1));
                 break;
             case 3:
                 team1.push_back(new ReptilePeople(1));
                 break;
             case 4:
                 team1.push_back(new BlueMen(1));
                 break;
             case 5:
                 team1.push_back(new TheShadow(1));
                 break;
             case 6:
                 cout << "Exiting game...." << endl;
                 exit(1);
                 break;
             }
        }

        int p2Choice;
        for(int i = 0; i < tSize; i++)
            {

             cout << "PLAYER 2 - Please select Fighter #" << i+1 << " you would like to add to your team.\n"
             << "Enter the integer corresponding to your choice."
             << endl << endl
             << "   1:     Goblin" << endl
             << "   2:     Barbarian" << endl
             << "   3:     Reptile People" << endl
             << "   4:     Blue Men" << endl
             << "   5:     The Shadow" << endl
             << "   6:     EXIT GAME" << endl << endl;

             cout << "PLAYER 2 Selection: ";

             //cin >> p2Choice;
             p2Choice = intCheck(1, 6);

//switch statement allows 1st player to select which race they would like to play as.
switch(p2Choice)
             {
             case 1:
                 team2.push_back(new Goblin(2));  //creates new Goblin class and inserts it into end of vector
                 break;
             case 2:
                 team2.push_back(new Barbarian(2));
                 break;
             case 3:
                 team2.push_back(new ReptilePeople(2));
                 break;
             case 4:
                 team2.push_back(new BlueMen(2));
                 break;
             case 5:
                 team2.push_back(new TheShadow(2));
                 break;
             case 6:
                 cout << "Exiting game...." << endl;
                 exit(1);
                 break;
             }
        }

    //prints out teams list
    cout << setw(40) << "TEAMS HAVE BEEN SELECTED" << endl << endl;

    cout << setw(20) << "PLAYER 1'S TEAM" << setw(30) << "PLAYER 2'S TEAM" << endl;
    cout << setw(20) << "---------------" << setw(30) << "---------------" << endl;
    for (int i = 0; i < tSize; i++)
    {
        cout << setw(15) << team1[i]->getRace() << setw(30) << team2[i]->getRace() << endl;
    }

    cout << endl;

    //The following executes while both teams have 'live' fighters
    while ( !team1.empty() && !team2.empty() )
    {

    cout << endl << "First, we need to determine which player attacks first." << endl;
    cout << "The player with the highest dice roll(1d6) will get to attack first." << endl << endl;

    team1[0]->DiceRoll(1, 6);    //calls DiceRoll function of derived class
    int p1roll = team1[0]->getdiceTotal();   //gets DiceRoll total from derived class
    cout << "PLAYER 1 has rolled a " << p1roll << "." << endl << endl;

    team2[0]->DiceRoll(1, 6);
    int p2roll = team2[0]->getdiceTotal();
    cout << "PLAYER 2 has rolled a " << p2roll << "." << endl << endl;

//dice roll totals from player 1 and player 2 are passed to function to determine winner
    int pWinner = goFirst(p1roll, p2roll);
    int pLoser = 0;
    if(pWinner == 1)//Player 1 has won dice roll
        {
            pLoser = 2;
        }
    if(pWinner == 2)  //Player 2 has won dice roll
        {
            pLoser = 1;
            team1.swap(team2);  //swaps teams
        }

    // calls and stores starting strengthpoints from class
    double p1SP = team1[0]->getstrengthPoints();
    int p1ID = team1[0]->getID();  //obtains ID num of race


    double p2SP = team2[0]->getstrengthPoints();
    int p2ID = team2[0]->getID();

    //these flags are used to indicate whether Goblin's Special has been activated
    int achillesFlagp1 = 0;
    int achillesFlagp2 = 0;

    while ( ( (p1SP > 0) || (p2SP > 0) ) && ( !team1.empty() && !team2.empty() ) )
    {
        double p1dmg;
        double p2dmg;

        cout << endl << "PLAYER " << pWinner << " attacks...with " << team1[0]->getName() << "(" << team1[0]->getRace() << ")" << endl;
        team1[0]->Attack(p2ID);    //winner's attack member function is executed

        cout << "PLAYER " << pLoser << " defends...with " << team2[0]->getName() << "(" << team2[0]->getRace() << ")" << endl;
        team2[0]->Defense();    //loser's defense member function is executed

        //IF statement compares IDs to see if Goblin is facing nonGoblin and whether Goblin Special Flag
        //has not already been turned on and also that Goblin has rolled a 12.
        if ( p1ID == 1 && p2ID != 1 && achillesFlagp1 == 0 && team1[0]->getdiceTotal() == 12 )
        {
            achillesFlagp1 = 1; //if conditions are met, this flag is activated for remainder of game.
            cout << "OUCH!!! Goblin has sliced " << team2[0]->getName() << "'s Achilles Tendon!" << endl;
            cout << team2[0]->getName() << "'s Attack has been reduced by 50% for the remainder of the fight!" << endl << endl;
        }

        //If Goblin Attack Special has been activated, this modified damage calculation will occur
        if ( achillesFlagp2 == 1 )
        {
            p2dmg = ( static_cast<double>(( team1[0]->getdiceTotal() )) / 2.0 ) - ( team2[0]->getdiceTotal() ) - ( team2[0]->getArmor() );

        }

        //this is the normal damage calculation that will run if Goblin Special is not active
        else {
            p2dmg = ( team1[0]->getdiceTotal() ) - ( team2[0]->getdiceTotal() ) - ( team2[0]->getArmor() );
        }

        //changes damage incurred to 0 if actually negative number so strengthpoints
        //are not increased from particularly strong defense roll
        if(p2dmg <= 0){ p2dmg = 0;}
        team1[0]->dmgGiven(p2dmg);
        p2SP = p2SP - p2dmg;

        //checks if victory condition has been met after player's Attack round
        if(p2SP <= 0)
            { p2SP = 0;
            cout << "PLAYER " << pLoser << " receives " << p2dmg << " Damage and now has " << p2SP << " strength points remaining." << endl;
            cout << "PLAYER " << pWinner << "'s " << team1[0]->getRace() << " IS VICTORIOUS IS COMBAT!!!" << endl << endl;

            p1SP = p1SP + ( p2dmg * 0.5);
            cout << team1[0]->getRace() << " has regenerated " << p1SP << " strength points and has been moved " << endl;
            cout << "to the back of line." << endl;
            team1[0]->healAmount(p1SP);
            team1[0]->killCounter();
            rotate(team1.begin(),team1.begin()+1,team1.end());

            if(!team2.empty())
            {
            cout << "Now the next fight shall begin...." << endl;
            losers2.push_back(team2[0]);
            team2.erase(team2.begin());
            }

            break;
            }

        cout << "PLAYER " << pLoser << " receives " << p2dmg << " Damage and now has " << p2SP << " strength points remaining." << endl;

        //2nd Player to move begins their attack round
        cout << endl << "PLAYER " << pLoser << " attacks...with " << team2[0]->getName() << "(" << team2[0]->getRace() << ")" << endl;
        team2[0]->Attack(p2ID);

        //1st player to move has their defensive roll
        cout << "PLAYER " << pWinner << " defends...with " << team1[0]->getName() << "(" << team1[0]->getRace() << ")" << endl;
        team1[0]->Defense();

        //IF statement compares IDs to see if Goblin is facing nonGoblin and whether Goblin Special Flag
        //has not already been turned on and also that Goblin has rolled a 12.
        if ( p2ID == 1 && p1ID != 1 && achillesFlagp2 == 0 && team2[0]->getdiceTotal() == 12 )
        {
            achillesFlagp2 = 1;
            cout << "OUCH!!! Goblin has sliced " << team1[0]->getName() << "'s Achilles Tendon!" << endl;
            cout << team1[0]->getName() << "'s Attack has been reduced by 50% for the remainder of the fight!" << endl << endl;
        }

        //If Goblin Attack Special has been activated, this modified damage calculation will occur
        if ( achillesFlagp1 == 1 )
        {
            p1dmg = ( static_cast<double>(( team2[0]->getdiceTotal() )) / 2.0 ) - ( team1[0]->getdiceTotal() ) - ( team1[0]->getArmor() );

        }

        //this is the normal damage calculation that will run if Goblin Special is not active
        else {

        p1dmg = ( team2[0]->getdiceTotal() ) - ( team1[0]->getdiceTotal() ) - ( team1[0]->getArmor() );
        }

        if(p1dmg <= 0){ p1dmg = 0;}
        team2[0]->dmgGiven(p1dmg);

        p1SP = p1SP - p1dmg;

        if(p1SP <= 0)
            { p1SP = 0;
            cout << "PLAYER " << pWinner << " receives " << p1dmg << " Damage and now has " << p1SP << " strength points remaining." << endl;
            cout << "PLAYER " << pLoser << "'s " << team2[0]->getRace() << " IS VICTORIOUS IN COMBAT!!!" << endl << endl;

            p2SP = p2SP + ( p1dmg * 0.5);
            cout << team2[0]->getRace() << " has regenerated " << p2SP << " strength points and has been moved " << endl;
            cout << "to the back of line." << endl;
            team2[0]->healAmount(p2SP);
            team2[0]->killCounter();
            rotate(team2.begin(),team2.begin()+1,team2.end());

            if(!team1.empty())
            {
                cout << "Now the next fight shall begin...." << endl;
                losers1.push_back(team1[0]);
                team1.erase(team1.begin());
            }

            break;
            }

        cout << "PLAYER " << pWinner << " receives " << p1dmg << " Damage and now has " << p1SP << " strength points remaining." << endl;

    }

    }

    for(unsigned int i = 0; i < team1.size(); i++)
    {
        fighters.push_back(team1[i]);
    }

    for(unsigned int i = 0; i < team2.size(); i++)
    {
        fighters.push_back(team2[i]);
    }

    for(unsigned int i = 0; i < losers1.size(); i++)
    {
        fighters.push_back(losers1[i]);
    }

    for(unsigned int i = 0; i < losers2.size(); i++)
    {
        fighters.push_back(losers2[i]);
    }

    int player1killNum = 0;
    int player2killNum = 0;

    for(unsigned int i = 0; i < fighters.size(); i++)
    {

        if( (fighters[i]->getteamID()) == 1 )
        {
            player1killNum = player1killNum + fighters[i]->getkills();
        }

        if( (fighters[i]->getteamID()) == 2 )
        {
            player2killNum = player2killNum + fighters[i]->getkills();
        }

    }

    if( player1killNum > player2killNum )
    {
        cout << endl << endl << "PLAYER 1 HAS DEFEATED PLAYER 2!!!" << endl << endl << endl;
    }

    if( player1killNum < player2killNum )
    {
        cout << endl << endl << "PLAYER 2 HAS DEFEATED PLAYER 1!!!" << endl << endl << endl;
    }

    sort(fighters.begin(), fighters.end(), sortBykills);
    cout << setw(48) << "FIGHTER STANDINGS BY NUMBER OF KILLS" << endl;
    cout << setw(48) << "------------------------------------" << endl;

    for (unsigned int i = 0; i < fighters.size(); i++)
    {
        string charName = fighters[i]->getName();
        string raceName = fighters[i]->getRace();
        cout << "RANK: " << i+1 << "   TEAM: " << fighters[i]->getteamID() << "   NAME: " << charName << "   RACE: " << raceName << "   KILLS: " << fighters[i]->getkills() << endl << endl;
    }

    cout << endl << endl;

    sort(fighters.begin(), fighters.end(), sortBydmg);
    cout << setw(49) << "FIGHTER STANDINGS BY DAMAGE INFLICTED" << endl;
    cout << setw(49) << "-------------------------------------" << endl;

    for (unsigned int i = 0; i < fighters.size(); i++)
    {
        string charName = fighters[i]->getName();
        string raceName = fighters[i]->getRace();
        cout << "RANK: " << i+1 << "   TEAM: " << fighters[i]->getteamID() << "   NAME: " << charName << "   RACE: " << raceName << "   DAMAGE INFLICTED: " << fighters[i]->gettotaldmg() << endl << endl;
    }

    cout << endl;
    //Destroys created objects
    for(unsigned int i = 0; i < team1.size(); i++)
    {
        delete team1[i];
    }
    team1.clear();

    for(unsigned int i = 0; i < team2.size(); i++)
    {
        delete team2[i];
    }
    team2.clear();

    for(unsigned int i = 0; i < losers1.size(); i++)
    {
        delete losers1[i];
    }
    losers1.clear();

    for(unsigned int i = 0; i < losers2.size(); i++)
    {
        delete losers2[i];
    }
    losers2.clear();

    fighters.clear();

    cout << endl;

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
                 continue;
                 break;

             case 2:
                 exit(1);
                 break;
             }

}while(menuOn);

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
        pWinner = 1;
        return pWinner;
    }

    else if(temp2 > temp1)
    {
        cout << "PLAYER 2 has won the dice roll." << endl << endl;
        flag1 = 2;
        pWinner = 2;
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
