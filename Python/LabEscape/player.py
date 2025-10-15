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

    def __init__(self):
        # Maze stuff
        self.x: int = 0
        self.y: int = 0
        self.discovered_maze: Maze|None = None

        # Inventory
        self.health: int = Player.MAX_HEALTH
        self.has_key: bool = False

    # noinspection SpellCheckingInspection
    # FIXME: Pass maze, return messages
    def update(self, game: 'Game') -> None:
        pressed_key = getInput()

        next_x = self.x  # Readability
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
            new_tile = self.discovered_maze.get(next_x, next_y)
            match new_tile:
                case tiles.WALL:
                    next_x = self.x
                    next_y = self.y

                case tiles.DOOR:
                    if self.has_key:
                        self.has_key = False
                        self.discovered_maze.set(next_x, next_y, tiles.EMPTY)

                        game.addMessage("Usaste la llave para abrir la puerta.")
                    else:
                        next_x = self.x
                        next_y = self.y

                        game.addMessage("Necesitas una llave para abrir la puerta.")

                case tiles.KEY:
                    if not self.has_key:
                        self.has_key = True
                        self.discovered_maze.set(next_x, next_y, tiles.EMPTY)

                        game.addMessage("¡Conseguiste una llave!")
                    else:
                        game.addMessage("No puedes llevar más llaves.")

                case tiles.TRAP:
                    self.health -= 1
                    if self.health > 0:
                        self.discovered_maze.set(next_x, next_y, tiles.EMPTY)

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
                        self.discovered_maze.set(next_x, next_y, tiles.EMPTY)

                        game.addMessage("Encontraste un pan duro del soriana...")
                        game.addMessage("Recuperaste 1 de salud.")
                    else:
                        game.addMessage("Pinche golosa, deja de tragar.")

                case tiles.EXIT:
                    game.nextLevel()
                    return

            self.x = next_x
            self.y = next_y

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
