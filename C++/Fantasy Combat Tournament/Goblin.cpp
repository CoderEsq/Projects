#include "Goblin.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

//Default Constructor
Goblin::Goblin(int teamNum)
{
    srand(time(NULL)); // Seeds random number generator
 //sets member value attributes
    setRace("Goblin");
    setteamID(teamNum);
    setName();
    setID(1);
    setTotaldmg(0);
    setKills(0);
    setstrengthPoints(8);
    setArmor(3);
    setAttdNum(2);
    setAttdSides(6);
    setDefdNum(1);
    setDefdSides(6);
}

int Goblin::DiceRoll(int DiceNum, int NumSides)
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

int Goblin::Attack(int Eident)
{
     //calls DiceRoll function and passes Attack dice attributes
    DiceRoll(AttdNum, AttdSides);
    cout << getRace() << " rolled a " << getDice1() << " and a " << getDice2() << " for an attack total of " << getdiceTotal() << endl;

return 0;
}

void Goblin::dmgGiven(double amount)
{
    totaldmg = totaldmg + amount;
}

int Goblin::Defense()
{
    //calls DiceRoll function and passes Defense dice attributes
    DiceRoll(DefdNum, DefdSides);
    cout << getRace() << " has " << getArmor() << " armor and rolled a " << getDice1() << " for a defense total of " << getdiceTotal() + getArmor() << endl;
    return 0;
}



Goblin::~Goblin()
{
    //dtor
}