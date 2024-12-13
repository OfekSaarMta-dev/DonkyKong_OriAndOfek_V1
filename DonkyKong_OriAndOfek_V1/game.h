#pragma once
#include "mario.h"
#include "Barrel.h"

class Mario; // Forward declaration
class Barrel; // Forward declaration



class Game {
private:
	char _ch = '\0'; // User input
	int _gameLoop = 0; // Game loop counter
	int _activeBarrels = 0; // Active barrels counter

	void run(); // Run the game
	void MenuScreen(); // Display the menu screen
	void InstructionsScreen(); // Display the instructions screen
	void gameOverScreen(); // Display the game over screen
	void gameWinningScreen(); // Display the winning screen
   
   
   

public:
	Game() : _ch('\0'), _gameLoop(0), _activeBarrels(0) {} // Constructor
	Game(const Game&) = delete;  // delete Copy constructor
    Game& operator=(const Game&) = delete; // delete Copy assignment operator

	void menu(); // Display the menu
	void resetStage(Barrel* pBarrel, Mario* pMario, Map* pMap); // Reset the stage (reset Mario, barrels and map (for lifes))

	int get_gameLoop() const { return _gameLoop; } // Get game loop
	int get_gameActiveBarrels() const { return _activeBarrels; } // Get active barrels

	void set_gameLoop(int x) { _gameLoop = x; } // Set game loop
	void set_gameActiveBarrels(int x) { _activeBarrels = x; } // Set active barrels










};







