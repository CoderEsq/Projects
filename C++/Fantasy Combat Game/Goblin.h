#ifndef GOBLIN_H
#define GOBLIN_H

#include "Creature.h"

#include <iostream>
#include <string>

class Goblin : public Creature
{
    public:
        Goblin();
        virtual ~Goblin();

    protected:
    private:
        virtual int getArmor() { return armor; }
        virtual int DiceRoll(int DiceNum, int NumSides);
        virtual int Attack(int ident);
        virtual int Defense();
};

#endif // GOBLIN_H
