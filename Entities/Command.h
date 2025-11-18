#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <string>

class Command {
public:
    using Action = std::function<void(const std::string&)>;

private:
    std::string name;
    std::string usage;
    Action action;

public:
    explicit Command(std::string&& name, std::string&& usage, Action&& action);

    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] const std::string& getUsage() const;

    void execute(const std::string& parameter) const;
};

#endif
