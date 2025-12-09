//
// Created by Franc on 30/11/2025.
//

#pragma once
#include <string>
#include <vector>
#include "color.hpp"
#include "trie_node.hpp"

constexpr auto COLOR_FILE = COLOR_YELLOW;
constexpr auto COLOR_FOLDER = COLOR_CYAN;

// FIXME: Update index on all operations

class Folder;

class File
{
    static std::string getPath(const File* file, std::string& s);

public:
    std::string filename;
    Folder* parent;

    // Weird variable to save restore path when deleted in the file system
    std::string restore_path{};

    std::string getPath() const;
    void moveTo(Folder* new_father);

    // Constructors
    explicit File(std::string  name, Folder* father = nullptr);
    virtual ~File(); // Remove from parent

    virtual bool isFolder() const
    {
        return false;
    }
};

class Folder : public File
{
    trie_node::TrieNode* index = new trie_node::TrieNode();

    void printSubtree(const std::string& prefix) const;

    public:
    std::vector<File*> entries;

    void addEntry(File* entry);

    File* findEntry(std::string_view name) const;
    void removeEntry(const File* file);

    bool existsPrefix(const std::string& prefix) const
    {
        return trie_node::isPrefix(index, prefix);
    }

    trie_node::TrieNode* getIndex() const
    {
        return index;
    }

    void showContents() const;

    // Constructors
    explicit Folder(const std::string& name, Folder* father = nullptr) : File(name, father) {}

    ~Folder() override; // Destroy tree

    bool isFolder() const override
    {
        return true;
    }
};