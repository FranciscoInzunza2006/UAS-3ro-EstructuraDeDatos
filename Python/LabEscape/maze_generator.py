import tiles
from maze import Maze
import random


def placePath(_maze: Maze, start_x: int, start_y: int, length: int, vertical: bool, direction: int):
    end_x = start_x + ((length * direction) if not vertical else 0)
    end_y = start_y + ((length * direction) if vertical else 0)

    for x in range(start_x, end_x):
        for y in range(start_y, end_y):
            if _maze.get(x, y) == tiles.EMPTY: return

            in_bounds = _maze.set(x, y, tiles.EMPTY)
            if not in_bounds:
                return

    new_start_x = random.randint(start_x, end_x) if vertical else start_x
    new_start_y = random.randint(start_y, end_y) if not vertical else start_y
    new_length = random.randint(3, 8)
    placePath(_maze, new_start_x, new_start_y, new_length, not vertical, random.choice([-1, 1]))


def generateMaze(width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH),
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)) -> Maze:
    generated_maze = Maze.empty(width, height)

    # Fill maze
    for row in range(height):
        for column in range(width):
            generated_maze.set(column, row, tiles.WALL)

    start_x = random.randint(0, width - 1)
    start_y = random.randint(0, height - 1)

    placePath(generated_maze, start_x, start_y, 20, True, 1)

    return generated_maze


if __name__ == "__main__":
    maze = generateMaze()
    maze.draw()
