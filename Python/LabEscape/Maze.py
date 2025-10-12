import Colors
import Game
import Tile
import Tiles
from typing import List

class Maze:
    def __init__(self, width:int = None, height:int = None):
        self.width:int = width
        self.height:int = height

        self.maze: List[List[Tile]] = [[Tiles.EMPTY] * self.width for _ in range(self.height)]

    @classmethod
    def empty(cls, width:int, height:int):
        return cls(width, height)

    @classmethod
    def fromString(cls, maze_map:List[str]):
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
        separator: str = "\t" + str(Tiles.WALL) * (self.width * 3 + 4)

        print(separator)
        for row in range(self.height):
            print(f"\t{Tiles.WALL}", end=" ")

            for column in range(self.width):
                tile = self.maze[row][column]
                if column == Game.player.x and row == Game.player.y:
                    if tile == Tiles.EMPTY:
                        print(f" {Tiles.PLAYER} ", end="")
                    else:
                        print(f"{Tiles.PLAYER} {tile}", end="")
                    continue

                if tile == Tiles.KEY:
                    print(f" {tile}", end="")
                else:
                    print(f" {tile} ", end="")



            print(f" {Tiles.WALL}")
        print(separator)
        print(Colors.RESET)

    def get(self, x:int, y:int):
        if (x < 0 or x >= self.width) or (y < 0 or y >= self.height):
            return Tiles.WALL
        return self.maze[y][x]

    def set(self, x:int, y:int, tile:str):
        self.maze[x][y] = tile
