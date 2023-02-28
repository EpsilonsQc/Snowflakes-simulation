#pragma once

#include "Snowflake.h"

namespace SF
{
    class SnowflakeNoContact final : public Snowflake
    {
    public:
        SnowflakeNoContact();

        void collide(Player& player) override;

    private:
        void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
