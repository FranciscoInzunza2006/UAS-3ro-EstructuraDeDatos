//
// Created by Franc on 30/11/2025.
//

#pragma once
#include <string>
#include <vector>

class Folder;

class File
{
    static std::string getPath(const File* file, std::string& s);

public:
    std::string name;
    Folder* father;

    std::string getPath() const;
    void move(Folder* new_father);

    // Constructors
    explicit File(std::string  name, Folder* father = nullptr);
    virtual ~File();

    virtual bool isFolder()
    {
        return false;
    }
};

class Folder : public File
{
    void printSubtree(const std::string& prefix) const;

    public:
    std::vector<File*> children;

    void removeChild(const File* file);

    void showContents() const;

    // Constructors
    explicit Folder(const std::string& name, Folder* father = nullptr) : File(name, father) {}

    ~Folder() override;

    bool isFolder() override
    {
        return true;
    }
};