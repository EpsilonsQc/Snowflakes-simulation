#include <Code_Utilities_Light_v2.h>
#include <iostream>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"

using namespace SF;

SnowflakeRebound::SnowflakeRebound() :
    Snowflake{},
    _alreadyHit{ false }
{
    _height = 2;
    _width = 2;
    _colorA = 1;
    _velocityX = BdB::randInt(RAND_MAX) < RAND_MAX / 2 ? -30 : 30;

    // calculateSizeInMemory();
}

void SnowflakeRebound::update()
{
    Snowflake::update();

    if (_positionX < _width || _positionX > SCREEN_WIDTH + _width) 
    {
        _deleteMe = true;
        return;
    }

    if (_positionY + _height > SCREEN_HEIGHT && !_alreadyHit)
    {
        rebound();
    }
    else if (_positionY > SCREEN_HEIGHT + _height && _alreadyHit)
    {
        _deleteMe = true;
    }
}

void SnowflakeRebound::collide(Player&)
{
    if (!_alreadyHit)
    {
        rebound();
    }
    else
    {
        _deleteMe = true;
    }
}

void SnowflakeRebound::rebound()
{
    _velocityY *= -1;
    _accelerationY = 300;
    _alreadyHit = true;
}

void SnowflakeRebound::calculateSizeInMemory()
{
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        cout << "Size of SnowflakeRebound is " << sizeof(*this) << " bytes." << endl;
    }
}
