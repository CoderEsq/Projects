#ifndef ROOM_H
#define ROOM_H

#include <iostream>

using std::string;

class Room
{
    public:
        Room();
        virtual ~Room();

        virtual void game() = 0;

        string getName() { return name; }
        int getwinLoss() { return winLoss; }

        Room* fore;
        Room* aft;
        Room* starboard;
        Room* port;

    protected:
        string name;
        int winLoss;
        void setName(string theName) { name = theName; }
        int intCheck(int minRange, int maxRange);

    private:

};

#endif // ROOM_H

