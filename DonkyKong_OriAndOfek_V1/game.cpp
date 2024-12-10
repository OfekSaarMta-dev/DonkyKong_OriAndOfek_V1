#pragma once

#include "game.h"
#include <conio.h> // For kbhit and getch functions

using namespace std;

// Displays the main menu and handles user input for menu options.
void Game::menu()
{
    while (true)
    {
        MenuScreen();
        char choice = _getch();

        switch (choice)
        {
        case '1':
            system("cls");
            this->run(); // Start a new game session
            break;

        case '8':
            InstructionsScreen(); // Display game instructions
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

    mario.setMap(map);   // Link Mario to map
    mario.setBarrel(barrels); // Link Mario to Barrels array


    for (int i = 0; i < GameConfig::MAX_BARRELS; i++)
    {
        barrels[i] = Barrel();    // Create a barrel and assign it to the array
        barrels[i].setMap(map);   // Set the map for each barrel
    }

    bool isPaused = false;

    int activeBarrels = 0;
    int gameLoop = 0;


    while (mario.getLife() > 0 && !mario.getWinningStatus())
    {
        activeBarrels = this->get_gameActiveBarrels();
        gameLoop = this->get_gameLoop();

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

            // Draw active barrels
            for (int i = 0; i < activeBarrels; i++)
            {
                barrels[i].draw();
            }
            mario.draw();

            Sleep(GameConfig::MOVE_DELAY);

            for (int i = 0; i < activeBarrels; i++)
            {
                if (barrels[i].isExploded())
                {
                    barrels[i].clearExplosion();
                }
                else
                {
                    barrels[i].erase();
                }
            }
            mario.erase();

            for (int i = 0; i < activeBarrels; i++)
            {
                barrels[i].move();
            }

            mario.move();

            set_gameLoop(gameLoop + 1);
            // Activate a new barrel every 16 loops, up to MAX_BARRELS
            if (gameLoop >= 16) /// change to game config
            {
                if (activeBarrels < GameConfig::MAX_BARRELS)
                {
                    this->set_gameActiveBarrels(activeBarrels + 1);
                }
                set_gameLoop(0); // Reset the counter
            }

            if (mario.getLifeStatus()) //checking if mario dies // _died = true
            {
                this->resetStage(barrels, &mario, &map);
            }
        }
        else
        {
            Sleep(GameConfig::MOVE_DELAY);
        }
    }

    if (mario.getLife() == 0) // Game Over
    {
        gameOverScreen();
    }
    else // Mario Won
    {
        gameWinningScreen();
    }

}


void Game::InstructionsScreen()
{
    system("cls");

    // instructions layout screen
    const char* instructionScreen[GameConfig::GAME_HEIGHT] = {
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
        "Q                                                                              Q", // 1
        "Q                                                                              Q", // 2
        "Q                               Instructions:                                  Q", // 3
        "Q                                                                              Q", // 4
        "Q                               a/A - Move Left                                Q", // 5
        "Q                               d/D - Move Right                               Q", // 6
        "Q                               w/W - Jump/Climb Up                            Q", // 7
        "Q                               x/X - Climb Down                               Q", // 8
        "Q                               s/S - Stay                                     Q", // 9
        "Q                               ESC - Pause Game                               Q", // 10
        "Q                                                                              Q", // 11
        "Q                                                                              Q", // 12
        "Q                          Press any key to return to menu...                  Q", // 13
        "Q                                                                              Q", // 14
        "Q                                                                              Q", // 15
        "Q                                                                              Q", // 16
        "Q                                                                              Q", // 17
        "Q                                                                              Q", // 18
        "Q                                                                              Q", // 19
        "Q                                                                              Q", // 20
        "Q                                                                              Q", // 21
        "Q                                                                              Q", // 22
        "Q                                                                              Q", // 23
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
    };

    // Print the instruction layout to the console
    for (int i = 0; i < GameConfig::GAME_HEIGHT-1; ++i)
    {
        cout << instructionScreen[i] << endl;
    }
    cout << instructionScreen[GameConfig::GAME_HEIGHT - 1];
    // Wait for user input to return to the menu
    _ch = _getch();

    //return cursur to start 
}

void Game::MenuScreen()
{
    system("cls"); // Clear the screen
    // Menu layout screen
    const char* menuMap[GameConfig::GAME_HEIGHT] = {
     "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
     "Q                                                                              Q", // 1
     "Q                                                                              Q", // 2
     "Q                      WELCOME TO DONKEY KONG CLASSIC                          Q", // 3
     "Q                                                                              Q", // 4
     "Q                      Developed by: Ofek Saar & Ori Ratzabi                   Q", // 5
     "Q                                                                              Q", // 6
     "Q                       1. Start a New Game                                    Q", // 7
     "Q                       8. Instructions                                        Q", // 8
     "Q                       9. Exit                                                Q", // 9
     "Q                                                                              Q", // 10
     "Q                                                                              Q", // 11
     "Q                       Enter Your Choice:                                     Q", // 12
     "Q                                                                              Q", // 13
     "Q                       Prepare to Climb, Jump, and be amazed!                 Q", // 14
     "Q                                                                              Q", // 15
     "Q                                                                              Q", // 16
     "Q                                                                              Q", // 17
     "Q                                                                              Q", // 18
     "Q                                                                              Q", // 19
     "Q                                                                              Q", // 20
     "Q                                                                              Q", // 21
     "Q                                                                              Q", // 22
     "Q                                                                              Q", // 23
     "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
    };

    // Print the menu  to the console
    for (int i = 0; i < GameConfig::GAME_HEIGHT -1; ++i)
    {
        cout << menuMap[i] << endl;
    }
    cout << menuMap[GameConfig::GAME_HEIGHT -1];

}


void Game::gameOverScreen()
{
    system("cls"); // Clear the screen
    // Game Over screen layout
    const char* gameOverMap[GameConfig::GAME_HEIGHT] = {
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
        "Q                                                                              Q", // 1
        "Q                                                                              Q", // 2
        "Q                                                                              Q", // 3
        "Q                            G A M E   O V E R                                 Q", // 4
        "Q                                                                              Q", // 5
        "Q                                                                              Q", // 6
        "Q                         Better luck next time!                               Q", // 7
        "Q                                                                              Q", // 8
        "Q                                                                              Q", // 9
        "Q                  Press any key to return to the menu...                      Q", // 10
        "Q                                                                              Q", // 11
        "Q                                                                              Q", // 12
        "Q                                                                              Q", // 13
        "Q                                                                              Q", // 14
        "Q                                                                              Q", // 15
        "Q                                                                              Q", // 16
        "Q                                                                              Q", // 17
        "Q                                                                              Q", // 18
        "Q                                                                              Q", // 19
        "Q                                                                              Q", // 20
        "Q                                                                              Q", // 21
        "Q                                                                              Q", // 22
        "Q                                                                              Q", // 23
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
    };

    // Print the Game Over screen
    for (int i = 0; i < GameConfig::GAME_HEIGHT-1; ++i)
    {
        cout << gameOverMap[i] << endl;
    }
    cout << gameOverMap[GameConfig::GAME_HEIGHT - 1];
    // Wait for user input to return to the menu
    _ch = _getch();

    //check mario life restore ////////////////////
}

void Game::gameWinningScreen()
{
    system("cls"); // Clear the screen
    // Game Winning screen layout
    const char* winningScreenMap[GameConfig::GAME_HEIGHT] = {
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
        "Q                                                                              Q", // 1
        "Q                                                                              Q", // 2
        "Q                         W   W   III   N   N   !!!                            Q", // 3
        "Q                         W   W    I    NN  N   !!!                            Q", // 4
        "Q                         W W W    I    N N N   !!!                            Q", // 5
        "Q                          W W    III   N  NN   !!!                            Q", // 6
        "Q                                                                              Q", // 7
        "Q                                                                              Q", // 8
        "Q                                                                              Q", // 9
        "Q                      C O N G R A T U L A T I O N S !                         Q", // 10
        "Q                                                                              Q", // 11
        "Q                  The princess was rescued by the brave Mario                 Q", // 12
        "Q                                                                              Q", // 13
        "Q                    Press any key to return to the menu...                    Q", // 14
        "Q                                                                              Q", // 15
        "Q                                                                              Q", // 16
        "Q                           *   *   *   *   *   *                              Q", // 17
        "Q                            * * * * * * * * * *                               Q", // 18
        "Q                             *   *   *   *   *                                Q", // 19
        "Q                                                                              Q", // 20
        "Q                                                                              Q", // 21
        "Q                                                                              Q", // 22
        "Q                                                                              Q", // 23
        "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
    };

    // Print the Winning Screen
    for (int i = 0; i < GameConfig::GAME_HEIGHT-1; ++i)
    {
        cout << winningScreenMap[i] << endl;
    }
    cout << winningScreenMap[GameConfig::GAME_HEIGHT - 1];

    // Wait for user input to return to the menu
    _ch = _getch();
}

void Game::resetStage(Barrel* pBarrels, Mario* pMario, Map* pMap)
{
    for (int i = 0; i < _activeBarrels; ++i)
    {
        pBarrels[i].resetBarrel();
    }

    pMario->reset(); // mario died
    set_gameLoop(0);
    set_gameActiveBarrels(0);

    pMap->eraseLife(pMario->getLife() + 1);
    pMap->drawLife(pMario->getLife());
}



