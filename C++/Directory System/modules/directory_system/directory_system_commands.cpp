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
    new Folder(tokens[0], root);
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