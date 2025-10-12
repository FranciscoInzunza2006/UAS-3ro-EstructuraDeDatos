import os
from typing import List

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
        os.system("cls" if os.name == "nt" else "clear")

        player.drawInventory()
        player.know_maze.draw()
        printMessages()
        Util.drawBottom()

        player.update()


def printMessages():
    if len(messages) > 0:
        Util.drawMiddleBox(messages)
        messages.clear()
