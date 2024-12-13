#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch) const// Draw character at Barrel's position
{
    int barrelX = _position.getX();
    int barrelY = _position.getY();
    gotoxy(barrelX, barrelY);
    cout << ch; // print barrel on screen
    
}


void Barrel::erase() const
{
    char originalChar = _pMap->getCharOriginalMap(_position);
    gotoxy(_position.getX(), _position.getY());
    cout << originalChar; // print original char

	_pMap->updateCurrMap(_position, originalChar); // erasing from current map (putting original char)
}

void Barrel::move() // Move Barrel
{

    int currX = _position.getX();
    int currY = _position.getY();

    Point newPosition; // Barrel's new position
	Point charBelow = { currX, currY + 1 }; // Point below Barrel


    // Check if Barrel is on the floor using the 
    if (!_pMap->isFloor(charBelow))// If there's no floor below Baarrel
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
		_count_falling++;
    }

	newPosition = Point(currX + _dir.x, currY + _dir.y); // Calculate new position

    if (_pMap->isFloor(newPosition)) // Upon collision with floor
    {
		if (_count_falling >= GameConfig::NUM_OF_CHARS_FOR_BARREL_EXPLODE) // If Barrel fell enough to explode
        {
			this->explosion(); // Explode Barrel
        }
        else
			_count_falling = 0; // Reset falling counter
        
        if (_pMap->isLfloor(newPosition)) // If Barrel is on the left floor
            _dir = { -1,0 }; // going left

        if (_pMap->isRfloor(newPosition)) // If Barrel is on the right floor
            _dir = { 1,0 };  // going right
    }
    else // Update position if no collision occurs
    {
		_position = newPosition; // Update Barrel's position
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
			newPosition = Point(newX, newY); // Calculate new position

			_pMap->updateCurrMap(newPosition, (char)GameConfig::utilKeys::EXPLOSION);
			gotoxy(newX, newY);
			cout << (char)GameConfig::utilKeys::EXPLOSION; // print explosion on screen
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
			newX = barrelX - 2 + i; // Calculate new x position
			newY = barrelY - j; // Calculate new y position
			newPosition = Point(newX, newY); // Calculate new position
			originalChar = _pMap->getCharOriginalMap(newPosition); // Get original char

			_pMap->updateCurrMap(newPosition, originalChar); // erasing from current map (putting original char)
			gotoxy(newX, newY);
			cout << originalChar;
		}
	}

    this->resetBarrel();
}

void Barrel::resetBarrel()
{
	this->erase();
	_position = Point(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL); // Reset Barrel's position
	_count_falling = 0; // Reset falling counter
	_exploded = false; // Reset explosion flag
}
