//
// Created by Franc on 28/11/2025.
//

#include <fstream>
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

    static void cleanup(const Node* node)
    {
        if (node == nullptr) return;
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }

    //region Main usage
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

    static Node* getSuccessor(Node* node)
    {
        node = node->right;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    static Node* search(Node* node, const int key)
    {
        if (node == nullptr)
            return nullptr;

        if (key < node->key) return search(node->left, key);
        if (key > node->key) return search(node->right, key);

        return node;
    }

    //endregion

    //region Tree properties
    static std::size_t size(const Node* node)
    {
        if (node == nullptr) return 0;
        return 1 + size(node->left) + size(node->right);
    }

    static std::size_t height(const Node* node)
    {
        if (node == nullptr) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

    //endregion

    //region Display
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

    //endregion

    //region IN OUT files
    static void save(const Node* node, std::ofstream& file)
    {
        if (node == nullptr) return;
        save(node->left, file);
        file << node->key << " ";
        save(node->right, file);
    }

    //endregion
public:
    BinarySearchTree() = default;
    explicit BinarySearchTree(const std::string& filename)
    {
        load(filename);
    }
    ~BinarySearchTree()
    {
        cleanup(root);
    }

    //region Main usage
    bool insert(const int key)
    {
        if (search(key) != nullptr) return false;

        root = insert(root, key);
        return true;
    }

    bool remove(const int key)
    {
        if (search(key) == nullptr) return false;

        root = remove(root, key);
        return true;
    }

    Node* search(const int key) const
    {
        return search(root, key);
    }

    //endregion

    //region Tree properties
    std::size_t height() const
    {
        return height(root);
    }

    std::size_t size() const
    {
        return size(root);
    }

    //endregion

    //region Display
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

    //endregion

    //region IN OUT files
    // FIXME: Loads the file in orden so every node only has a right branch
    bool load(const std::string& filename)
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

    // FIXME: Saving it in pre-order might help
    bool save(const std::string& filename) const
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

    //endregion
};

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
