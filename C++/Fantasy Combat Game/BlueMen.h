#ifndef BLUEMEN_H
#define BLUEMEN_H

#include "Creature.h"

#include <iostream>
#include <string>

class BlueMen : public Creature
{
    public:
        BlueMen();
        virtual ~BlueMen();

    protected:

    private:
        virtual int getArmor() { return armor; }
        virtual int DiceRoll(int DiceNum, int NumSides);
        virtual int Attack(int ident);
        virtual int Defense();
};

#endif // BLUEMEN_H
