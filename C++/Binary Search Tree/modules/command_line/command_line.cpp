//
// Created by Franc on 29/11/2025.
//

#include <functional>
#include <iomanip>
#include <iostream>
#include <utility>
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

    void printHelp() const
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

    Command(CommandInfo&& info, Action&& action) : info(std::move(info)), args({}), action(std::move(action))
    {
    }

    Command(CommandInfo&& info, const std::vector<CommandInfo>& arguments,
            Action&& action) : info(std::move(info)), args(arguments), action(std::move(action))
    {
    };
};

class CommandLine
{
    std::vector<Command> commands;

    void executeCommand(const Tokens& tokens)
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

            if (command->args.size() != tokens.size() - 1)
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

    void printGeneralHelp() const
    {
        std::cout <<
            "Para obtener más información acerca de un comando, escriba help seguido del nombre de comando o use la bandera '-h' después del nombre del comando.\n";
        std::cout << std::left;
        for (const auto& command : commands)
        {
            std::cout << std::setw(15) << command.info.name << ' ' << command.info.description << '\n';
        }
        std::cout << std::right;
    }

    static Tokens tokenize(const std::string_view input)
    {
        Tokens tokens;

        bool in_word = false;
        for (const char c : input)
        {
            if (c == ' ')
            {
                in_word = false;
                continue;
            }

            if (!in_word)
            {
                in_word = true;
                tokens.emplace_back();
            }
            tokens.back().push_back(c);
        }
        return tokens;
    }

    const Command* findCommand(const std::string_view token) const
    {
        for (const auto& cmd : commands)
        {
            if (cmd.info.name == token)
                return &cmd;
        }

        return nullptr;
    }

public:
    bool running = true;

    explicit CommandLine(std::vector<Command> commands) : commands(std::move(commands))
    {
    }

    void processInput()
    {
        std::string input;
        std::getline(std::cin, input);

        const auto tokens = tokenize(input);
        if (tokens.empty())
            return;

        constexpr auto RED = "\033[0;31m";
        constexpr auto RESET = "\033[0m";
        try
        {
            executeCommand(tokens);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << RED << " Invalid stuff going on" << RESET << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << RED << e.what() << RESET << '\n';
        }
    }
};

void foo(...)
{
    std::cout << "Hello, World!\n";
}

int square(const int a)
{
    return a * a;
}

int main()
{
    const std::vector commands{
        Command(
            {"insert", "Inserta un número en el árbol."},
            {{"Valor", "El valor que se va a ingresar, no debe estár en el árbol."}},
            [](const Tokens& tokens)
            {
                const int val = std::stoi(tokens[0]);
                std::cout << "Square: " << square(val) << '\n';
            }
        ),

        Command({"search", "Busca un número en el árbol y muestra su ruta."}, {
                    {"Valor", "El valor que se va a buscar."}
                }, &foo),
        Command({"delete", "Elimina un número del árbol."}, {
                    {"Valor", "El valor que se va a eliminar, debe estár en el árbol"}
                }, &foo),
        Command({"inorder", "Inserta un número en el árbol."}, &foo),
        Command({"preorder", "Inserta un número en el árbol."}, &foo),
        Command({"postorder", "Inserta un número en el árbol."}, &foo),
        Command({"height", "Inserta un número en el árbol."}, &foo),
        Command({"size", "Inserta un número en el árbol."}, &foo),
        Command({"export", "Inserta un número en el árbol."}, &foo),
    };
    CommandLine cmd(commands);

    while (cmd.running)
    {
        std::cout << ">> ";
        cmd.processInput();
    }

    return 0;
}
