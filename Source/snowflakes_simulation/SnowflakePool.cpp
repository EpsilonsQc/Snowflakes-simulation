#include <Code_Utilities_Light_v2.h>

#include "Globals.h"
#include "SnowflakePool.h"

using namespace SF;

template<typename T>
SnowflakePool<T>::SnowflakePool() :
	_nbSnowflakes{ 0 }
{
	_pool = make_unique<T[]>(MAX_SNOWFLAKES); // allocate the pool
}

template<typename T>
void SnowflakePool<T>::spawnSnowflake(double positionX, double positionY)
{
	if (_nbSnowflakes < MAX_SNOWFLAKES)
	{
		_pool[_nbSnowflakes].initialize(positionX, positionY); // set snowflake to active
		++_nbSnowflakes; // increment the number of snowflakes
	}
}

template<typename T>
void SnowflakePool<T>::destroySnowflake(uint deleteIndex)
{
	uint lastIndex = _nbSnowflakes - 1; // index of the last snowflake

	_pool[deleteIndex] = _pool[lastIndex];
	--_nbSnowflakes; // decrement the number of snowflakes
}

template<typename T>
T& SnowflakePool<T>::get(uint index) const
{
	return _pool[index];
}

template<typename T>
uint SnowflakePool<T>::getSnowflakesQty() const
{
	return _nbSnowflakes;
}

template<typename T>
void SnowflakePool<T>::clear()
{
    _nbSnowflakes = 0;
}

template<typename T>
void SnowflakePool<T>::snowflakesPositionUpdate()
{
    for (uint i{}; i < getSnowflakesQty(); ++i)
    {
        get(i).update();
    }
}

template<typename T>
void SnowflakePool<T>::snowflakesCollisionTest(Player& player)
{
    for (uint i{}; i < getSnowflakesQty(); ++i)
    {
        get(i).testCollision(player);
    }
}

template<typename T>
void SnowflakePool<T>::disableSnowflakes()
{
    for (uint i{}; i < getSnowflakesQty(); ++i)
    {
        if (get(i).isActive() && get(i).shouldDelete())
        {
            destroySnowflake(i); // "delete" : set snowflake to inactive
        }
    }
}

template<typename T>
void SnowflakePool<T>::renderSnowflakes() const
{
    for (uint i{}; i < getSnowflakesQty(); ++i)
    {
        get(i).render(); // Render the snowflakes
    }
}
