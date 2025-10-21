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

    if (grid.get(cx - 2, cy) != tiles.EMPTY or
            grid.get(cx + 2, cy) != tiles.EMPTY or
            grid.get(cx, cy - 2) != tiles.EMPTY or
            grid.get(cx, cy + 2) != tiles.EMPTY):
        li = [1, 2, 3, 4]
        while len(li) > 0:
            dir = random.choice(li)
            li.remove(dir)

            if dir == Directions.UP.value:
                nx = cx
                mx = cx
                ny = cy - 2
                my = cy - 1
            elif dir == Directions.DOWN.value:
                nx = cx
                mx = cx
                ny = cy + 2
                my = cy + 1
            elif dir == Directions.LEFT.value:
                nx = cx - 2
                mx = cx - 1
                ny = cy
                my = cy
            elif dir == Directions.RIGHT.value:
                nx = cx + 2
                mx = cx + 1
                ny = cy
                my = cy
            else:
                nx = cx
                mx = cx
                ny = cy
                my = cy

            if grid.get(nx, ny) != tiles.EMPTY:
                if not grid.set(mx, my, tiles.EMPTY):
                    return
                generate(grid, nx, ny)


def generateMaze(width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH),
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)) -> Maze:
    generated_maze = Maze.empty(width, height)

    # Fill maze
    for row in range(height):
        for column in range(width):
            if row % 2 == 1 or column % 2 == 1:
                generated_maze.set(column, row, tiles.WALL)

    start_x = random.randint(0, width - 1)
    start_y = random.randint(0, height - 1)

    if start_x % 2 == 1:
        start_x += 1
    if start_y % 2 == 1:
        start_y += 1

    generate(generated_maze, start_x, start_y)

    generated_maze.set(start_x, start_y, tiles.LIFE)

    return generated_maze


if __name__ == "__main__":
    maze = generateMaze(11, 11)
    maze.draw()
