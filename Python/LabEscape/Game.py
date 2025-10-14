from typing import List

import Textbox
from Maze import Maze
from Player import Player

LEVELS: List[List[str]] = [
    [
        " #    ",
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
    current_level: int = -1
    maze = None
    messages: List[str] = []
    keep_going: bool = True

    @staticmethod
    def loop():
        Game.nextLevel()
        while True:
            # os.system("cls" if os.name == "nt" else "clear")

            Player.drawInventory()
            Player.know_maze.draw()
            Game.printMessages()
            Textbox.drawBottom()

            if not Game.keep_going:
                break

            Player.update()

    @staticmethod
    def printMessages():
        if len(Game.messages) > 0:
            Textbox.drawMiddleBox(Game.messages)
            Game.messages.clear()

    @staticmethod
    def nextLevel():
        Game.current_level += 1

        if Game.current_level < len(LEVELS):
            Game.maze = Maze.fromString(LEVELS[Game.current_level])

            Player.know_maze = Game.maze
        else:
            Game.addMessage("GG")
            Game.keep_going = False

    @staticmethod
    def gameOver():
        Game.keep_going = False

    @staticmethod
    def addMessage(message: str) -> None:
        Game.messages.append(message)

    @staticmethod
    def addMessages(messages: List[str]) -> None:
        for message in messages:
            Game.addMessage(message)
