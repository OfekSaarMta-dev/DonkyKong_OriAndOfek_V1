#include "map.h"
#include "general.h"
#include <Windows.h>
#include <cstring>
#include <iostream>
using namespace std;

// Checks if Mario's current location is not a space character
bool Map::currentMarioLocation(int x, int y) 
{
    return (this->getCharOriginalMap(_mario->getX(), _mario->getY()) != (char)GameConfig::utilKeys::SPACE);
}

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

// Draws a character at specified coordinates if it's not a space
void Map::drawChar(int x, int y) 
{
    if (this->currentMarioLocation(x, y)) 
    { // Check if current Mario location is not SPACE
        gotoxy(x, y);
        cout << _originalMap[y][x];
    }
}