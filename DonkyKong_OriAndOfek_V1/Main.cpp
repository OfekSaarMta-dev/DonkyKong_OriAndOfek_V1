#pragma once

#include <iostream>
#include "menu.h"


int main()
{
    Menu menu;
    menu.show();
}


/*

BEFORE BARRELS, MAP SHOULD BE PERFECT (>,<,)

* change menu to game
* change show to menu
* remove cursor
* To do Point object instead of working with x ,y 
* 
* while falling after 5 chars the game will restart to original map and mirio will start from the begining and score will reduse by 1
* mario movement should be nicer
* mario should be able to climb ladder without staying on the floor
* after falling to fall only in dir_y
* when pressing ESC the game should freez and when pressing ESC again the game should continue
*/
