//
// Created by Franc on 06/12/2025.
//

#include "trie_node.hpp"

#include <string>

namespace trie_node
{
    // Method to insert a key into the Trie
    void insert(TrieNode* root, const std::string& key)
    {
        // Initialize the curr pointer with the root node
        TrieNode* curr = root;

        // Iterate across the length of the string
        for (char c : key)
        {
            const auto index = static_cast<unsigned char>(c);
            if (index >= RANGE)
            {
                throw std::runtime_error("Value " + std::to_string(index) + " out of range.");
            }

            // Check if the node exists for the
            // current character in the Trie
            if (curr->children[index] == nullptr)
            {
                // If node for current character does
                // not exist then make a new node
                // Keep the reference for the newly
                // created node
                curr->children[index] = new TrieNode();
                if (!curr->children[index])
                    throw std::bad_alloc();
            }

            // Move the curr pointer to the
            // newly created node
            curr = curr->children[index];
        }

        // Mark the end of the word
        curr->isLeaf = true;
    }

    void remove(TrieNode* root, const std::string& key)
    {
        if (root == nullptr)
        {
            return;
        }

        TrieNode* curr = root;

        for (char c : key)
        {
            const auto index = static_cast<unsigned char>(c);
            if (index >= RANGE)
            {
                throw std::runtime_error("Value " + std::to_string(c) + " out of range.");
            }

            if (curr->children[index] == nullptr)
                break;

            curr = curr->children[index];
        }

        curr->isLeaf = false;
    }


// Method to search a key in the Trie
bool search(TrieNode* root, const std::string& key)
{
    if (root == nullptr)
    {
        return false;
    }

    // Initialize the curr pointer with the root node
    TrieNode* curr = root;

    // Iterate across the length of the string
    for (char c : key)
    {
        const auto index = static_cast<unsigned char>(c);
        if (index >= RANGE)
        {
            throw std::runtime_error("Value " + std::to_string(c) + " out of range.");
        }

        // Check if the node exists for the
        // current character in the Trie
        if (curr->children[index] == nullptr)
            return false;

        // Move the curr pointer to the
        // already existing node for the
        // current character
        curr = curr->children[index];
    }

    // Return true if the word exists
    // and is marked as ending
    return curr->isLeaf;
}

// Method to check if a prefix exists in the Trie
bool isPrefix(TrieNode* root, const std::string& prefix)
{
    // Initialize the curr pointer with the root node
    TrieNode* curr = root;

    // Iterate across the length of the prefix string
    for (char c : prefix)
    {
        const auto index = static_cast<unsigned char>(c);
        if (index >= RANGE)
        {
            throw std::runtime_error("Value " + std::to_string(c) + " out of range.");
        }

        // Check if the node exists for the current character in the Trie
        if (curr->children[index] == nullptr)
            return false;

        // Move the curr pointer to the already existing node
        // for the current character
        curr = curr->children[index];
    }

    // If we reach here, the prefix exists in the Trie
    return true;
}

}
