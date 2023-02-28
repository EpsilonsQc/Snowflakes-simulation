#include <raylib.h>
#include <iostream>
#include <cassert>
#include <cmath>

#include "Globals.h"
#include "Player.h"

using namespace std;
using namespace SF;

Player::Player(double positionX, double positionY) :
    GameObject{positionX, positionY},
    _inputs{false},
    _isJumping{false}
{
    _width = 70;
    _height = 50;

    _colorR = 0;
    _colorG = 0.63;
    _colorB = 0.8;
    _colorA = 1;

    _accelerationY = +1000;
	
    // calculateSizeInMemory();
}

void Player::update()
{
    float dt = GetFrameTime();

    // Process input
    _accelerationX = _inputs.left * -1000 + _inputs.right * 1000;

    if (!_isJumping && _inputs.jump) 
    {
        _velocityY = -600;
        _isJumping = true;
    }

    if (_inputs.down) 
    {
        if (_height == 50)
        {
            _positionY += 25;
        }
		
        _height = 25;
        _accelerationY = +1500;
    } 
    else 
    {
        if (_height == 25)
        {
            _positionY -= 25;
        }
		
        _height = 50;
        _accelerationY = +1000;
    }

    GameObject::update();

    // Damping
    if (!_inputs.left && !_inputs.right) 
    {
        double sign_vx = copysign(1, _velocityX);

        _velocityX -= dt * sign_vx * 300;

        // Sign change : set to zero
        if (copysign(1, _velocityX) != sign_vx)
        {
            _velocityX = 0;
        }
            
    }

    if (_velocityX > 350)
    {
        _velocityX = 350;
    }
        
    if (_velocityX < -350)
    {
        _velocityX = -350;
    }

    if (_positionX < 0) 
    {
        _positionX = 0;
        _velocityX *= -0.5;
    }

    if (_positionX + _width > SCREEN_WIDTH) 
    {
        _positionX = SCREEN_WIDTH - _width;
        _velocityX *= -0.5;
    }

    if (_positionY + _height > SCREEN_HEIGHT) 
    {
        _positionY = SCREEN_HEIGHT - _height;
        _velocityY = 0;
        _isJumping = false;
    }
}

void Player::setPosition(double positionX, double positionY)
{
    _positionX = positionX;
    _positionY = positionY;
}

void Player::setDirection(double left, double right, double down, double jump)
{
    _inputs.left  = left;
    _inputs.right = right;
    _inputs.down  = down;
    _inputs.jump  = jump;
}

void Player::render() const
{
    GameObject::render();

    Rectangle r;
    r.x         = (float) _positionX;
    r.y         = (float) _positionY;
    r.width     = (float) _width;
    r.height    = (float) _height;

    Color c1
    {
        (uchar)(_colorR * 255),
        (uchar)(_colorG * 255),
        (uchar)(_colorB * 255),
        (uchar)(_colorA * 255)
    };

    // Head
    DrawRectangleRec(r, c1);

    Color c2{0, 0, 0, 255};

    int offset = 0;

    if (_velocityX > 0)
    {
        offset = 3;
    }
    else if (_velocityX < 0)
    {
        offset = -3;
    }

    // Eyes
    r.width  = 6;
    r.height = 6;

    // Left eye
    r.x = (float) (_positionX + _width/4.0 - 3) + offset;
    r.y = (float) (_positionY + _height/3.0 - 3);
    DrawRectangleRec(r, c2);

    // Right eye
    r.x = (float) (_positionX + 3*_width/4.0 - 3) + offset;
    DrawRectangleRec(r, c2);

    // Mouth
    int mouthY = (int)(_positionY + 3*_height/4.0);
    DrawLine((int)(_positionX + _width/4.0), mouthY, (int)(_positionX + 3*_width/4.0), mouthY, c2);
}

void Player::collide(Player&)
{
    assert(0);
}

void Player::calculateSizeInMemory()
{
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        cout << "Size of Player is " << sizeof(*this) << " bytes." << endl;
    }
}

