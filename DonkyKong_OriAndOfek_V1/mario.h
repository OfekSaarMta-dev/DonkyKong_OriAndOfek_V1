#pragma once
#include "gameConfig.h"
#include "general.h"
#include "map.h"
#include <iostream>
#include"point.h"

using namespace std;

class Map;
class Mario
{
private:

	Point _position; // Mario's position
	GameConfig::Direction _dir{0, 0}; // starting dir.x and dir.y
	Map* _pMap = nullptr; // Pointer to Map object


	void draw(char ch);// Draw character at Mario's position
	

public:
	Mario() : _position(GameConfig::START_X_MARIO,GameConfig::START_Y_MARIO){}  // Constructor
		
	void draw() { draw('@'); }  // Draw Mario
	void erase(); // Erase Mario

	// Getters for position
	int getX() {return _position.getX();}
	int getY() {return _position.getY();}

	void keyPressed(char key);  // Handle key press
	void jump();  // Perform jump action
	void climb(char key);  // Perform climb action
	void move();  // Move Mario
	void setMap(Map& map) { _pMap = &map; }  // Set Map reference
};