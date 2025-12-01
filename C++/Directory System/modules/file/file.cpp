//
// Created by Franc on 30/11/2025.
//

#include "file.hpp"

#include <iostream>
#include <memory>
#include <utility>

std::string File::getPath(const File* file, std::string& s)
{
    if (file->father != nullptr)
        s = getPath(file->father, s) + "/";
    return s + file->name;
}

void File::showPath() const
{
    std::string path;
    std::cout << getPath(this, path) << std::endl;
}

File::File(std::string  name, Folder* father) : name(std::move(name)), father(father)
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

    father->removeChild(this);
    father = new_father;

    if (new_father != nullptr)
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

void Folder::removeChild(File* file)
{
    const auto iterator = std::ranges::find(children.begin(), children.end(), file);
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
