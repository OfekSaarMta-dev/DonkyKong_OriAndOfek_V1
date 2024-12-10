#pragma once

#include "gameConfig.h"
#include "general.h"


class Map
{
private:

	// Original map layout
	
	const char* _originalMap[GameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q    LIVES LEFT: # # #                                                         Q", // 2
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
		  "Q    ====>>>============                       ==== ===========<<<=========    Q", // 13
		  "Q                       >>>=========                   H                       Q", // 14
		  "Q                             =====>>>>===========     H                       Q", // 15
		  "Q                                                      H                       Q", // 16
		  "Q                                                      H                       Q", // 17
		  "Q                                                      H                       Q", // 18
		  "Q               ================================== ==========                  Q", // 19
		  "Q                         H                                                    Q", // 20
		  "Q                         H                                                    Q", // 21
		  "Q                         H                                                    Q", // 22
		  "Q=================================>>>>=========================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};



	// Current map state
	char _currentMap[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]; // +1 for null terminator
	
public:
	Map(){}
	Map(const Map&) = delete;             // Copy constructor
	Map& operator=(const Map&) = delete; // Copy assignment operator


	void reset(); // Reset map to original state
	void print() const;  // Print current map state
	char getCharCurrentMap(int x, int y) const;
	char getCharOriginalMap(int x, int y) const;
	bool isEdge(const int x, const int y) const;
	bool isFloor(const int x, const int y) const;
	bool isLadder(const int x, const int y) const;
	bool isRfloor(const int x, const int y) const;
	bool isLfloor(const int x, const int y) const;
	bool isSpace(const int x, const int y) const;
	void updateCurrMap(const int x,const int y,const char ch);

	void drawLife(const int life) const;
	void eraseLife(const int life) const;

};

