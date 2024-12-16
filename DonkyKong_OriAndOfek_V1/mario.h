#pragma once
#include "general.h"
#include "point.h"
#include "barrel.h"
#include "map.h"

using namespace std;

class Map; // Forward declaration
class Barrel; // Forward declaration

class Mario

{
private:

	Point _position; // Mario's position
	Point _newPosition; //Mario's potential new position, unused until being assigned
	GameConfig::Direction _dir{ 0, 0 }; // starting dir.x and dir.y // standing still
	Map* _pMap = nullptr; // Pointer to Map object
	Barrel* _pBarrel = nullptr; // Pointer to Barrel object

	int _jumpCounter = 0; // Counter for jump height
	int _countFalling = -1; 
	int _life = 3; // Mario's life counter
	bool _isJumping = false;
	bool _died = false;
	bool _isFalling = false;


	void draw(char ch) const;// Draw character at Mario's position
	

public:
	Mario() : _position(GameConfig::START_X_MARIO, GameConfig::START_Y_MARIO), _jumpCounter(0), _countFalling(-1), _life(3), _isJumping(false), _died(false), _isFalling(false) {}  // Constructor
	Mario(const Mario&) = delete; //delete Copy constructor - we do not want anyone to copy mario in any case!;
	Mario& operator=(const Mario&) = delete; //delete Copy assignment operator - we do not want anyone to do an assignmen on mario in any case!


	void draw() { draw('@'); }  // Draw Mario

	void erase(); // Erase Mario

	// Get functions
	int getX() const { return _position.getX(); } // Get Mario's x position
	int getY() const { return _position.getY(); } // Get Mario's y position
	int getLife() const { return _life; } // Get Mario's life counter
	bool getLifeStatus() const { return _died; } // Get Mario's life status
	
	//Set functions
	void setMap(Map& map) { _pMap = &map; }  // Set Map reference
	void setBarrel(Barrel* barrel) { _pBarrel = barrel; } // set Barrel reference


	void keyPressed(char key);  // Handle key press
	void jump();  // Perform jump action
	void climb(char key);  // Perform climb action
	void move();  // Move Mario
	bool gotHit()const; // Check if Mario got hit by a barrel or explosion 
	bool rescuedPauline() const; // Check if Mario tuched Pauline
	void reset();  // resets Mario in case he dies
};