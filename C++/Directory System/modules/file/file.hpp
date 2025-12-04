//
// Created by Franc on 30/11/2025.
//

#pragma once
#include <string>
#include <vector>
#include "color.hpp"

constexpr auto COLOR_FILE = COLOR_YELLOW;
constexpr auto COLOR_FOLDER = COLOR_CYAN;

class Folder;

class File
{
    static std::string getPath(const File* file, std::string& s);

public:
    std::string filename;
    Folder* parent;

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
    void printSubtree(const std::string& prefix) const;

    public:
    std::vector<File*> entries;

    File* findEntry(std::string_view name) const;
    void removeEntry(const File* file);

    void showContents() const;

    // Constructors
    explicit Folder(const std::string& name, Folder* father = nullptr) : File(name, father) {}

    ~Folder() override; // Destroy tree

    bool isFolder() const override
    {
        return true;
    }
};