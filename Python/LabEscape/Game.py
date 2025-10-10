from time import sleep
from typing import List

import Tiles
import Util
from Maze import Maze
from Player import Player

maze = Maze(12, 12)
messages: List[str] = []
player = Player(0, 0, 12, 12)
player.know_maze = maze

maze.set(2, 2, Tiles.KEY)

def loop():
    while True:
        Util.printSeparator()
        print("Inventario")
        Util.printSeparator()

        player.know_maze.draw()

        Util.printSeparator()
        printMessages()

        player.action()
        sleep(0.1)

def printMessages():
    if len(messages) > 0:
        for message in messages:
            print(message)
        messages.clear()
        Util.printSeparator()