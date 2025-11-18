#ifndef HOUSE_H
#define HOUSE_H

#include "Location.h"

#include <vector>

class House {
private:
    std::vector<Location> locations;

public:
    House();

    House& addLocation(Location&& location);

    void showAvailableLocations() const;

    [[nodiscard]] Location* findLocationByName(const std::string& locationName);
};

#endif
