#include "Inventory.h"

#include <algorithm>
#include <iostream>

Inventory::Inventory() = default;

Inventory& Inventory::addItem(Item&& item) {
    items.emplace_back(std::move(item));

    return *this;
}

Inventory& Inventory::removeItem(const std::string& itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),[] (const Item& item) {
        return item.getName().empty();
    }),items.end());

    auto it = std::find_if(items.begin(), items.end(),[&itemName](const Item& item) {
        return item.getName() == itemName;
    });

    if (it != items.end()) {
        items.erase(it);
    }

    return *this;
}

std::vector<Item>& Inventory::getItems() {
    return items;
}

void Inventory::describe() const {
    if (items.empty()) {
        std::cout << "Inventory is empty." << std::endl;
    } else {
        std::cout << "Items in inventory:" << std::endl;
        for (const Item& item : items) {
            std::cout << "    " << item.getName() << std::endl;
        }
    }
}

Item* Inventory::findItemByName(const std::string& itemName) {
    for (Item& item : items) {
        if (item.getName() == itemName) {
            return &item;
        }
    }

    return nullptr;
}
