#include <Code_Utilities_Light_v2.h>
#include <raylib.h>
#include <cmath>

#include "Snowflake.h"
#include "SnowflakeSine.h"

using namespace SF;

SnowflakeSine::SnowflakeSine() :
    Snowflake{}
{
    _timeSinceStart = BdB::randInt(RAND_MAX) / (double)RAND_MAX * 2 * PI;

	// calculateSizeInMemory();
}

void SnowflakeSine::update() 
{
    float deltaTime = GetFrameTime();
    _timeSinceStart += deltaTime;

    _velocityX = 50 * sin(3 * _timeSinceStart);

    Snowflake::update();
}

void SnowflakeSine::calculateSizeInMemory()
{
	static bool firstTime = true;
	if (firstTime)
	{
		firstTime = false;
		cout << "Size of SnowflakeSine is " << sizeof(*this) << " bytes." << endl;
	}
}
