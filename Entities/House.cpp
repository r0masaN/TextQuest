#include "House.h"

#include <iostream>

House::House() = default;

House& House::addLocation(Location&& location) {
    this -> locations.emplace_back(std::move(location));

    return *this;
}

void House::showAvailableLocations() const {
    std::cout << "All available locations:" << std::endl;
    for (const Location& room : this -> locations) {
        if (room.isLocationAvailable()) {
            std::cout << "    " << room.getName() << std::endl;
        }
    }
}

Location* House::findLocationByName(const std::string& locationName) {
    for (Location& location : this -> locations) {
        if (location.getName() == locationName) {
            return &location;
        }
    }

    return nullptr;
}
