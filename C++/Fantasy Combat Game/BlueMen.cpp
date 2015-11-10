#include "BlueMen.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

//Default Constructor
BlueMen::BlueMen()
{
    srand(time(NULL)); // Seeds random number generator

     //sets member value attributes
    setName("Blue Men");
    setID(4);
    setstrengthPoints(12);
    setArmor(3);
    setAttdNum(2);
    setAttdSides(10);
    setDefdNum(3);
    setDefdSides(6);
}

int BlueMen::DiceRoll(int DiceNum, int NumSides)
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

    else if(DiceNum == 3)
    {
        setDice1((rand() % NumSides) + 1);
        setDice2((rand() % NumSides) + 1);
        setDice3((rand() % NumSides) + 1);
        setdiceTotal( getDice1() + getDice2() + getDice3() );
    }
    return 0;
}

int BlueMen::Attack(int Eident)
{
     //calls DiceRoll function and passes Attack dice attributes
    DiceRoll(AttdNum, AttdSides);
    cout << getName() << " rolled a " << getDice1() << " and a " << getDice2() <<" for an attack total of " << getdiceTotal() << endl;

return 0;
}

int BlueMen::Defense()
{
    //calls DiceRoll function and passes Defense dice attributes
    DiceRoll(DefdNum, DefdSides);
    cout << getName() << " has " << getArmor() << " armor and rolled a " << getDice1() << " and a " << getDice2() << " and a " << getDice3() << " for a defense total of " << getdiceTotal() + getArmor() << endl;
    return 0;
}

BlueMen::~BlueMen()
{
    //dtor
}
