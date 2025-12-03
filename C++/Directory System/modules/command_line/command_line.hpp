//
// Created by Franc on 29/11/2025.
//

#pragma once

#include "command.hpp"

class CommandLine
{
    const std::vector<Command> commands;

    void executeCommand(const Tokens& tokens);

    void printGeneralHelp() const;

    const Command* findCommand(std::string_view token) const;

public:
    bool running = true;

    void processInput();

    class Tokenizer
    {
    public:
        static Tokens tokenize(std::string_view input);
    };

    explicit CommandLine(std::vector<Command> commands) : commands(std::move(commands))
    {
    }

};
