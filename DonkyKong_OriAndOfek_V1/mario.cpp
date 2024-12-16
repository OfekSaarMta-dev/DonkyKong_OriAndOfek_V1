#include "mario.h"

void Mario::draw(char ch) const // Draw character at Mario's position
{
    gotoxy(_position.getX(), _position.getY());
    cout << ch;
}

void Mario::erase() // erases Mario
{
    char originalChar = _pMap->getCharOriginalMap(_position);
    gotoxy(_position.getX(), _position.getY());
    cout << originalChar; // Restore original character instead of erasing it with space.
}

// Handles key presses to control Mario's actions
void Mario::keyPressed(char key)
{
	int currX = _position.getX();
	int currY = _position.getY();
    if(!_isFalling)
    {
        if (_pMap->isLadder(Point(currX, currY + 1)))
        { // Mario on ladder right now
            switch (std::tolower(key))
            { // Options to climb up/down
            case (char)GameConfig::movementKeys::UP:
                climb(key);
                break;

            case (char)GameConfig::movementKeys::DOWN:
                climb(key);
                break;

            case (char)GameConfig::movementKeys::STAY: // stay on ladder
                _dir = { 0, 0 };
                break;
            }
        }
        else 
        { // Mario on floor
            switch (std::tolower(key))
            {
                case (char)GameConfig::movementKeys::LEFT:
                    _dir = { -1, 0 };
                    break;

                case (char)GameConfig::movementKeys::RIGHT:
                    _dir = { 1, 0 };
                    break;

                case (char)GameConfig::movementKeys::UP: // Jump or climb check
                    if (!_pMap->isLadder(Point(currX, currY)) && _pMap->isFloor(Point(currX, currY + 1)))
                    {
                        jump();
                    }
					else if (_pMap->isLadder(Point(currX, currY))) // Mario on ladder
                    {
                        climb(key);
                    }
                    break;

                case (char)GameConfig::movementKeys::DOWN: // Mario stand above a ladder and wants to climb down
                    if (_pMap->isLadder(Point(currX, currY + 2)))
                    {
                        climb(key);
                    }
                    break;

                case (char)GameConfig::movementKeys::STAY: // stay on floor
                     _dir = {0, 0};
                     break;

                default:
                     // Invalid key, do nothing
                     break; 
            }
        }
    }
}


// performs jump action
void Mario::jump()
{
    // Going up
    _dir.y = -1;
	_isJumping = true;// set Mario is jumping
}




// Handles climbing up or down ladders based on key input
void Mario::climb(char key) 
{
    Point charBelow = {_position.getX(), _position.getY() + 1}; // makes a Point from char below Mario
    Point twoCharsBelow = { _position.getX(), _position.getY() + 2 }; // makes a Point from 2 chars below Mario

    if (key == (char)GameConfig::movementKeys::UP)
    {
        _dir = { 0, -1 }; // Climb up
    }
    else //(key == (char)GameConfig::movementKeys::DOWN)
    {
        if (_pMap->isLadder(twoCharsBelow) && _pMap->isFloor(charBelow)) // mario is on floor and trying to climb down
        {
            this->erase();
            _position.setY(getY() + 2); // Move down two steps on ladder
        }
        _dir = { 0, 1 }; // Climb down (moves down)
    }
}




// Moves Mario based on current direction and checks for collisions with edges or floors
void Mario::move()
{
    int currX = _position.getX();
    int currY = _position.getY();
    Point charBelow = { currX, currY + 1 }; // Point to 1 char below Mario

    if (_isJumping || _pMap->isSpace(charBelow)) // if mario isn't on floor, he is above space
    {
        if(!_isFalling) // if Mario wasn't falling, set Mario correct member to true (falling)
            _isFalling = true;
        if (_dir.y == -1) // if in the "going up" part of jumping
        {
            if (_jumpCounter == 2) // if mario reaches peak of jump, fall
            {
                _dir.y = 1;
	    		_countFalling = 0;
                _jumpCounter = 0;
            }
            else
                _jumpCounter++;
        }
        else // not in the middle of a jump
        {
            _dir.y = 1; // Free fall if there's no floor below Mario
            _countFalling++; // Count falling steps
        }
    }

    _newPosition = Point(currX + _dir.x, currY + _dir.y); // create Point for Mario's new position

	if (this->gotHit()) // mario got hit by a barrel or explosion and died
	{
		_died = true;
	}
    else if (_pMap->isEdge(_newPosition) || _pMap->isFloor(_newPosition)) // Upon collision with edge/floor
    {
        if (_pMap->isLadder(_position) && _dir.y == -1) // when Mario climbing up a ladder and hitting upper floor
        {
            _position.setY(currY - 2); // Move Mario above the floor
            _dir = { 0, 0 }; // stop his movement
            _isFalling = false; // set falling to false
            _isJumping = false; // set jumping to false
        }
        else if (_pMap->isSpace(charBelow)) // if mario walk on top of a hole in the floor
        {
            _dir = { 0, 1 }; // fall straight down
        }
        else if (_dir.y == 1 && _pMap->isFloor(_newPosition)) // Mario is falling and about to hit a floor
        {
            if (_countFalling >= GameConfig::NUM_OF_CHARS_FOR_MARIO_DIE) // if mario fell too far
            {
				_died = true; // Mario died
            }
            else // if mario hit the floor but fell less than 5 chars
            {
                _countFalling = -1; // reset falling counter
                _dir.y = 0; // stop falling when hitting the floor and keep on moving in X axis
            }
            _isJumping = false;
            _isFalling = false;
        }
        else // if mario walked into a wall or edge
        {
            _dir = { 0, 0 }; // Stop movement
        }
    }
    else // Update position if no collision occurs (common case)
    {
        _position = _newPosition;
    }
}


// Check if Mario got hit by a barrel or explosion
bool Mario::gotHit() const
{
    char currentChar = _pMap->getCharCurrentMap(_position); // gets currentMap char at Mario's position
    char nextChar = _pMap->getCharCurrentMap(_newPosition); // gets currentMap char at Mario's new position
	if (currentChar == (char)GameConfig::utilKeys::EXPLOSION || currentChar == (char)GameConfig::utilKeys::BARREL ||
        nextChar == (char)GameConfig::utilKeys::EXPLOSION || nextChar == (char)GameConfig::utilKeys::BARREL) // if Mario's current or next position is barrel or explosion
	{
		return true;
	}
	return false;
}

// Check if Mario tuched Pauline
bool Mario::rescuedPauline() const
{
    return _pMap->getCharOriginalMap(_position) == (char)GameConfig::utilKeys::PAULINE; // if Mario's current position is Pauline
}


// resets Mario in case he dies
void Mario::reset()
{
    _position = Point(GameConfig::START_X_MARIO, GameConfig::START_Y_MARIO); // Reset Mario's position
    _countFalling = -1; // Reset falling counter
    _dir = { 0, 0 }; // Stop movement
    _died = false;
    _isJumping = false;
    _isFalling = false;
    _life--; // decreace life by one
}