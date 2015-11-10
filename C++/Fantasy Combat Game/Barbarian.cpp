#include "Barbarian.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

//Default Constructor
Barbarian::Barbarian()
{
    srand(time(NULL)); // Seeds random number generator

 //sets member value attributes
    setName("Barbarian");
    setID(2);
    setstrengthPoints(12);
    setArmor(0);
    setAttdNum(2);
    setAttdSides(6);
    setDefdNum(2);
    setDefdSides(6);


}

int Barbarian::DiceRoll(int DiceNum, int NumSides)
{
    if(DiceNum == 1)
        {
            setDice1((rand() % NumSides) + 1);
            setdiceTotal( getDice1() );
        }

    else if(DiceNum == 2)
    {
        setDice1((rand() % NumSides) + 1);
        setDice2((rand() % NumSides) + 1);
        setdiceTotal( getDice1() + getDice2() );
    }

    return 0;
}

int Barbarian::Attack(int Eident)
{
     //calls DiceRoll function and passes Attack dice attributes
    DiceRoll(AttdNum, AttdSides);
    cout << getName() << " rolled a " << getDice1() << " and a " << getDice2() << " for an attack total of " << getdiceTotal() << endl;

return 0;
}

int Barbarian::Defense()
{
    //calls DiceRoll function and passes Defense dice attributes
    DiceRoll(DefdNum, DefdSides);
    cout << getName() << " has " << getArmor() << " armor and rolled a " << getDice1() << " and a " << getDice2() << " for a defense total of " << getdiceTotal() + getArmor() << endl;
    return 0;
}

Barbarian::~Barbarian()
{
    //dtor
}
