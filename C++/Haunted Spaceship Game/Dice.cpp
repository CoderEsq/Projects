#include "Dice.h"

#include <iostream>
#include <cstdlib>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::streamsize;

//Constructor
Dice::Dice(string RmName)
{
    setName(RmName);
    winLoss = 0;
}

//Game function for ghost in this particular type of room
void Dice::game()
{
    cout << "A ghost challenges you to a game of Dice!" << endl << endl;

    int playerDice = (rand() % 6) + 1;
    int ghostDice =  (rand() % 6) + 1;

    cout << "Press ENTER to roll your dice against your opponent." << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');


    cout << "You have rolled a " << playerDice << " and your opponent has rolled a " << ghostDice << endl;

    if (playerDice == ghostDice) {cout << "You and the ghost both rolled a " << playerDice << ". It's a tie. Would you like to try again?" << endl << endl;}
    if (playerDice < ghostDice) {cout << "You lose. Would you like to try again?" << endl << endl;}
    if (playerDice > ghostDice) {cout << "You win! Take this part as a reward. Good Luck." << endl << endl; winLoss = 1;}
}

//Destructor
Dice::~Dice()
{
    //cout << "object destroyed" << endl;
}
