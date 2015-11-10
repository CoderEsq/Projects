#include "Room.h"

#include <algorithm>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::numeric_limits;
using std::max;

//Constructor
Room::Room()
{

}

//checks if input is valid integer
int Room::intCheck(int minRange, int maxRange)
{
	int input;

	while ( ( !(cin >> input) ) || (input < minRange) || (input > maxRange) || cin.peek() != '\n')
	{
		cout << "Please enter an integer between " << minRange << " and " << maxRange << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return input;
}


//Destructor
Room::~Room()
{
    //cout << "object destroyed" << endl;
}
