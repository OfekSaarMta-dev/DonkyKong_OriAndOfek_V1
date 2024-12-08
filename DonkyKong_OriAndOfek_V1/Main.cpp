#pragma once
#include "game.h"


int main()
{
    Game game;
    game.menu();
}


/*
* remove cursor
* be able to jump on ledder while moving  
* while falling after 5 chars the game will restart to original map and mirio will start from the begining and score will reduse by 1
* add life to mario in private
* add count falling to mario in private
* add block for copy ctor 
* 
* mario died and it will restart mario to start and take 1 life, if life = 0 (CLEAR SCREEN AND WRITE GAME OVER ADD 2 OPTIONS, 1 TO FINISH AND 2 TO TRY AGain
* 
* mario die when the barrel hit him and restart map, takes down a life
* add life to screen
* add colors to screen
* when mario touch dollar, wins the game and write a congratulations message, add option to restart game
* when life  = 0, game over and restart game
* add const to functions - go 1 by 1 to add const for example drow mario function....
* !!!!!!
* mario doesn't die when falling .... !!!!!!
* !!!!!!
* to check if our functions are to dependent on each other
* add dirr of mario and barrel to ctor
* change game.h all functions to private
**/ 
