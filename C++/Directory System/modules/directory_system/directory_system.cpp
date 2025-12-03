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
            {{"name(s)", "One or many(space separated) names for the new directories."}},
            [this](const Tokens& tokens) { makeDirectory(tokens); },
            true
        ),
        Command(
            {"touch", "Creates a empty file"},
            {{"path", "The path of the new file"}},
            [this](const Tokens& tokens) { createFile(tokens); }
        ),
        Command(
            {"rm", "Deletes a file or directory."},
            {{"name(s)", "One or many(space separated) names of the files to delete."}},
            [this](const Tokens& tokens) { deleteFile(tokens); },
            true
        ),
        Command(
            {"cd", "Changes the console working directory."},
            {{"Path", "Path"}},
            [this](const Tokens& tokens) { changeWorkingDirectory(tokens); }
        ),
        Command( // TODO: Show passed path contents
            {"dir", "Shows current directory contents"},
            {{"Path", "Path", true}},
            [this](const Tokens& tokens) { showFiles(tokens); },
            true
        )
    };
}

DirectorySystem::DirectorySystem() : cmd(createCommands())
{
    // Some basic structure for testing
    const auto documents = new Folder("Documents", root);
    new File("Homework v2.pdf", documents);
    new Folder("CBTIS 45°", documents);

    new Folder("Images", root);
    new Folder("Videos", root);
    new Folder("3D models", root);

    new File("Homework.pdf", trash_bin);

    Folder* c = new Folder("C", new Folder("B", new Folder("A", root)));
    for (int i = 0; i < 5; i++)
        new File(std::to_string(i) + ".txt", c);


    root->showContents();
}

DirectorySystem::~DirectorySystem() = default;

void DirectorySystem::run()
{
    while (cmd.running)
    {
        std::cout << current_directory->getPath() << "/> ";
        cmd.processInput();
        std::cout << std::endl;
    }
}

Tokens DirectorySystem::PathParser::tokenize(const std::string& str)
{
    Tokens tokens;

    size_t start = 0;
    while (start < str.size())
    {
        size_t end = str.find('/', start);
        if (end == std::string::npos) end = str.size();
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    return tokens;
}

std::pair<Folder*, std::string> DirectorySystem::PathParser::parse(const std::string& str) const
{
    Folder* container_folder = system.current_directory;
    std::string name;

    const Tokens tokens = tokenize(str);
    std::size_t i = 0;

    // If the first token is empty then it was root (ej: /A/B)
    if (tokens[0].empty())
    {
        container_folder = system.root;
        i++;
    }

    for (; i < tokens.size(); ++i)
    {
        const std::string& token = tokens[i];

        // FIXME: This token.empty() might become problematic
        if (token.empty() || token == ".")
            continue;

        if (token == "..")
        {
            if (container_folder->father != nullptr)
                container_folder = container_folder->father;
            continue;
        }

        const bool is_last = (i == tokens.size() - 1);
        File* a = container_folder->search(token);

        if (a == nullptr)
        {
            if (!is_last)
                throw std::runtime_error("\"" + token + "\" No such file or directory.");

            // final component is the new name (mkdir, touch, etc.)
            name = token;
            break;
        }

        if (a->isFolder())
        {
            container_folder = static_cast<Folder*>(a); // NOLINT(*-pro-type-static-cast-downcast)
        }
        else
        {
            if (!is_last)
                throw std::runtime_error(a->name + " isn't a directory.");

            // file as last component -> its name
            name = token;
        }
    }


    return {container_folder, name};
}


