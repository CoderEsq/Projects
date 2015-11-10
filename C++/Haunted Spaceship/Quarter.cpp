#include "Quarter.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

//Constructor
Quarter::Quarter(string RmName)
{
    setName(RmName);
    winLoss = 0;
}

//Game function for ghost in this particular type of room
void Quarter::game()
{
    cout << "A ghost challenges you to a game of heads or tails!" << endl << endl;
    cout << "Enter an integer to choose heads or tails." << endl
            << "   1:     Heads" << endl
            << "   2:     Tails" << endl << endl;

            cout << "Your Selection: ";

            int coinSelect = intCheck(1, 2);

            if ((rand() % 2) == (coinSelect - 1) )
            {
                winLoss = 1;
                if(coinSelect == 1)
                {
                    cout << "The coin has landed HEADS up!" << endl;
                    cout << "You Win! Take this part as a reward. Good Luck." << endl << endl;
                }

                if(coinSelect == 2)
                {
                    cout << "The coin has landed TAILS up!" << endl;
                    cout << "You Win! Take this part as a reward. Good Luck." << endl << endl;
                }
            }

            else
            {
                if(coinSelect == 2)
                {
                    cout << "The coin has landed HEADS up!" << endl;
                    cout << "You Lose. Would you like to try again?" << endl << endl;
                }

                if(coinSelect == 1)
                {
                    cout << "The coin has landed TAILS up!" << endl;
                    cout << "You Lose. Would you like to try again?" << endl << endl;
                }
            }
}

//Destructor
Quarter::~Quarter()
{
    //cout << "object destroyed" << endl;
}
