#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeSine : public Snowflake
    {
    public:
        SnowflakeSine();

        void update() override;
    private:
        double _timeSinceStart;

        void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
