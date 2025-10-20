import tiles
from maze import Maze
import random


def placePath(_maze: Maze, start_x: int, start_y: int, length: int, vertical: bool, direction: int):
    if length == 0:
        return
    x: int = start_x
    y: int = start_y
    placed_paths = 0

    while placed_paths < length:
        if _maze.get(x, y) == tiles.EMPTY: return

        in_bounds = _maze.set(x, y, tiles.EMPTY)
        if not in_bounds:
            direction *= -1

        if vertical: y += direction
        else: x += direction

        placed_paths += 1

        if not in_bounds:
            break

    sx = x
    sy = y
    if random.random() < 0.5:
        if vertical: sy = start_y + random.randrange(0, length)
        else: sx = start_x + random.randrange(0, length)

    new_length = random.randint(3, 8)
    placePath(_maze, sx, sy, new_length, not vertical, random.choice([-1, 1]))


def generateMaze(width: int = random.randint(Maze.MIN_WIDTH, Maze.MAX_WIDTH),
                 height: int = random.randint(Maze.MIN_HEIGHT, Maze.MAX_HEIGHT)) -> Maze:
    generated_maze = Maze.empty(width, height)

    # Fill maze
    for row in range(height):
        for column in range(width):
            generated_maze.set(column, row, tiles.WALL)

    start_x = random.randint(0, width - 1)
    start_y = random.randint(0, height - 1)

    placePath(generated_maze, start_x, start_y, random.randint(5, 10), random.choice([True, False]), random.choice([-1, 1]) )

    generated_maze.set(start_x, start_y, tiles.LIFE)

    return generated_maze


if __name__ == "__main__":
    maze = generateMaze(20, 20)
    maze.draw()
