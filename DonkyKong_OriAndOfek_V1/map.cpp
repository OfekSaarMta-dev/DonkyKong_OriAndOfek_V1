#include "map.h"
#include "general.h"
#include <Windows.h>
#include <cstring>
#include <iostream>
using namespace std;


bool Map::currentMarioLocation(int x, int y)
	{
		return (this->getCharOriginalMap(_mario->getX(), _mario->getY()) != (char)GameConfig::utilKeys::SPACE);
	}


void Map::reset() {
	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) {
		memcpy(_currentMap[i], _originalMap[i], GameConfig::GAME_WIDTH + 1);
	}
}

void Map::print() const {
	for (int i = 0; i < GameConfig::GAME_HEIGHT - 1; i++) {
		std::cout << _currentMap[i] << '\n';
	}
	std::cout << _currentMap[GameConfig::GAME_HEIGHT - 1];
}


void Map::drawChar(int x, int y)
	{
		if(this->currentMarioLocation(x, y)) // check if current mario location is char different than SPACE
		{
			gotoxy(x, y);
			cout << _originalMap[y][x];
		}
	}