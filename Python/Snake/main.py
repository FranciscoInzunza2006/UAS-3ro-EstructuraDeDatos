from time import sleep

from board import Board
from common import *
from screens import MainMenuScreen, Screen, GameOverScreen, GameplayScreen


class Snake:
    WINDOW_CAPTION = "Snake"

    TARGET_FRAMERATE = 60

    def __init__(self):
        self.running: bool = False
        self.display_surface: pygame.surface.Surface | None = None

        self.window_width: int = BOARD_WIDTH * Board.CELL_SIZE
        self.window_height: int = BOARD_HEIGHT * Board.CELL_SIZE
        self.window_dimensions = self.window_width, self.window_height

        self.fps = pygame.time.Clock()

        self.current_screen: Screen | None = None

    def init(self):
        pygame.init()
        pygame.display.set_caption(self.WINDOW_CAPTION)
        self.display_surface = pygame.display.set_mode(self.window_dimensions, pygame.HWSURFACE | pygame.DOUBLEBUF)
        self.running = True

        self.current_screen = MainMenuScreen()

    def handleEvent(self, event: pygame.event.Event):
        if event.type == pygame.QUIT:
            self.running = False
        elif event.type == MAIN_MENU:
            self.current_screen = MainMenuScreen()
        elif event.type == GAME_START:
            self.current_screen = GameplayScreen()
        elif event.type == GAME_OVER:
            self.draw()
            sleep(1)
            self.current_screen = GameOverScreen()
        elif event.type == NEXT_LEVEL:
            self.current_screen.reset()

    def draw(self):
        self.display_surface.fill(WHITE)
        self.current_screen.draw(self.display_surface)
        pygame.display.update()

    def run(self):
        self.init()

        # Main loop
        while self.running:
            for event in pygame.event.get():
                self.handleEvent(event)

            self.current_screen.step()
            self.draw()

            self.fps.tick(self.TARGET_FRAMERATE)
        pygame.quit()


def main():
    game = Snake()
    game.run()

if __name__ == "__main__":
    main()
