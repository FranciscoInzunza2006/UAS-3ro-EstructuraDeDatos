//
// Created by Franc on 29/11/2025.
//

#include "binary_search_tree.hpp"

#include <fstream>
#include <iostream>

//region Constructors and Destructor
BinarySearchTree::BinarySearchTree(const std::string& filename)
{
    load(filename);
}

BinarySearchTree::~BinarySearchTree()
{
    cleanup(root);
}

void BinarySearchTree::cleanup(const Node* node)
{
    if (node == nullptr) return;
    cleanup(node->left);
    cleanup(node->right);
    delete node;
}

//endregion

//region Tree usage
bool BinarySearchTree::insert(const int key)
{
    if (search(key) != nullptr) return false;

    root = insert(root, key);
    return true;
}

Node* BinarySearchTree::insert(Node* node, const int key)
{
    if (node == nullptr)
        return new Node(key);

    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);

    return node;
}

bool BinarySearchTree::remove(const int key)
{
    if (search(key) == nullptr) return false;

    root = remove(root, key);
    return true;
}

Node* BinarySearchTree::remove(Node* node, const int key)
{
    if (node == nullptr)
        return nullptr;

    if (key < node->key) node->left = remove(node->left, key);
    else if (key > node->key) node->right = remove(node->right, key);
    else
    {
        // Leaf node
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        // One child
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Two children
        const Node* successor = getSuccessor(node);
        node->key = successor->key;
        node->right = remove(node->right, successor->key);
    }

    return node;
}

Node* BinarySearchTree::getSuccessor(Node* node)
{
    node = node->right;
    while (node->left != nullptr)
        node = node->left;
    return node;
}

Node* BinarySearchTree::search(const int key) const
{
    return search(root, key);
}

Node* BinarySearchTree::search(Node* node, const int key)
{
    if (node == nullptr)
        return nullptr;

    if (key < node->key) return search(node->left, key);
    if (key > node->key) return search(node->right, key);

    return node;
}

//endregion

//region Properties
std::size_t BinarySearchTree::size() const
{
    return size(root);
}

std::size_t BinarySearchTree::size(const Node* node)
{
    if (node == nullptr) return 0;
    return 1 + size(node->left) + size(node->right);
}

std::size_t BinarySearchTree::height() const
{
    return height(root);
}

std::size_t BinarySearchTree::height(const Node* node)
{
    if (node == nullptr) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

//endregion

//region Displaying
void BinarySearchTree::displayInOrder() const
{
    displayInOrder(root);
}

void BinarySearchTree::displayInOrder(const Node* node)
{
    if (node != nullptr)
    {
        displayInOrder(node->left);
        std::cout << node->key << "   ";
        displayInOrder(node->right);
    }
}

void BinarySearchTree::displayPreOrder() const
{
    displayPreOrder(root);
}

void BinarySearchTree::displayPreOrder(const Node* node)
{
    if (node != nullptr)
    {
        std::cout << node->key << "   ";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
}

void BinarySearchTree::displayPostOrder() const
{
    displayPostOrder(root);
}

void BinarySearchTree::displayPostOrder(const Node* node)
{
    if (node != nullptr)
    {
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        std::cout << node->key << "   ";
    }
}

//endregion

//region IN OUT Files
// FIXME: Saving it in pre-order might help
bool BinarySearchTree::save(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }
    save(root, file);
    file.close();
    return true;
}

void BinarySearchTree::save(const Node* node, std::ofstream& file)
{
    if (node == nullptr) return;
    save(node->left, file);
    file << node->key << " ";
    save(node->right, file);
}

// FIXME: Loads the file in orden so every node only has a right branch
bool BinarySearchTree::load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    int val;
    while (file >> std::ws >> val) insert(val);

    file.close();
    return true;
}

//endregion
