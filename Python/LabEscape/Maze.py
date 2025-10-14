from typing import List

import Colors
import Textbox
import Tile
import Tiles


class Maze:
    def __init__(self, width: int = None, height: int = None):
        self.width: int = width
        self.height: int = height

        self.maze: List[List[Tile]] = [[Tiles.EMPTY] * self.width for _ in range(self.height)]

    @classmethod
    def empty(cls, width: int, height: int):
        return cls(width, height)

    @classmethod
    def fromString(cls, maze_map: List[str]):
        width = len(maze_map[0])
        height = len(maze_map)

        maze = cls(width, height)

        player_x = None
        player_y = None
        for y in range(height):
            if len(maze_map[y]) != width:
                raise ValueError(f"The maze has a wrong width in the row: {y}")
            for x in range(width):
                tile_char: str = maze_map[y][x].upper()

                tile = {
                    "#": Tiles.WALL,
                    "K": Tiles.KEY,
                    " ": Tiles.EMPTY,
                    "P": Tiles.PLAYER,
                    "D": Tiles.DOOR,
                    "E": Tiles.EXIT,

                    "T": Tiles.TRAP,
                    "*": Tiles.TRAP,

                    "H": Tiles.LIFE
                }.get(tile_char, None)

                if tile is None:
                    raise ValueError(f"Unknown character {tile_char}")

                if  tile == Tiles.PLAYER:
                    player_x = x
                    player_y = y
                else:
                    maze.maze[y][x] = tile

        return maze, player_x, player_y

    def draw(self, player_x, player_y):
        tile_width = 3
        offset_length = 2
        row_width = tile_width * self.width + 3

        row_right_padding: int = Textbox.BOX_WIDTH - offset_length - row_width

        offset: str = " " * offset_length
        maze_str: str = ""
        for y in range(self.height):
            maze_str += f"{offset}{Tiles.WALL} "
            for x in range(self.width):
                tile = self.maze[y][x]
                tile_str = str(tile)

                left_pad = tile_width // 2
                right_pad = tile_width - left_pad - 1
                if x == player_x and y == player_y:
                    if tile == Tiles.EMPTY:
                        tile_str = str(Tiles.PLAYER)
                    else:
                        tile_str = str(Tiles.PLAYER) + tile_str
                        left_pad -= 1

                maze_str += " " * left_pad + tile_str + " " * right_pad
            maze_str += str(Tiles.WALL) + Colors.RESET + (" " * row_right_padding) + "\n"

        top_bottom_walls: str = offset + Tiles.WALL.color + (Tiles.WALL.char * row_width) + Colors.RESET + (
                " " * row_right_padding) + "\n"
        maze_str = top_bottom_walls + maze_str + top_bottom_walls

        Textbox.drawMiddleBox(maze_str.splitlines())
        print(Colors.RESET, end="")

    def get(self, x: int, y: int):
        if (x < 0 or x >= self.width) or (y < 0 or y >= self.height):
            return Tiles.WALL
        return self.maze[y][x]

    def set(self, x: int, y: int, tile: str):
        self.maze[y][x] = tile
