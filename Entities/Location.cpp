#include "Location.h"

#include <utility>
#include <algorithm>
#include <iostream>

Location::Location(bool isAvailable, std::string&& name, std::string&& description) : isAvailable(isAvailable), name(std::move(name)), description(std::move(description)), items() {}

Location::Location(Location&& other) noexcept : name(std::move(other.name)), description(std::move(other.description)), items(std::move(other.items)), isAvailable(other.isAvailable) {}

Location& Location::addItem(Item&& item) {
    items.emplace_back(std::move(item));

    return *this;
}

Location& Location::removeItem(const std::string& itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),[] (const Item& item) {
        return item.getName().empty();
    }),items.end());

    auto it = std::find_if(items.begin(), items.end(),[&itemName] (const Item& item) {
        return item.getName() == itemName;
    });

    if (it != items.end()) {
        items.erase(it);
    }

    return *this;
}

bool Location::isLocationAvailable() const {
    return isAvailable;
}

void Location::setLocationAvailable(const bool&& isRoomAvailable) {
    isAvailable = isRoomAvailable;
}

const std::string& Location::getName() const {
    return name;
}

std::vector<Item>& Location::getItems() {
    return items;
}


void Location::describe() const {
    std::cout << description << std::endl;
}

void Location::showAvailableItems(const std::string& location) const {
    std::cout << "All available items in the " << location << ":" << std::endl;

    for (const Item& item : items) {
        if (item.isItemAvailable()) {
            std::cout << "    " << item.getName() << std::endl;
        }
    }
}

Item* Location::findItemByName(const std::string& itemName) {
    for (Item& item : items) {
        if (item.getName() == itemName) {
            return &item;
        }
    }

    return nullptr;
}
