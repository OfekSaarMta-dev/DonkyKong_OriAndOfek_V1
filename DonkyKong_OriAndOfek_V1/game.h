#pragma once
#include "mario.h"
#include "Barrel.h"

class Mario;
class Barrel;



class Game {
private:
    char _ch ='\0';
	int _gameLoop = 0;
	int _activeBarrels = 0;

    void run();
    void MenuScreen();
    void InstructionsScreen();
    void gameOverScreen();
    void gameWinningScreen();
   
   
   

public:
    Game() : _ch('\0'), _gameLoop(0), _activeBarrels(0) {}
    Game(const Game&) = delete; 
    Game& operator=(const Game&) = delete; // Copy assignment operator

    void menu();
    void resetStage(Barrel* pBarrel, Mario* pMario, Map* pMap);

    int get_gameLoop() const { return _gameLoop; }
    int get_gameActiveBarrels() const { return _activeBarrels; }

    void set_gameLoop(int x) { _gameLoop = x; } 
    void set_gameActiveBarrels(int x) { _activeBarrels = x; }










};







