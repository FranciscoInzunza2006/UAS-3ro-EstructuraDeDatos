import tiles
from maze import Maze
import random


def generateMaze(width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH),
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)) -> Maze:
    generated_maze = Maze.empty(width, height)

    # Place walls
    number_of_starter_walls: int = (width * height) * 45 // 100
    for i in range(number_of_starter_walls):
        x: int = random.randint(0, width - 1)
        y: int = random.randint(0, height - 1)

        vertical: bool = bool(random.randint(0, 1))
        direction = random.choice([1, -1])

        xw = x
        yw = y
        while True:
            if generated_maze.get(xw, yw) == tiles.WALL:
                break

            generated_maze.set(xw, yw, tiles.WALL)
            if vertical:
                yw += direction
            else:
                xw += direction

            if random.random() < 0.1:
                break

    return generated_maze


if __name__ == "__main__":
    maze = generateMaze()
    maze.draw()
