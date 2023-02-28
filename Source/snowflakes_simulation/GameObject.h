#pragma once

namespace SF
{
    class Player;

    class GameObject
    {
    public:
		GameObject();
        GameObject(double positionX, double positionY);

        virtual void initialize(double positionX, double positionY); // "new"
        virtual void update();
        virtual void render() const;
		
        void testCollision(Player&);

        bool isActive() const; // "isActive"
        bool shouldDelete() const;

    protected:
        bool isColliding(const Player&) const;
        virtual void collide(Player&) = 0;

        double _positionX;
        double _positionY;
        double _width;
        double _height;
		double _velocityX;
		double _velocityY;
		double _accelerationX;
		double _accelerationY;

		double _colorR, _colorG, _colorB, _colorA; // color
        bool _deleteMe;
        bool _isActive;

    private:
        void calculateSizeInMemory(); // calculates the size of the object in memory
    };
}
