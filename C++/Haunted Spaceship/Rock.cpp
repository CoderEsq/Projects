#include "Rock.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

//Constructor
Rock::Rock(string RmName)
{
    setName(RmName);
    winLoss = 0;
}

//Game function for ghost in this particular type of room
void Rock::game()
{
    cout << "A ghost challenges you to a game of rock, paper, scissors!" << endl << endl;

    cout << "Enter an integer to choose which gesture you would like to throw." << endl
            << "   1:     Rock" << endl
            << "   2:     Paper" << endl
            << "   3:     Scissors" << endl << endl;

            cout << "Your Selection: ";

            int handSelect = intCheck(1, 3);
            int ghostSelect = (rand() % 3) + 1;

            if( (handSelect == 1 && ghostSelect == 3) || (handSelect == 2 && ghostSelect == 1) || (handSelect == 3 && ghostSelect == 2) )
            {
                 winLoss = 1;
            }

            if (handSelect == 1 && ghostSelect == 1) {cout << "You and the ghost both chose ROCK. It's a tie. Would you like to try again?" << endl << endl;}
            if (handSelect == 2 && ghostSelect == 2) {cout << "You and the ghost both chose PAPER. It's a tie. Would you like to try again?" << endl << endl;}
            if (handSelect == 3 && ghostSelect == 3) {cout << "You and the ghost both chose SCISSORS. It's a tie. Would you like to try again?" << endl << endl;}

            if (handSelect == 1 && ghostSelect == 2) {cout << "PAPER beats ROCK. You lose. Would you like to try again?" << endl << endl;}
            if (handSelect == 1 && ghostSelect == 3) {cout << "ROCK beats SCISSORS. You win! Take this part as a reward. Good Luck." << endl << endl;}

            if (handSelect == 2 && ghostSelect == 1) {cout << "PAPER beats ROCK. You win! Take this part as a reward. Good Luck." << endl << endl;}
            if (handSelect == 2 && ghostSelect == 3) {cout << "SCISSORS beats PAPER. You lose! Would you like to try again?" << endl << endl;}

            if (handSelect == 3 && ghostSelect == 1) {cout << "ROCK beats SCISSORS. You lose. Would you like to try again?" << endl << endl;}
            if (handSelect == 3 && ghostSelect == 2) {cout << "SCISSORS beats PAPER. You win! Take this part as a reward. Good Luck." << endl << endl;}
}

//Destructor
Rock::~Rock()
{
    //cout << "object destroyed" << endl;
}
