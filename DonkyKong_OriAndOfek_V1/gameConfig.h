#pragma once

#include <iostream>

class GameConfig
{
public:
    // Game dimensions
    static constexpr int GAME_WIDTH = 80;  // x
    static constexpr int GAME_HEIGHT = 25; // y


    // Jump parameters
    static constexpr int JUMP_HEIGHT = 2;
    static constexpr int JUMP_DURATION = 50;

    // Movement delay
    static constexpr int MOVE_DELAY = 100;

    // Utility keys enum
    enum class utilKeys { SPACE = ' ', LADDER = 'H', FLOOR = '=', LFLOOR = '<', RFLOOR = '>',END_OF_ROAD = '#', EDGE = 'Q', ESC = 27 };

    // Movement keys enum
    enum class movementKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's' };

    // Direction struct for movement
    struct Direction { int x, y; };

    // Game state flags
    bool isRunning = true;
    bool isPaused = false;

    // Array of directions corresponding to movement keys
    static constexpr Direction directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0} };

    // Starting position for Mario
    static constexpr int START_X_MARIO = 78;
    static constexpr int START_Y_MARIO = 22;
	static constexpr int NUM_OF_CHARS_FOR_MArio_DIE = 5;

    // barrels parameters
    static constexpr int MAX_BARRELS = 5;
	static constexpr int NUM_OF_CHARS_FOR_BARREL_EXPLODE = 8;
    static constexpr int START_x_BARREL = 49 ;
    static constexpr int START_Y_BARREL = 4;


};