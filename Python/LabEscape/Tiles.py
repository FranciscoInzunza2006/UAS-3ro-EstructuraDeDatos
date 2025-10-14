import Colors
from Tile import Tile

ASCII:bool = True

if ASCII:
    EMPTY = Tile("•", Colors.GRAY)

    PLAYER = Tile("P", Colors.BRIGHT_RED)

    WALL = Tile("#", Colors.CYAN)
    DOOR = Tile("#", Colors.MAGENTA)
    EXIT = Tile("@", Colors.BRIGHT_MAGENTA)

    KEY = Tile("K", Colors.YELLOW)
    TRAP = Tile("*", Colors.DARK_GRAY)
    LIFE = Tile("H", Colors.BRIGHT_RED)
else:
    EMPTY = Tile("•", Colors.RESET)

    PLAYER = Tile("P", Colors.CYAN)

    WALL = Tile("#", Colors.DARK_GRAY)
    DOOR = Tile("#", Colors.BROWN)
    EXIT = Tile("░", Colors.BRIGHT_MAGENTA)

    KEY = Tile("⚿", Colors.YELLOW)
    TRAP = Tile("*", Colors.RED)
    LIFE = Tile("❤", Colors.BRIGHT_RED)

# 🗝 ❤ ⚿