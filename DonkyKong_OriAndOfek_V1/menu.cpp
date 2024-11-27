#pragma once

#include "menu.h"
#include "gameConfig.h"
#include "map.h"
#include "mario.h"

#include <iostream>
#include <conio.h> // for kbhit+getch
#include <Windows.h>


using namespace std;

void Menu::show()
{
    while (true)
    {
        system("cls");
        cout << "Donkey Kong\n";
        cout << "1. Start a new game\n";
        cout << "8. Instructions\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        char choice = _getch();
        switch (choice)
        {
        case '1':
        {
            system("cls");
            this->run();
        }
        break;
        case '8':
            showInstructions();
            break;
        case '9':
            return;


        }
    }
}

void Menu::run()
{
    Map map;
    map.reset();
	map.print();
    Mario mario;
	mario.setMap(map);
    map.setMario(mario);

    while (true)
    {
		mario.draw();
        if (_kbhit())
        {
            char keyPressed = _getch();
            if (keyPressed == (char)GameConfig::utilKeys::ESC)
                break;
			mario.keyPressed(keyPressed);
        }
		Sleep(GameConfig::MOVE_DELAY);
        mario.erase();
        map.drawChar(mario.getX(), mario.getY());
		//Sleep(GameConfig::MOVE_DELAY);
		mario.move();
    }
}

