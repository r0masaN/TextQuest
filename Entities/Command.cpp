#include "Command.h"

#include <utility>

Command::Command(std::string&& name, std::string&& usage, Command::Action&& action) : name(std::move(name)), usage(std::move(usage)), action(std::move(action)) {}

const std::string& Command::getName() const {
    return name;
}

const std::string& Command::getUsage() const {
    return usage;
}

void Command::execute(const std::string& parameter) const {
    action(parameter);
}
