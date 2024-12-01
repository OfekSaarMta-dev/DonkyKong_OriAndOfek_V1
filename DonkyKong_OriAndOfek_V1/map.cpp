#include "map.h"
#include "general.h"
#include <Windows.h>
#include <cstring>
#include <iostream>
using namespace std;


// Resets the current map to its original state
void Map::reset() 
{
    for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) 
    {
        memcpy(_currentMap[i], _originalMap[i], GameConfig::GAME_WIDTH + 1);
    }
}

// Prints the current state of the map to the console
void Map::print() const {
    for (int i = 0; i < GameConfig::GAME_HEIGHT - 1; i++) 
    {
        std::cout << _currentMap[i] << '\n';
    }
    std::cout << _currentMap[GameConfig::GAME_HEIGHT - 1];
}

