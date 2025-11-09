
import pygame

WHITE = (255, 255, 255)

class Board:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        board = [[] * width] * height

class Segment:
    def __init__(self, x:int, y:int):
        self.x = x
        self.y = y
        self.next: Segment | None = None

class Player(pygame.sprite.Sprite):
    SNAKE_COLOR = (0, 255, 0)
    STARTING_SEGMENTS = 5

    def __init__(self, board: Board):
        super().__init__()

        # Create body segments
        board_x_center = board.width // 2
        board_y_center = board.height // 2

        segment = None
        for s in range(self.STARTING_SEGMENTS):
            seg = Segment(board_x_center - s, board_y_center)
            seg.next = segment
            segment = seg

        self.body: Segment = segment

    def step(self):
        segment = self.body
        while segment is not None:
            segment.x += 1
            segment = segment.next

    def draw(self, surface: pygame.Surface):
        segment = self.body
        while segment is not None:
            pygame.draw.rect(surface, self.SNAKE_COLOR, (segment.x, segment.y, 16, 16))
            segment = segment.next

class Snake:
    def __init__(self):
        self.running: bool = False
        self.display_surface: pygame.surface.Surface | None = None

        self.width: int = 640
        self.height: int = 480
        self.dimensions = self.width, self.height

        self.fps = pygame.time.Clock()
        self.fps.tick(60)

        self.board = Board(16, 16)
        self.player = Player(self.board)

    def init(self):
        pygame.init()
        pygame.display.set_caption("Snake")
        self.display_surface = pygame.display.set_mode(self.dimensions, pygame.HWSURFACE | pygame.DOUBLEBUF)
        self.running = True

    def check_event(self, event: pygame.event.Event):
        if event.type == pygame.QUIT:
            self.running = False

    def step(self):
        self.player.step()

    def draw(self):
        self.display_surface.fill(WHITE)

        self.player.draw(self.display_surface)

        pygame.display.update()

    def cleanup(self):
        pygame.quit()

    def run(self):
        self.init()
        foo = pygame.time.Clock()
        while self.running:
            for event in pygame.event.get():
                self.check_event(event)

            self.step()
            self.draw()

            foo.tick(60)
        self.cleanup()

def main():
    game = Snake()
    game.run()

if __name__ == "__main__":
    main()