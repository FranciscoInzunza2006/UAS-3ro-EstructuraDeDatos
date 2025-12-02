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
            [this](const Tokens& tokens) { makeDirectory(tokens); },
            true
        ),
        Command( // TODO: Show passed path contents
            {"dir", "Shows current directory contents"},
            {{"Path", "Path", true}},
            [this](const Tokens& tokens) { showFiles(tokens); },
            true
        )
    };
}

std::pair<Folder*, std::string> DirectorySystem::parsePath(std::string path) const
{
    Folder* container_folder = current_directory;
    std::string name;

    if (path[0] == '/')
    {
        container_folder = root;
        path.erase(0, 1);
    }

    do
    {
        const std::string DELIMITER = "/";
        std::size_t token_length = path.find(DELIMITER);
        if (token_length == std::string::npos)
            token_length = path.length();

        name = path.substr(0, token_length);
        File* a;
        if (name == "..")
        {
            if (container_folder->father != nullptr)
                container_folder = container_folder->father;
            goto consume;
        }
        if (name == ".") goto consume;

        a = container_folder->search(name);
        if (a == nullptr)
        {
            // TODO: Throw or something
            goto consume;
        }

        if (!a->isFolder())
        {
            break;
        }

        container_folder = static_cast<Folder*>(a);

        consume:
        path.erase(0, token_length + DELIMITER.length());
    } while (!path.empty());

    return std::pair{container_folder, name};
}

DirectorySystem::DirectorySystem() : cmd(createCommands())
{
    // Some basic structure for testing
    const auto documents = new Folder("Documents", root);
    new File("Homework v2.pdf", documents);

    new Folder("Images", root);
    new Folder("Videos", root);
    new Folder("3D models", root);

    new File("Homework.pdf", trash_bin);
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
