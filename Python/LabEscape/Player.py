import keyboard

import Colors
import Game
import Tiles
import Util
from Maze import Maze
from enum import IntEnum
from Util import BOX_WIDTH

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
    MAX_LIVES: int = 3

    def __init__(self):
        self.x = 0
        self.y = 0
        self.know_maze = None

        # Inventory
        self.lives: int = Player.MAX_LIVES
        self.has_key: bool = False

    def drawInventory(self):
        padding: int = BOX_WIDTH
        color_code_len:int = len(Colors.GRAY) # The color codes messes up with the length

        lives: str = "Lives: "
        lives += Tiles.LIFE.color +  (str(Tiles.LIFE.char) + " ") * self.lives

        missing_lives: int = Player.MAX_LIVES - self.lives
        lives += Colors.GRAY + (Tiles.LIFE.char + " ") * missing_lives

        padding -= len(lives) - color_code_len * (2 if missing_lives > 0 else 1)

        inventory: str = ""
        inventory += (Tiles.KEY.color if self.has_key else Colors.GRAY) + Tiles.KEY.char + " "
        padding -= len(inventory) - color_code_len * 1

        Util.drawTopBox([f"{lives}{' ' * padding}{inventory}{Colors.RESET}"])

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
