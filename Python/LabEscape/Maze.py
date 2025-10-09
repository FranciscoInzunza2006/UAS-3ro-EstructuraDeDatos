import Colors
import Tile
import Tiles
from typing import List

class Maze:
    def __init__(self, width:int, height:int):
        self.width:int = width
        self.height:int = height

        self.maze: List[List[Tile]] = [[Tiles.EMPTY] * self.height for _ in range(self.width)]

    def draw(self):
        separator: str = "\t" + str(Tiles.WALL) * (self.width * 3 + 4)

        print(separator)
        for row in range(self.height):
            print(f"\t{Tiles.WALL}", end=" ")

            for column in range(self.width):
                tile = self.maze[column][row]
                print(f" {tile} ", end="")

            print(f" {Tiles.WALL}")
        print(separator)
        print(Colors.RESET)

    def get(self, x:int, y:int):
        if (x < 0 or x > self.width) or (y < 0 or y > self.height):
            return Tiles.WALL
        return self.maze[x][y]

    def set(self, x:int, y:int, tile:str):
        self.maze[x][y] = tile
