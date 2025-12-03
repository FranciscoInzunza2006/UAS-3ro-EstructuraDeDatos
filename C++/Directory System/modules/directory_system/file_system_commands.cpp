//
// Created by Franc on 01/12/2025.
//

#include <iostream>

#include "file_system.hpp"
#include "file.hpp"

std::vector<Command> FileSystemUI::createCommands()
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

void FileSystemUI::createFile(const Tokens& tokens)
{
    const auto [folder, name] = parsePath(tokens[0]);
    const auto new_file = new File(name, folder);

    std::cout << '\"' << new_file->getPath() << "\" created.\n";
}

void FileSystemUI::makeDirectory(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto [folder, name] = parsePath(token);
        const auto new_folder = new Folder(name, folder);
        std::cout << '\"' << new_folder->getPath() << "\" created.\n";
    }
}

void FileSystemUI::moveFile(const Tokens& tokens)
{
}

void FileSystemUI::renameFile(const Tokens& tokens)
{
}

void FileSystemUI::searchFile(const Tokens& tokens)
{
}

void FileSystemUI::deleteFile(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto [folder, name] = parsePath(token);

        // FIXME: Doesn't works on directories (check for empty name)
        if (File* file = folder->search(name))
        {
            file->move(system.trash_bin);
            std::cout << '\"' << name << "\" deleted.\n";
        } else
        {
            std::cout << '\"' << name << "\" not found.\n";
        }
    }
}

void FileSystemUI::showFiles(const Tokens& tokens)
{
    system.getWorkingDirectory()->showContents();
}

void FileSystemUI::showPath(const Tokens& tokens)
{
}

void FileSystemUI::saveFile(const Tokens& tokens)
{
}

void FileSystemUI::loadFile(const Tokens& tokens)
{
}

void FileSystemUI::changeWorkingDirectory(const Tokens& tokens)
{
    const auto [folder, name] = parsePath(tokens[0]);

    // Due to the way the parse works if the last thing is a file name or a
    // not existing directory the name will have something in it.
    if (!name.empty()) throw std::runtime_error("\"" + name + "\" is not a directory.");

    system.setWorkingDirectory(folder);
}
