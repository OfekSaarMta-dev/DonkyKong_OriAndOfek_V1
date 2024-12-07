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
    if (_pMap->getCharOriginalMap(_position.getX(), _position.getY() + 1) == (char)GameConfig::utilKeys::LADDER)
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
            if (_pMap->getCharOriginalMap(_position.getX(), _position.getY()) != (char)GameConfig::utilKeys::LADDER &&
                _pMap->isFloor(_position.getX(), _position.getY() + 1)) 
            {
                jump();
            }
            else if (_pMap->getCharOriginalMap(_position.getX(), _position.getY()) == (char)GameConfig::utilKeys::LADDER)
            {
                climb(key);
            }
            break;

        case (char)GameConfig::movementKeys::DOWN:
            if (_pMap->getCharOriginalMap(_position.getX(), _position.getY() + 2) == (char)GameConfig::utilKeys::LADDER)
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
        if (_pMap->getCharOriginalMap(_position.getX(), _position.getY() + 2) == (char)GameConfig::utilKeys::LADDER)
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
    /*if (position mario == position barrel || position mario == erea of the explosion '*')
    {
		die();
	}*/

    // Check if Mario is on the floor 
    if (!_pMap->isFloor(_position.getX(), _position.getY() + 1) && // If there's no floor below Mario
        _pMap->getCharOriginalMap(_position.getX(), _position.getY() + 1) == (char)GameConfig::utilKeys::SPACE) //he is not on ladder which means there is space below him
    {
        if(_dir.y == -1) // if in the middle of jumping
        {
            if (_jumpCounter == 1) // if mario reaches peak of jump, fall
            {
				_dir.y = 1;
                _jumpCounter = 0;
            }                     
            else                  
                _jumpCounter++;   
        }
        else // not in the middle of a jump
        {
            _dir.y = 1; // Free fall if there's no floor below Mario
        }
        _count_falling++; // Count falling steps
    }
    else // new 
    {
        // Mario lands on the floor
        if (_count_falling >= GameConfig::NUM_OF_CHARS_FOR_MARIO_DIE && _pMap->getCharOriginalMap(_position.getX(), _position.getY() + 1) == (char)GameConfig::utilKeys::FLOOR)
        {
            die(); // Trigger Mario's death
        }

        _count_falling = 0; // Reset falling count when hitting the floor if he is not dead;
    }

    const int newX = _position.getX() + _dir.x;
    const int newY = _position.getY() + _dir.y;

    if (_pMap->getCharOriginalMap(newX, newY) == (char)GameConfig::utilKeys::EDGE ||
        _pMap->isFloor(newX, newY)) // Upon collision with edge
    {
        if (_pMap->getCharOriginalMap(_position.getX(), _position.getY()) == (char)GameConfig::utilKeys::LADDER && _dir.y == -1) // when Mario climbing up a ladder and hitting upper floor
        {
            _position.setY(getY() - 2); // Move Mario avove the floor
            _dir = { 0, 0 };
        }
        else if (_pMap->getCharOriginalMap(getX(), getY() + 1) == (char)GameConfig::utilKeys::SPACE) // if mario walk onto a hole in the floor
        {
			_dir = { 0, 1 }; // fall straight down
        }
        else if (_dir.y == 1)
        {
			_dir.y = 0; // stop falling when hitting the floor and keep on moving in X axis
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

void Mario::die()
{
	_position.setXY(GameConfig::START_X_MARIO, GameConfig::START_Y_MARIO); // Reset Mario's position
	_count_falling = 0; // Reset falling counter
	_dir = { 0, 0 }; // Stop movement
	_jumpCounter = 0; // Reset jump counter
	_pMap->reset(); // Reset map

    system("cls"); // Clear console screen
    
	_pMap->print(); // Print map


	/*if (_life > 0)
	{
		decreaseLife(); // Decrease life count
	}
	else
	{
		cout << "Game Over!" << endl;
		

	}*/
}

void Mario::erase()
{
    char originalChar = _pMap->getCharOriginalMap(_position.getX(), _position.getY());
    gotoxy(_position.getX(), _position.getY());
    cout << originalChar; // Restore original character instead of erasing it with space.
}