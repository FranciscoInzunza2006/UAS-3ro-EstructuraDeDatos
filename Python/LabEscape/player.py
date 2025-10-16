import colors
import tiles
from input import getInput, Controls
import textbox

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from game import Game
    from maze import Maze


class Player:
    MAX_HEALTH: int = 3
    VISION_RADIUS: int = 2

    def __init__(self):
        # Maze stuff
        self.x: int = 0
        self.y: int = 0
        self.discovered_maze: Maze | None = None

        # Inventory
        self.health: int = Player.MAX_HEALTH
        self.has_key: bool = False

    def update(self, game: 'Game') -> None:
        pressed_key = getInput()

        # Handle input
        next_x = self.x
        next_y = self.y
        match pressed_key:
            case Controls.RIGHT_KEY:
                next_x += 1
            case Controls.LEFT_KEY:
                next_x -= 1
            case Controls.UP_KEY:
                next_y -= 1
            case Controls.DOWN_KEY:
                next_y += 1

            # DEBUG
            case Controls.ONE:
                game.nextLevel()
                return

            case Controls.TWO:
                self.health -= 1
            case Controls.THREE:
                self.health += 1

            case Controls.FOUR:
                self.has_key = not self.has_key

        if next_x != self.x or next_y != self.y:
            self.move(game, next_x, next_y)

    # noinspection SpellCheckingInspection
    def move(self, game: 'Game', to_x: int, to_y: int):
        # Collision and interaction
        new_tile = game.maze.get(to_x, to_y)
        maze = game.maze
        match new_tile:
            case tiles.WALL:
                to_x = self.x
                to_y = self.y

            case tiles.DOOR:
                if self.has_key:
                    self.has_key = False
                    maze.set(to_x, to_y, tiles.EMPTY)

                    game.addMessage("Usaste la llave para abrir la puerta.")
                else:
                    to_x = self.x
                    to_y = self.y

                    game.addMessage("Necesitas una llave para abrir la puerta.")

            case tiles.KEY:
                if not self.has_key:
                    self.has_key = True
                    maze.set(to_x, to_y, tiles.EMPTY)

                    game.addMessage("¡Conseguiste una llave!")
                else:
                    game.addMessage("No puedes llevar más llaves.")

            case tiles.TRAP:
                self.health -= 1
                if self.health > 0:
                    maze.set(to_x, to_y, tiles.EMPTY)

                    game.addMessage("¡Caiste en una trampa! Sigues con tu vida.")
                    game.addMessage("Perdiste 1 de salud.")
                else:
                    game.gameOver()

                    game.addMessage("¿PORQUÉ?")
                    game.addMessage("¿PORQUÉ HICISTE ESO?")
                    game.addMessage("¿HOLA? ¿SÍ? ¿ASOCIACIÓN DE GENTE QUE TIENE OJOS?")
                    game.addMessage("¡NUMERO EQUIVOCADO!")
                    game.addMessage("PORQUE NO ME CREO QUE EL QUE TENGO AQUÍ ENFRENTE")
                    game.addMessage("PUEDA SER TAN IMBECIL")
                    game.addMessage("EN SERIO. ¿COMO HICISTE ESO?")
                    game.addMessage("USA TUS OJOS")
                    game.addMessage("ES POR TU CULPA QUE BRONCE EXISTE PEDAZO DE MANCO")
                    game.addMessage("NO TE QUIERO VER OTRA VEZ")

            case tiles.LIFE:
                if self.health < Player.MAX_HEALTH:
                    self.health += 1
                    maze.set(to_x, to_y, tiles.EMPTY)

                    game.addMessage("Encontraste un pan duro del soriana...")
                    game.addMessage("Recuperaste 1 de salud.")
                else:
                    game.addMessage("Pinche golosa, deja de tragar.")

            case tiles.EXIT:
                game.nextLevel()
                return

        self.x = to_x
        self.y = to_y

        self.revealMazeAround(game.maze)

    def revealMazeAround(self, maze: 'Maze') -> None:
        for surround_y in range(self.y - Player.VISION_RADIUS, self.y + Player.VISION_RADIUS + 1):
            if surround_y < 0: continue
            if surround_y >= maze.height: break

            for surround_x in range(self.x - Player.VISION_RADIUS, self.x + Player.VISION_RADIUS + 1):
                if surround_x < 0: continue
                if surround_x >= maze.width: break

                self.discovered_maze.set(surround_x, surround_y, maze.get(surround_x, surround_y))

    def drawInventory(self):
        padding: int = textbox.BOX_WIDTH
        color_code_len: int = len(colors.GRAY)  # The color codes messes up with the length

        health_display: str = "Lives: "
        health_display += colors.BRIGHT_RED + (str(tiles.LIFE.char) + " ") * self.health

        missing_health: int = self.MAX_HEALTH - self.health
        health_display += colors.GRAY + (tiles.LIFE.char + " ") * missing_health

        padding -= len(health_display) - color_code_len * 2

        inventory: str = ""
        inventory += (tiles.KEY.color if self.has_key else colors.GRAY) + tiles.KEY.char + " "
        padding -= len(inventory) - color_code_len * 1

        textbox.drawTopBox([f"{health_display}{' ' * padding}{inventory}{colors.RESET}"])
