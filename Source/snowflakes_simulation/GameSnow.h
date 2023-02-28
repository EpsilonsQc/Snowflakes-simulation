#pragma once

#include <vector>
#include <array>

#include "Globals.h"
#include "Game.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
#include "SnowflakePool.h"

using namespace std;
using namespace Core;

namespace SF
{
	class GameSnow final: public Game
	{
        using PresetList = array<ulong, 9>;

	public:
	    GameSnow();
		~GameSnow();

	    void handleInput() override;
        void update() override;
        void render() const override;

	    void init(uint);
	    void addSnowflake();
	    void addSnowflake(double, double);

	private:
		int getClickX(); // returns the x position of the mouse click in the window
		int getClickY(); // returns the y position of the mouse click in the window

		int activeSnowflakesQty() const; // returns the number of active snowflakes
		
		// Amount of snowflakes preset
	    inline static PresetList _presets = {50000, 100000, 150000, 200000, 250000, 275000, 300000, 325000, 350000};

		// Game is "paused" or not
		bool _isPaused;
		
		// Player
		Player _player;
		
		// Pools of snowflakes
		SnowflakePool<Snowflake> _snowflakesPool; // pool of snowflake
		SnowflakePool<SnowflakeRebound> _snowflakesReboundPool; // pool of snowflakeRebound
		SnowflakePool<SnowflakeNoContact> _snowflakesNoContactPool; // pool of snowflakeNoContact
		SnowflakePool<SnowflakeSine> _snowflakesSinePool; // pool of snowflakSine
	};
}
