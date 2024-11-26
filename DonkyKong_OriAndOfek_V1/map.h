#pragma once

#include "gameConfig.h"

class Map
{
	const char* originalMap[GameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                                              ===========H=====               Q", // 7
		  "Q                                                         H                    Q", // 8
		  "Q                                                         H                    Q", // 9
		  "Q                                                         H                    Q", // 10
		  "Q           =H==================================================               Q", // 11
		  "Q            H                                                                 Q", // 12
		  "Q            H                                                                 Q", // 13
		  "Q        ==============H=====                 =========H==============         Q", // 14
		  "Q                      H                               H                       Q", // 15
		  "Q                      H      ==================       H                       Q", // 16
		  "Q                      H                               H                       Q", // 17
		  "Q                      H                               H                       Q", // 18
		  "Q               ==========H=======    ====H====================                Q", // 19
		  "Q                         H               H                                    Q", // 20
		  "Q                         H               H                                    Q", // 21
		  "Q                         H               H                                    Q", // 22
		  "Q==============================================================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char currentMap[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]; // +1 for null terminator
public:
	void reset();
	void print() const;
	char getCharCurrentMap(int x, int y) const
	{
		return currentMap[y][x];
	}
	char getCharOriginalMap(int x, int y) const
	{
		return originalMap[y][x];
	}
};

