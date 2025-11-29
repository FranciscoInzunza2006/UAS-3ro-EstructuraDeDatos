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

    // Source - https://stackoverflow.com/a
    // Posted by Adrian Schneider, modified by community. See post 'Timeline' for change history
    // Retrieved 2025-11-28, License - CC BY-SA 4.0
    static void displayInOrder(const std::string& prefix, const Node* node, const bool isLeft)
    {
        if (node == nullptr) return;

        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->left, true);

        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->key << '\n';

        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }

    static void displayPreOrder(const std::string& prefix, const Node* node, const bool isLeft)
    {
        if (node == nullptr) return;

        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->key << '\n';

        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->left, true);
        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }

    static void displayPostOrder(const std::string& prefix, const Node* node, const bool isLeft)
    {
        if (node == nullptr) return;

        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->right, false);

        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->key << '\n';

        displayInOrder(prefix + (isLeft ? "│   " : "    "), node->left, true);
    }

public:
    void insert(const int key) { root = insert(root, key); }

    bool remove(const int key)
    {
        root = remove(root, key);
        return true;
    }

    Node* search(int key);

    void displayInOrder() const { displayInOrder("", root, false); }
    void displayPostOrder() const { displayPostOrder("", root, false); }
    void displayPreOrder() const { displayPreOrder("", root, false); }

    int height();
    int size();

    void save();
};

int main()
{
    auto tree = BinarySearchTree();

    constexpr int sequence[] = {45, 15, 79, 90, 10, 55, 12, 20, 50};
    for (const int val : sequence)
    {
        tree.insert(val);
    }

    std::cout << "Tree:\n";
    tree.displayInOrder();

    std::cout << "Removed:\n"
        "\t- 90\n"
        "\t- 79\n"
        "\t- 45\n";
    tree.remove(90);
    tree.remove(79);
    tree.remove(45);
    tree.displayInOrder();

    return 0;
}
