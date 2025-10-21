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
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)):
    generated_maze = Maze.empty(width, height)
    global force_exit
    force_exit = 0
    if width % 2 == 0:
        width += 1
    if height % 2 == 1:
        height += 1

    # Fill entire maze with walls
    fill_tile = random.choice([tiles.WALL, tiles.TRAP])
    for row in range(height):
        for column in range(width):
            generated_maze.set(column, row, fill_tile)

    # Ensure start position is odd (to align with the 2-step pattern)
    start_x = random.randint(0, width - 1)
    start_y = random.randint(0, height - 1)
    if start_x % 2 == 0:
        start_x = max(1, start_x - 1)
    if start_y % 2 == 0:
        start_y = max(1, start_y - 1)

    generate(generated_maze, start_x, start_y)

    while True:
        place_x = random.randint(0, width - 1)
        place_y = random.randint(0, height - 1)

        if generated_maze.get(place_x, place_y) == tiles.EMPTY:
            generated_maze.set(place_x, place_y, tiles.EXIT)
            break

    for i in range(15):
        place_x = random.randint(0, width - 1)
        place_y = random.randint(0, height - 1)

        if generated_maze.get(place_x, place_y) == tiles.EMPTY:
            generated_maze.set(place_x, place_y,
                               random.choice([tiles.TRAP, tiles.LIFE, tiles.KEY]))
        elif generated_maze.get(place_x, place_y) == tiles.WALL:
            generated_maze.set(place_x, place_y, tiles.DOOR)


    return generated_maze, start_x, start_y

if __name__ == "__main__":
    maze = generateMaze(9, 9)
    maze.draw()