//
// Created by Franc on 29/11/2025.
//

#include <functional>
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

    bool runCommand(const Command& command, std::string_view str);

    bool parseCommand(const std::string_view input)
    {
        const std::vector<std::string> tokens = split(input);

        constexpr int COMMAND = 0;

        if (tokens[COMMAND] == "exit")
        {
            running = false;
            return true;
        }

        for (const Command& command : commands)
        {
            if (command.command.first == tokens[COMMAND])
            {
                command.callback();
                return true;
            }
        }

        return true;
    }

public:
    explicit CommandLine(const std::vector<Command>& commands) : commands(commands)
    {
    }

    bool running = true;

    bool read()
    {
        std::string input;
        //input = "   insert 10    ";
        std::getline(std::cin, input);

        return parseCommand(input);
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
        Command({"delete", "Elimina un número del árbol."}, &foo),
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
}
