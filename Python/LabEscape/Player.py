import keyboard
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
        self.know_maze = Maze(maze_width, maze_height)

    def update(self):
        pressed_key = getInput()
        self.action(pressed_key)

    def action(self, pressed_key):
        match pressed_key:
            case Controls.RIGHT_KEY:
                self.x = (self.x + 1) % self.know_maze.width


