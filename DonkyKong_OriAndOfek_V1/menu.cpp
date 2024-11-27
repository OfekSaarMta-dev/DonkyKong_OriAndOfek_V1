#pragma once

#include "menu.h"
#include "gameConfig.h"
#include "map.h"
#include "mario.h"

#include <iostream>
#include <conio.h> // For kbhit and getch functions
#include <Windows.h>

using namespace std;

// Displays the main menu and handles user input for menu options.
void Menu::show()
{
    while (true)
    {
        system("cls"); // Clear screen for menu display
        cout << "Donkey Kong\n";
        cout << "1. Start a new game\n";
        cout << "8. Instructions\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        char choice = _getch(); // Get user input without echoing to console

        switch (choice)
        {
        case '1':
            system("cls");
            this->run(); // Start a new game session
            break;

        case '8':
            showInstructions(); // Display game instructions
            break;

        case '9':
            return; // Exit menu loop and end program

        default:
            break; // Ignore invalid inputs
        }
    }
}

// Runs the main game loop where Mario interacts with the map.
void Menu::run()
{
    Map map;
    map.reset();   // Reset map to initial state
    map.print();   // Print map to console

    Mario mario;
    mario.setMap(map);   // Link Mario to map for interaction

    map.setMario(mario);   // Link map to Mario for interaction

    while (true)
    {
        mario.draw();   // Draw Mario at current position

        if (_kbhit())   // Check if a key has been pressed without blocking execution
        {
            char keyPressed = _getch();   // Get pressed key

            if (keyPressed == (char)GameConfig::utilKeys::ESC)
                break;   // Exit game loop on ESC key press

            mario.keyPressed(keyPressed);   // Handle key press event for Mario's actions
        }

        Sleep(GameConfig::MOVE_DELAY);   // Delay to control game speed

        mario.erase();   // Erase previous Mario position before updating

        map.drawChar(mario.getX(), mario.getY());   // Redraw character at updated position

        mario.move();   // Update Mario's position based on current direction and interactions with map elements.
    }
}