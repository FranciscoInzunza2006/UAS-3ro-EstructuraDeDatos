//
// Created by Franc on 01/12/2025.
//

#pragma once
#include <stdexcept>

#include "command.hpp"
#include "command_line.hpp"
#include "file.hpp"

using Tokens = std::vector<std::string>;

class FileSystem
{
public:
    Folder* root = new Folder("ROOT");
    Folder* trash_bin = new Folder("BIN", root);

    void setWorkingDirectory(Folder* new_working_directory)
    {
        if (current_directory == new_working_directory) return;

        const Folder* dir = new_working_directory;
        while (dir != nullptr && dir != root)
        {
            dir = dir->father;
        }

        if (dir == nullptr)
            throw std::invalid_argument("The given folder isn't on the file system.");

        current_directory = new_working_directory;
    }

    Folder* getWorkingDirectory() const { return current_directory; }

private:
    Folder* current_directory = root;
};

class PathParser
{
    FileSystem* system;

public:
    explicit PathParser(FileSystem* system) : system(system)
    {
    }

    static Tokens tokenize(const std::string& path);
    std::pair<Folder*, std::string> parse(const Tokens& path_tokens) const;

    static bool isFolder(const std::pair<Folder*, std::string>& thingy)
    {
        return thingy.second.empty();
    }

    static bool isFileOrName(const std::pair<Folder*, std::string>& thingy)
    {
        return !thingy.second.empty();
    }
};

class FileSystemCommands
{
    FileSystem* system{};
    PathParser path_parser;
public:
    explicit FileSystemCommands(FileSystem* system) : system(system), path_parser(PathParser(system)) {}

    void createFile(const Tokens& tokens);
    void makeDirectory(const Tokens& tokens);
    void moveFile(const Tokens& tokens);
    void renameFile(const Tokens& tokens);
    void searchFile(const Tokens& tokens);
    void deleteFile(const Tokens& tokens);
    void showFiles(const Tokens& tokens);
    void showPath(const Tokens& tokens);

    void saveFile(const Tokens& tokens);
    void loadFile(const Tokens& tokens);

    void changeWorkingDirectory(const Tokens& tokens);
    std::pair<Folder*, std::string> parsePath(const std::string& path) const
    {
        return path_parser.parse(path_parser.tokenize(path));
    }
};

class FileSystemUI
{
public:
    FileSystem system = FileSystem();
    CommandLine cmd;
    FileSystemCommands commands;

    void run();

    ~FileSystemUI() = default;
private:
    std::vector<Command> createCommands();
};