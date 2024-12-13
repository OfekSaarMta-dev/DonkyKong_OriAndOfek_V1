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

char Map::getCharCurrentMap(const Point& point) const     // Get character at specified coordinates
{
	return _currentMap[point.getY()][point.getX()]; // Get character at specified coordinates
}

char Map::getCharOriginalMap(const Point& point) const  
{
	return _originalMap[point.getY()][point.getX()]; // Get character at specified coordinates
}

bool Map::isEdge(const Point& point) const
{
	return getCharOriginalMap(point) == (char)GameConfig::utilKeys::EDGE; // Check if point is edge
}


bool Map::isFloor(const Point& point) const
{
    return getCharOriginalMap(point) == (char)GameConfig::utilKeys::FLOOR ||
           getCharOriginalMap(point) == (char)GameConfig::utilKeys::LFLOOR ||
		getCharOriginalMap(point) == (char)GameConfig::utilKeys::RFLOOR; // Check if point is floor in any kind
}

bool Map::isLadder(const Point& point) const // Check if point is ladder
{
	return getCharOriginalMap(point) == (char)GameConfig::utilKeys::LADDER;
}


bool Map::isRfloor(const Point& point) const // Check if point is right floor
{
    return getCharOriginalMap(point) == (char)GameConfig::utilKeys::RFLOOR;
}

bool Map::isLfloor(const Point& point) const // Check if point is left floor
{
    return getCharOriginalMap(point) == (char)GameConfig::utilKeys::LFLOOR;
}

bool Map::isSpace(const Point& point) const // Check if point is space
{
	return getCharOriginalMap(point) == (char)GameConfig::utilKeys::SPACE;
}


void Map::updateCurrMap(const Point& point, const char ch) // Update current map state
{
    _currentMap[point.getY()][point.getX()] = ch;
}

void Map::drawLife(const int life) const // Draw life
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
