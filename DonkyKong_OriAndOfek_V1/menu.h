#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>

class Menu {
    char ch;
private:
    void showInstructions()
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

public:

    void show();
    void run();

};







