#include "Barrel.h"
using namespace std;


void Barrel::draw(char ch)// Draw character at Barrel's position
{
    int barrelX = _position.getX();
    int barrelY = _position.getY();
    gotoxy(barrelX, barrelY);
    cout << ch; // print barrel on screen
    
    _pMap->updateCurrMap(barrelX, barrelY, ch); // put barrel inside current map
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
    // Check if Barrel is on the floor using the 
    if (!_pMap->isFloor(_position.getX(), _position.getY() + 1))// If there's no floor below Baarrel
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Barrel
		_count_falling++;
    }

    const int newX = _position.getX() + _dir.x;
    const int newY = _position.getY() + _dir.y;

    if (_pMap->isFloor(newX, newY)) // Upon collision with floor
    {
        if(_count_falling >= GameConfig::NUM_OF_CHARS_FOR_BARREL_EXPLODE)
        {
            this->explosion();
            // 
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

void Barrel::explosion()
{
    //*****
    //***** 
    //**O** 
    
    int barrelX = _position.getX();
    int barrelY = _position.getY();

    gotoxy(barrelX - 2, barrelY - 2);
    for (int i = 0; i < 5; i++)
    {
        cout << "*";
    }

    gotoxy(barrelX - 2, barrelY - 1);
    for (int i = 0; i < 5; i++)
    {
        cout << "*";
    }

    gotoxy(barrelX - 2, barrelY);
    for (int i = 0; i < 6; i++)
    {
        if(i != 2)
            cout << "*";
    }

  
	this->erase();
    _position.setXY(GameConfig::START_x_BARREL, GameConfig::START_Y_BARREL);
    _count_falling = 0;
}

void Barrel::clearExplosion()
{
	int barrelX = _position.getX();
	int barrelY = _position.getY();

    char originalChar = _pMap->getCharOriginalMap(barrelX, barrelY);


	gotoxy(barrelX - 2, barrelY - 2);
	for (int i = 0; i < 5; i++)
	{
        cout << originalChar; // print original char
    }

	gotoxy(barrelX - 2, barrelY - 1);
	for (int i = 0; i < 5; i++)
	{
        cout << originalChar; // print original char
    }

	gotoxy(barrelX - 2, barrelY);
	for (int i = 0; i < 6; i++)
	{
		if (i != 2)
            cout << originalChar; // print original char
    }
}
