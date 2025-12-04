//
// Created by Franc on 30/11/2025.
//

#include "file.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

std::string File::getPath(const File* file, std::string& s)
{
    if (file->parent != nullptr)
        s = getPath(file->parent, s) + "/";
    return s + file->filename;
}

std::string File::getPath() const
{
    std::string s;
    return getPath(this, s);
}

File::File(std::string name, Folder* father) : filename(std::move(name)), parent(father)
{
    if (father == nullptr) return;
    father->entries.push_back(this);
}

File::~File()
{
    //std::cerr << name << " destroyed.\n";
    if (parent == nullptr) return;
    parent->removeEntry(this);
}

void File::moveTo(Folder* new_father)
{
    if (parent == new_father) return;

    // Check if it's a sub-folder
    const Folder* f = new_father;
    while (f != nullptr)
    {
        if (f == this)
        {
            throw std::invalid_argument(new_father->filename + " is a descendant of " + filename);
        }
        f = f->parent;
    }

    // Get adopted
    parent->removeEntry(this);
    parent = new_father;
    new_father->entries.push_back(this);
}

void Folder::printSubtree(const std::string& prefix) const
{
    const size_t n = entries.size();
    for (size_t i = 0; i < n; ++i)
    {
        File* child = entries[i];
        const bool isLast = (i == n - 1);

        std::cout << prefix
            << (isLast ? "└── " : "├── ")
            << child->filename << "\n";

        if (child->isFolder())
        {
            std::string childPrefix = prefix + (isLast ? "    " : "│   ");
            static_cast<Folder*>(child)->printSubtree(childPrefix);
        }
    }
}

void Folder::showContents() const
{
    std::cout << filename << "\n";
    printSubtree("");
    std::cout << "\n";
}

File* Folder::findEntry(const std::string_view name) const
{
    for (const auto child : entries)
        if (child->filename == name) return child;

    return nullptr;
}

void Folder::removeEntry(const File* file)
{
    const auto iterator = std::find(entries.begin(), entries.end(), file);
    if (iterator != entries.end())
    {
        *iterator = entries.back();
        entries.pop_back();
    }
}

Folder::~Folder()
{
    for (const File* child : entries)
    {
        delete child;
    }
}
