//
// Created by Franc on 29/11/2025.
//

#pragma once

#include <fstream>
#include <string>

#include "node.hpp"

class BinarySearchTree
{
    Node* root = nullptr;

    static void cleanup(const Node* node);

    static Node* insert(Node* node, int key);
    static Node* remove(Node* node, int key);
    static Node* getSuccessor(Node* node);
    static Node* search(Node* node, int key);

    static std::size_t size(const Node* node);
    static std::size_t height(const Node* node);

    static void displayInOrder(const Node* node);
    static void displayPreOrder(const Node* node);
    static void displayPostOrder(const Node* node);

    static void displayPathToNode(const Node* current_node, const Node* node);

    static void save(const Node* node, std::ofstream& file);

public:
    BinarySearchTree() = default;
    explicit BinarySearchTree(const std::string& filename);
    ~BinarySearchTree();

    // Performance: O(log n) where n is the size of the tree
    // log n due to the algorithm and the data structure used
    // Assumes a complete tree
    // Note: "insert" and "remove" implementation are O(2log n) due to searching if the value already exist in the tree.
    bool insert(int key);
    bool remove(int key);
    Node* search(int key) const;

    // Performance: O(n) where n is the size of the tree
    // It iterates through the whole tree
    std::size_t height() const;
    std::size_t size() const;

    // Performance: O(n) where n is the size of the tree
    // It iterates through the whole tree
    void displayInOrder() const;
    void displayPreOrder() const;
    void displayPostOrder() const;

    // Performance: O(n) where n is the depth of the node
    // It iterates through the whole tree
    void displayPathToNode(const Node* node) const;

    // Performance: O(n) where n is the size of the tree
    // It iterates through the whole tree
    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
};
