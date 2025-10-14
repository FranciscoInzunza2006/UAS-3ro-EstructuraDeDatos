import Colors
import Game
import Textbox
import Tiles
from Input import getInput, Controls
from Textbox import BOX_WIDTH


class Player:
    MAX_HEALTH: int = 3

    # Maze stuff
    x = 0
    y = 0
    know_maze = None

    # Inventory
    health: int = MAX_HEALTH
    has_key: bool = False

    # noinspection SpellCheckingInspection
    @staticmethod
    def update():
        pressed_key = getInput()

        x = Player.x  # Readability
        y = Player.y
        match pressed_key:
            case Controls.RIGHT_KEY:
                x += 1
            case Controls.LEFT_KEY:
                x -= 1
            case Controls.UP_KEY:
                y -= 1
            case Controls.DOWN_KEY:
                y += 1

            #DEBUG
            case Controls.ONE:
                Game.nextLevel()

            case Controls.TWO:
                Player.health -= 1
            case Controls.THREE:
                Player.health += 1

            case Controls.FOUR:
                Player.has_key = not Player.has_key

        if x != Player.x or y != Player.y:
            new_tile = Player.know_maze.get(x, y)
            match new_tile:
                case Tiles.WALL:
                    x = Player.x
                    y = Player.y

                case Tiles.DOOR:
                    if Player.has_key:
                        Player.has_key = False
                        Player.know_maze.set(x, y, Tiles.EMPTY)

                        Game.messages.append("Usaste la llave para abrir la puerta.")
                    else:
                        x = Player.x
                        y = Player.y

                        Game.messages.append("Necesitas una llave para abrir la puerta.")

                case Tiles.KEY:
                    if not Player.has_key:
                        Player.has_key = True
                        Player.know_maze.set(x, y, Tiles.EMPTY)

                        Game.messages.append("¡Conseguiste una llave!")
                    else:
                        Game.messages.append("No puedes llevar más llaves.")

                case Tiles.TRAP:
                    Player.health -= 1
                    Player.know_maze.set(x, y, Tiles.EMPTY)

                    Game.messages.append("¡Caiste en una trampa!")
                    Game.messages.append("Perdiste 1 de salud.")

                case Tiles.LIFE:
                    Player.health += 1
                    Player.know_maze.set(x, y, Tiles.EMPTY)

                    Game.messages.append("Encontraste un pan duro del soriana...")
                    Game.messages.append("Recuperaste 1 de salud.")

                case Tiles.EXIT:
                    Game.nextLevel()

                    Game.messages.append("Entras en un portal...")
                    Game.messages.append(f"Nivel {Game.current_level + 1}")
                    return

            Player.x = x
            Player.y = y

    @staticmethod
    def drawInventory():
        padding: int = BOX_WIDTH
        color_code_len: int = len(Colors.GRAY)  # The color codes messes up with the length

        health_display: str = "Lives: "
        health_display += Colors.BRIGHT_RED  + (str(Tiles.LIFE.char) + " ") * Player.health

        missing_health: int = Player.MAX_HEALTH - Player.health
        health_display += Colors.GRAY + (Tiles.LIFE.char + " ") * missing_health

        padding -= len(health_display) - color_code_len * 2

        inventory: str = ""
        inventory += (Tiles.KEY.color if Player.has_key else Colors.GRAY) + Tiles.KEY.char + " "
        padding -= len(inventory) - color_code_len * 1

        Textbox.drawTopBox([f"{health_display}{' ' * padding}{inventory}{Colors.RESET}"])
