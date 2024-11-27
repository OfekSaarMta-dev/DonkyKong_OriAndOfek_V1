#pragma once

#include <iostream>

class GameConfig
{
public:
	static constexpr int GAME_WIDTH = 80;//x
	static constexpr int GAME_HEIGHT = 25;//y
	static constexpr int JUMP_HEIGHT = 2;
	static constexpr int JUMP_DURATION = 50;
	static constexpr int MOVE_DELAY = 100;

	enum class utilKeys {SPACE = ' ' ,LADDER = 'H' ,FLOOR = '=', EDGE = 'Q', ESC = 27 }; // utility keys

	enum class movementKeys {LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's' };

	struct Direction { int x, y; }; // inner private struct
	static constexpr Direction directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0} };

	// the directions array order is exactly the same as the keys array - must keep it that way

	static constexpr int START_X = 1;
	static constexpr int START_Y = 22;


};
