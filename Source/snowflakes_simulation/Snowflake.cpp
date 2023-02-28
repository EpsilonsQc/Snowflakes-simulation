#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"

using namespace SF;

Snowflake::Snowflake() :
	GameObject()
{
    // calculateSizeInMemory();
}

void Snowflake::initialize(double positionX, double positionY)
{
    GameObject::initialize(positionX, positionY);

    _width = 3;
    _height = 6;

    _colorR = 0.8;
    _colorG = 0.8;
    _colorB = 1;
    _colorA = 0.3;

    _velocityY = 100 + BdB::randInt(RAND_MAX) / (double)RAND_MAX * 100;
}

void Snowflake::update()
{
    GameObject::update();

    if (_positionY > SCREEN_HEIGHT + _height) 
    {
        _deleteMe = true;
    }
}

void Snowflake::collide(Player&)
{
    _deleteMe = true;
}

void Snowflake::calculateSizeInMemory()
{
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        cout << "Size of Snowflake is " << sizeof(*this) << " bytes." << endl;
    }
}
