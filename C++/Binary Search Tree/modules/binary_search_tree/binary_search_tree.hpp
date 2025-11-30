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

    bool insert(int key);
    bool remove(int key);
    Node* search(int key) const;

    std::size_t height() const;
    std::size_t size() const;

    void displayInOrder() const;
    void displayPreOrder() const;
    void displayPostOrder() const;

    void displayPathToNode(const Node* node) const;

    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
};
