#ifndef DICE_H
#define DICE_H

#include "Room.h"

//derived class from abstract Room class
class Dice : public Room
{
    public:
        Dice(string RmName);
        virtual ~Dice();

        void game();

    protected:

    private:

};

#endif // DICE_H

