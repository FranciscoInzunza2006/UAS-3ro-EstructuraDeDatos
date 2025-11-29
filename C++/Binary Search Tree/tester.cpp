//
// Created by Franc on 29/11/2025.
//

#include <iostream>

#include "modules/binary_search_tree/binary_search_tree.hpp"

int main()
{
    auto tree = BinarySearchTree();

    // Create tree
    constexpr int sequence[] = {45, 15, 79, 90, 10, 55, 12, 20, 50};
    for (const int val : sequence) tree.insert(val);

    std::cout << "Tree:\n";
    tree.displayInOrder();

    // Properties
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << "Height: " << tree.height() << '\n';

    // Search node
    std::cout << '\n';
    constexpr int needles[] = {20, 100};
    for (const int needle : needles)
    {
        std::cout << "Searching " << needle << ": " << (tree.search(needle) != nullptr ? "Found" : "Not found") << "\n";
    }
    std::cout << '\n';

    // Remove nodes
    constexpr int to_remove[] = {-7, 90, 79, 45};
    for (const int val : to_remove)
    {
        tree.remove(val);
        std::cout << "Removed: " << val << "; Size: " << tree.size() << "; Height: " << tree.height() << '\n';
        tree.displayInOrder();
        std::cout << '\n';
    }

    // IN OUT Files
    tree.save("test.txt");
    auto tree2 = BinarySearchTree("test.txt");

    return 0;
}
