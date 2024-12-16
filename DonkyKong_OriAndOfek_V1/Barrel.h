#pragma once
#include "point.h" // Assuming a Point class to handle positions
#include "general.h"
#include "gameConfig.h"
#include "map.h"

class Map; // Forward declaration

class Barrel 
{
private:
	Point _position; // Barrel's position
	GameConfig::Direction _dir = { 0, 1 }; // starting dir.x and dir.y // free falling
	Map* _pMap = nullptr; // Pointer to Map object
	int _count_falling = 0; // Counter for falling
	bool _exploded = false; // Barrel exploded flag

	void draw (char ch) const;// Draw character at Barrel's position

public:

	Barrel() : _position(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL), _dir({ 0, 1 }), _count_falling(0), _exploded(false) {} // Constructor

	void draw() const {draw((char)GameConfig::utilKeys::BARREL);} // Draw Barrel  

	void erase() const; // Erase Barrel
	void move();  // Move Barrel
	void setMap(Map& map) { _pMap = &map; } // Set Map reference
	void explosion();	// Barrel explosion
	void clearExplosion();	// Clear explosion
	bool isExploded() const { return _exploded; }	// Check if Barrel exploded
	void resetBarrel();	// Reset Barrel in the start position

	
};