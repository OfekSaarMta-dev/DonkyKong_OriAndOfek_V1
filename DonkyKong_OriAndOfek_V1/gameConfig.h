#pragma once

#include <iostream>

class GameConfig
{
public:
	static constexpr int GAME_WIDTH = 80;//x
	static constexpr int GAME_HEIGHT = 25;//y
	static constexpr int JUMP_HEIGHT = 2;
	static constexpr int JUMP_DURATION = 50;
	static constexpr int MOVE_DELAY = 50;

	enum class utilKeys {LADDER = 'H' ,FLOOR = '=', EDGE = 'Q', ESC = 27 }; // utility keys

	static constexpr char eKeys[]{ 'a', 'd', 'w', 'x', 's'};
	static constexpr size_t numKeys = sizeof(eKeys) / sizeof(eKeys[0]);
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0} };

	static constexpr int START_X = 1;
	static constexpr int START_Y = 22;


};
