#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "Creature.h"

#include <iostream>
#include <string>

class Barbarian : public Creature
{
    public:
        Barbarian(int teamNum);
        virtual ~Barbarian();

    protected:

    private:
        virtual int getArmor() { return armor; }
        virtual int DiceRoll(int DiceNum, int NumSides);
        virtual int Attack(int ident);
        virtual void dmgGiven(double amount);
        virtual int Defense();
};

#endif // BARBARIAN_H
