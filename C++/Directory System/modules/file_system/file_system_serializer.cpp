//
// Created by Franc on 04/12/2025.
//

#include <sstream>
#include <stack>
#include <stack>
#include <stack>

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
    // if (entries_count == 0)
    // {
    //     foo += "{}";
    //     return;
    // }

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
    serializeItem(system->root_directory, output);
    output += "\n}";

    return output;
}

void FileSystemSerializer::load(FileSystem* system, const std::string& json)
{
    /// IDEAS:
    /// Ignore first char and last bracket
    /// When open bracket add a folder to the with the parent set to the last value in the  stack
    ///     Hardcode trashbin and root
    /// Pop when closing bracket
    /// When null is found create file

    FileSystem sys = FileSystem();
    std::stack<Folder*> folders{};
    std::istringstream json_stream{json};

    while (json_stream)
    {
        if (json_stream.peek() == '}')
        {
            while (json_stream.peek() == '}')
            {
                folders.pop();
                json_stream.ignore();

                // Avoid segfault do to the extra brackets at start and end
                if (folders.empty())
                {
                    goto ret;
                }

                if (json_stream.peek() == '\n')
                    json_stream.ignore();
            }
        }

        std::string key;
        {
            std::string buffer;
            std::getline(json_stream, buffer, ':');

            std::stringstream ss(buffer);
            ss >> std::ws;

            // Abusing getline to get the key
            std::getline(ss, key, '"');
            std::getline(ss, key, '"');
        }

        std::string value;
        json_stream >> std::ws;
        std::getline(json_stream, value);

        if (value[0] == '{')
        {
            if (key == "")
            {
                folders.push(sys.root_directory);
                continue;
            }

            if (key == "BIN")
            {
                folders.push(sys.trash_bin);
                continue;
            }

            folders.push(new Folder(key, folders.top()));
            continue;
        }

        if (key == "")
            break;
        new File(key, folders.top());
    }

    ret:
    if (!folders.empty())
    {
        throw std::runtime_error("Error when loading json");
    }

    *system = sys;
}