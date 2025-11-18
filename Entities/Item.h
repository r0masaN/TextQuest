#ifndef ITEM_H
#define ITEM_H

#include <functional>
#include <string>

class Item {
public:
    using Action = std::function<void()>;

private:
    bool isAvailable;
    std::string name;
    std::string description;
    Action action;

public:
    explicit Item(bool isAvailable, std::string&& name, std::string&& description, Action&& action);

    Item(Item&& other) noexcept;

    [[nodiscard]] Item& operator=(Item&& other) noexcept;

    [[nodiscard]] bool operator==(const Item& other) const;

    [[nodiscard]] bool isItemAvailable() const;

    void setItemAvailable(const bool&& isItemAvailable);

    [[nodiscard]] const std::string& getName() const;

    void describe() const;

    void interact() const;
};

#endif
