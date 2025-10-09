from typing import List
import Util
from Maze import Maze
from Player import Player

class Game:
    def __init__(self):
        self.maze = Maze(12, 12)
        self.messages: List[str] = []
        self.player = Player(0, 0)

    def loop(self):
        while True:
            Util.printSeparator()
            print("Inventario")
            Util.printSeparator()

            self.maze.draw()

            Util.printSeparator()

            self.printMessages()
            self.player.update(self.maze)

    def printMessages(self):
        if len(self.messages) > 0:
            for message in self.messages:
                print(message)
            self.messages.clear()
            Util.printSeparator()