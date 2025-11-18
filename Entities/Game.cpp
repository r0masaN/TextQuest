#include "Game.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>

Game::Game() : inventory() {
    house.addLocation(std::move(Location(true, "Desolate Street",
                                         "A once-busy street now lies silent, with cars abandoned and nature slowly reclaiming the concrete.")
                                        .addItem(Item(true, "Backpack",
                                                      "An old, worn backpack lying against a streetlamp.",
                                                      [this] () -> void {
                                                          std::cout
                                                                  << "Inside, you find a 'Water Bottle' and a 'Map of the Neighborhood'."
                                                                  << std::endl;

                                                          Item *item = currentRoom->findItemByName("Water Bottle");
                                                          if (item != nullptr) {
                                                              item->setItemAvailable(true);
                                                          }

                                                          item = currentRoom->findItemByName("Map of the Neighborhood");
                                                          if (item != nullptr) {
                                                              item->setItemAvailable(true);
                                                          }
                                                      }))

                                        .addItem(Item(true, "Newspaper Clipping",
                                                      "A piece of newspaper, fluttering in the wind, caught on a fence.",
                                                      [] () -> void {
                                                          std::cout
                                                                  << "The article speaks of sudden disappearances across the city. Hints at the mystery surrounding the empty world."
                                                                  << std::endl;
                                                      }))

                                        .addItem(Item(false, "Water Bottle",
                                                      "A piece of newspaper, fluttering in the wind, caught on a fence.",
                                                      [] () -> void {
                                                          std::cout
                                                                  << "Essential for staying hydrated during exploration. May be refillable at a source in the house."
                                                                  << std::endl;
                                                      }))

                                        .addItem(Item(false, "Map of the Neighborhood",
                                                      "Found inside the Backpack on the Desolate Street.",
                                                      [] () -> void {
                                                          std::cout
                                                                  << "Provides clues to locations around the house that may hold valuable resources or secrets."
                                                                  << std::endl;
                                                      }))))

            .addLocation(std::move(Location(true, "Dusty Living Location",
                                            "Layers of dust cover the once cozy furniture. Sunlight barely pierces through the dirty windows.")
                                           .addItem(Item(true, "Old Photograph",
                                                         "A faded photograph of the house in better times, with a family smiling.",
                                                         [this] () -> void {
                                                             std::cout
                                                                     << "Flipping it over reveals a note: 'The key is under the third floorboard.'"
                                                                     << std::endl;

                                                             Item *item = currentRoom->findItemByName("Rusty Key");
                                                             if (item != nullptr) {
                                                                 item->setItemAvailable(true);
                                                             }
                                                         }))

                                           .addItem(Item(true, "Locked Box",
                                                         "A small, intricate box that refuses to open.",
                                                         [this] () -> void {
                                                             Item *item = inventory.findItemByName("Rusty Key");

                                                             if (item != nullptr) {
                                                                 std::cout
                                                                         << "Using the 'Rusty Key' unlocks the box, revealing a 'Flashlight'"
                                                                         << std::endl;
                                                                 inventory.removeItem("Rusty Key");
                                                                 currentRoom->removeItem("Locked Box");

                                                                 item = currentRoom->findItemByName("Flashlight");
                                                                 if (item != nullptr) {
                                                                     item->setItemAvailable(true);
                                                                 }

                                                             } else {
                                                                 std::cout
                                                                         << "You tried to open the box, but nothing happened."
                                                                         << std::endl;
                                                             }
                                                         }))

                                           .addItem(Item(false, "Rusty Key",
                                                         "A key found under the third floorboard in the Dusty Living Location.",
                                                         [this] () -> void {
                                                             Item *item = inventory.findItemByName("Locked Box");

                                                             if (item != nullptr) {
                                                                 std::cout
                                                                         << "Using the 'Rusty Key' unlocks the 'Locked Box', revealing a 'Flashlight'"
                                                                         << std::endl;
                                                                 inventory.removeItem("Locked Box");
                                                                 currentRoom->removeItem("Rusty Key");

                                                                 item = currentRoom->findItemByName("Flashlight");
                                                                 if (item != nullptr) {
                                                                     item->setItemAvailable(true);
                                                                 }

                                                             } else {
                                                                 std::cout
                                                                         << "You tried to open the box, but nothing happened."
                                                                         << std::endl;
                                                             }
                                                         }))

                                           .addItem(Item(false, "Flashlight",
                                                         "Found inside the Locked Box in the Dusty Living Location.",
                                                         [this] () -> void {
                                                             std::cout << "Can be used to explore dark areas."
                                                                       << std::endl;

                                                             Location *room = house.findLocationByName("Silent Bedroom");
                                                             if (room != nullptr) {
                                                                 room->setLocationAvailable(true);
                                                             }

                                                             room = house.findLocationByName("Basement");
                                                             if (room != nullptr) {
                                                                 room->setLocationAvailable(true);
                                                             }
                                                         }))));

    commands = {
            Command("exit", "\"exit\" --- Exit the game.", [] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    std::cout << "Exiting the game." << std::endl;
                    exit(0);
                }
            }),

            Command("help", "\"help\" --- Show all allowed commands.", [this] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    std::cout << "Allowed commands:" << std::endl;
                    for (const Command& command: commands) {
                        std::cout << "    " << command.getUsage() << std::endl;
                    }
                }
            }),

            Command("show inventory", "\"show inventory\" --- Show all items in the inventory.", [this] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    inventory.describe();
                }
            }),

            Command("go to", "\"go to <the location>\" --- Move to the selected location.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the location to go to." << std::endl;

                } else {
                    Location* targetRoom = house.findLocationByName(parameter);

                    if (targetRoom != nullptr && targetRoom->isLocationAvailable()) {
                        currentRoom = targetRoom;
                        std::cout << "You came into the " << parameter << "." << std::endl;

                    } else {
                        std::cout << "There is no " << parameter << " in the territory." << std::endl;
                    }
                }
            }),

            Command("put in inventory", "\"put in inventory <the item from the current location>\" --- Put the selected item in the inventory.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item to put in the inventory." << std::endl;

                } else {
                    auto it = std::find_if(currentRoom -> getItems().begin(), currentRoom -> getItems().end(), [&] (const Item& product)  -> bool {
                        return product.getName() == parameter && product.isItemAvailable();
                    });

                    if (it != currentRoom -> getItems().end()) {
                        inventory.getItems().emplace_back(std::move(*it));
                        currentRoom -> getItems().erase(it);
                        std::cout << "You put the " << parameter << " in the inventory." << std::endl;

                    } else {
                        std::cout << "There is no " << parameter << " in the " << currentRoom -> getName() << "." << std::endl;
                    }
                }
            }),

            Command("remove from inventory", "\"remove from inventory <the item from the inventory>\" --- Remove the selected item from the inventory.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item to remove from the inventory." << std::endl;

                } else {
                    Item* targetItem = inventory.findItemByName(parameter);

                    if (targetItem != nullptr) {
                        currentRoom -> addItem(std::move(*targetItem));
                        inventory.removeItem(parameter);
                        std::cout << "You removed the " << parameter << " from the inventory." << std::endl;

                    } else {
                        std::cout << "There is no " << parameter << " in the inventory." << std::endl;
                    }
                }
            }),

            Command("inspect in location", "\"inspect in location <the item from the current location>\" --- Inspect the selected item from the current location.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item from the current location to inspect." << std::endl;

                } else {
                    Item* targetItem = currentRoom -> findItemByName(parameter);

                    if (targetItem != nullptr && targetItem -> isItemAvailable()) {
                        targetItem -> describe();

                    } else {
                        std::cout << "There is no " << parameter << " in the " << currentRoom << "." << std::endl;
                    }
                }
            }),

            Command("inspect in inventory", "\"inspect in inventory <the item from the inventory>\" --- Inspect the selected item from the inventory.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item from the inventory to inspect." << std::endl;

                } else {
                    Item* targetItem = inventory.findItemByName(parameter);

                    if (targetItem != nullptr) {
                        targetItem -> describe();

                    } else {
                        std::cout << "There is no " << parameter << " in the inventory." << std::endl;
                    }
                }
            }),

            Command("inspect location", "\"inspect location\" --- Inspect the current location.", [this] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    currentRoom -> describe();
                }
            }),

            Command("show all locations", "\"show all locations\" --- Show all available locations.", [this] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    house.showAvailableLocations();
                }
            }),

            Command("show all items in location", "\"show all items in location\" --- Show all available items in the current location.", [this] (const std::string &parameter) -> void {
                if (!parameter.empty()) {
                    std::cout << "This command doesn't need any parameters." << std::endl;
                } else {
                    currentRoom -> showAvailableItems(currentRoom -> getName());
                }
            }),

            Command("interact in location with", "\"interact in location with <the item from the current location>\" --- Interact with the item from the current location.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item from the current location to interact." << std::endl;

                } else {
                    Item* targetItem = currentRoom -> findItemByName(parameter);

                    if (targetItem != nullptr && targetItem -> isItemAvailable()) {
                        targetItem -> interact();

                    } else {
                        std::cout << "There is no " << parameter << " in the " << currentRoom << "." << std::endl;
                    }
                }
            }),

            Command("interact in inventory with", "\"interact in inventory with <the item from the inventory>\" --- Interact with the item from the inventory.", [this] (const std::string &parameter) -> void {
                if (parameter.empty()) {
                    std::cout << "Select the item from the inventory to interact." << std::endl;

                } else {
                    Item* targetItem = inventory.findItemByName(parameter);

                    if (targetItem != nullptr) {
                        targetItem -> interact();

                    } else {
                        std::cout << "There is no " << parameter << " in the inventory." << std::endl;
                    }
                }
            })
    };

    currentRoom = house.findLocationByName("Desolate Street");
}

void Game::startGame() const {
    std::cout << "You are standing now on the " << currentRoom -> getName() << "." << std::endl;
    std::cout << "(write \"help\" for more options)" << std::endl;
}

void Game::execCommandFromLine(std::string& commandLine) const {
    if (!commandLine.empty()) {
        std::cout << std::endl;

        bool isCommandFound = false;

        std::string parameterLine;
        size_t beginPosition = commandLine.find('<');
        size_t endPosition = commandLine.find('>');

        if (beginPosition != std::string::npos && endPosition != std::string::npos && endPosition > beginPosition) {
            parameterLine = commandLine.substr(beginPosition + 1, endPosition - beginPosition - 1);
            commandLine = commandLine.substr(0, beginPosition - 1);
        } else {
            parameterLine = "";
        }

        Game::cleanString(commandLine);
        Game::cleanString(parameterLine);

        for (const Command& command : commands) {
            if (commandLine == command.getName()) {
                command.execute(parameterLine);
                isCommandFound = true;
                break;
            }
        }

        if (!isCommandFound) {
            std::cout << "Unknown command. Write \"help\" for more options" << std::endl;
        }
    }
}

void Game::cleanString(std::string& inputString) {
    auto new_end = std::unique(inputString.begin(), inputString.end(), [] (char a, char b) {
        return std::isspace(a) && std::isspace(b);
    });
    inputString.erase(new_end, inputString.end());

    size_t start = inputString.find_first_not_of(' ');
    size_t end = inputString.find_last_not_of(' ');

    if (start != std::string::npos && end != std::string::npos) {
        inputString = inputString.substr(start, end - start + 1);
    } else if (start == std::string::npos) {
        inputString.clear();
    }
}

// better variant
/*
void Game::cleanString(std::string& inputString) {
    inputString.erase(
            std::unique(
                    inputString.begin(),
                    inputString.end(),
                    [](const char& a, const char& b) noexcept -> bool {
                        return std::isspace(a) && std::isspace(b);
                    }
            ),
            inputString.end()
    );

    if (inputString.starts_with(' ')) inputString.erase(inputString.begin());
    if (inputString.ends_with(' ')) inputString.pop_back();
}
*/
