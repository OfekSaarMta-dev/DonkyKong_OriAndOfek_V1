#pragma once

#include <iostream>

class GameConfig
{
public:
    // Game dimensions
	static constexpr int GAME_WIDTH = 80;// x
    static constexpr int GAME_HEIGHT = 25; // y

    // Movement delay
	static constexpr int MOVE_DELAY = 78; 

    // Utility keys enum
    enum class utilKeys { SPACE = ' ', LADDER = 'H', FLOOR = '=', LFLOOR = '<', RFLOOR = '>', BARREL = 'O', EDGE = 'Q', EXPLOSION = '*', PAULINE = '$', ESC = 27 };

    // Movement keys enum
    enum class movementKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's' };

    // colors keys enum
    enum class colors { RED = 12, LIGHTBLUE = 3, BLUE = 1, GOLD = 14, WHITE = 7 };

    // Direction struct for movement
	struct Direction { int x, y; }; 

    // Starting position for Mario
    static constexpr int START_X_MARIO = 78;
    static constexpr int START_Y_MARIO = 22;
	static constexpr int NUM_OF_CHARS_FOR_MARIO_DIE = 5;

    // Barrels parameters
    static constexpr int MAX_BARRELS = 4;
	static constexpr int NUM_OF_CHARS_FOR_BARREL_EXPLODE = 8;
    static constexpr int START_x_BARREL = 49;
    static constexpr int START_Y_BARREL = 3;
    static constexpr int EXPLOSION_DELAY = 25;
    static constexpr int LOOPS_FOR_BARREL = 23;

    // Life parameters
    static constexpr int LIFE_X = 17;
    static constexpr int LIFE_y = 2;

};