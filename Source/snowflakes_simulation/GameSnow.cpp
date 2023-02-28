#include <Code_Utilities_Light_v2.h>
#include <raylib.h>
#include <iostream>

#include "Globals.h"
#include "GameSnow.h"
#include "Player.h"
#include "SnowflakePool.h"
#include "SnowflakePool.cpp" // required for template implementation

using namespace SF;

GameSnow::GameSnow() :
	_isPaused(false), // game is not paused
	_player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) // initialize the player at the center of the screen
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE); // initialize the game window with raylib
    SetTargetFPS(FPS); // Set our game to run at a target frames-per-second (defined in Globals.h)
	init(_presets[0]); // initialize the game with the first preset
	BdB::srandInt((uint)time(0)); // initialize the random number generator
}

GameSnow::~GameSnow()
{
	CloseWindow(); // End the game window
}

void GameSnow::init(uint nbSnowflakes)
{
    cout << "Init with " << nbSnowflakes << " snowflakes." << endl;
	
    // Clear the screen
    _snowflakesPool.clear();
	_snowflakesNoContactPool.clear();
	_snowflakesReboundPool.clear();
	_snowflakesSinePool.clear();
	
	// Spawn snowflakes
    for (uint i{}; i < nbSnowflakes; ++i)
    {
		double x = BdB::randInt(SCREEN_WIDTH); // random x position
		double y = BdB::randInt(10, SCREEN_HEIGHT); // random y position

		addSnowflake(x, y); // add a snowflake at the random position
    }
}

void GameSnow::addSnowflake()
{
	addSnowflake(BdB::randInt(SCREEN_WIDTH), -10); // spawn snowflake at the top of the screen
}

void GameSnow::addSnowflake(double positionX, double positionY)
{
    int random = BdB::randInt(RAND_MAX); // random number between 0 and RAND_MAX

    if (random < RAND_MAX / 10) // 10% chance
    {
		_snowflakesPool.spawnSnowflake(positionX, positionY); 
    }
    else if (random < RAND_MAX / 5 * 2) // 20% chance
    {
		_snowflakesReboundPool.spawnSnowflake(positionX, positionY);
    }
    else if (random < RAND_MAX / 2) // 30% chance
    {
		_snowflakesNoContactPool.spawnSnowflake(positionX, positionY);
    }
    else // 40% chance
    {
		_snowflakesSinePool.spawnSnowflake(positionX, positionY);
    }
}

int GameSnow::activeSnowflakesQty() const
{
	return
		_snowflakesPool.getSnowflakesQty() + 
        _snowflakesNoContactPool.getSnowflakesQty() + 
        _snowflakesReboundPool.getSnowflakesQty() + 
        _snowflakesSinePool.getSnowflakesQty();
}

int GameSnow::getClickX()
{
    return clamp(GetMouseX(), 0, SCREEN_WIDTH);
}

int GameSnow::getClickY()
{
    return clamp(GetMouseY(), 0, SCREEN_HEIGHT);
}

void GameSnow::handleInput()
{
	// Left mouse button input, set player position
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        _player.setPosition(GetMouseX(), GetMouseY());
    }

	// Directional keys
    _player.setDirection
    (
        IsKeyDown(KeyboardKey::KEY_LEFT),
        IsKeyDown(KeyboardKey::KEY_RIGHT),
        IsKeyDown(KeyboardKey::KEY_DOWN),
        (IsKeyDown(KeyboardKey::KEY_UP) || IsKeyDown(KeyboardKey::KEY_SPACE))
    );

    // Key pressed
    int key = GetKeyPressed();
	
    switch (key)
    {
        // Pause
        case KeyboardKey::KEY_P:            
            _isPaused = !_isPaused;
            break;

		// Quit
        case KeyboardKey::KEY_ESCAPE:
            _keepPlaying = false;
            break;

        // Number of particles (preset)
        case KeyboardKey::KEY_KP_1:
        case KeyboardKey::KEY_KP_2:
        case KeyboardKey::KEY_KP_3:
        case KeyboardKey::KEY_KP_4:
        case KeyboardKey::KEY_KP_5:
        case KeyboardKey::KEY_KP_6:
        case KeyboardKey::KEY_KP_7:
        case KeyboardKey::KEY_KP_8:
        case KeyboardKey::KEY_KP_9:
            init(_presets[key - KeyboardKey::KEY_KP_1]);
            break;
    }
}

void GameSnow::update()
{
	// If game is paused, don't update (early out)
    if (_isPaused)
    {
        return;
    }

    // Update player position
	_player.update(); 
	
    // Update snowflakes position
    _snowflakesPool.snowflakesPositionUpdate();
	_snowflakesNoContactPool.snowflakesPositionUpdate();
	_snowflakesReboundPool.snowflakesPositionUpdate();
	_snowflakesSinePool.snowflakesPositionUpdate();
	
    // Test collision between snowflakes and player
    _snowflakesPool.snowflakesCollisionTest(_player);
	_snowflakesNoContactPool.snowflakesCollisionTest(_player);
	_snowflakesReboundPool.snowflakesCollisionTest(_player);
	_snowflakesSinePool.snowflakesCollisionTest(_player);
	
    // Get the number of active snowflakes
	uint size_before = activeSnowflakesQty();
	
    // Disable snowflakes that are out of the screen or that have collided with the player
    _snowflakesPool.disableSnowflakes();
	_snowflakesNoContactPool.disableSnowflakes();
	_snowflakesReboundPool.disableSnowflakes();
	_snowflakesSinePool.disableSnowflakes();
	
	// Get the number of snowflakes to add
    uint nb_new_snowflakes = size_before - activeSnowflakesQty();
	
    // For each missing snowflake, add a new one
	for (uint i{}; i < nb_new_snowflakes; ++i)
    {
        addSnowflake();
    }
}

void GameSnow::render() const
{
    BeginDrawing();
    {
        // Clear the screen to blank
		ClearBackground(BLANK); 

        // Render the player
		_player.render(); 
		
        // Render the snowflakes
        _snowflakesPool.renderSnowflakes(); 
		_snowflakesNoContactPool.renderSnowflakes();
		_snowflakesReboundPool.renderSnowflakes();
		_snowflakesSinePool.renderSnowflakes();		
		
        // Draw current FPS at the top left corner
        DrawFPS(20, 20);
	}
	EndDrawing();
}
