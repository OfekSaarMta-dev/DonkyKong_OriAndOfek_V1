#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch)// Draw character at Barrel's position
{
    int barrelX = _position.getX();
    int barrelY = _position.getY();
    gotoxy(barrelX, barrelY);
    cout << ch; // print barrel on screen
    
}


void Barrel::erase()
{
    char originalChar = _pMap->getCharOriginalMap(_position);
    gotoxy(_position.getX(), _position.getY());
    cout << originalChar; // print original char

	_pMap->updateCurrMap(_position, originalChar); // erasing from current map (putting original char)
}

void Barrel::move()
{
    Point newPosition;

    int currX = _position.getX();
    int currY = _position.getY();

    // Check if Barrel is on the floor using the 
    if (!_pMap->isFloor(Point(currX, currY + 1)))// If there's no floor below Baarrel
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
		_count_falling++;
    }

    newPosition = Point(currX + _dir.x, currY + _dir.y);

    if (_pMap->isFloor(newPosition)) // Upon collision with floor
    {
        if(_count_falling >= GameConfig::NUM_OF_CHARS_FOR_BARREL_EXPLODE)
        {
            this->explosion();
        }
        else
            _count_falling = 0;
        
        if(_pMap->isLfloor(newPosition))
            _dir = GameConfig::directions[0]; // going left

        if(_pMap->isRfloor(newPosition))
        _dir = GameConfig::directions[1]; // going right
    }
    else // Update position if no collision occurs
    {
        _position = newPosition;
        _pMap->updateCurrMap(newPosition, (char)GameConfig::utilKeys::BARREL); // put barrel inside current map
    }
}

void Barrel::explosion()
{
	_exploded = true;

    Point newPosition;

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
            newPosition = Point(newX, newY);

			_pMap->updateCurrMap(newPosition, (char)GameConfig::utilKeys::EXPLOSION);
			gotoxy(newX, newY);
			cout << (char)GameConfig::utilKeys::EXPLOSION;
        }
    }

	
}

void Barrel::clearExplosion()
{
    Sleep(GameConfig::EXPLOSION_DELAY);

    Point newPosition;

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
            newPosition = Point(newX, newY);
            originalChar = _pMap->getCharOriginalMap(newPosition);

			_pMap->updateCurrMap(newPosition, originalChar);
			gotoxy(newX, newY);
			cout << originalChar;
		}
	}

    this->resetBarrel();
}

void Barrel::resetBarrel()
{
	this->erase();
    _position = Point(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL);
    _count_falling = 0;
    _exploded = false;
}
