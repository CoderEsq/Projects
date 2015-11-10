#include "ReptilePeople.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

//Default Constructor
ReptilePeople::ReptilePeople(int teamNum)
{
    srand(time(NULL)); // Seeds random number generator

    //sets member value attributes
    setRace("Reptile People");
    setteamID(teamNum);
    setName();
    setID(3);
    setstrengthPoints(18);
    setArmor(7);
    setTotaldmg(0);
    setKills(0);
    setAttdNum(3);
    setAttdSides(6);
    setDefdNum(1);
    setDefdSides(6);
}

int ReptilePeople::DiceRoll(int DiceNum, int NumSides)
{
    if(DiceNum == 1)
        {
            setDice1((rand() % NumSides) + 1); //sets Dice1 member variable
            setdiceTotal( getDice1() ); //sets DiceTotal member variable
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

int ReptilePeople::Attack(int Eident)
{
    //calls DiceRoll function and passes Attack dice attributes
    DiceRoll(AttdNum, AttdSides);
    cout << getRace() << " rolled a " << getDice1() << " and a " << getDice2() << " and a " << getDice3() <<" for an attack total of " << getdiceTotal() << endl;

return 0;
}

void ReptilePeople::dmgGiven(double amount)
{
    totaldmg = totaldmg + amount;
}

int ReptilePeople::Defense()
{
    //calls DiceRoll function and passes Defense dice attributes
    DiceRoll(DefdNum, DefdSides);
    cout << getRace() << " has " << getArmor() << " armor and rolled a " << getDice1() << " for a defense total of " << getdiceTotal() + getArmor() << endl;
    return 0;
}

//Destructor
ReptilePeople::~ReptilePeople()
{
}
