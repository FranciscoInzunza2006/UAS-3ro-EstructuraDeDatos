from board import Board
from common import *
from item_manager import ItemManager

from player import Player


class Screen:
    # Fonts
    def __init__(self):
        self.FONT_1 = pygame.font.SysFont("monospace", 30)

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        pass


class MainMenuScreen(Screen):
    def __init__(self):
        super().__init__()

    def step(self):
        key_pressed = pygame.key.get_pressed()
        if key_pressed[pygame.K_SPACE]:
            pygame.event.post(EVENT_GAME_START)

    def draw(self, surface: pygame.Surface):
        pass


class GameplayScreen(Screen):
    def __init__(self):
        super().__init__()
        self.board = None
        self.player = None
        self.item_manager = None
        self.level = 0

        self.reset()

    def step(self):
        self.player.step(self.item_manager)
        self.item_manager.step()

    def draw(self, surface: pygame.Surface):
        self.board.draw(surface)
        self.player.draw(surface)
        self.item_manager.draw(surface)

    def reset(self):
        self.board = Board(BOARD_WIDTH, BOARD_HEIGHT)
        self.player = Player(self.board)
        self.item_manager = ItemManager()

        self.level += 1

class GameOverScreen(Screen):
    def __init__(self):
        super().__init__()
        self.GAME_OVER_TEXT = self.FONT_1.render("GAME OVER", True, WHITE, BLACK)

    def step(self):
        key_pressed = pygame.key.get_pressed()
        if key_pressed[pygame.K_RETURN]:
            pygame.event.post(EVENT_MAIN_MENU)

    def draw(self, surface: pygame.Surface):
        surface.fill(BLACK)
        surface.blit(self.GAME_OVER_TEXT, (10, 10))
