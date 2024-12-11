#pragma once
#include "general.h"
#include "map.h"
#include "point.h"
#include "barrel.h"

using namespace std;

class Map;
class Barrel;
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
	bool _died = false;
	bool _isFalling = false;


	void draw(char ch) const;// Draw character at Mario's position
	

public:
	Mario() : _position(GameConfig::START_X_MARIO,GameConfig::START_Y_MARIO), _jumpCounter(0),_countFalling(-1), _life(3), _died(false), _isFalling(false) {}  // Constructor
	Mario(const Mario&) = delete;
	Mario& operator=(const Mario&) = delete;


	void draw() { draw('@'); }  // Draw Mario

	void erase(); // Erase Mario

	// Get functions
	int getX() const {return _position.getX();}
	int getY() const {return _position.getY();}
	int getLife() const { return _life; }
	bool getLifeStatus() const { return _died; }
	
	//Set functions
	void setMap(Map& map) { _pMap = &map; }  // Set Map reference
	void setBarrel(Barrel* barrel) { _pBarrel = barrel; } // set Barrel reference


	void keyPressed(char key);  // Handle key press
	void jump();  // Perform jump action
	void climb(char key);  // Perform climb action
	void move();  // Move Mario
	bool gotHit()const;
	bool rescuedPauline() const;
	void reset();  // Mario die
};