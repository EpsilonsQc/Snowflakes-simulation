#pragma once

namespace SF
{
    using uchar = unsigned char;
    using uint = unsigned int;
    using ulong = unsigned long;

    static const char* WINDOW_TITLE = "Snowflakes simulator";
	
    const int SCREEN_WIDTH  = 720;
    const int SCREEN_HEIGHT = 480;

	const uint FPS = 30; // target FPS
	const uint MAX_SNOWFLAKES = 350000; // max number of snowflakes in the pool
}
