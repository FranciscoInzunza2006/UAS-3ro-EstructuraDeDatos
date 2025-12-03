//
// Created by Franc on 03/12/2025.
//

#include "file_system.hpp"

// Path parser stuff
Tokens PathParser::tokenize(const std::string& path)
{
    Tokens tokens{};

    size_t start = 0;
    while (start < path.size())
    {
        size_t end = path.find('/', start);
        if (end == std::string::npos) end = path.size();
        tokens.push_back(path.substr(start, end - start));
        start = end + 1;
    }

    if (tokens.empty()) return {""};

    return tokens;
}

std::pair<Folder*, std::string> PathParser::parse(const Tokens& path_tokens) const
{
    std::string name;
    std::size_t i = 0;
    Folder* container_directory = system->getWorkingDirectory();

    // If the first token is empty then it was root (ej: /A/B)
    if (path_tokens[0].empty())
    {
        container_directory = system->root;
        i++;
    }

    for (; i < path_tokens.size(); i++)
    {
        const std::string& token = path_tokens[i];

        // FIXME: This token.empty() might become problematic
        if (token.empty() || token == ".")
            continue;

        if (token == "..")
        {
            if (container_directory->father != nullptr)
                container_directory = container_directory->father;
            continue;
        }

        const bool is_last = (i == path_tokens.size() - 1);
        File* a = container_directory->search(token);

        if (a == nullptr)
        {
            if (!is_last)
                throw std::runtime_error("\"" + token + "\" No such file or directory.");

            // final component is the new name (mkdir, touch, etc.)
            name = token;
            break;
        }

        if (a->isFolder())
        {
            container_directory = static_cast<Folder*>(a); // NOLINT(*-pro-type-static-cast-downcast)
        }
        else
        {
            if (!is_last)
                throw std::invalid_argument(a->name + " isn't a directory.");

            // file as last component -> its name
            name = token;
        }
    }

    return {container_directory, name};
}