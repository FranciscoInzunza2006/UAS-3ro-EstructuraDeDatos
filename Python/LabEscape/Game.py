from typing import List

import Textbox
from Maze import Maze
from Player import Player

LEVELS: List[List[str]] = [
    [
        "P#    ",
        " #K # ",
        "    # ",
        "#####D",
        "E     ",
    ],
    [
        "P      T    H    E",  # <-- Max width
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


    def loop(self):
        self.nextLevel()
        while True:
            # os.system("cls" if os.name == "nt" else "clear")

            self.player.drawInventory()
            self.player.discovered_maze.draw(self.player.x, self.player.y)
            self.printMessages()
            Textbox.drawBottom()

            if not self.keep_going:
                break

            self.player.update()

    def printMessages(self):
        if len(self.messages) > 0:
            Textbox.drawMiddleBox(self.messages)
            self.messages.clear()

    def nextLevel(self):
        self.current_level += 1

        if self.current_level < len(LEVELS):
            self.maze, self.player.x, self.player.y = Maze.fromString(LEVELS[self.current_level])
            self.player.discovered_maze = self.maze

            Player.know_maze = self.maze
        else:
            self.addMessage("GG")
            self.keep_going = False

    def gameOver(self):
        self.keep_going = False

    def addMessage(self, message: str) -> None:
        self.messages.append(message)

    def addMessages(self, messages: List[str]) -> None:
        for message in messages:
            self.addMessage(message)
