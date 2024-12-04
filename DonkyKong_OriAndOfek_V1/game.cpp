#pragma once

#include "game.h"
#include "gameConfig.h"
#include "map.h"
#include "mario.h"
#include "Barrel.h"

#include <iostream>
#include <conio.h> // For kbhit and getch functions
#include <Windows.h>

using namespace std;

// Displays the main menu and handles user input for menu options.
void Game::menu()
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
void Game::run()
{
    Map map;
    map.reset();   // Reset map to initial state
    map.print();   // Print map to console

    Mario mario;
    Barrel barrel;

    mario.setMap(map);   // Link Mario to map for interaction
    barrel.setMap(map);   // Link Barrel to map for interaction


	bool isRunning = true;
	bool isPaused = false;

    while (isRunning)
    {
        if (_kbhit())
        { // Check if a key has been pressed
            char keyPressed = _getch(); // Get pressed key

            if (keyPressed == (char)GameConfig::utilKeys::ESC) // pressing ESC
            {
                if (!isPaused)
                {
                    // Pause
                    isPaused = true;
                    system("CLS"); // Clear the screen for pause message
                    cout << "Game Paused. Press ESC to resume..." << endl;
                    cout << "Enjoy so Far????"<< endl;
                    // while (_getch() != (char)GameConfig::utilKeys::ESC) //       to decide if good or bad
                }
                else
                {
                    // Unpause
                    isPaused = false;
                    system("CLS"); // Clear the screen when resuming
                    map.print();   // Redraw the map
                    mario.draw();  // Redraw Mario where he left off
                    barrel.draw(); // Redraw barrel where he left off
                }
                continue;
            }

            if (!isPaused) // the game is running 
            {
                mario.keyPressed(keyPressed);
            }
        }

        if (!isPaused) // running 
        {
            mario.draw(); 
            barrel.draw();

            Sleep(GameConfig::MOVE_DELAY); 

            mario.erase();
            barrel.erase();

            mario.move(); 
            barrel.move();
        }
       else 
       {
            Sleep(100); 
       }
    }


}

void Game::showInstructions()
{
    system("cls");
    std::cout << "Instructions:\n";
    std::cout << "a/A - Move Left\n";
    std::cout << "d/D - Move Right\n";
    std::cout << "w/W - Jump/Climb Up\n";
    std::cout << "x/X - Climb Down\n";
    std::cout << "s/S - Stay\n";
    std::cout << "ESC - Pause Game\n";
    std::cout << "\nPress any key to return to menu...";
    ch = _getch();
}