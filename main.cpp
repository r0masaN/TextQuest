#include "Entities\Game.h"

#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Game game;
    game.startGame();

    std::string commandLine;
    while (1) {
        std::cout << "> ";
        std::getline(std::cin, commandLine);
        game.execCommandFromLine(commandLine);
    }

    return 0;
}
