//
// Created by Franc on 30/11/2025.
//

#include "file.hpp"

#include <iostream>
#include <memory>

// std::string File::getPath(std::string s)
// {
//     if (father != nullptr) return father->getPath(s);
//     return name + "/";
// }

File::File(const std::string& name, Folder* father) : name(name), father(father)
{
    if (father == nullptr) return;
    father->children.push_back(this);
}

void File::showPath()
{
    return;
}

void File::move(Folder* new_father)
{
}

void Folder::printSubtree(const std::string& prefix)
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

void Folder::showContents()
{
    std::cout << name << "\n";
    printSubtree("");
    std::cout << "\n";
}
