//
// Created by Franc on 29/11/2025.
//

#pragma once

#include "command.hpp"

class CommandLine
{
    std::vector<Command> commands;

    void executeCommand(const Tokens& tokens);

    void printGeneralHelp() const;

    static Tokens tokenize(std::string_view input);

    const Command* findCommand(std::string_view token) const;

public:
    bool running = true;

    explicit CommandLine(std::vector<Command> commands) : commands(std::move(commands))
    {
    }

    void processInput();
};
