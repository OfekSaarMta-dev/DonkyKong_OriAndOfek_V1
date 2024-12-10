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
	GameConfig::Direction _dir{ 0, 0 }; // starting dir.x and dir.y // standing still
	Map* _pMap = nullptr; // Pointer to Map object
	Barrel* _pBarrel = nullptr; // Pointer to Barrel object

	int _jumpCounter = 0; // Counter for jump height
	int _count_falling = -1;
	int _life; // Mario's life counter
	bool _died = false;

	void draw(char ch);// Draw character at Mario's position
	

public:
	Mario() : _position(GameConfig::START_X_MARIO,GameConfig::START_Y_MARIO), _jumpCounter(0),_count_falling(-1), _life(3) {}  // Constructor
	Mario(const Mario&) = delete;
	Mario& operator=(const Mario&) = delete;


	void draw() { draw('@'); }  // Draw Mario
	void drawLives() const;  // Draw Mario's lives
	void decreaseLife();  // Decrease Mario's life
	void erase(); // Erase Mario

	// Getters for position and life
	int getX() {return _position.getX();}
	int getY() {return _position.getY();}
	int getLife() const { return _life; }
	bool getStatus() const { return _died; }



	void keyPressed(char key);  // Handle key press
	void jump();  // Perform jump action
	void climb(char key);  // Perform climb action
	void move();  // Move Mario
	void setMap(Map& map) { _pMap = &map; }  // Set Map reference
	void setBarrel(Barrel* barrel) { _pBarrel = barrel; } // set Barrel reference
	void die();  // Mario die
	bool gotHit();
};