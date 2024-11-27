#include "mario.h"
#include "gameConfig.h"


void Mario::keyPressed(char key) 
{
	if (_pMap->getCharOriginalMap(_x, _y + 1) == (char)GameConfig::utilKeys::LADDER) // mario in the middle of a ladder
	{
		switch (std::tolower(key)) // options to climb up / down
		{
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
	else // mario is standing on a floor
	{
		switch (std::tolower(key))
		{

		case (char)GameConfig::movementKeys::LEFT: // case 0
			_dir = GameConfig::directions[0];
			break;

		case (char)GameConfig::movementKeys::RIGHT: // case 1
			_dir = GameConfig::directions[1];
			break;

		case (char)GameConfig::movementKeys::UP:// jump and climbing test // case 2
			if (_pMap->getCharOriginalMap(_x, _y) != (char)GameConfig::utilKeys::LADDER)
			{
				jump();
			}
			else if (_pMap->getCharOriginalMap(_x, _y) == (char)GameConfig::utilKeys::LADDER)
			{
				climb(key);
			}
			break;

		case (char)GameConfig::movementKeys::DOWN: // case 3
			if (_pMap->getCharOriginalMap(_x, _y + 2) == (char)GameConfig::utilKeys::LADDER)
			{
				climb(key);
			}
			break;

		case (char)GameConfig::movementKeys::STAY: // case 4
			_dir = GameConfig::directions[4];

		default:
			// invalid key, do nothing
			break;

		}
	}
	
}


void Mario::jump() // fix jump (lo lehikanes ba kir)
{
	if (_pMap->getCharOriginalMap(_x-1, _y) != (char)GameConfig::utilKeys::EDGE && _pMap->getCharOriginalMap(_x+1, _y) != (char)GameConfig::utilKeys::EDGE)
	{
		//Going up
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

		//Fall down
		_dir.y = 1;
		_y += _dir.y;
		this->draw();
		Sleep(GameConfig::JUMP_DURATION);
		this->erase();
		_y += _dir.y;
		_x += _dir.x;
		this->draw();

		_dir.y = 0;
	}
}

void Mario::climb(char key)
{
	if (key == (char)GameConfig::movementKeys::UP)
	{
			_dir.y = -1;
	}
	else //(key == (char)GameConfig::movementKeys::DOWN)
	{
		if(_pMap->getCharOriginalMap(_x, _y + 2) == (char)GameConfig::utilKeys::LADDER)
		{
			this->erase();
			_y += 2;
		}
		_dir.y = 1;
	}
}



void Mario::move()
{

	if (_pMap->getCharOriginalMap(_x, _y + 1) == (char)GameConfig::utilKeys::SPACE) // mario is free falling
	{
		_dir.y = 1;
	}
	int newX = _x + _dir.x;
	int newY = _y + _dir.y;

	// Better use a function in Map to check if the new position is valid

	if (_pMap->getCharCurrentMap(newX, newY) == (char)GameConfig::utilKeys::EDGE || _pMap->getCharCurrentMap(newX, newY) == (char)GameConfig::utilKeys::FLOOR)
	{
		if (_dir.y == -1)
		{
			_y += -2;
		}

		_dir = { 0, 0 };
	}
	else
	{
		_x = newX;
		_y = newY;
		//Sleep(GameConfig::MOVE_DELAY);
	}
}































/*

void Mario::draw(char ch)
{
	gotoxy(_x, _y);
	cout << ch;
}


bool Mario::isOnLadder(const Ladder* ladders)
{
	for (int i = 0; i < GameConfig::NUM_OF_LADDERS; i++)
	{
		const int ladder_x = ladders[i].getLadder_x();
		const int ladder_y = ladders[i].getLadder_y();
		const int ladder_height = ladders[i].getLadder_height();
		if ((_y < ladder_y && _y > ladder_y - ladder_height) && _x == ladder_x)
			return true;
	}
	return false;
}



void Mario::move(GameConfig::eKeys key)
{
	const int JUMP_HEIGHT = 2;
	const int JUMP_DURATION = 200;


	if (isOnLadder(_ladders))
	{
		switch (key)
		{
		case GameConfig::eKeys::UP:
			dir_x = 0;
			dir_y = -1;
			break;

		case GameConfig::eKeys::DOWN:
			dir_x = 0;
			dir_y = 1;
			break;

		case GameConfig::eKeys::STAY:
			dir_x = 0;
			dir_y = 0;
			break;
		}
		_x += dir_x;
		_y += dir_y;
		Sleep(JUMP_DURATION);
	}
	else
	{
		dir_y = GameConfig::DIR_Y;

		switch (key)
		{
		case GameConfig::eKeys::LEFT:
			dir_x = -1;
			dir_y = 0;
			break;

		case GameConfig::eKeys::RIGHT:
			dir_x = 1;
			dir_y = 0;
			break;

		case GameConfig::eKeys::UP:
			dir_y = -1;

			// Jump up
			for (int i = 1; i <= JUMP_HEIGHT; i++)
			{
				this->draw(' ');
				_y += dir_y;
				_x += dir_x;
				this->draw('@');
				Sleep(JUMP_DURATION);
			}

			// Hang in the air briefly
			Sleep(JUMP_DURATION);

			dir_y = 2;
			// Fall down
			this->draw(' ');
			_y += dir_y;
			Sleep(JUMP_DURATION);

			dir_y = 0;

			break;

		case GameConfig::eKeys::STAY:
			dir_x = 0;
			dir_y = 0;
			break;

		}
		_x += dir_x;
		_y += dir_y;

	}
}

*/