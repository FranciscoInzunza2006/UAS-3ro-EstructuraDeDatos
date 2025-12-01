//
// Created by Franc on 30/11/2025.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>

class Folder;

class File
{
std::string getPath(std::string s);

public:
    std::string name;
    Folder* father;

    // static File::create(const std::string& name, Folder* father = nullptr)
    // {
    //     new File(name, father)
    // }

    // Constructors
    explicit File(const std::string& name, Folder* father = nullptr);
    virtual ~File() = default;

    virtual bool isFolder()
    {
        return false;
    }

    void showPath();
    void move(Folder* new_father);
};

class Folder : public File
{
    void printSubtree(const std::string& prefix);
    public:
    std::vector<File*> children;

    bool isFolder() override
    {
        return true;
    }

    void showContents();

    // Constructors
    explicit Folder(const std::string& name, Folder* father = nullptr) : File(name, father) {};
    ~Folder() override
    {
        std::cerr << name << " destroyed.\n";
        for (const File* child : children)
        {
            delete child;
        }
    }
};