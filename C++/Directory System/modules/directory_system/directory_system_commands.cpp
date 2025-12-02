//
// Created by Franc on 01/12/2025.
//

#include <iostream>

#include "directory_system.hpp"
#include "file.hpp"

void DirectorySystem::createFile(const Tokens& tokens)
{
    const auto [folder, name] = parsePath(tokens[0]);
    const auto new_file = new File(name, folder);
    std::cout << '\"' << new_file->getPath() << "\" created.\n";
}

void DirectorySystem::makeDirectory(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto [folder, name] = parsePath(token);
        const auto new_folder = new Folder(name, folder);
        std::cout << '\"' << new_folder->getPath() << "\" created.\n";
    }
}

void DirectorySystem::moveFile(const Tokens& tokens)
{
}

void DirectorySystem::renameFile(const Tokens& tokens)
{
}

void DirectorySystem::searchFile(const Tokens& tokens)
{
}

void DirectorySystem::deleteFile(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto [folder, name] = parsePath(token);

        // FIXME: Doesn't works on directories (check for empty name)
        if (File* file = folder->search(name))
        {
            file->move(trash_bin);
            std::cout << '\"' << name << "\" deleted.\n";
        } else
        {
            std::cout << '\"' << name << "\" not found.\n";
        }
    }
}

void DirectorySystem::showFiles(const Tokens& tokens)
{
    current_directory->showContents();
}

void DirectorySystem::showPath(const Tokens& tokens)
{
}

void DirectorySystem::saveFile(const Tokens& tokens)
{
}

void DirectorySystem::loadFile(const Tokens& tokens)
{
}

void DirectorySystem::changeWorkingDirectory(const Tokens& tokens)
{
    const auto [folder, name] = parsePath(tokens[0]);

    // Due to the way the parse works if the last thing is a file name or a
    // not existing directory the name will have something in it.
    if (!name.empty()) throw std::runtime_error("\"" + name + "\" is not a directory.");

    current_directory = folder;
}
