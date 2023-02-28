#include <Code_Utilities_Light_v2.h>
#include <raylib.h>

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"

using namespace SF;

GameObject::GameObject() :
    _positionX{}, _positionY{},
    _width{}, _height{},
    _velocityX{ 0 }, _velocityY{ 0 }, _accelerationX{ 0 }, _accelerationY{ 0 },
    _colorR{}, _colorG{}, _colorB{}, _colorA{},
    _deleteMe{false},
    _isActive{false}
{
    // calculateSizeInMemory();
}

GameObject::GameObject(double x, double y) :
    _positionX{x}, _positionY{y},
    _width{}, _height{},
    _velocityX{0}, _velocityY{0}, _accelerationX{0}, _accelerationY{0},
    _colorR{}, _colorG{}, _colorB{}, _colorA{},
    _deleteMe{false},
	_isActive{false}
{
    // calculateSizeInMemory();
}

void GameObject::initialize(double x, double y)
{
    _positionX = x;
    _positionY = y;
    _isActive = true; // "new"
    _deleteMe = false;
}

void GameObject::update()
{
	float dt = GetFrameTime();
    _velocityX += dt * _accelerationX;
    _velocityY += dt * _accelerationY;

    _positionX += dt * _velocityX;
    _positionY += dt * _velocityY;
}

void GameObject::render() const
{
    Color c
    { 
       (uchar) (_colorR * 255),
       (uchar) (_colorG * 255),
       (uchar) (_colorB * 255),
       (uchar) (_colorA * 255)
    };

    Rectangle r{};
    r.x         = (float) _positionX;
    r.y         = (float) _positionY;
    r.width     = (float) _width;
    r.height    = (float) _height;

    DrawRectangleRec(r, c);
}

void GameObject::testCollision(Player& player)
{
    if (isColliding(player))
    {
		collide(player);
    }
}

bool GameObject::isColliding(const Player& player) const
{
	return !(
        player._positionX + player._width < _positionX ||  // Right-Left
		player._positionX > _positionX + _width ||         // Left-Right
		player._positionY + player._height < _positionY || // Top-Bottom
		player._positionY > _positionY + _height);         // Bottom-Top
}

bool GameObject::isActive() const
{
    return _isActive;
}

bool GameObject::shouldDelete() const
{
    return _deleteMe;
}

void GameObject::calculateSizeInMemory()
{
	static bool firstTime = true;
	if (firstTime)
	{
		firstTime = false;
        cout << "Size of GameObject is " << sizeof(*this) << " bytes." << endl;
	}
}
