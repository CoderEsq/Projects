#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>

using std::string;

class Creature
{
    public:
        Creature();
        virtual ~Creature();

        string getName() { return name; }
        double getstrengthPoints() { return strengthPoints; }
        int getdiceTotal() { return diceTotal; }
        int getID() { return ID; }
        virtual int getArmor() = 0;

        virtual int DiceRoll(int DiceNum, int NumSides) = 0;
        virtual int Attack(int Eident) = 0;
        virtual int Defense() = 0;

    protected:
        int getDice1() { return dice1; }
        int getDice2() { return dice2; }
        int getDice3() { return dice3; }
        int getAttdNum() { return AttdNum; }
        int getAttdSides() { return AttdSides; }
        int getDefdNum() { return DefdNum; }
        int getDefdSides() { return DefdSides; }

        int ID;
        int AttdNum;
        int AttdSides;
        int DefdNum;
        int DefdSides;
        int dice1;
        int dice2;
        int dice3;
        int diceTotal;
        int armor;
        double strengthPoints;
        string name;

        void setName(string theName) { name = theName; }
        void setArmor(int theArmor) { armor = theArmor; }
        void setstrengthPoints(double theSP) { strengthPoints = theSP; }
        void setDice1(int d1) { dice1 = d1; }
        void setDice2(int d2) { dice2 = d2; }
        void setDice3(int d3) { dice3 = d3; }
        void setdiceTotal(int dT) { diceTotal = dT; }
        void setAttdNum(int ANum) { AttdNum = ANum; }
        void setAttdSides(int ASides) { AttdSides = ASides; }
        void setDefdNum(int DNum) { DefdNum = DNum; }
        void setDefdSides(int DSides) { DefdSides = DSides; }
        void setID(int identNum) { ID = identNum; }

    private:


};

#endif // CREATURE_H
