
class Tile:
    def __init__(self, char:str, color:str) -> None:
        self.char = char
        self.color = color
    def __str__(self) -> str:
        return self.color + self.char