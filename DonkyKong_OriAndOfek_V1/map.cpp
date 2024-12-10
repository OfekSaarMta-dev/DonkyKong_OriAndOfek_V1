#include "map.h"
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
        cout << _currentMap[i] << '\n';
    }
    cout << _currentMap[GameConfig::GAME_HEIGHT - 1];
}

char Map::getCharCurrentMap(int x, int y) const     // Get character at specified coordinates
{
  return _currentMap[y][x];         
}

char Map::getCharOriginalMap(int x, int y) const
{
    return _originalMap[y][x];
}

bool Map::isEdge(const int x, const int y) const
{
    return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::EDGE;
}


bool Map::isFloor(const int x, const int y) const
{
    return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::FLOOR ||
           getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::LFLOOR ||
           getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::RFLOOR;
}

bool Map::isLadder(const int x, const int y) const
{
    return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::LADDER;
}

bool Map::isRfloor(const int x, const int y) const
{
    return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::RFLOOR;
}

bool Map::isLfloor(const int x, const int y) const
{
    return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::LFLOOR;
}

bool Map::isSpace(const int x, const int y) const
{
	return getCharOriginalMap(x, y) == (char)GameConfig::utilKeys::SPACE;
}


void Map::updateCurrMap(const int x, const int y, const char ch)
{
    _currentMap[y][x] = ch;
}

void Map::drawLife(const int life) const
{
    gotoxy(GameConfig::LIFE_X, GameConfig::LIFE_y);
    for(int i = 0; i < life; ++i)
    {
        cout << "# ";
    }
}

void Map::eraseLife(const int prevLife) const
{
    gotoxy(GameConfig::LIFE_X, GameConfig::LIFE_y);
    for (int i = 0; i < prevLife; ++i)
    {
        cout << "  ";
    }
}
