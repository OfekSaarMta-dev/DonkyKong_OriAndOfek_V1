#include "mario.h"
#include "gameConfig.h"

// Handles key presses to control Mario's actions
void Mario::keyPressed(char key)
{
    if (_pMap->getCharOriginalMap(_x, _y + 1) == (char)GameConfig::utilKeys::LADDER) 
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

        case (char)GameConfig::movementKeys::UP: // Jump or climb test
            if (_pMap->getCharOriginalMap(_x, _y) != (char)GameConfig::utilKeys::LADDER) 
            {
                jump();
            }
            else if (_pMap->getCharOriginalMap(_x, _y) == (char)GameConfig::utilKeys::LADDER) 
            {
                climb(key);
            }
            break;

        case (char)GameConfig::movementKeys::DOWN:
            if (_pMap->getCharOriginalMap(_x, _y + 2) == (char)GameConfig::utilKeys::LADDER) 
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
    if (_pMap->getCharOriginalMap(_x - 1, _y) != (char)GameConfig::utilKeys::EDGE &&
        _pMap->getCharOriginalMap(_x + 1, _y) != (char)GameConfig::utilKeys::EDGE)
    {
        // Going up
        _dir.y = -1;
        this->erase();
        _x += _dir.x;
        for (int i = 1; i <= GameConfig::JUMP_HEIGHT; i++)
        {
            _y += _dir.y;
            this->draw();
            Sleep(GameConfig::JUMP_DURATION);
            this->erase();
        }

        // Falling down
        _dir.y = 1;
        _y += _dir.y;
        this->draw();
        Sleep(GameConfig::JUMP_DURATION);
        this->erase();
        _y += _dir.y;
        _x += _dir.x;
        this->draw();

        _dir.y = 0; // Reset vertical direction after jump
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
        if (_pMap->getCharOriginalMap(_x, _y + 2) == (char)GameConfig::utilKeys::LADDER)
        {
            this->erase();
            _y += 2; // Move down two steps on ladder
        }
        _dir.y = 1; // Climb down
    }
}

// Moves Mario based on current direction and checks for collisions with edges or floors
void Mario::move() 
{

    if (_pMap->getCharOriginalMap(_x, _y + 1) == (char)GameConfig::utilKeys::SPACE)
    {
        _dir.y = 1; // Free fall if there's space below Mario
    }
    int newX = _x + _dir.x;
    int newY = _y + _dir.y;

    if (_pMap->getCharCurrentMap(newX, newY) == (char)GameConfig::utilKeys::EDGE ||
        _pMap->getCharCurrentMap(newX, newY) == (char)GameConfig::utilKeys::FLOOR)
    {
        if (_dir.y == -1)
        {
            _y += -2; // Adjust position when hitting an edge while moving up
        }

        _dir = { 0, 0 }; // Stop movement upon collision with edge or floor
    }
    else
    {
        _x = newX; // Update position if no collision occurs
        _y = newY;
    }
}