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
            {"ren", "Renames a file or directory."},
            {
                {"OldName", "Path to the file."},
                {"NewName", "New name of the file."}
            },
            [this](const Tokens& tokens) { commands.renameFile(tokens); }
        ),
        Command(
            {"mv", "Moves a file or directory to a new location."},
            {
                {"OldPath", "Path to the file."},
                {"NewPath", "New path of the file."}
            },
            [this](const Tokens& tokens) { commands.moveFile(tokens); }
        ),
        Command(
            {"cd", "Changes the console working directory."},
            {{"Path", "Path"}},
            [this](const Tokens& tokens) { commands.changeDirectory(tokens); }
        ),
        Command({"search", "Checks if a file or folder exists at the path given."},
                {{"Path", "Path"}},
                [this](const Tokens& tokens) { commands.searchFile(tokens); }
        ),
        Command(
            {"save", "Saves the folder structure to a JSON in the given path."},
            {{"Path", "Path"}},
            [this](const Tokens& tokens) { commands.saveFile(tokens); }
        ),
        Command(
            {"load", "Loads the folder structure from JSON in the given path."},
            {{"Path", "Path"}},
            [this](const Tokens& tokens) { commands.loadFile(tokens); }
        ),
        Command(
            {"dir", "Shows directory contents"},
            {{"Path", "Path", true}},
            [this](const Tokens& tokens) { commands.listEntries(tokens); },
            true
        ),
        Command(
            {"path", "Shows the absolute path of the given file or current directory"},
            {{"Path", "Path", true}},
            [this](const Tokens& tokens) { commands.showAbsolutePath(tokens); },
            true
        ),
        Command(
            {"restore", "Restore the file of the trash bin at the path it used to be."},
            {{"File", "Path of the file (inside the BIN folder)"}},
            [this](const Tokens& tokens) { commands.restoreFile(tokens); }
        ),
        Command(
            {"clear-trash", "Clears the trash bin"},
            [this](const Tokens& tokens) { commands.clearTrash(tokens); }
        ),
        Command(
            {"cls", "Cleans the screen."},
            [](const Tokens&) { std::system("cls"); }
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

void FileSystemCommands::moveFile(const Tokens& tokens)
{
    const std::string& file = tokens[0];
    ParsingResult old_file = resolvePath(file);
    if (!old_file.exists()) throw std::runtime_error(file + " not found.");

    const std::string& new_location = tokens[1];
    ParsingResult location = resolvePath(new_location);
    if (!location.exists()) throw std::runtime_error(new_location + " does not exist.");
    if (!location.isFolder()) throw std::runtime_error(new_location + " new location must be a folder.");

    const std::string new_path = new_location + "/" + file;
    ParsingResult new_file = resolvePath(new_path);
    if (new_file.exists()) throw std::runtime_error(new_path + " already exists.");

    auto* const new_container_folder = static_cast<Folder*>(location.file);
    old_file.file->moveTo(new_container_folder);

    std::cout << "Moved.\n";
}

// TODO: Name validation (can put illegal characters on the name or nothing at all)
void FileSystemCommands::renameFile(const Tokens& tokens)
{
    const std::string& file_path = tokens[0];

    ParsingResult file = resolvePath(file_path);
    if (!file.exists()) throw std::runtime_error(file_path + " not found.");

    const std::string& new_name = tokens[1];
    const std::string new_path = file.file->parent->getPath() + "/" + new_name;

    const ParsingResult new_file = resolvePath(new_path);
    if (new_file.exists()) throw std::runtime_error(new_name + " already exists.");

    file.file->filename = new_name;
    std::cout << "File renamed.\n";
}

void FileSystemCommands::searchFile(const Tokens& tokens)
{
    std::string file_path = tokens[0];
    ParsingResult file = resolvePath(file_path);
    if (!file.exists()) throw std::runtime_error(file_path + " not found.");

    std::cout << "File found.\n";
}

void FileSystemCommands::removeFile(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        const auto path = resolvePath(token);

        if (!path.exists()) throw std::runtime_error("\"" + token + "\" does not exist.");

        // FIXME: Doesn't works on directories (check for empty name)
        path.file->restore_path = path.file->parent->getPath();
        path.file->moveTo(system->trash_bin);
        std::cout << '\"' << path.file->filename << "\" deleted.\n";
    }
}

void FileSystemCommands::restoreFile(const Tokens& tokens)
{
    const std::string& file_path = tokens[0];
    const ParsingResult result = resolvePath("/BIN/" + file_path);

    if (!result.exists()) throw std::runtime_error(file_path + " not found in trash bin.");

    File* file = result.file;;
    const ParsingResult restore_path = resolvePath(file->restore_path);
    if (!restore_path.exists()) throw std::runtime_error("\"" + file->restore_path + "\" Restore path not found.");

    file->moveTo(static_cast<Folder*>(restore_path.file));
    std::cout << file_path << " restored.\n";
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

void FileSystemCommands::showAbsolutePath(const Tokens& tokens) const
{
    if (tokens.empty())
    {
        std::cout << system->getWorkingDirectory()->getPath() << '\n';
        return;
    }

    if (tokens.size() > 1) throw std::runtime_error("Too many arguments");

    const ParsingResult path = resolvePath(tokens[0]);

    if (!path.exists()) throw std::runtime_error("File does not exist.");
    std::cout << path.file->getPath() << '\n';
}

void FileSystemCommands::saveFile(const Tokens& tokens)
{
    const std::string& filename = tokens[0];

    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) throw std::runtime_error("Can't open file.");

    FileSystemSerializer serializer(system);
    file << serializer.serialize();

    file.close();
    std::cout << filename << " saved.\n";
}

void FileSystemCommands::loadFile(const Tokens& tokens)
{
    const std::string& filename = tokens[0];

    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) throw std::runtime_error("Can't open file.");

    std::string content;
    file.seekg(0, std::ios::end);
    content.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    content.assign(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());

    FileSystemSerializer::load(system, content);

    file.close();
    std::cout << filename << " loaded.\n";
}

void FileSystemCommands::clearTrash(const Tokens&)
{
    if (system->trash_bin->entries.empty())
    {
        std::cout << "The trash bin is empty.\n";
        return;
    }

    for (const auto& trash : system->trash_bin->entries)
    {
        delete trash;
    }
    std::cout << "Trash emptied.\n";
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
