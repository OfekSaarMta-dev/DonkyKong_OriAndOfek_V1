#include "mario.h"

void Mario::draw(char ch) const // Draw character at Mario's position
{
    gotoxy(_position.getX(), _position.getY());
    cout << ch;
}

void Mario::erase()
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

            case (char)GameConfig::movementKeys::STAY:
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

                case (char)GameConfig::movementKeys::DOWN:
                    if (_pMap->isLadder(Point(currX, currY + 2)))
                    {
                        climb(key);
                    }
                    break;

                case (char)GameConfig::movementKeys::STAY:
                     _dir = {0, 0};
                     break;

                default:
                     // Invalid key, do nothing
                     break; 
            }
        }
    }
}


       
void Mario::jump()
{
    // Going up
    _dir.y = -1;
	_isJumping = true;// Mario is jumping
}




// Handles climbing up or down ladders based on key input
void Mario::climb(char key) 
{
    Point charBelow = {_position.getX(), _position.getY() + 1};
    Point twoCharsBelow = { _position.getX(), _position.getY() + 2 };

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
        _dir = { 0, 1 }; // Climb down
    }
}




// Moves Mario based on current direction and checks for collisions with edges or floors
void Mario::move()
{
    int currX = _position.getX();
    int currY = _position.getY();
    Point charBelow = { currX, currY + 1 };

    if (_isJumping) // if mario isn't on floor, he is above space
    {
        if(!_isFalling)
            _isFalling = true;
        if (_dir.y == -1) // if in the middle of jumping
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

    _newPosition = Point(currX + _dir.x, currY + _dir.y);

	if (this->gotHit()) // mario got hit by a barrel or explosion
	{
		_died = true;
	}
    else if (_pMap->isEdge(_newPosition) || _pMap->isFloor(_newPosition)) // Upon collision with edge/floor
    {
        if (_pMap->isLadder(_position) && _dir.y == -1) // when Mario climbing up a ladder and hitting upper floor
        {
            _position.setY(currY - 2); // Move Mario above the floor
            _dir = { 0, 0 }; // and stop his movement
            _isFalling = false;
            _isJumping = false;
        }
        else if (_pMap->isSpace(charBelow)) // if mario walk on top of a hole in the floor
        {
            _dir = { 0, 1 }; // fall straight down
        }
        else if (_dir.y == 1 && _pMap->isFloor(_newPosition)) // Mario is falling and about to hit a floor
        {
            if (_countFalling >= GameConfig::NUM_OF_CHARS_FOR_MARIO_DIE) // if mario fell too far
            {
				_died = true; // Trigger Mario's death
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
    else // Update position if no collision occurs
    {
        _position = _newPosition;
    }
}

bool Mario::gotHit() const
{
    char currentChar = _pMap->getCharCurrentMap(_position);
    char nextChar = _pMap->getCharCurrentMap(_newPosition);
	if (currentChar == (char)GameConfig::utilKeys::EXPLOSION || currentChar == (char)GameConfig::utilKeys::BARREL ||
        nextChar == (char)GameConfig::utilKeys::EXPLOSION || nextChar == (char)GameConfig::utilKeys::BARREL)
	{
		return true;
	}
	return false;
}

bool Mario::rescuedPauline() const
{
    return _pMap->getCharOriginalMap(_position) == (char)GameConfig::utilKeys::PAULINE;
}



void Mario::reset()
{
    _position = Point(GameConfig::START_X_MARIO, GameConfig::START_Y_MARIO); // Reset Mario's position
    _countFalling = -1; // Reset falling counter
    _dir = { 0, 0 }; // Stop movement
    _died = false;
    _isJumping = false;
    _isFalling = false;
    _life--;
}