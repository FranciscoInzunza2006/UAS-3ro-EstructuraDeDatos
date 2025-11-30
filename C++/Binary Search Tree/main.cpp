//
// Created by Franc on 28/11/2025.
//

#include <iostream>

#include "modules/binary_search_tree/binary_search_tree.hpp"
#include "modules/command_line/command.hpp"
#include "modules/command_line/command_line.hpp"

int main()
{
    auto tree = BinarySearchTree();

    const std::vector commands
    {
        Command(
            {"insert", "Inserta un número en el árbol."},
            {{"Valor", "El valor que se va a ingresar, no debe estár en el árbol."}},
            [&tree](const Tokens& tokens)
            {
                const int val = std::stoi(tokens[0]);

                const bool inserted = tree.insert(val);
                std::cout << (inserted
                                  ? "Se inserto el valor."
                                  : "El valor ya se encontraba en el árbol y no se inserto.") << '\n';
            }
        ),
        Command(
            {"search", "Busca un número en el árbol y muestra su ruta."},
            {{"Valor", "El valor que se va a ingresar, no debe estár en el árbol."}},
            [&tree](const Tokens& tokens)
            {
                const int val = std::stoi(tokens[0]);

                //TODO: Show node path
                const Node* node = tree.search(val);
                std::cout << (node != nullptr
                                  ? "Está en el árbol."
                                  : "El valor no está en el árbol.") << '\n';
            }

        ),
        Command({"delete", "Elimina un número del árbol."},
                {{"Valor", "El valor que se va a eliminar, debe estár en el árbol"}},
                [&tree](const Tokens& tokens)
                {
                    const int val = std::stoi(tokens[0]);

                    //TODO: Show node path
                    const bool inserted = tree.insert(val);
                    std::cout << (inserted
                                      ? "Se elimino el valor."
                                      : "El valor no se encontraba en el árbol.") << '\n';
                }),

        Command({"inorder", "Muestra el árbol en In-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayInOrder(); }),
        Command({"preorder", "Muestra el árbol en Pre-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayPreOrder(); }),
        Command({"postorder", "Muestra el árbol en Post-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayPostOrder(); }),

        Command({"height", "Muestra la altura del árbol"},
                [&tree]([[maybe_unused]] const Tokens& tokens) { std::cout << "Altura: " << tree.height() << '\n'; }),
        Command({"size", "Muestra el tamaño del árbol (cantidad de nodos)."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { std::cout << "Tamaño: " << tree.size() << '\n'; }),

        Command({"export", "Guarda el árbol (en In-Orden) a un archivo."},
                [&tree]([[maybe_unused]] const Tokens& tokens)
                {
                    if (tree.save("tree.txt"))
                    {
                        std::cout << "El árbol se guardo correctamente.\n";
                    } else
                    {
                        std::cout << "Hubo un error guardando el árbol.\n";
                    }
                }),
    };
    CommandLine cmd(commands);

    while (cmd.running)
    {
        std::cout << " >> ";
        cmd.processInput();
    }

    return 0;
}
