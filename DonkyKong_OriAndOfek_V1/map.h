#pragma once

#include "gameConfig.h"
#include "mario.h"

class Mario;

class Map
{
	const char* _originalMap[GameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                  &                           Q", // 5
		  "Q                                                  =          $                Q", // 6
		  "Q                                              <<<<=============               Q", // 7
		  "Q                                                         H                    Q", // 8
		  "Q                                                         H                    Q", // 9
		  "Q                                                         H                    Q", // 10
		  "Q           ====================================================               Q", // 11
		  "Q            H                                                                 Q", // 12
		  "Q            H                                                                 Q", // 13
		  "Q        =====================                ========================         Q", // 14
		  "Q                              ====                    H                       Q", // 15
		  "Q                             ==================       H                       Q", // 16
		  "Q                                                      H                       Q", // 17
		  "Q                                                      H                       Q", // 18
		  "Q               =================== ===========================                Q", // 19
		  "Q                         H                                                    Q", // 20
		  "Q                         H                                                    Q", // 21
		  "Q                         H                                                    Q", // 22
		  "Q==============================================================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char _currentMap[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]; // +1 for null terminator

	Mario* _mario = nullptr;

	bool currentMarioLocation(int x, int y);

public:
	void reset();
	void print() const;
	char getCharCurrentMap(int x, int y) const
	{
		return _currentMap[y][x];
	}
	char getCharOriginalMap(int x, int y) const
	{
		return _originalMap[y][x];
	}
	void setMario(Mario& mario) {_mario = &mario;}
	void drawChar(int x, int y);

};

