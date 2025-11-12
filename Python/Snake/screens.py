import math

from board import Board
from common import *
from item_manager import ItemManager

from player import Player


class Screen:
    # Fonts
    def __init__(self):
        self.FONT_1 = pygame.font.SysFont("monospace", 60)
        self.FONT_2 = pygame.font.SysFont("arial", 20)

        self.width = BOARD_WIDTH * TILE_SIZE_PX
        self.height = BOARD_HEIGHT * TILE_SIZE_PX

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
        elif key_pressed[pygame.K_ESCAPE]:
            pygame.event.post(EVENT_GAME_OVER)

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
        self.item_manager.step(self.level)

    def draw(self, surface: pygame.Surface):
        self.board.draw(surface)
        self.player.draw(surface)
        self.item_manager.draw(surface)

    def reset(self):
        self.board = Board(BOARD_WIDTH, BOARD_HEIGHT)
        self.player = Player(self.level)
        self.item_manager = ItemManager()

        self.level += 1


class GameOverScreen(Screen):
    def __init__(self):
        super().__init__()

        center_x = self.width // 2
        center_y = self.height // 2

        self.game_over_hover_speed = 0.002
        self.game_over_hover_distance = 10

        self.GAME_OVER_TEXT = self.FONT_1.render("GAME OVER", True, WHITE, BLACK)
        self.game_over_rect = self.GAME_OVER_TEXT.get_rect(center=(center_x, center_y))

        game_over_height = self.game_over_rect.bottom + self.game_over_hover_distance * 4

        self.INSTRUCTIONS_TEXT = self.FONT_2.render("Press Enter to continue", True, WHITE, BLACK)
        self.instructions_rect = self.INSTRUCTIONS_TEXT.get_rect(center=(center_x, game_over_height))


    def step(self):
        key_pressed = pygame.key.get_pressed()
        if key_pressed[pygame.K_RETURN]:
            pygame.event.post(EVENT_MAIN_MENU)

    def draw(self, surface: pygame.Surface):
        surface.fill(BLACK)

        y_offset = math.floor(math.sin(pygame.time.get_ticks() * self.game_over_hover_speed) * self.game_over_hover_distance)

        surface.blit(self.GAME_OVER_TEXT, self.game_over_rect.move(0, y_offset))
        surface.blit(self.INSTRUCTIONS_TEXT, self.instructions_rect)
