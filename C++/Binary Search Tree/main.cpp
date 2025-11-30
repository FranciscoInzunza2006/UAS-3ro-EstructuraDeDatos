//
// Created by Franc on 28/11/2025.
//

#include <iostream>

#include "binary_search_tree.hpp"
#include "command.hpp"
#include "command_line.hpp"

int main()
{
    //region Set Up
    auto tree = BinarySearchTree();

    const std::vector commands
    {
        Command(
            {"insert", "Inserta un número en el árbol."},
            {{"Valor", "El valor que se va a ingresar; no debe estar en el árbol."}},
            [&tree](const Tokens& tokens)
            {
                const int val = std::stoi(tokens[0]);

                const bool inserted = tree.insert(val);
                std::cout << (inserted
                                  ? "Se insertó el valor."
                                  : "El valor ya se encontraba en el árbol y no se insertó.") << '\n';
            }
        ),
        Command(
            {"search", "Busca un número en el árbol y muestra su ruta."},
            {{"Valor", "El valor que se va a buscar."}},
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
                {{"Valor", "El valor que se va a eliminar; debe estar en el árbol."}},
                [&tree](const Tokens& tokens)
                {
                    const int val = std::stoi(tokens[0]);

                    const bool removed = tree.remove(val);
                    std::cout << (removed
                                      ? "Se eliminó el valor."
                                      : "El valor no se encontraba en el árbol.") << '\n';
                }),

        Command({"inorder", "Muestra el árbol en In-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayInOrder(); }),
        Command({"preorder", "Muestra el árbol en Pre-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayPreOrder(); }),
        Command({"postorder", "Muestra el árbol en Post-Orden."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { tree.displayPostOrder(); }),

        Command({"height", "Muestra la altura del árbol."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { std::cout << "Altura: " << tree.height() << '\n'; }),
        Command({"size", "Muestra el tamaño del árbol (cantidad de nodos)."},
                [&tree]([[maybe_unused]] const Tokens& tokens) { std::cout << "Tamaño: " << tree.size() << '\n'; }),

        Command({"export", "Guarda el árbol (en In-Orden) en un archivo."},
                [&tree]([[maybe_unused]] const Tokens& tokens)
                {
                    if (tree.save("tree.txt"))
                    {
                        std::cout << "El árbol se guardó correctamente.\n";
                    }
                    else
                    {
                        std::cout << "Hubo un error al guardar el árbol.\n";
                    }
                }),
        Command({"load", "Carga el árbol desde un archivo."},
                [&tree]([[maybe_unused]] const Tokens& tokens)
                {
                    if (tree.load("tree.txt"))
                    {
                        std::cout << "El árbol se cargó correctamente.\n";
                    }
                    else
                    {
                        std::cout << "Hubo un error al cargar el árbol.\n";
                    }
                }),
    };
    CommandLine cmd(commands);
    //endregion

    std::cout <<
        "-------------------------------------------------------------------\n"
        "Árboles binarios de búsqueda\n"
        "Por Francisco Javier\n"
        "-------------------------------------------------------------------\n"
        "Instrucciones:\n"
        "   Escribe comandos para interactuar con la aplicación.\n"
        "   Escribe 'help' para consultar la lista de comandos disponibles.\n"
        "   Escribe 'exit' para salir.\n"
        "-------------------------------------------------------------------\n";
    while (cmd.running)
    {
        std::cout << " >> ";
        cmd.processInput();
        std::cout << '\n';
    }

    return 0;
}
