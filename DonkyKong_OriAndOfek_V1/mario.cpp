#include "mario.h"
#include "gameConfig.h"

// Handles key presses to control Mario's actions
void Mario::keyPressed(char key)
{
    if (_pMap->getCharOriginalMap(_position._x, _position._y + 1) == (char)GameConfig::utilKeys::LADDER)
    { // Mario on ladder
        switch (std::tolower(key)) 
        { // Options to climb up/down
        case (char)GameConfig::movementKeys::UP:
            climb(key);
            break;

        case (char)GameConfig::movementKeys::DOWN:
            climb(key);
            break;

        case (char)GameConfig::movementKeys::STAY:
            _dir = GameConfig::directions[4];
            break;

        }
    }

    else { // Mario on floor
        switch (std::tolower(key))
        {
        case (char)GameConfig::movementKeys::LEFT:
            _dir = GameConfig::directions[0];
            break;

        case (char)GameConfig::movementKeys::RIGHT:
            _dir = GameConfig::directions[1];
            break;

        case (char)GameConfig::movementKeys::UP: // Jump or climb check
            if (_pMap->getCharOriginalMap(_position._x, _position._y) != (char)GameConfig::utilKeys::LADDER && 
                _pMap->isFloor(_position._x, _position._y + 1)) // do a function isOnLadder
            {
                jump();
            }
            else if (_pMap->getCharOriginalMap(_position._x, _position._y) == (char)GameConfig::utilKeys::LADDER)
            {
                climb(key);
            }
            break;

        case (char)GameConfig::movementKeys::DOWN:
            if (_pMap->getCharOriginalMap(_position._x, _position._y + 2) == (char)GameConfig::utilKeys::LADDER)
            {
                climb(key);
            }
            break;

        case (char)GameConfig::movementKeys::STAY:
            _dir = GameConfig::directions[4];
        default:
            // Invalid key, do nothing
            break;

        }
    }
}

// Handles Mario's jumping action with a simple upward and downward motion
void Mario::jump()
{
    // Going up
    this->erase();
    _dir.y = -1;

    for (int i = 1; i <= GameConfig::JUMP_HEIGHT; i++)
    {
        int newX = _position._x + _dir.x;
        int newY = _position._y + _dir.y;

        if(_pMap->getCharOriginalMap(newX, newY) == (char)GameConfig::utilKeys::EDGE || // do as a function 
           _pMap->isFloor(newX, newY))
        {
           break;
        }
        else
        {
        _position._x = newX;
        _position._y = newY;
        this->draw();
        Sleep(GameConfig::JUMP_DURATION); 
        this->erase();
        }
    }
}




// Handles climbing up or down ladders based on key input
void Mario::climb(char key) 
{
    if (key == (char)GameConfig::movementKeys::UP)
    {
        _dir.y = -1; // Climb up
    }
    else //(key == (char)GameConfig::movementKeys::DOWN)
    {
        if (_pMap->getCharOriginalMap(_position._x, _position._y + 2) == (char)GameConfig::utilKeys::LADDER)
        {
            this->erase();
            _position._y += 2; // Move down two steps on ladder
        }
        _dir.y = 1; // Climb down
    }
}




// Moves Mario based on current direction and checks for collisions with edges or floors
void Mario::move() 
{
    // Check if Mario is on the floor using the new isOnFloor method
	if (!_pMap->isFloor(_position._x, _position._y + 1) && // If there's no floor below Mario
		_pMap->getCharOriginalMap(_position._x, _position._y + 1) == (char)GameConfig::utilKeys::SPACE) //he is not on ladder which means there is space below him
    {
        _dir.x = 0;
        _dir.y = 1; // Free fall if there's no floor below Mario
    }

    const int newX = _position._x + _dir.x;
    const int newY = _position._y + _dir.y;

    if (_pMap->getCharOriginalMap(newX, newY) == (char)GameConfig::utilKeys::EDGE ||
        _pMap->isFloor(newX, newY)) // Upon collision with edge
    {
        if (_pMap->getCharOriginalMap(_position._x, _position._y) == (char)GameConfig::utilKeys::LADDER && 
            _dir.y == -1) // when Mario climbing up a ladder and hitting upper floor
            {
            _position._y += -2; // Move Mario avove the floor
            }
        _dir = { 0, 0 }; // Stop movement
    }
    else // Update position if no collision occurs
    {
        _position._x = newX; 
        _position._y = newY;
    }
}

void Mario::erase()
{
    char originalChar = _pMap->getCharOriginalMap(_position._x, _position._y);
    gotoxy(_position._x, _position._y);
    cout << originalChar; // Restore original character instead of erasing it with space.
}