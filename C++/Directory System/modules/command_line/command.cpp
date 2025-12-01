//
// Created by Franc on 30/11/2025.
//

#include "file.hpp"

#include <iostream>

void Command::printHelp() const
{
    std::cout << info.name << ' ';
    for (const auto& arg : args)
    {
        std::cout << '<' << arg.name << "> ";
    }
    std::cout << '\n' << info.description << '\n';

    for (const auto& arg : args)
    {
        std::cout << "\t" << arg.name << " : " << arg.description << "\n";
    }
}
