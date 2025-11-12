import math

from board import Board
from common import *
import common
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

        center_x = self.width // 2
        center_y = self.height // 2

        self.thingy_speed = 0.004
        self.thingy_scale = 0.25

        self.TITLE_TEXT = self.FONT_1.render("SNAKE", True, WHITE, BLACK)
        self.title_rect = self.TITLE_TEXT.get_rect(center=(center_x, center_y))

        self.INSTRUCTIONS_TEXT = self.FONT_2.render("Press Space to continue", True, WHITE, BLACK)
        self.instructions_rect = self.INSTRUCTIONS_TEXT.get_rect(center=(center_x, self.title_rect.bottom + 40))

        scores.sort(reverse=True)


    def step(self):
        key_pressed = pygame.key.get_pressed()
        if key_pressed[pygame.K_SPACE]:
            pygame.event.post(EVENT_GAME_START)
        elif key_pressed[pygame.K_ESCAPE]:
            pygame.event.post(EVENT_GAME_OVER)

    def draw(self, surface: pygame.Surface):
        surface.fill(BLACK)

        center_x = self.width // 2
        center_y = self.height // 2

        val = math.sin(pygame.time.get_ticks() * self.thingy_speed)

        rot = (math.sin(pygame.time.get_ticks() * self.thingy_speed)) * 10
        scale = math.sin(pygame.time.get_ticks() * self.thingy_speed * 2) * self.thingy_scale
        title = pygame.transform.rotozoom(self.TITLE_TEXT, rot, 1 + scale)
        rect = title.get_rect(center=(center_x, center_y))

        surface.blit(title, rect)
        surface.blit(self.INSTRUCTIONS_TEXT, self.instructions_rect)

        # Scores
        scores_str = ["Scores:"]

        for ranking, score in enumerate(common.scores, 1):
            scores_str.append(f"  #{ranking}: {score}")

        x = 16
        y = 16
        for s in scores_str:
            text = self.FONT_2.render(s, True, WHITE, BLACK)
            surface.blit(text, (x, y))
            y += text.get_height() + 10



class GameplayScreen(Screen):
    def __init__(self):
        super().__init__()
        self.board = None
        self.player = None
        self.item_manager = None
        self.level = 0

        common.current_score = 0

        self.reset()

    def step(self):
        self.player.step(self.item_manager)
        self.item_manager.step()

    def draw(self, surface: pygame.Surface):
        self.board.draw(surface)
        self.player.draw(surface)
        self.item_manager.draw(surface)

        txt = self.FONT_2.render(f"Score: {common.current_score}", True, BLACK)
        surface.blit(txt, (16, 16))

    def reset(self):
        self.board = Board(BOARD_WIDTH, BOARD_HEIGHT)
        self.player = Player(self.level)
        self.item_manager = ItemManager(self.level)

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

        last_score = common.scores[len(common.scores) - 1]
        self.score_msg = self.FONT_2.render(f"You got a score of {last_score}", True, WHITE, BLACK)
        self.score_rect = self.score_msg.get_rect(center=(center_x, game_over_height))

        self.INSTRUCTIONS_TEXT = self.FONT_2.render("Press Enter to continue", True, WHITE, BLACK)
        self.instructions_rect = self.INSTRUCTIONS_TEXT.get_rect(center=(center_x, self.score_rect.bottom + 10))




    def step(self):
        key_pressed = pygame.key.get_pressed()
        if key_pressed[pygame.K_RETURN]:
            pygame.event.post(EVENT_MAIN_MENU)

    def draw(self, surface: pygame.Surface):
        surface.fill(BLACK)

        y_offset = math.floor(math.sin(pygame.time.get_ticks() * self.game_over_hover_speed) * self.game_over_hover_distance)

        surface.blit(self.GAME_OVER_TEXT, self.game_over_rect.move(0, y_offset))
        surface.blit(self.INSTRUCTIONS_TEXT, self.instructions_rect)
        surface.blit(self.score_msg, self.score_rect)


