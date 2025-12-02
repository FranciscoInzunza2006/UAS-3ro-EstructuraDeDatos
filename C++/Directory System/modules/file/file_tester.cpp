//
// Created by Franc on 01/12/2025.
//

#include <iostream>

#include "file.hpp"

int main()
{
    auto root = new Folder("");

    auto games_folder = new Folder("Juegos", root);

    auto minecraft_folder = new Folder("Minecraft", games_folder);
    new File("Chafaland.zip", minecraft_folder);

    auto mods_folder = new Folder("Mods", minecraft_folder);
    new File("Chafaland Modpack.zip", mods_folder);
    new File("Paco's Modpack.zip", mods_folder);

    auto terraria_folder = new Folder("Terraria", games_folder);
    new File("Mocorito Simulator.zip", terraria_folder);
    new File("Mods.zip", terraria_folder);

    new Folder("Documentos", root);
    new Folder("Imagenes", root);
    new Folder("Musica", root);
    new Folder("Videos", root);

    auto planeta_verguetta = new File("Planeta Verguetta.zip", root);

    root->showContents();

    std::cout << mods_folder->getPath() << '\n';
    mods_folder->showContents();

    std::cout << mods_folder->children[0]->getPath() << '\n';

    planeta_verguetta->move(minecraft_folder);
    root->showContents();

    games_folder->removeChild(terraria_folder);
    delete terraria_folder;
    root->showContents();

    minecraft_folder->move(mods_folder);
    root->showContents();

    delete root;
    return 0;
}
