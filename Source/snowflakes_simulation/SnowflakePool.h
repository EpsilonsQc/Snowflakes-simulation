#pragma once

#include <Code_Utilities_Light_v2.h>
#include <memory> // for unique_ptr

#include "Snowflake.h" // for Snowflake

namespace SF
{
	template<typename T>
    class SnowflakePool
    {
    public:
        SnowflakePool();

		void spawnSnowflake(double positionX, double positionY);
		void destroySnowflake(uint deleteIndex);
		
		T& get(uint index) const;
		uint getSnowflakesQty() const;
	
		void clear(); // clear the pools
		void snowflakesPositionUpdate(); // updates the position of the snowflakes
		void snowflakesCollisionTest(Player& player); // tests the collision between the snowflakes and the player
		void disableSnowflakes(); // destroy snowflakes
		void renderSnowflakes() const; // renders snowflakes
		
	private:
		unique_ptr<T[]> _pool; // pool of snowflakes
		uint _nbSnowflakes; // number of active snowflakes in the pool
	};
}
