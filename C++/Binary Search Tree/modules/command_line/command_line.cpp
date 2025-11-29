//
// Created by Franc on 29/11/2025.
//

#include <iostream>
#include <vector>

class Command
{
};

class CommandLine
{
    static std::vector<std::string> split(const std::string_view str)
    {
        std::vector<std::string> result;

        int i = 0;
        bool in_word = false;
        for (const char c : str)
        {
            if (c != ' ')
            {
                in_word = true;

                if (result.size() == i) result.emplace_back("");
                result[i].push_back(c);
            }
            else
            {
                if (in_word)
                {
                    in_word = false;
                    i++;
                }
            }
        }
        return result;
    }

    bool parseCommand(const std::string_view input)
    {
        auto foo = split(input);
    }

public:
    bool read()
    {
        std::string input;
        std::getline(std::cin, input);

        parseCommand(input);
        return true;
    }
};

int main()
{
    CommandLine cmd;
    cmd.read();
}
