#include "TheShadow.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

//Default Constructor
TheShadow::TheShadow()
{
    srand(time(NULL)); // Seeds random number generator

 //sets member value attributes
    setName("The Shadow");
    setID(5);
    setstrengthPoints(12);
    setArmor(0);
    setAttdNum(2);
    setAttdSides(10);
    setDefdNum(1);
    setDefdSides(6);
}

int TheShadow::DiceRoll(int DiceNum, int NumSides)
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

int TheShadow::getArmor()
{
    //Creates random number and tests whether it is even or odd
    //allows Shadow to avoid damage 50% of the time
    if((rand() % 2 == 0))
    {
        cout << "The Shadow has manipulated your perception and takes 0 damage." << endl;
        return 100; //returns a large armor value which cancels out any possible amount of damage received
    }

    else { return armor; }
}

int TheShadow::Attack(int Eident)
{
     //calls DiceRoll function and passes Attack dice attributes
    DiceRoll(AttdNum, AttdSides);
    cout << getName() << " rolled a " << getDice1() << " and a " << getDice2() << " for an attack total of " << getdiceTotal() << endl;

return 0;
}

int TheShadow::Defense()
{
    //calls DiceRoll function and passes Defense dice attributes
    DiceRoll(DefdNum, DefdSides);
    cout << getName() << " has rolled a " << getDice1() << " for a defense total of " << getdiceTotal() << endl;
    return 0;
}



TheShadow::~TheShadow()
{
    //dtor
}
