/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 3/12/2015
*   Last Modification Date:       3/16/2015
*   Filename:                     final.cpp
*
*   Overview:   This program is a game in which the player must collect 10 pieces to
*               complete repairs to their escape pod before their oxygen tank runs out.
*
*   Input:  The input shall consist of integers to select different directions.
*
*   Output: The output of the program will be messages to the user.
****************************************************************************************/

#include "Room.h"
#include "Quarter.h"
#include "Rock.h"
#include "Dice.h"
#include "Player.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <cstdlib>
#include <typeinfo>
#include <ctime>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::streamsize;
using std::numeric_limits;
using std::max;
using std::setw;


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
    srand((time(NULL)));    //seeds random number generator
    bool menuOn = true;

    do{     //this do-while loop will execute while the player wants to continue playing
    Player player;
    Room* location;

    //assigns base pointers to derived class objects
    Room* room1 = new Quarter("Bridge");
    Room* room2 = new Rock("Communications Room");
    Room* room3 = new Dice("AirLock");
    Room* room4 = new Quarter("Medical Bay");
    Room* room5 = new Rock("Crew Quarters");
    Room* room6 = new Dice("Greenhouse");
    Room* room7 = new Quarter("Engineering Lab 1");
    Room* room8 = new Rock("Engineering Lab 2");
    Room* room9 = new Dice("Engine Room");
    Room* room10 = new Quarter("Escape Pod");

    //links pointers and creates linked structure
    room1->fore = NULL;
    room1->aft = room2;
    room1->starboard = NULL;
    room1->port = NULL;

    room2->fore = room1;
    room2->aft = room4;
    room2->starboard = room3;
    room2->port = NULL;

    room3->fore = NULL;
    room3->aft = NULL;
    room3->starboard = NULL;
    room3->port = room2;

    room4->fore = room2;
    room4->aft = room5;
    room4->starboard = NULL;
    room4->port = NULL;

    room5->fore = room4;
    room5->aft = room6;
    room5->starboard = NULL;
    room5->port = room10;

    room6->fore = room5;
    room6->aft = room7;
    room6->starboard = NULL;
    room6->port = NULL;

    room7->fore = room6;
    room7->aft = room8;
    room7->starboard = NULL;
    room7->port = NULL;

    room8->fore = room7;
    room8->aft = room9;
    room8->starboard = NULL;
    room8->port = NULL;

    room9->fore = room8;
    room9->aft = NULL;
    room9->starboard = NULL;
    room9->port = NULL;

    room10->fore = NULL;
    room10->aft = NULL;
    room10->starboard = room5;
    room10->port = NULL;

    location = room1; //sets starting room.

    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl << endl;
    cout << setw(50) << "WELCOME TO THE HAUNTED SPACESHIP" << endl;
    cout << setw(50) << "--------------------------------" << endl << endl;

    cout << "Your entire crew is dead and you killed them. Did you have any other choice?\n"
         << "6 hours ago, NASA informed your ship that a X97 magnitude solar flare is\n"
         << "scheduled to slam into your vessel within the next 24 hours. Things went\n"
         << "downhill pretty quickly after the crew received the dire news. There were 11\n"
         << "crew members aboard your ship...and a single escape pod. People panicked. Crew\n"
         << "members began stripping the escape pod of vital components to prevent a\n"
         << "premature launch and spreading out across the ship to negotiate for their own,\n"
         << "individual survival. You, on the other hand, began manually overriding each of\n"
         << "the redundant safety controls in the ship's software. This was not too\n"
         << "difficult of a challenge since you are a graduate of one the best online,\n"
         << "computer science programs ever accredited by the Northwest Commission on\n"
         << "Colleges & Universities.\n\n"
         << "When you were finished, you calmly put on your spacesuit and opened the airlock." << endl << endl;

    cout << "Press ENTER to continue..." << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

   cout << "Your plan worked for the most part. Everyone is dead. YAYYYY!!! But...their\n"
        << "ghosts remain. And they are kind of upset with you. You need to collect the 10\n"
        << "missing pieces which are located in the 10 accessible compartments of the ship\n"
        << "being guarded by the 10 ghost crew members. You can only carry up to 4 pieces\n"
        << "in your backpack at the same time so when your backpack is full return to the\n"
        << "ESCAPE POD to assemble some parts and free up space. Also, one more thing.\n\n"

         << "You have a VERY LIMITED supply of oxygen in your spacesuit. Every time you\n"
         << "move from one compartment to another, you use up oxygen. Every time you\n"
         << "attempt to enter a sealed off section of the spaceship, you use up oxygen.\n"
         << "Every time you engage with one of your former crew members, you use up oxygen.\n"
         << "You must make it to the ESCAPE POD and get it working.\n\n"

         << "In order to survive, you must bring all 10 pieces to the ESCAPE POD before you\n"
         << "run out of oxygen and die. Good luck with that!" << endl << endl;

    cout << "Press ENTER to begin..." << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

    //while loop runs while Win/Loss conditions haven't been met
    while( player.getOxygen() > 0 && !(player.getInventory() >= 10 && location->getName() == "Escape Pod") )
    {
        //if player is in escape pod, then parts are assembled
        if( location->getName() == "Escape Pod" )
        {
            player.assemble();  //used to remove parts from backpack and assemble
            if (player.getInventory() >= 10)    //if assembled parts >= 10, loop will terminate
            {
                break;
            }
        }

    cout << "You are in the " << location->getName() << " room." << endl;
    cout << "You are carrying " << player.getBackpack() << " parts in your backpack." << endl;
    cout << "You have assembled " << player.getInventory() << " of 10 parts needed to repair the escape pod." << endl;
    cout << "You have " << player.getOxygen() << "% of your oxygen remaining." << endl << endl;

    cout << "Which direction would you like to travel?" << endl
             << "   1:     Fore" << endl
             << "   2:     Aft" << endl
             << "   3:     Starboard" << endl
             << "   4:     Port" << endl
             << "   5:     Engage Ghost" << endl
             << "   6:     Take Suicide Pill" << endl << endl;

            cout << "Your Selection: ";

             int choice = intCheck(1, 6);
             cout << endl << endl;

            cout << "--------------------------------------------------------------------";
            cout << "------------" << endl << endl;

    switch(choice)
             {
             case 1:
                 //checks pointer for target
                 if(location->fore != NULL)
                 {
                     player.Breath(1);  //used to decrease oxygen level
                     location = location->fore;
                     continue;
                 }
                 else
                 {
                     cout << "That section of the spaceship is sealed. You may not enter." << endl << endl;
                     player.Breath(1);
                 }
                 break;
             case 2:
                 if(location->aft != NULL)
                 {
                     player.Breath(1);
                     location = location->aft;
                     continue;
                 }
                 else
                 {
                     cout << "That section of the spaceship is sealed. You may not enter." << endl << endl;
                     player.Breath(1);
                 }
                 break;
             case 3:
                 if(location->starboard != NULL)
                 {
                     player.Breath(1);
                     location = location->starboard;
                     continue;
                 }
                 else
                 {
                     cout << "That section of the spaceship is sealed. You may not enter." << endl << endl;
                     player.Breath(1);
                 }
                 break;
             case 4:
                 if(location->port != NULL)
                 {
                     player.Breath(1);
                     location = location->port;
                     continue;
                 }
                 else
                 {
                     cout << "That section of the spaceship is sealed. You may not enter." << endl << endl;
                     player.Breath(1);
                 }
                 break;
             case 5:
                 {
                 if(location->getwinLoss() != 1)//checks if player has already defeated ghost in current room
                    {
                        player.Breath(1);
                        if( player.getBackpack() < 4 )  //If player has 4 items in backpack, player cannot play game against ghost.
                        {
                            location->game();   //executes ghost game function
                            if( location->getwinLoss() == 1 )   //checks if player defeated ghost
                            {
                                player.collectItem();   //if player has won, player collects 1 part
                                continue;
                            }
                        }
                        else
                        {
                            cout << "Your back pack is full! Return to the ESCAPE POD and assemble" << endl;
                            cout << "some parts to free up space in your backpack. HURRY!" << endl << endl;
                        }
                    }
                else
                    {
                        cout << "You have already vanquished the ghost in this room and collected the part." << endl;
                        cout << "Move on to another part of the ship before you die! HURRY!" << endl << endl;
                    }
                 }
                 break;
             case 6:
                 cout << endl << "Meh, surviving is too much of a hassle." << endl;
                 exit(1);
             }
    }

    //Checks loop termination condition to see if player won or lost
    if ( player.getOxygen() > 0 )
    {
        cout << "Congratulations, you successfully launched in the escape pod and survive! " << endl;
    }

    else
    {
        cout << "You ran out of oxygen and died on your spacecraft." << endl;
        cout << "Your soul joins the rest of the crew on THE HAUNTED SPACESHIP..." << endl << endl;
    }

    //deletes objects pointed to by pointers
    delete room1;
    delete room2;
    delete room3;
    delete room4;
    delete room5;
    delete room6;
    delete room7;
    delete room8;
    delete room9;
    delete room10;

    cout << endl << "Would you like to play again?" << endl;
    cout << "Enter 1 if you would like to play again " << endl
         << "or Enter 2 if you would like to exit the program." << endl << endl;

    cout << "Your Selection: ";

    int playAgain = intCheck(1, 2);

    cout << endl << endl;

//checks if users want to play again or exit program
switch(playAgain)
             {
             case 1:
                 continue;
                 break;

             case 2:
                 cout << "Exiting program...thank you for playing!" << endl;
                 exit(1);
                 break;
             }

}while(menuOn);

    return 0;
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
