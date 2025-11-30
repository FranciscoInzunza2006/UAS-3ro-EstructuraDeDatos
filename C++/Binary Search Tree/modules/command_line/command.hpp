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

class Command
{
public:
    CommandInfo info;
    std::vector<CommandInfo> args;
    Action action;

    void printHelp() const;

    Command(CommandInfo&& info, Action&& action) : info(std::move(info)), args({}), action(std::move(action))
    {
    }

    Command(CommandInfo&& info, const std::vector<CommandInfo>& arguments,
            Action&& action) : info(std::move(info)), args(arguments), action(std::move(action))
    {
    };
};
