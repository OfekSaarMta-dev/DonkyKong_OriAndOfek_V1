#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch)// Draw character at Barrel's position
{
    gotoxy(_position._x, _position._y);
    cout << ch;
}


void Barrel::erase()
{
    char originalChar = _pMap->getCharOriginalMap(_position._x, _position._y);
    gotoxy(_position._x, _position._y);
    cout << originalChar; // Restore original character instead of erasing it with space.
}

void Barrel::move()
{
    // Check if Barrel is on the floor using the isFloor method
    if (!_pMap->isFloor(_position._x, _position._y + 1))/* && // If there's no floor below Baarrel
        _pMap->getCharOriginalMap(_position._x, _position._y + 1) == (char)GameConfig::utilKeys::SPACE) //he is not on ladder which means there is space below him*/
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
    }

    const int newX = _position._x + _dir.x;
    const int newY = _position._y + _dir.y;

    if (_pMap->isFloor(newX, newY)) // Upon collision with floor
    {
        if(_pMap->isEndOfRoad(newX, newY))
        {
            _dir = {0, 0};
            _position.setXY(newX, newY);
            this->erase();
        }

        if(_pMap->isLfloor(newX, newY))
            _dir = GameConfig::directions[0]; // going left

        if(_pMap->isRfloor(newX, newY))
            _dir = GameConfig::directions[1]; // going right
    }
    else // Update position if no collision occurs
    {
        _position._x = newX;
        _position._y = newY;
    }
}
