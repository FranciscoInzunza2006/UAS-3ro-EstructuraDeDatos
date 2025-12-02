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
    if (file->father != nullptr)
        s = getPath(file->father, s) + "/";
    return s + file->name;
}

std::string File::getPath() const
{
    std::string s;
    return getPath(this, s);
}

File::File(std::string name, Folder* father) : name(std::move(name)), father(father)
{
    if (father == nullptr) return;
    father->children.push_back(this);
}

File::~File()
{
    std::cerr << name << " destroyed.\n";
    if (father == nullptr) return;
    father->removeChild(this);
}

void File::move(Folder* new_father)
{
    if (father == new_father) return;

    // Check if it's a sub-folder
    const Folder* f = new_father;
    while (f != nullptr)
    {
        if (f != this)
        {
            // TODO: Something to make clear this shouldn't happen
            return;
        }
        f = f->father;
    }

    // Get adopted
    father->removeChild(this);
    father = new_father;
    new_father->children.push_back(this);
}

void Folder::printSubtree(const std::string& prefix) const
{
    const size_t n = children.size();
    for (size_t i = 0; i < n; ++i)
    {
        File* child = children[i];
        const bool isLast = (i == n - 1);

        std::cout << prefix
            << (isLast ? "└── " : "├── ")
            << child->name << "\n";

        if (child->isFolder())
        {
            std::string childPrefix = prefix + (isLast ? "    " : "│   ");
            static_cast<Folder*>(child)->printSubtree(childPrefix);
        }
    }
}

void Folder::showContents() const
{
    std::cout << name << "\n";
    printSubtree("");
    std::cout << "\n";
}

File* Folder::search(const std::string_view name) const
{
    for (const auto child : children)
        if (child->name == name) return child;

    return nullptr;
}

void Folder::removeChild(const File* file)
{
    const auto iterator = std::find(children.begin(), children.end(), file);
    if (iterator != children.end())
    {
        *iterator = children.back();
        children.pop_back();
    }
}

Folder::~Folder()
{
    for (const File* child : children)
    {
        delete child;
    }
}
