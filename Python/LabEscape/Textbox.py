from typing import List

TOP_LEFT:str = "┌"
TOP_RIGHT:str = "┐"

TEE_LEFT = "├"
TEE_RIGHT = "┤"

HORIZONTAL_LINE: str = "─"
VERTICAL_LINE: str = "│"

BOTTOM_LEFT:str = "└"
BOTTOM_RIGHT:str = "┘"

BOX_WIDTH: int = 60
BOX_TOP: str = f"{TOP_LEFT}{HORIZONTAL_LINE * (BOX_WIDTH+2)}{TOP_RIGHT}"
BOX_SEPARATOR: str = f"{TEE_LEFT}{HORIZONTAL_LINE * (BOX_WIDTH+2)}{TEE_RIGHT}"
BOX_BOTTOM: str = f"{BOTTOM_LEFT}{HORIZONTAL_LINE * (BOX_WIDTH+2)}{BOTTOM_RIGHT}"

def drawTopBox(lines: List[str]):
    print(BOX_TOP)
    for s in lines:
        print(f"{VERTICAL_LINE} {s:<{BOX_WIDTH}} {VERTICAL_LINE}")

def drawMiddleBox(lines: List[str]):
    print(BOX_SEPARATOR)
    for s in lines:
        print(f"{VERTICAL_LINE} {s:<{BOX_WIDTH}} {VERTICAL_LINE}")

def drawBottom():
    print(BOX_BOTTOM)


if __name__ == "__main__":
    drawTopBox(["My very","cool app"])
    drawMiddleBox(["Some more", "info (I guess)."])
    drawMiddleBox(["A bit more", "?????."])
    drawBottom()