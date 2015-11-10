#include "Creature.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

Creature::Creature()
{
    //ctor
}


void Creature::setName()
{
    cout << endl << "What would you like to name your "<< getRace() << "?" << endl;
    cout << "NAME: ";
    cin >> name;
    cout << endl << endl;
    cout << "--------------------------------------------------------------------";
    cout << "------------" << endl;
}


Creature::~Creature()
{
    cout << "object destroyed" << endl; //dtor
}
