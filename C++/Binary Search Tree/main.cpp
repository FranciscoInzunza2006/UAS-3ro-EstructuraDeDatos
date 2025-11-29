//
// Created by Franc on 28/11/2025.
//

#include <iostream>

class Node
{
public:
    int key{};
    Node* left = nullptr;
    Node* right = nullptr;


    explicit Node(const int key) : key(key)
    {
    }

    Node(const int key, Node* left, Node* right) : key(key), left(left), right(right)
    {
    }
};

class BinarySearchTree
{
    Node* root = nullptr;

    static Node* insert(Node* node, const int key)
    {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);

        return node;
    }

    static Node* remove(Node* node, const int key)
    {
        if (node == nullptr)
            return nullptr;

        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            // FIXME: Memory leaks
            if (node->left == nullptr)
            {
                return node->right;
            }
            if (node->right == nullptr)
            {
                return node->left;
            }

            const Node* successor = findMin(node);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }

        return node;
    }

    static Node* findMin(Node* node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Display
    static void displayInOrder(const Node* node)
    {
        if (node != nullptr)
        {
            displayInOrder(node->left);
            std::cout << node->key << "   ";
            displayInOrder(node->right);
        }
    }

    static void displayPreOrder(const Node* node)
    {
        if (node != nullptr)
        {
            std::cout << node->key << "   ";
            displayPreOrder(node->left);
            displayPreOrder(node->right);
        }
    }

    static void displayPostOrder(const Node* node)
    {
        if (node != nullptr)
        {
            displayPostOrder(node->left);
            displayPostOrder(node->right);
            std::cout << node->key << "   ";
        }
    }

public:
    void insert(const int key) { root = insert(root, key); }

    bool remove(const int key)
    {
        root = remove(root, key);
        return true;
    }

    Node* search(int key);

    void displayInOrder() const
    {
        displayInOrder(root);
        std::cout << std::endl;
    }

    void displayPreOrder() const
    {
        displayPreOrder(root);
        std::cout << std::endl;
    }

    void displayPostOrder() const
    {
        displayPostOrder(root);
        std::cout << std::endl;
    }

    int height();
    int size();

    void save();
};

int main()
{
    auto tree = BinarySearchTree();

    constexpr int sequence[] = {45, 15, 79, 90, 10, 55, 12, 20, 50};
    for (const int val : sequence) tree.insert(val);

    std::cout << "Tree:\n";
    tree.displayInOrder();

    std::cout << "\nRemoved:\n"
        "  - 90\n"
        "  - 79\n"
        "  - 45\n";
    tree.remove(90);
    tree.displayInOrder();
    tree.remove(79);
    tree.displayInOrder();
    tree.remove(45);
    tree.displayInOrder();

    return 0;
}
