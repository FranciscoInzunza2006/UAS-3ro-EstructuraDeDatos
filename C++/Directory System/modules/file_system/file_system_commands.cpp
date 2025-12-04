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
            [this](const Tokens& tokens) { commands.makeDirectory(tokens); },
            true
        ),
        Command(
            {"touch", "Creates a empty file"},
            {{"names(s)", "One or many(space separated) names for the new directories."}},
            [this](const Tokens& tokens) { commands.createFile(tokens); },
            true
        ),
        Command(
            {"rm", "Deletes a file or directory."},
            {{"name(s)", "One or many(space separated) names of the files to delete."}},
            [this](const Tokens& tokens) { commands.removeFile(tokens); },
            true
        ),
        Command(
            {"cd", "Changes the console working directory."},
            {{"Path", "Path"}},
            [this](const Tokens& tokens) { commands.changeDirectory(tokens); }
        ),
        Command( // TODO: Show passed path contents
            {"dir", "Shows current directory contents"},
            {{"Path", "Path", true}},
            [this](const Tokens& tokens) { commands.listEntries(tokens); },
            true
        ),
        Command(
            {"cls", "Cleans the screen."},
            [](const Tokens&){std::system("cls");}
            )
    };
}

// FIXME: Make all operations atomic. Nothing of making some and then rest failing.

void FileSystemCommands::createFile(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const ParsingResult result = resolvePath(token);

        // TODO: Note when there's a file or folder with the same name
        if (result.exists())
            throw std::runtime_error(token + " already exists.");

        auto* const container_folder = static_cast<Folder*>(result.file);
        const auto new_file = new File(result.name, container_folder);

        std::cout << '\"' << new_file->getPath() << "\" created.\n";
    }
}

void FileSystemCommands::makeDirectory(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const ParsingResult result = resolvePath(token);

        // TODO: Note when there's a file or folder with the same name
        if (result.exists())
            throw std::runtime_error(token + " already exists.");

        auto* const container_folder = static_cast<Folder*>(result.file);
        const auto new_folder = new Folder(result.name, container_folder);

        std::cout << '\"' << new_folder->getPath() << "\" created.\n";
    }
}
//
// void FileSystemCommands::moveFile(const Tokens& tokens)
// {
// }
//
// void FileSystemCommands::renameFile(const Tokens& tokens)
// {
// }
//
// void FileSystemCommands::searchFile(const Tokens& tokens)
// {
// }

void FileSystemCommands::removeFile(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto path = resolvePath(token);

        if (!path.exists()) throw std::runtime_error("\"" + token +  "\" does not exist.");

        // FIXME: Doesn't works on directories (check for empty name)
        path.file->moveTo(system->trash_bin);
        std::cout << '\"' << path.file->filename << "\" deleted.\n";
    }
}

void FileSystemCommands::listEntries(const Tokens& tokens) const
{
    if (tokens.empty())
    {
        system->getWorkingDirectory()->showContents();
        return;
    }

    if (tokens.size() > 1) throw std::runtime_error("Too many arguments");

    const ParsingResult path = resolvePath(tokens[0]);

    if (!path.exists()) throw std::runtime_error("Folder does not exist.");
    if (!path.isFolder()) throw std::runtime_error("\"" + path.file->filename + "\" is not a directory.");

    auto* const container_folder = static_cast<Folder*>(path.file);
    container_folder->showContents();
}
//
// void FileSystemCommands::showPath(const Tokens& tokens)
// {
// }
//
// void FileSystemCommands::saveFile(const Tokens& tokens)
// {
// }
//
// void FileSystemCommands::loadFile(const Tokens& tokens)
// {
// }
//
void FileSystemCommands::changeDirectory(const Tokens& tokens)
{
    const ParsingResult path = resolvePath(tokens[0]);

    if (!path.exists()) throw std::runtime_error("Folder does not exist.");
    if (!path.isFolder()) throw std::runtime_error("\"" + path.file->filename + "\" is not a directory.");

    auto* const container_folder = static_cast<Folder*>(path.file);
    system->setWorkingDirectory(container_folder);
}
