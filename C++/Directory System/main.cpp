//
// Created by Franc on 30/11/2025.
//

#include <iostream>
#include <vector>

#include "command_line.hpp"

class Node
{
public:
    std::string name;
    bool is_folder;

    std::string contents;
    // TODO: Hashing
    std::vector<Node*> children;

    // Source - https://stackoverflow.com/a
    // Posted by Aaron
    // Retrieved 2025-11-30, License - CC BY-SA 4.0
    void printSubtree(const std::string& prefix)
    {
        if (children.empty()) return;
        std::cout << prefix;
        size_t nchildren = children.size();
        std::cout << (nchildren > 1 ? "├── " : "");

        for (size_t i = 0; i < nchildren; ++i)
        {
            Node* c = children[i];
            if (i < nchildren - 1)
            {
                if (i > 0)
                {
                    std::cout << prefix << "├── ";
                }
                bool printStrand = nchildren > 1 && !c->children.empty();
                std::string newPrefix = prefix + (printStrand ? "│\t" : "\t");
                std::cout << c->name << "\n";
                c->printSubtree(newPrefix);
            }
            else
            {
                std::cout << (nchildren > 1 ? prefix : "") << "└── ";
                std::cout << c->name << "\n";
                c->printSubtree(prefix + "\t");
            }
        }
    }

    void printTree()
    {
        std::cout << name << "\n";
        printSubtree("");
        std::cout << "\n";
    }

    /// Constructors
    Node(std::string_view name, bool is_folder) : name(name), is_folder(is_folder)
    {
        if (is_folder) children = std::vector<Node*>{};
        else contents = std::string{};
    }

    Node(std::string_view name, std::string_view contents) : name(name), is_folder(false), contents(contents)
    {
    }

    Node(std::string_view name, std::vector<Node*>&& children) : name(name), is_folder(true),
                                                                 children(std::move(children))
    {
    }

    ~Node()
    {
        if (!is_folder) return;

        for (const Node* child : children)
            delete child;
    }
};



int main()
{
    Node* tree{
        new Node("/",
                 std::vector{
                     new Node("Juegos", std::vector{
                                  new Node("Minecraft", std::vector{
                                               new Node("Chafaland.zip", std::string("Un mundo acá bien perro")),
                                               new Node("Mods", std::vector{
                                                            new Node("Chafaland Modpack.zip",
                                                                     std::string("Jenny's Mod")),
                                                            new Node("Paco's Modpack.zip",
                                                                     std::string("Es igual a vanilla")),
                                                        })
                                           })
                              }),
                     new Node("Documentos", true)
                 }
        )
    };
    tree->printTree();
    delete tree;

    std::vector<Command> commands{
        Command(
            {"mkdir", "Crea una carpeta"},
            {{"Nombre(s)", "El nombre de la carpeta, se pueden crear multiples carpetas al mismo tiempo si se separan con espacios"}},
                [](Tokens tokens{
                }

            )
    }

    auto cmd = CommandLine(commands);
    while (cmd.running)
    {

    }

    return 0;
}
