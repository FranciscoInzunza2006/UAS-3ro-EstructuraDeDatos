import Colors
import Game
import Tile
import Tiles
from typing import List


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

        for row in range(height):
            if len(maze_map[row]) != width:
                raise ValueError(f"The maze has a wrong width in the row: {row}")
            for column in range(width):
                tile_char: str = maze_map[row][column].upper()

                tile = {
                    "#": Tiles.WALL,
                    "K": Tiles.KEY,
                    " ": Tiles.EMPTY,
                    "P": Tiles.PLAYER,
                    "D": Tiles.DOOR,
                    "E": Tiles.EXIT,
                }.get(tile_char, None)

                if tile is None:
                    raise ValueError(f"Unknown character {tile_char}")

                maze.maze[row][column] = tile

        return maze

    def draw(self):
        tile_width = 3
        offset: str = " " * 2

        maze_str: str = ""
        for y in range(self.height):
            maze_str += f"{offset}{Tiles.WALL} "
            for x in range(self.width):
                tile: Tile = self.maze[y][x]
                tile_str: str = str(tile)

                left_pad = tile_width // 2
                right_pad = tile_width - left_pad - 1
                if x == Game.player.x and y == Game.player.y:
                    if tile == Tiles.EMPTY:
                        tile_str = str(Tiles.PLAYER)
                    else:
                        tile_str = str(Tiles.PLAYER) + tile_str
                        left_pad -= 1

                maze_str += " " * left_pad + tile_str + " " * right_pad
            maze_str += f"{Tiles.WALL}\n"

        top_bottom_walls: str = offset + Tiles.WALL.color + Tiles.WALL.char * (self.width * tile_width + 3)
        print(f"{top_bottom_walls}\n"
              f"{maze_str}"
              f"{top_bottom_walls}{Colors.RESET}")

    def get(self, x: int, y: int):
        if (x < 0 or x >= self.width) or (y < 0 or y >= self.height):
            return Tiles.WALL
        return self.maze[y][x]

    def set(self, x: int, y: int, tile: str):
        self.maze[y][x] = tile
