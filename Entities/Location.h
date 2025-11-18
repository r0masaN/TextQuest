#ifndef LOCATION_H
#define LOCATION_H

#include "Item.h"

#include <string>
#include <vector>

class Location {
private:
    bool isAvailable;
    std::string name;
    std::string description;
    std::vector<Item> items;

public:
    explicit Location(bool isAvailable, std::string&& name, std::string&& description);

    Location(Location&& other) noexcept;

    Location& addItem(Item&& item);

    Location& removeItem(const std::string& itemName);

    [[nodiscard]] bool isLocationAvailable() const;

    void setLocationAvailable(const bool&& isRoomAvailable);

    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] std::vector<Item>& getItems();

    void describe() const;

    void showAvailableItems(const std::string& location) const;

    [[nodiscard]] Item* findItemByName(const std::string& itemName);
};

#endif
