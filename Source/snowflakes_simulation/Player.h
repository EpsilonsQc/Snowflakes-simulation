#pragma once

#include "GameObject.h"

namespace SF
{
    class Player : public GameObject
    {
    public:
        Player(double positionX, double positionY);

        void update() override;
        void render() const override;

        void collide(Player& player) override;

        void setPosition(double positionX, double positionY);
        void setDirection(double left, double right, double down, double jump);

    private:
        struct Inputs
        {
            bool left;
            bool right;
            bool down;
            bool jump;
        } _inputs;

        bool _isJumping;

		void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
