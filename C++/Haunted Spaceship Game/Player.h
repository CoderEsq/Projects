#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();
        virtual ~Player();

        int getInventory() { return inventory; }
        void assemble();

        int getBackpack() { return backpack; }
        void collectItem() { backpack++; }  //increments number of parts in backpack

        int getOxygen() { return oxygen; }
        void Breath(int O2loss) { oxygen = oxygen - O2loss; }   //depletes oxygen by set value

    protected:
        void setOxygen(int O2) { oxygen = O2; }
        int oxygen;

        void setInventory(int itemNum) { inventory = itemNum; }
        int inventory;

        int backpack;
        void setBackpack(int bpNum) { backpack = bpNum;}

    private:

};

#endif // PLAYER_H

