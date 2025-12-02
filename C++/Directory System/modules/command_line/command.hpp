//
// Created by Franc on 30/11/2025.
//

#pragma once
#include <functional>
#include <string>
#include <vector>

using Tokens = std::vector<std::string>;
using Action = std::function<void(const Tokens&)>;

struct CommandInfo
{
    std::string name;
    std::string description;
};

struct Argument
{
    std::string name;
    std::string description;
    bool optional = false; // Note: Command must be flagged as variadic, this is only for formatting purposes.
};

class Command
{
public:
    CommandInfo info;
    std::vector<Argument> args;
    Action action;
    bool variadic = false; // Takes undefined amount of arguments

    void printHelp() const;

    Command(CommandInfo&& info, const Action& action) : info(std::move(info)), args({}), action(action)
    {
    }

    Command(CommandInfo&& info, Action&& action) : info(std::move(info)), args({}), action(std::move(action))
    {
    }

    Command(CommandInfo&& info, const std::vector<Argument>& arguments,
            Action&& action) : info(std::move(info)), args(arguments), action(std::move(action))
    {
    }

    Command(CommandInfo&& info, const std::vector<Argument>& arguments,
            Action&& action, const bool is_variadic) : info(std::move(info)), args(arguments),
                                                       action(std::move(action)), variadic(is_variadic)
    {
    }
};
