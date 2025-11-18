#ifndef GAME_H
#define GAME_H

#include "House.h"
#include "Inventory.h"
#include "Location.h"
#include "Command.h"

class Game {
private:
    House house;
    Inventory inventory;
    Location* currentRoom;
    std::vector<Command> commands;

public:
    explicit Game();

    void startGame() const;

    void execCommandFromLine(std::string& commandLine) const;

    static void cleanString(std::string& inputString);
};

#endif
