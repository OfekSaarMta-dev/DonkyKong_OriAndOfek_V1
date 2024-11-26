#include "map.h"

#include <cstring>
#include <iostream>


void Map::reset() {
	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) {
		memcpy(currentMap[i], originalMap[i], GameConfig::GAME_WIDTH + 1);
	}
}

void Map::print() const {
	for (int i = 0; i < GameConfig::GAME_HEIGHT - 1; i++) {
		std::cout << currentMap[i] << '\n';
	}
	std::cout << currentMap[GameConfig::GAME_HEIGHT - 1];
}

