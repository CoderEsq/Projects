#include <iostream>
#include <string>
#include "item.h"

using std::cout;
using std::endl;

//Default Constructor definition
Item::Item() {
    unitName = " ";
    unitType = " ";
    unitNum = 0.00;
    unitPrice = 0.00;
    subTotal = 0.00;
}

//Overload Constructor definition
Item::Item(string uName, string uType, double uNum, double uPrice) {
    unitName = uName;
    unitType = uType;
    unitNum = uNum;
    unitPrice = uPrice;
    subTotal = ((double)uNum) * ((double)uPrice);
}

//Accessor Function Definitions
string Item::getName() {
    return unitName;
}

string Item::getType() {
    return unitType;
}

double Item::getNum() {
    return unitNum;
}

double Item::getPrice() {
    return unitPrice;
}

double Item::getsubTotal() {
    return (((double)unitNum) * ((double)unitPrice));
}

//Mutator Function Definitions
void Item::setName(string uName){
    unitName = uName;
}

void Item::setType(string uType){
    unitType = uType;
}

void Item::setNum(double uNum){
    unitNum = uNum;
}

void Item::setPrice(double uPrice){
    unitPrice = uPrice;
}

//Destructor Definition
Item::~Item() { }





