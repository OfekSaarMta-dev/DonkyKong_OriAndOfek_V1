#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch)// Draw character at Barrel's position
{
    int barrelX = _position.getX();
    int barrelY = _position.getY();
    gotoxy(barrelX, barrelY);
    cout << ch; // print barrel on screen
    
    //_pMap->updateCurrMap(barrelX, barrelY, ch); // put barrel inside current map
}


void Barrel::erase()
{
    int barrelX = _position.getX();
    int barrelY = _position.getY();
    char originalChar = _pMap->getCharOriginalMap(barrelX, barrelY);
    gotoxy(barrelX, barrelY);
    cout << originalChar; // print original char

	_pMap->updateCurrMap(barrelX, barrelY, originalChar); // erasing from current map (putting original char)
}

void Barrel::move()
{
    int currX = _position.getX();
    int currY = _position.getY();

    // Check if Barrel is on the floor using the 
    if (!_pMap->isFloor(currX, currY + 1))// If there's no floor below Baarrel
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
		_count_falling++;
    }

    const int newX = currX + _dir.x;
    const int newY = currY + _dir.y;

    if (_pMap->isFloor(newX, newY)) // Upon collision with floor
    {
        if(_count_falling >= GameConfig::NUM_OF_CHARS_FOR_BARREL_EXPLODE)
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
        _pMap->updateCurrMap(newX, newY, 'O'); // put barrel inside current map
    }
}

void Barrel::explosion()
{
	_exploded = true;

    int barrelX = _position.getX();
    int barrelY = _position.getY();
    int newX;
    int newY;

    //*****
    //***** 
    //**O** 

    for (int i = 0; i < 5; i++) //columns
    {
        for (int j = 2; j >= 0; j--) //rows
        {
			newX = barrelX - 2 + i;
			newY = barrelY - j;

			_pMap->updateCurrMap(newX, newY, (char)GameConfig::utilKeys::EXPLOSION);
			gotoxy(newX, newY);
			cout << (char)GameConfig::utilKeys::EXPLOSION;
        }
    }

	
}

void Barrel::clearExplosion()
{
	_exploded = false;

	int barrelX = _position.getX();
	int barrelY = _position.getY();
	int newX;
	int newY;
    char originalChar;

	for (int i = 0; i < 5; i++) //columns
	{
        for (int j = 2; j >= 0; j--) //rows
		{
			newX = barrelX - 2 + i;
			newY = barrelY - j;
            originalChar = _pMap->getCharOriginalMap(newX, newY);

			_pMap->updateCurrMap(newX, newY, originalChar);
			gotoxy(newX, newY);
			cout << originalChar;
		}
	}

	this->erase();
	_position.setXY(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL);
	_count_falling = 0;
}
