//
// Created by Franc on 01/12/2025.
//

#pragma once
#include "command.hpp"
#include "command_line.hpp"
#include "file.hpp"

class DirectorySystem
{
    Folder* const root = new Folder("ROOT");
    Folder* const trash_bin = new Folder("BIN", root);

    Folder* current_directory = root;

    CommandLine cmd;
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

    std::vector<Command> createCommands();
    std::pair<Folder*, std::string> parsePath(std::string path) const;
    public:
    DirectorySystem();
    ~DirectorySystem();

    void run();
};



