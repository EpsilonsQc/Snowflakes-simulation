#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeRebound final : public Snowflake
    {
    public:
		SnowflakeRebound();

        void update() override;
        void collide(Player&) override;

    private:
        bool _alreadyHit;
        void rebound();

        void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
