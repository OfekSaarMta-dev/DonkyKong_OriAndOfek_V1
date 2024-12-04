#pragma once
#include "point.h" // Assuming a Point class to handle positions
#include "general.h"
#include "gameConfig.h"
#include "map.h"
#include <iostream>


class Barrel 
{
private:

	Point _position;
	Map* _pMap = nullptr; 
	GameConfig::Direction _dir{ 0, 1 }; // starting dir.x and dir.y

	void draw(char ch);// Draw character at Barrel's position
	

public:

	Barrel() : _position(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL) {} // Constructor

	void draw()
	{
		draw('O'); // Draw Barrel
	} 
	void erase(); // Erase Barrel
	void move();  // Move Barrel
	void setMap(Map& map) { _pMap = &map; } // Set Map reference

	




};