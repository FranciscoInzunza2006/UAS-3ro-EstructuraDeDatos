from enum import Enum

import tiles
from maze import Maze
import random

class Directions(Enum):
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4

def generate(grid: Maze, cx: int, cy: int):
    grid.set(cx, cy, tiles.EMPTY)

    directions = [Directions.UP, Directions.DOWN, Directions.LEFT, Directions.RIGHT]
    random.shuffle(directions)  # Randomize direction order

    for direction in directions:
        if direction == Directions.UP:
            nx, ny = cx, cy - 2
            mx, my = cx, cy - 1
        elif direction == Directions.DOWN:
            nx, ny = cx, cy + 2
            mx, my = cx, cy + 1
        elif direction == Directions.LEFT:
            nx, ny = cx - 2, cy
            mx, my = cx - 1, cy
        elif direction == Directions.RIGHT:
            nx, ny = cx + 2, cy
            mx, my = cx + 1, cy

        # Check if the target cell is within bounds and unvisited
        if (0 <= nx < grid.width and 0 <= ny < grid.height and
            grid.get(nx, ny) != tiles.EMPTY):
            grid.set(mx, my, tiles.EMPTY)
            generate(grid, nx, ny)

def generateMaze(width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH),
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)) -> Maze:
    generated_maze = Maze.empty(width, height)

    # Fill entire maze with walls
    for row in range(height):
        for column in range(width):
            generated_maze.set(column, row, tiles.WALL)

    # Ensure start position is odd (to align with the 2-step pattern)
    start_x = random.randint(0, width - 1)
    start_y = random.randint(0, height - 1)
    if start_x % 2 == 0:
        start_x = max(1, start_x - 1)
    if start_y % 2 == 0:
        start_y = max(1, start_y - 1)

    generate(generated_maze, start_x, start_y)

    # Set player start position
    generated_maze.set(start_x, start_y, tiles.LIFE)

    return generated_maze

if __name__ == "__main__":
    maze = generateMaze(9, 9)
    maze.draw()