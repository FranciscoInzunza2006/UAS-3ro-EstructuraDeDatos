from time import sleep
from typing import List

import Tiles
import Util
from Maze import Maze
from Player import Player

maze_map = [
    " #    ",
    " #K # ",
    "    # ",
    "#####D",
    "E     ",
]
maze = Maze.fromString(maze_map)

messages: List[str] = []
player = Player(0, 0, maze.width, maze.height)
player.know_maze = maze
def loop():
    while True:
        Util.printSeparator()
        print("Inventario")
        Util.printSeparator()

        #maze.draw()
        player.know_maze.draw()

        Util.printSeparator()
        printMessages()

        player.update()


def printMessages():
    if len(messages) > 0:
        for message in messages:
            print(message)
        messages.clear()
        Util.printSeparator()
