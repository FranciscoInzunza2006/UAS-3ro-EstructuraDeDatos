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

std::pair<Folder*, std::string> DirectorySystem::parsePath(std::string path) const
{
    Folder* container_folder = current_directory;
    std::string name;

    if (path[0] == '/')
    {
        container_folder = root;
        path.erase(0, 1);
    }

    if (path.empty())
        goto end;

    do
    {
        const std::string DELIMITER = "/";
        std::size_t token_length = path.find(DELIMITER);
        if (token_length == std::string::npos)
            token_length = path.length();

        const std::string token = path.substr(0, token_length);
        path.erase(0, token_length + DELIMITER.length());
        File* a;
        if (token == "..")
        {
            if (container_folder->father != nullptr)
                container_folder = container_folder->father;
            continue;
        }
        if (token == ".") continue;

        a = container_folder->search(token);
        if (a == nullptr)
        {
            if (!path.empty())
                throw std::runtime_error("\"" + token + "\" No such file or directory.");
            name = token;
            break;
        }

        if (a->isFolder())
        {
            container_folder = static_cast<Folder*>(a);
        }
        else if (!path.empty())
        {
            if (token.back() != '/')
                throw std::runtime_error(a->name + " isn't a directory.");

            name = token;
            name.pop_back();
        }
    }
    while (!path.empty());

    end:
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
