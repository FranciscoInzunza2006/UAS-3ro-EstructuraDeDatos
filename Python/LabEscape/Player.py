import keyboard

import Game
import Tiles
from Maze import Maze
from enum import IntEnum

class Controls(IntEnum):
    RIGHT_KEY = 77
    LEFT_KEY = 75
    UP_KEY = 72
    DOWN_KEY = 80


def getInput() -> int:
    while True:
        event = keyboard.read_event()
        if event.event_type == keyboard.KEY_DOWN:
            key: int = event.scan_code
            if key in Controls:
                return key
            else:
                print(f"Key: {event.name}, ScanCode: {event.scan_code}")


class Player:
    def __init__(self, start_x: int, start_y:int, maze_width:int, maze_height:int):
        self.x = start_x
        self.y = start_y
        self.know_maze = Maze.empty(maze_width, maze_height)

        # Inventory
        self.lives: int = 3
        self.has_key: bool = False

    def update(self):
        pressed_key = getInput()
        self.action(pressed_key)

    def action(self, pressed_key):
        last_x = self.x
        last_y = self.y
        match pressed_key:
            case Controls.RIGHT_KEY:
                self.x = self.x + 1
            case Controls.LEFT_KEY:
                self.x = self.x - 1
            case Controls.UP_KEY:
                self.y = self.y - 1
            case Controls.DOWN_KEY:
                self.y = self.y + 1

        new_tile = self.know_maze.get(self.x, self.y)
        match new_tile:
            case Tiles.WALL:
                self.x = last_x
                self.y = last_y
            case Tiles.DOOR:
                if self.has_key:
                    self.know_maze.set(self.x, self.y, Tiles.EMPTY)
                    self.has_key = False
                    Game.messages.append("Usaste la llave para abrir la puerta.")
                else:
                    self.x = last_x
                    self.y = last_y
                    Game.messages.append("Necesitas una llave para abrir la puerta.")

            case Tiles.KEY:
                if not self.has_key:
                    self.know_maze.set(self.x, self.y, Tiles.EMPTY)
                    self.has_key = True
                    Game.messages.append("¡Conseguiste una llave!")
                else:
                    Game.messages.append("No puedes llevar más llaves.")








