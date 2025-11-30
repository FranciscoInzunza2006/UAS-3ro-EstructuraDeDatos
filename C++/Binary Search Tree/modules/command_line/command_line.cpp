//
// Created by Franc on 29/11/2025.
//

#include <functional>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

typedef std::pair<std::string, std::string_view> StringPair;

class Command
{
public:
    StringPair command;
    std::function<void()> callback;
    std::vector<StringPair> params;

    void printHelp() const
    {
        std::cout << command.first << ' ';
        for (const auto & param : params)
        {
            std::cout << '<' << param.first << "> ";
        }
        std::cout << '\n' << command.second << '\n';

        for (const auto & param : params)
        {
            std::cout << "\t" << param.first << " : " << param.second << "\n";
        }
    }

    Command() = default;

    Command(StringPair command, std::function<void()> callback, const std::vector<StringPair>& params = {}) :
        command(std::move(command)), callback(std::move(callback)), params(params)
    {
    };
};

class CommandLine
{
    std::vector<Command> commands;

    static std::vector<std::string> split(const std::string_view str)
    {
        std::vector<std::string> tokens;

        bool in_word = false;
        for (const char c : str)
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

    const Command* getCommand(const std::string_view token) const
    {
        for (const auto & cmd : commands)
        {
            if (cmd.command.first == token)
                return &cmd;
        }


        return nullptr;
    }

    void runCommand(const std::vector<std::string>& tokens)
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
                printHelp();
                return;
            }

            if (tokens.size() > 2)
            {
                throw std::runtime_error("Too many arguments");
            }

            if (const auto command = getCommand(tokens[1]); command != nullptr)
            {
                command->printHelp();
                return;
            }

            throw std::runtime_error("Unknown command");
        }

        if (const auto command = getCommand(command_token); command != nullptr)
        {
            command->callback();
        }
        throw std::runtime_error("Unknown command");
    }

    static std::vector<std::string> parseCommand(const std::string_view input)
    {
        //const std::vector<std::string> tokens = split(input);
        return split(input);
    }

    void printHelp() const
    {
        std::cout << "Para obtener más información acerca de un comando, escriba -h después del comando.\n";
        std::cout << std::left;
        for (const auto & command : commands)
        {
            std::cout << std::setw(15) << command.command.first << command.command.second << '\n';
        }
        std::cout << std::right;
    }
public:
    explicit CommandLine(const std::vector<Command>& commands) : commands(commands)
    {
    }

    bool running = true;

    void read()
    {
        std::string input;
        //input = "   insert 10    ";
        std::getline(std::cin, input);

        const std::vector<std::string> tokens = parseCommand(input);
        if (tokens.empty())
            return;

        try
        {
            runCommand(tokens);
        } catch (const std::exception& e)
        {
            constexpr auto RED = "\033[0;31m";
            constexpr auto RESET = "\033[0m";
            std::cout << RED << e.what() << RESET << '\n';
        }

    }
};

bool foo()
{
    std::cout << "Hello, World!\n";
    return true;
}

int main()
{
    const std::vector commands = {
        Command({"insert", "Inserta un número en el árbol."}, &foo, {
            {"Valor", "El valor que se va a ingresar, no debe estár en el árbol."}
        }),
        Command({"search", "Busca un número en el árbol y muestra su ruta."}, &foo, {
            {"Valor", "El valor que se va a buscar."}
        }),
        Command({"delete", "Elimina un número del árbol."}, &foo, {
                {"Valor", "El valor que se va a eliminar, debe estár en el árbol"}
        }),
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
        cmd.read();
    }

    return 0;
}
