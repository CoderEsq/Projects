#ifndef REPTILEPEOPLE_H
#define REPTILEPEOPLE_H

#include "Creature.h"

#include <iostream>
#include <string>

class ReptilePeople : public Creature
{
    public:
        ReptilePeople();
        virtual ~ReptilePeople();

    protected:

    private:
        virtual int getArmor() { return armor; }
        virtual int DiceRoll(int DiceNum, int NumSides);
        virtual int Attack(int ident);
        virtual int Defense();
};

#endif // REPTILEPEOPLE_H
