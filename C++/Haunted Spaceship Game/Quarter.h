#ifndef QUARTER_H
#define QUARTER_H

#include "Room.h"

//derived class from abstract Room class
class Quarter : public Room
{
    public:
        Quarter(string RmName);
        virtual ~Quarter();

        void game();

    protected:

    private:

};

#endif // QUARTER_H
