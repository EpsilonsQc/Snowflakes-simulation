#pragma once

#include "GameObject.h"

namespace SF
{
    class Snowflake : public GameObject
    {
    public:
        Snowflake();

        void initialize(double positionX, double positionY);

        virtual void update() override;
        virtual void collide(Player&) override;

    private:
		void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
