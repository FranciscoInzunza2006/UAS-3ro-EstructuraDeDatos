//
// Created by Franc on 01/12/2025.
//

#include "directory_system.hpp"
#include "file.hpp"

void DirectorySystem::createFile(const Tokens& tokens)
{
}

void DirectorySystem::makeDirectory(const Tokens& tokens)
{
    for (const auto& token : tokens)
    {
        new Folder(token, root);
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