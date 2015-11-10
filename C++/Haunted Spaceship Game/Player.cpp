#include "Player.h"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

//Constructor
Player::Player()
{
    //sets initial conditions for player
    setInventory(0);
    setOxygen(100);
    setBackpack(0);
}

//This function is called when player enteres Escape Pod.
// It empties their backpack and "assembles" the pod
void Player::assemble()
{
    inventory = inventory + backpack;
    setBackpack(0);
}

//Destructor
Player::~Player()
{
    //cout << "object destroyed" << endl;
}

