#pragma once

#include "gameConfig.h"
#include "general.h"
#include "point.h"

class Point;

class Map
{
private:

	// Original map layout
	
	const char* _originalMap[GameConfig::GAME_HEIGHT] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q    LIVES LEFT: # # #                                       $                 Q", // 2
		  "Q                                                            =                 Q", // 3
		  "Q                                                  &         H                 Q", // 4
		  "Q                                                  =         H                 Q", // 5
		  "Q                                              <<<<=============               Q", // 6
		  "Q                                                      H  H                    Q", // 7
		  "Q                                                      H  H                    Q", // 8
		  "Q           ===============================<<<<<<===============               Q", // 9
		  "Q            H                                         H                       Q", // 10
		  "Q            H                                         H                       Q", // 11
		  "Q            H                                         H                       Q", // 12
		  "Q    ====>>>============                       ==== ===========<<<=========    Q", // 13
		  "Q                       >>>=========                   H                       Q", // 14
		  "Q                             =====>>>>===========     H                       Q", // 15
		  "Q                                                      H                       Q", // 16
		  "Q                                                      H                       Q", // 17
		  "Q                                                      H                       Q", // 18
		  "Q               ================================== ==========                  Q", // 19
		  "Q                         H                            H                       Q", // 20
		  "Q                         H                            H                       Q", // 21
		  "Q                         H                            H                       Q", // 22
		  "Q=================================>>>>=========================================Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};



	// Current map state
	char _currentMap[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]; // +1 for null terminator
	
public:
	Map(){}
	Map(const Map&) = delete;             // delete Copy constructor - we do not want anyone to copy map in any case!
	Map& operator=(const Map&) = delete; // delete Copy assignment operator - we do not want anyone to do an assignmen on map in any case!


	void reset(); // Reset map to original state
	void print() const;  // Print current map state
	char getCharCurrentMap(const Point& point) const; // Get character from current map state
	char getCharOriginalMap(const Point& point) const; // Get character from original map state
	bool isEdge(const Point& point) const; // Check if point is edge
	bool isFloor(const Point& point) const; // Check if point is floor
	bool isLadder(const Point& point) const; // Check if point is ladder
	bool isRfloor(const Point& point) const; // Check if point is right floor
	bool isLfloor(const Point& point) const; // Check if point is left floor
	bool isSpace(const Point& point) const; // Check if point is space
	void updateCurrMap(const Point& point, const char ch); // Update current map state

	void drawLife(const int life) const; // Draw life
	void eraseLife(const int life) const; // Erase life

};

