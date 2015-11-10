#ifndef ROCK_H
#define ROCK_H

#include "Room.h"

//derived class from abstract Room class
class Rock : public Room
{
    public:
        Rock(string RmName);
        virtual ~Rock();

        void game();
    protected:

    private:

};

#endif // ROCK_H

