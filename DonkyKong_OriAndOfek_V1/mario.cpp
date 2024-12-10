#include "mario.h"

void Mario::draw(char ch)// Draw character at Mario's position
{
    gotoxy(_position.getX(), _position.getY());
    cout << ch;
}

/*void Mario::drawLives() const
{
	gotoxy(17, 2); // Position to draw lives
    for (int i = 0; i < _life; ++i) 
    {
        cout << "# ";
    }
    cout << endl;
}

void Mario:: decreaseLife()
{
    if (_life > 0)
        _life--;
}*/

// Handles key presses to control Mario's actions
void Mario::keyPressed(char key)
{
	int currX = _position.getX();
	int currY = _position.getY();
    if (_pMap->isLadder(currX, currY + 1))
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
            if (!_pMap->isLadder(currX, currY) && _pMap->isFloor(currX, currY + 1))
            {
                jump();
            }
            else if (_pMap->isLadder(currX, currY))
            {
                climb(key);
            }
            break;

        case (char)GameConfig::movementKeys::DOWN:
            if (_pMap->isLadder(currX, currY + 2))
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

void Mario::jump()
{
    // Going up
    _dir.y = -1;
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
        if (_pMap->isLadder(_position.getX(), _position.getY() + 2))
        {
            this->erase();
            _position.setY(getY() + 2); // Move down two steps on ladder
        }
        _dir.y = 1; // Climb down
    }
}




// Moves Mario based on current direction and checks for collisions with edges or floors
void Mario::move()
{
    int currX = _position.getX();
    int currY = _position.getY();
    if(this->rescuedPauline())
    {
        _won = true;
    }
    else if (this->gotHit()) // mario got hit by a barrel or explosion
    {
		_died = true;
    }
    else
    {
        if (!_pMap->isFloor(currX, currY + 1) && _pMap->isSpace(currX, currY + 1)) // if mario isn't on floor, he is above space
        {
            if (_dir.y == -1) // if in the middle of jumping
            {
                if (_jumpCounter == 1) // if mario reaches peak of jump, fall
                {
                    _dir.y = 1;
					_count_falling++;
                    _jumpCounter = 0;
                }
                else
                    _jumpCounter++;
            }
            else // not in the middle of a jump
            {
                _dir.y = 1; // Free fall if there's no floor below Mario
                _count_falling++; // Count falling steps
            }
        }

        const int newX = currX + _dir.x;
        const int newY = currY + _dir.y;

        if (_pMap->isEdge(newX, newY) || _pMap->isFloor(newX, newY)) // Upon collision with edge/floor
        {
            if (_pMap->isLadder(currX, currY) && _dir.y == -1) // when Mario climbing up a ladder and hitting upper floor
            {
                _position.setY(currY - 2); // Move Mario above the floor
                _dir = { 0, 0 }; // and stop his movement
            }
            else if (_pMap->isSpace(currX, currY + 1)) // if mario walk on top of a hole in the floor
            {
                _dir = { 0, 1 }; // fall straight down
            }
            else if (_dir.y == 1 && _pMap->isFloor(newX, newY)) // Mario is falling and about to hit a floor
            {
                if (_count_falling >= GameConfig::NUM_OF_CHARS_FOR_MARIO_DIE) // if mario fell too far
                {
					_died = true; // Trigger Mario's death
                }
                else // if mario hit the floor but fell less than 5 chars
                {
                    _count_falling = -1; // reset falling counter
                    _dir.y = 0; // stop falling when hitting the floor and keep on moving in X axis
                }
            }
            else // if mario walked into a wall or edge
            {
                _dir = { 0, 0 }; // Stop movement
            }
        }
        else // Update position if no collision occurs
        {
            _position.setXY(newX, newY);
        }
    }
}

void Mario::reset()
{
	_position.setXY(GameConfig::START_X_MARIO, GameConfig::START_Y_MARIO); // Reset Mario's position
	_count_falling = -1; // Reset falling counter
	_dir = { 0, 0 }; // Stop movement
    _died = false;
    _life--;
}

bool Mario::gotHit()
{
    char currentChar = _pMap->getCharCurrentMap(_position.getX(), _position.getY());
	if (currentChar == (char)GameConfig::utilKeys::EXPLOSION || currentChar == (char)GameConfig::utilKeys::BARREL)
	{
		return true;
	}
	return false;
}

bool Mario::rescuedPauline()
{
    return _pMap->getCharOriginalMap(_position.getX(), _position.getY()) == (char)GameConfig::utilKeys::PAULINE;
}

void Mario::erase()
{
    int currX = _position.getX();
    int currY = _position.getY();
    char originalChar = _pMap->getCharOriginalMap(currX, currY);
    gotoxy(currX, currY);
    cout << originalChar; // Restore original character instead of erasing it with space.
}