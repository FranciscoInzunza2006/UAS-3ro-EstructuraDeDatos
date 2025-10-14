import Colors
from Tile import Tile

EMPTY = Tile("•", Colors.GRAY)

PLAYER = Tile("P", Colors.BRIGHT_RED)

WALL = Tile("#", Colors.CYAN)
DOOR = Tile("#", Colors.MAGENTA)
EXIT = Tile("@", Colors.BRIGHT_MAGENTA)

KEY = Tile("K", Colors.YELLOW)
TRAP = Tile("*", Colors.DARK_GRAY)
LIFE = Tile("H", Colors.BRIGHT_GREEN)

ASCII: bool = False
if ASCII:
    PLAYER.char = "Ϫ"

    KEY.char = "⚿"
    LIFE.char = "❤"

# 🗝 ❤ ⚿
