//
// Created by Franc on 01/12/2025.
//

#include "file_system.hpp"

#include <iostream>

#include "command.hpp"
#include <conio.h>

FileSystemUI::FileSystemUI() : cmd(createCommands())
{
    // Some basic structure for testing
    const auto documents = new Folder("Documents", system.root_directory);
    new File("Homework v2.pdf", documents);
    new Folder("CBTIS 45", documents);

    new Folder("Images", system.root_directory);
    new Folder("Videos", system.root_directory);
    new Folder("3D models", system.root_directory);

    new File("Homework.pdf", system.trash_bin);

    Folder* c = new Folder("C", new Folder("B", new Folder("A", system.root_directory)));
    for (int i = 0; i < 5; i++)
        new File(std::to_string(i) + ".txt", c);


    system.root_directory->showContents();
}


std::vector<std::string> command_history;
std::string FileSystemUI::customGetLine()
{
    std::string input;
    input.reserve(32);
    std::size_t cursor_position = 0;
    std::size_t history_index = command_history.size();
    //std::size_t file_index = 0;

    auto updateLine = [&input, &cursor_position](const std::string& new_line)
    {
        const std::size_t size = input.size();
        while (cursor_position > 0)
        {
            _putch('\b');
            cursor_position--;
        }

        while (cursor_position < size)
        {
            _putch(' ');
            cursor_position++;
        }

        while (cursor_position > 0)
        {
            _putch('\b');
            cursor_position--;
        }

        input = new_line;
        cursor_position = new_line.size();
        std::cout << new_line;
    };

    auto autocomplete = [&input, this, updateLine]()
    {
        if (input.empty()) return;

        // If first word command
        // If not god knows
        bool is_command = false;

        std::size_t word_start = input.find_last_of(' ');
        if (word_start == std::string::npos)
        {
            is_command = true;
            word_start = 0;
        }

        const std::string word = input.substr(word_start, input.size() - word_start);

        if (is_command)
        {
            auto cmds = cmd.getCommands();
            for (const auto& c : cmds)
            {
                auto name = c.info.name;

                // Is prefix
                if (input == name.substr(0, input.size()))
                {
                    updateLine(name + " ");
                    break;
                }
            }
        } else
        {
            const std::string argument = input.substr(word_start+1);
            if (argument.empty()) return;

            const Folder* wd = system.getWorkingDirectory();
            if (!wd->existsPrefix(argument)) return;

            // std::cout << "\nArg: " << argument << '\n';
            for (const auto& entry : wd->entries)
            {
                // Is prefix
                if (argument == entry->filename.substr(0, argument.size()))
                {
                    updateLine(input.substr(0, word_start+1) + entry->filename + " ");
                    break;
                }
            }
        }

        // std::cout << "\n--" << word << "\nIs command: " << is_command << '\n';
    };

    int c{};
    while (c != '\n' && c != '\r')
    {
        c = getch();
        // std::cout << input << "\n";

        if (c == 224)
        {
            int code = _getch();

            switch (code)
            {
            case 75: // Left arrow
                if (cursor_position > 0)
                {
                    _putch('\b');
                    cursor_position--;
                }

                break;

            case 77: // Right arrow
                if (cursor_position < input.size())
                {
                    putch(input[cursor_position]);
                    cursor_position++;
                }
                break;

            case 72: // Up arrow
                if (history_index > 0)
                {
                    history_index--;
                    updateLine(command_history[history_index]);
                }
                break;

            case 80: // Down arrow
                if (history_index < command_history.size())
                {
                    history_index++;
                    updateLine(history_index == command_history.size() ? "" : command_history[history_index]);
                }
                break;
            }

            continue;
        }

        switch (c)
        {
        case '\n':
        case '\r':
            break;

        case '\t':
                autocomplete();
            break;

        case '\b':
            if (cursor_position > 0)
            {
                cursor_position--;
                input.erase(cursor_position, 1);

                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
            break;

        default:
            if (c < RANGE)
            {
                _putch(c);

                if (cursor_position < input.size())input[cursor_position] = static_cast<char>(c);
                else input.insert(cursor_position, 1, static_cast<char>(c));
                cursor_position++;
            }
            break;
        }
    }
    _putch('\n');

    if (!input.empty())
        command_history.push_back(input);
    return input;
}


void FileSystemUI::run()
{
    while (cmd.running)
    {
        std::cout << system.getWorkingDirectory()->getPath() << "/> ";

        //std::string input = customGetLine();
        std::string input;
        std::getline(std::cin, input);

        cmd.processInput(input);
        std::cout << std::endl;
    }
}
