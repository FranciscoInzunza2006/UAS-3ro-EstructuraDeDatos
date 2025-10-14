from typing import List

import Textbox
from Maze import Maze
from Player import Player

levels: List[List[str]] = [
    [
        " #    ",
        " #K # ",
        "    # ",
        "#####D",
        "E     ",
    ],
    [
        "P      T    H   E",
    ],
]

current_level: int = -1
maze = None
messages: List[str] = []

def loop():
    nextLevel()
    while True:
        # os.system("cls" if os.name == "nt" else "clear")

        Player.drawInventory()
        Player.know_maze.draw()
        printMessages()
        Textbox.drawBottom()

        Player.update()

def printMessages():
    if len(messages) > 0:
        Textbox.drawMiddleBox(messages)
        messages.clear()

def nextLevel():
    global current_level
    current_level += 1

    global maze
    maze = Maze.fromString(levels[current_level])

    Player.know_maze = maze