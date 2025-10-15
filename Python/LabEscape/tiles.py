import colors

class Tile:
    def __init__(self, char:str, color:str) -> None:
        self.char = char
        self.color = color
    def __str__(self) -> str:
        return self.color + self.char

EMPTY = Tile("•", colors.GRAY)

PLAYER = Tile("P", colors.BRIGHT_RED)

WALL = Tile("#", colors.CYAN)
DOOR = Tile("#", colors.MAGENTA)
EXIT = Tile("@", colors.BRIGHT_MAGENTA)

KEY = Tile("K", colors.YELLOW)
TRAP = Tile("*", colors.DARK_GRAY)
LIFE = Tile("H", colors.BRIGHT_GREEN)

ASCII: bool = True
if ASCII:
    PLAYER.char = "Ϫ"

    KEY.char = "⚿"
    LIFE.char = "❤"

# 🗝 ❤ ⚿
