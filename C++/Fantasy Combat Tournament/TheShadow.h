#ifndef THESHADOW_H
#define THESHADOW_H

#include "Creature.h"

#include <iostream>
#include <string>

class TheShadow : public Creature
{
    public:
        TheShadow(int teamNum);
        virtual ~TheShadow();

    protected:

    private:
        virtual int getArmor();
        virtual int DiceRoll(int DiceNum, int NumSides);
        virtual int Attack(int ident);
        virtual void dmgGiven(double amount);
        virtual int Defense();
};

#endif // THESHADOW_H
