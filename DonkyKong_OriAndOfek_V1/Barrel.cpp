#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch)// Draw character at Barrel's position
{
    gotoxy(_position.getX(), _position.getY());
    cout << ch;
}


void Barrel::erase()
{
    char originalChar = _pMap->getCharOriginalMap(_position.getX(), _position.getY());
    gotoxy(_position.getX(), _position.getY());
    cout << originalChar; // Restore original character instead of erasing it with space.
}

void Barrel::move()
{
    // Check if Barrel is on the floor using the isFloor method
    if (!_pMap->isFloor(_position.getX(), _position.getY() + 1))/* && // If there's no floor below Baarrel
        _pMap->getCharOriginalMap(_position._x, _position._y + 1) == (char)GameConfig::utilKeys::SPACE) //he is not on ladder which means there is space below him*/
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
		_count_falling++;
    }

    const int newX = _position.getX() + _dir.x;
    const int newY = _position.getY() + _dir.y;

    if (_pMap->isFloor(newX, newY)) // Upon collision with floor
    {
        if(_count_falling >= 8)
        {
            this->explosion();
        }
        else
            _count_falling = 0;
        
        if(_pMap->isLfloor(newX, newY))
            _dir = GameConfig::directions[0]; // going left

        if(_pMap->isRfloor(newX, newY))
        _dir = GameConfig::directions[1]; // going right

       
    }
    else // Update position if no collision occurs
    {
        _position.setXY(newX, newY);
     
    }
}
