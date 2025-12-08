//
// Created by Franc on 29/11/2025.
//

#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>
#include "command_line.hpp"



void CommandLine::executeCommand(const Tokens& tokens)
{
    const std::string_view command_token = tokens[0];
    if (command_token == "exit")
    {
        running = false;
        return;
    }

    if (command_token == "help")
    {
        if (tokens.size() == 1)
        {
            printGeneralHelp();
            return;
        }

        if (tokens.size() > 2)
        {
            throw std::runtime_error("Too many arguments");
        }

        if (const auto command = findCommand(tokens[1]); command != nullptr)
        {
            command->printHelp();
            return;
        }

        throw std::runtime_error("Unknown command: " + std::string(command_token));
    }

    if (const auto command = findCommand(command_token); command != nullptr)
    {
        if (tokens.size() == 2 && tokens[1] == "-h")
        {
            command->printHelp();
            return;
        }

        if (!command->variadic && command->args.size() != tokens.size() - 1)
        {
            throw std::runtime_error(
                "Wrong number of arguments for command '" + std::string(command_token) +
                "'. Expected " + std::to_string(command->args.size()) + "."
            );
        }

        const auto args = std::vector(tokens.begin() + 1, tokens.end());
        command->action(args);

        return;
    }
    throw std::runtime_error("Unknown command: " + std::string(command_token));
}

void CommandLine::printGeneralHelp() const
{
    std::cout <<
        "Para obtener más información acerca de un comando, escriba help seguido del nombre del comando o use la bandera '-h' después del nombre del comando.\n";
    std::cout << std::left;
    for (const auto& command : commands)
    {
        std::cout << std::setw(15) << command.info.name << ' ' << command.info.description << '\n';
    }
    std::cout << std::right;
}

const Command* CommandLine::findCommand(const std::string_view token) const
{
    for (const auto& cmd : commands)
    {
        if (cmd.info.name == token)
            return &cmd;
    }

    return nullptr;
}

Tokens CommandLine::Tokenizer::tokenize(const std::string_view input)
{
    Tokens tokens;

    bool in_string = false;
    bool in_word = false;
    for (const char c : input)
    {
        if (c == ' ' && !in_string)
        {
            in_word = false;
            continue;
        }

        if (c == '"')
        {
            in_string = !in_string;
            continue;
        }

        if (!in_word)
        {
            in_word = true;
            tokens.emplace_back();
        }
        tokens.back().push_back(c);
    }

    if (in_string)
        throw std::runtime_error("Unclosed quotes in input");

    return tokens;
}

void CommandLine::processInput(const std::string_view input)
{
    Tokens tokens;
    try
    {
        tokens = Tokenizer::tokenize(input);
    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    if (tokens.empty())
        return;

    constexpr auto RED = "\033[0;31m";
    constexpr auto RESET = "\033[0m";
    try
    {
        executeCommand(tokens);
    }
    // catch (const std::invalid_argument&)
    // {
    //     std::cout << RED << "Valor invalido ingresado." << RESET << '\n';
    // }
    catch (const std::exception& e)
    {
        std::cout << RED << e.what() << RESET << '\n';
    }
}
