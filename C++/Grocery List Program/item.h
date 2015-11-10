#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using std::string;

class Item {
public:
    //Default Constructor
    Item();

    //Overload Constructor
    Item(string, string, double, double);

    //Accessor Functions
    string getName();
    string getType();
    double getNum();
    double getPrice();
    double getsubTotal();

    //Mutator Functions
    void setName(string);
    void setType(string);
    void setNum(double);
    void setPrice(double);

    //Destructor
    ~Item();

private:
    //Member Variables
    string unitName;
    string unitType;
    double unitNum;
    double unitPrice;
    double subTotal;
};


#endif // ITEM_H
