//
// Created by Franc on 06/12/2025.
//

#pragma once

#include <bits/stdc++.h>

constexpr int RANGE = 128;

namespace trie_node
{
    class TrieNode
    {
    public:
        // Array for children nodes of each node
        TrieNode* children[RANGE]{};

        // for end of word
        bool isLeaf = false;

        TrieNode() = default;

        ~TrieNode()
        {
            for (const auto& i : children)
                delete i;
        }
    };

    void insert(TrieNode* root, const std::string& key);
    void remove(TrieNode* root, const std::string& key);
    bool search(TrieNode* root, const std::string& key);
    bool isPrefix(TrieNode* root, const std::string& prefix);

    void print(TrieNode* node, const std::string& prefix = "");
}
