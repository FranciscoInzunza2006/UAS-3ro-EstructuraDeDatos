import os
import random
from typing import List

import textbox
from maze import Maze
from maze_generator import generateMaze
from player import Player

LEVELS: List[List[str]] = [
    [
        "P#    ",
        " #K # ",
        "    # ",
        "#####D",
        "E     ",
    ],
    [
        "P      T    H    E",
    ],
    [
        "         *    * DE",
        "* *****     *   *#",
        "      *  *   *****",
        " ******  * * *    ",
        " *   H*  ***** ** ",
        " * *****       *  ",
        " * **   ******** *",
        " * ** *       **  ",
        "K*    *P*****     ",
    ]
]

class Game:
    def __init__(self):
        self.player = Player()
        self.current_level: int = -1
        self.maze = None
        self.messages: List[str] = []
        self.keep_going: bool = True

        self.step_count = 0


    def loop(self):
        self.nextLevel()
        while True:
            #os.system("cls" if os.name == "nt" else "clear")

            self.player.drawInventory()
            self.player.discovered_maze.draw(self.player)
            self.printMessages()
            textbox.drawBottom()

            if not self.keep_going:
                break

            self.player.update(self)

    def printMessages(self):
        if len(self.messages) > 0:
            textbox .drawMiddleBox(self.messages)
            self.messages.clear()

    def nextLevel(self):
        self.current_level += 1

        if self.current_level < len(LEVELS):
            self.maze = Maze.fromString(LEVELS[self.current_level], self.player)
            self.player.changeMaze(self.maze, False)

            self.addMessage("Entras en un portal...")
            self.addMessage(f"Nivel {self.current_level + 1}")
        else:
            width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH)
            height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)

            self.maze, px, py = generateMaze(width, height)
            self.player.x = px
            self.player.y = py
            self.player.changeMaze(self.maze, False)

            self.addMessage("El calabozo se siente infinito...")
            self.addMessage(f"Nivel {self.current_level + 1}")

    def gameOver(self):
        self.keep_going = False

    def addMessage(self, message: str) -> None:
        self.messages.append(message)

    def addMessages(self, messages: List[str]) -> None:
        for message in messages:
            self.addMessage(message)
