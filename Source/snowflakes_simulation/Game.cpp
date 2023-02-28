#include "Game.h"

using namespace Core;

Game::Game() : _keepPlaying(true) {} // CTOR
Game::~Game() {} // DTOR

void Game::loop()
{
    while (_keepPlaying)
    {
        handleInput(); // Events
        update(); // Update
        render(); // Draw
    }
}
