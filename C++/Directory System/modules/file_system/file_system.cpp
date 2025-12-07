//
// Created by Franc on 01/12/2025.
//

#include "file_system.hpp"

#include <iostream>

#include "command.hpp"

FileSystemUI::FileSystemUI() : cmd(createCommands())
{
    // Some basic structure for testing
    const auto documents = new Folder("Documents", system.root_directory);
    new File("Homework v2.pdf", documents);
    new Folder("CBTIS 45", documents);

    new Folder("Images", system.root_directory);
    new Folder("Videos", system.root_directory);
    new Folder("3D models", system.root_directory);

    new File("Homework.pdf", system.trash_bin);

    Folder* c = new Folder("C", new Folder("B", new Folder("A", system.root_directory)));
    for (int i = 0; i < 5; i++)
        new File(std::to_string(i) + ".txt", c);


    system.root_directory->showContents();
}

void FileSystemUI::run()
{
    while (cmd.running)
    {
        std::cout << system.getWorkingDirectory()->getPath() << "/> ";

        std::string input;
        std::getline(std::cin, input);

        cmd.processInput(input);
        std::cout << std::endl;
    }
}

