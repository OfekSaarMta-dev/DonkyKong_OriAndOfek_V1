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

void Game::run()
{
    Map map;
    map.reset();   // Reset map to initial state
    map.print();   // Print map to console

    Mario mario;
    Barrel barrels[GameConfig::MAX_BARRELS];

    mario.setMap(map);   // Link Mario to map for interaction
    for (int i = 0; i < GameConfig::MAX_BARRELS; i++)
    {
        barrels[i] = Barrel();    // Create a barrel and assign it to the array
        barrels[i].setMap(map);   // Set the map for each barrel
    }

    bool isRunning = true;
    bool isPaused = false;

    int activeBarrels = 0;       // Tracks number of active barrels
    int gameLoopCounter = 0;     // Counter to control barrel activation

    while (isRunning)
    {
        if (_kbhit())
        {
            char keyPressed = _getch(); // Get pressed key

            if (keyPressed == (char)GameConfig::utilKeys::ESC) // pressing ESC
            {
                if (!isPaused)
                {
                    isPaused = true;
                    system("CLS"); // Clear the screen for pause message
                    cout << "Game Paused. Press ESC to resume..." << endl;
                    cout << "Enjoy so Far????" << endl;
                }
                else
                {
                    isPaused = false;
                    system("CLS"); // Clear the screen when resuming
                    map.print();   // Redraw the map
                    mario.draw();  // Redraw Mario
                    for (int i = 0; i < activeBarrels; i++)
                    {
                        barrels[i].draw();
                    }
                }
                continue;
            }

            if (!isPaused)// running 
            {
                mario.keyPressed(keyPressed);
            }
        }

        if (!isPaused) // the game is running
        {
            mario.drawLives(); // Show lives
            mario.draw();

            // Draw active barrels
            for (int i = 0; i < activeBarrels; i++)
            {
                barrels[i].draw();
            }

            Sleep(GameConfig::MOVE_DELAY);

            mario.erase();
            for (int i = 0; i < activeBarrels; i++)
            {
                barrels[i].erase();
            }

            mario.move();
            for (int i = 0; i < activeBarrels; i++)
            {
                barrels[i].move();
            }

            gameLoopCounter++;

            // Activate a new barrel every 16 loops, up to MAX_BARRELS
            if (gameLoopCounter >= 16) /// change to game config
            {
                if (activeBarrels < GameConfig::MAX_BARRELS)
                {
                    activeBarrels++;
                }
                gameLoopCounter = 0; // Reset the counter
            }
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