//
// Created by Franc on 04/12/2025.
//

#include "file_system.hpp"

void FileSystemSerializer::serializeItem(File* file, std::string& foo)
{
    foo += "\"" + file->filename + "\": ";
    if (!file->isFolder())
    {
        foo += "null";
        return;
    }

    Folder* folder = dynamic_cast<Folder*>(file);
    const std::size_t entries_count = folder->entries.size();
    if (entries_count == 0)
    {
        foo += "{}";
        return;
    }

    foo += "{\n";
    for (std::size_t i = 0; i < entries_count; i++)
    {
        serializeItem(folder->entries[i], foo);
        bool is_last = i == entries_count - 1;
        if (!is_last) foo += ",";

        foo += "\n";
    }
    foo += "}";
}

std::string FileSystemSerializer::serialize()
{
    std::string output;
    output.reserve(256);

    output += "{\n";
    serializeItem(system.root_directory, output);
    output += "\n}";

    return output;
}

void FileSystemSerializer::load(std::string json)
{

}