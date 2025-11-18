#include "Item.h"

#include <utility>
#include <iostream>

Item::Item(bool isAvailable, std::string&& name, std::string&& description, Item::Action&& action) : isAvailable(isAvailable), name(std::move(name)), description(std::move(description)), action(std::move(action)) {}

Item::Item(Item&& other) noexcept : name(std::move(other.name)), description(std::move(other.description)), isAvailable(other.isAvailable), action(std::move(other.action)) {}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        description = std::move(other.description);
        isAvailable = other.isAvailable;
        action = std::move(other.action);
    }

    return *this;
}

bool Item::operator==(const Item& other) const {
    return name == other.name && description == other.description && isAvailable == other.isAvailable;
}

bool Item::isItemAvailable() const {
    return isAvailable;
}

void Item::setItemAvailable(const bool&& isItemAvailable) {
    isAvailable = isItemAvailable;
}

const std::string& Item::getName() const {
    return name;
}

void Item::describe() const {
    std::cout << description << std::endl;
}

void Item::interact() const {
    action();
}
