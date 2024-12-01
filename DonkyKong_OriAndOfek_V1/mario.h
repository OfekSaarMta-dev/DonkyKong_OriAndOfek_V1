#pragma once
#include "gameConfig.h"
#include "general.h"
#include "map.h"
#include <iostream>
#include"point.h"

using namespace std;

class Map;
class Point; 

class Mario
{
	// Mario's position
	
	Point _position; // Barrel's position


	GameConfig::Direction _dir{0, 0}; // starting dir.x and dir.y
	Map* _pMap = nullptr; // Pointer to Map object


	void draw(char ch)// Draw character at Mario's position
	{
		gotoxy(_position._x, _position._y);
		cout << ch;
	}

	public:
		Mario() : _position(GameConfig::START_X,GameConfig::START_Y){}  // Constructor
		
		void draw() { draw('@'); }  // Draw Mario
		void erase(); // Erase Mario

		// Getters for position
		int getX() {return _position._x;}
		int getY() {return _position._y;}
		void keyPressed(char key);  // Handle key press
		void jump();  // Perform jump action
		void climb(char key);  // Perform climb action
		void move();  // Move Mario
		void setMap(Map& map) { _pMap = &map; }  // Set Map reference
};



/*
class Mario
{
	int _x;
	int _y;
	int dir_x;
	int dir_y;

	const Ladder* _ladders = nullptr;
	const Floor* _floors = nullptr;




public:
	Mario()
	{
		_x = GameConfig::MIN_X + 1; _y = GameConfig::MIN_Y - 1;
		dir_x = GameConfig::DIR_X; dir_y = GameConfig::DIR_Y;
	}


	void setLaddersAndFloors (Map& map)
	{
		_ladders = map.getLadders();
		_floors = map.getFloors();
	}


	void draw(char ch);
	bool isOnLadder(const Ladder* ladders);
	void move(GameConfig::eKeys key);


};


*/
