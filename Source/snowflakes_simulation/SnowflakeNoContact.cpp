#include <iostream>

#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeNoContact.h"

using namespace std;
using namespace SF;

SnowflakeNoContact::SnowflakeNoContact() :
    Snowflake{}
{
    _colorA = 0.2;

	// calculateSizeInMemory();
}

void SnowflakeNoContact::collide(Player&) 
{
	// do nothing
}

void SnowflakeNoContact::calculateSizeInMemory()
{
	static bool firstTime = true;
	if (firstTime)
	{
		firstTime = false;
		cout << "Size of SnowflakeNoContact is " << sizeof(*this) << " bytes." << endl;
	}
}
