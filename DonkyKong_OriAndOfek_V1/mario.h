#pragma once
#include "gameConfig.h"
#include "general.h"
#include "map.h"
#include <iostream>

using namespace std;

class Map;

class Mario
{
	int _x;
	int _y;
	GameConfig::Direction _dir{0, 0}; // starting dir.x and dir.y
	Map* _pMap = nullptr;

	void draw(char ch)
	{
		gotoxy(_x, _y);
		cout << ch;
	}

	public:
		Mario() : _x(GameConfig::START_X), _y(GameConfig::START_Y) {}
		
		void draw() { draw('@'); }
		void erase() { draw(' '); }

		int getX() {return _x;}
		int getY() {return _y;}
		void keyPressed(char key);
		void jump();
		void climb(char key);
		void move();
		void setMap(Map& map) { _pMap = &map; }
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
