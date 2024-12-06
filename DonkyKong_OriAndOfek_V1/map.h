#pragma once

#include "gameConfig.h"


class Map
{
private:

	// Original map layout
	
	const char* _originalMap[GameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                                                            $                 Q", // 3
		  "Q                                                  &         =                 Q", // 4
		  "Q                                                  =         H                 Q", // 5
		  "Q                                              <<<<=============               Q", // 6
		  "Q                                                         H                    Q", // 7
		  "Q                                                         H                    Q", // 8
		  "Q           ===============================<<<<<<===============               Q", // 9
		  "Q            H                                                                 Q", // 10
		  "Q            H                                                                 Q", // 11
		  "Q            H                                                                 Q", // 12
		  "Q    ====>>>==================                ===== ===========<<<====         Q", // 13
		  "Q                             >>>>==                   H                       Q", // 14
		  "Q                             =====>>>>===========     H                       Q", // 15
		  "Q                                                      H                       Q", // 16
		  "Q                                                      H                       Q", // 17
		  "Q                                                      H                       Q", // 18
		  "Q               ================================== ==========                  Q", // 19
		  "Q                         H                                                    Q", // 20
		  "Q                         H                                                    Q", // 21
		  "Q                         H                                   #                Q", // 22
		  "Q=================================>>>>=========================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};



	// Current map state
	char _currentMap[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]; // +1 for null terminator



	
public:
	void reset(); // Reset map to original state
	void print() const;  // Print current map state
	char getCharCurrentMap(int x, int y) const;
	char getCharOriginalMap(int x, int y) const;
	bool isFloor(const int x, const int y) const;
	bool isRfloor(const int x, const int y) const;
	bool isLfloor(const int x, const int y) const;
	bool isEndOfRoad(const int x, const int y) const;
};

