import Colors
import Textbox
import Tiles
from Input import getInput, Controls
from Maze import Maze
from Textbox import BOX_WIDTH


class Player:
    MAX_HEALTH: int = 3

    def __init__(self):
        # Maze stuff
        self.x: int = 0
        self.y: int = 0
        self.discovered_maze = None

        # Inventory
        self.health: int = Player.MAX_HEALTH
        self.has_key: bool = False

    # noinspection SpellCheckingInspection
    # FIXME: Pass maze, return messages
    def update(self):
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
                # game.nextLevel()
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
                case Tiles.WALL:
                    next_x = self.x
                    next_y = self.y

                case Tiles.DOOR:
                    if self.has_key:
                        self.has_key = False
                        self.discovered_maze.set(next_x, next_y, Tiles.EMPTY)

                        #game.addMessage("Usaste la llave para abrir la puerta.")
                    else:
                        next_x = self.x
                        next_y = self.y

                        #game.addMessage("Necesitas una llave para abrir la puerta.")

                case Tiles.KEY:
                    if not self.has_key:
                        self.has_key = True
                        self.discovered_maze.set(next_x, next_y, Tiles.EMPTY)

                        #game.addMessage("¡Conseguiste una llave!")
                    else:
                        pass#game.addMessage("No puedes llevar más llaves.")

                case Tiles.TRAP:
                    if self.health > 1:
                        self.health -= 1
                        self.discovered_maze.set(next_x, next_y, Tiles.EMPTY)

                        #game.addMessage("¡Caiste en una trampa! Sigues con tu vida.")
                        #game.addMessage("Perdiste 1 de salud.")
                    else:
                        pass#game.addMessage("¿PORQUÉ?")
                        #game.addMessage("¿PORQUÉ HICISTE ESO?")
                        #game.addMessage("¿HOLA? ¿SÍ? ¿ASOCIACIÓN DE GENTE QUE TIENE OJOS?")
                        #game.addMessage("¡NUMERO EQUIVOCADO!")
                        #game.addMessage("PORQUE NO ME CREO QUE EL QUE TENGO AQUÍ ENFRENTE")
                        #game.addMessage("PUEDA SER TAN IMBECIL")
                        #game.addMessage("EN SERIO. ¿COMO HICISTE ESO?")
                        #game.addMessage("USA TUS OJOS")
                        #game.addMessage("ES POR TU CULPA QUE BRONCE EXISTE PEDAZO DE MANCO")
                        #game.addMessage("NO TE QUIERO VER OTRA VEZ")

                case Tiles.LIFE:
                    if self.health < Player.MAX_HEALTH:
                        self.health += 1
                        self.discovered_maze.set(next_x, next_y, Tiles.EMPTY)

                        #game.addMessage("Encontraste un pan duro del soriana...")
                        #game.addMessage("Recuperaste 1 de salud.")
                    else:
                        pass#game.addMessage("Pinche golosa, deja de tragar.")

                case Tiles.EXIT:
                    #game.nextLevel()

                    #game.addMessage("Entras en un portal...")
                    #game.addMessage(f"Nivel {game.current_level + 1}")
                    return

            self.x = next_x
            self.y = next_y

    def drawInventory(self):
        padding: int = BOX_WIDTH
        color_code_len: int = len(Colors.GRAY)  # The color codes messes up with the length

        health_display: str = "Lives: "
        health_display += Colors.BRIGHT_RED + (str(Tiles.LIFE.char) + " ") * self.health

        missing_health: int = self.MAX_HEALTH - self.health
        health_display += Colors.GRAY + (Tiles.LIFE.char + " ") * missing_health

        padding -= len(health_display) - color_code_len * 2

        inventory: str = ""
        inventory += (Tiles.KEY.color if self.has_key else Colors.GRAY) + Tiles.KEY.char + " "
        padding -= len(inventory) - color_code_len * 1

        Textbox.drawTopBox([f"{health_display}{' ' * padding}{inventory}{Colors.RESET}"])
