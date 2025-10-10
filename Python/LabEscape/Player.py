import keyboard
from Maze import Maze


class Player:
    RIGHT_KEY: int = 77
    LEFT_KEY: int = 75
    UP_KEY: int = 72
    DOWN_KEY: int = 80

    def __init__(self, start_x: int, start_y:int, maze_width:int, maze_height:int):
        self.x = start_x
        self.y = start_y
        self.know_maze = Maze(maze_width, maze_height)

    def action(self):
        while True:
            event = keyboard.read_event()
            if event.event_type == keyboard.KEY_DOWN:
                key: int = event.scan_code
                if key == self.RIGHT_KEY:
                    self.x = self.x + 1
                elif key == self.LEFT_KEY:
                    self.x = self.x - 1
                elif key == self.UP_KEY:
                    self.y = self.y - 1
                elif key == self.DOWN_KEY:
                    self.y = self.y + 1
                else:
                    print(f"Key: {event.name}, ScanCode: {event.scan_code}")
                    continue

                break
