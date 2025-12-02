//
// Created by Franc on 01/12/2025.
//

#include "directory_system.hpp"

#include <iostream>

#include "command.hpp"

std::vector<Command> DirectorySystem::createCommands()
{
    return std::vector{
        Command(
            {"mkdir", "Creates a new directory"},
            {{"Name(s)", "One or many(space separated) names for the new directories."}},
            [this](const Tokens& tokens) { makeDirectory(tokens); }
        )
    };
};

DirectorySystem::DirectorySystem() : cmd(createCommands())
{
}

DirectorySystem::~DirectorySystem() = default;

void DirectorySystem::run()
{
    while (cmd.running)
    {
        std::cout << current_directory->getPath() <<  "/> ";
        cmd.processInput();
        std::cout << std::endl;
    }
}
