from enum import Enum

import pygame

WHITE = (255, 255, 255)



class Board:
    CELL_SIZE = 32
    def __init__(self, width, height):
        self.width = width
        self.height = height

        self.board = [[] * width] * height

        self.surf = pygame.Surface((self.width * self.CELL_SIZE, self.height * self.CELL_SIZE))

        self.surf.fill(WHITE)
        for y in range(self.height):
            i = y % 2
            for x in range(self.width):
                if i % 2 == 0:
                    pygame.draw.rect(self.surf, (192, 192, 192), (x * self.CELL_SIZE, y * self.CELL_SIZE, self.CELL_SIZE, self.CELL_SIZE))

                i += 1

    def draw(self, surface: pygame.Surface):
        surface.blit(self.surf,  self.surf.get_rect())

class Segment:
    def __init__(self, x:int, y:int):
        self.x = x
        self.y = y
        self.next: Segment | None = None

class Player:
    SNAKE_COLOR = (0, 255, 0)
    STARTING_SEGMENTS = 5

    class DIRECTION(Enum):
        UP = 1
        DOWN = 2
        LEFT = 3
        RIGHT = 4

    def __init__(self, board: Board):
        # Create body segments
        board_x_center = board.width // 2
        board_y_center = board.height // 2

        self.movement_cooldown = 60
        self.movement_direction = self.DIRECTION.RIGHT
        self.ticks_for_next_move = self.movement_cooldown

        segment = None
        for s in range(self.STARTING_SEGMENTS):
            seg = Segment(board_x_center - s, board_y_center)
            seg.next = segment
            segment = seg

        self.body: Segment = segment

    def step(self):
        pressed_keys = pygame.key.get_pressed()

        if pressed_keys[pygame.K_LEFT] and self.movement_direction != self.DIRECTION.RIGHT:
            self.movement_direction = self.DIRECTION.LEFT
        elif pressed_keys[pygame.K_RIGHT] and self.movement_direction != self.DIRECTION.LEFT:
            self.movement_direction = self.DIRECTION.RIGHT
        elif pressed_keys[pygame.K_UP] and self.movement_direction != self.DIRECTION.DOWN:
            self.movement_direction = self.DIRECTION.UP
        elif pressed_keys[pygame.K_DOWN] and self.movement_direction != self.DIRECTION.UP:
            self.movement_direction = self.DIRECTION.DOWN

        self.ticks_for_next_move -= 1
        if self.ticks_for_next_move <= 0:
            self.ticks_for_next_move = self.movement_cooldown

            self.updateSegmentsPosition(self.body, self.body.next)

            match self.movement_direction:
                case self.DIRECTION.UP:
                    self.body.y -= 1
                case self.DIRECTION.DOWN:
                    self.body.y += 1
                case self.DIRECTION.LEFT:
                    self.body.x -= 1
                case self.DIRECTION.RIGHT:
                    self.body.x += 1

            self.body.x = self.body.x % 16
            self.body.y = self.body.y % 16

    def updateSegmentsPosition(self, segment: Segment, next: Segment):
        if next is None:
            return

        self.updateSegmentsPosition(next, next.next)

        next.x = segment.x
        next.y = segment.y

    def draw(self, surface: pygame.Surface):
        segment = self.body
        while segment is not None:
            pygame.draw.rect(surface, self.SNAKE_COLOR,
                             (segment.x * Board.CELL_SIZE, segment.y * Board.CELL_SIZE, Board.CELL_SIZE, Board.CELL_SIZE))
            segment = segment.next

class Snake:
    BOARD_WIDTH = 16
    BOARD_HEIGHT = 16

    def __init__(self):
        self.running: bool = False
        self.display_surface: pygame.surface.Surface | None = None

        self.width: int = self.BOARD_WIDTH * Board.CELL_SIZE
        self.height: int = self.BOARD_HEIGHT * Board.CELL_SIZE
        self.dimensions = self.width, self.height

        self.fps = pygame.time.Clock()

        self.board = Board(self.BOARD_WIDTH, self.BOARD_HEIGHT)
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

        self.board.draw(self.display_surface)
        self.player.draw(self.display_surface)

        pygame.display.update()

    def cleanup(self):
        pygame.quit()

    def run(self):
        self.init()

        while self.running:
            for event in pygame.event.get():
                self.check_event(event)

            self.step()
            self.draw()

            self.fps.tick(60)
        self.cleanup()

def main():
    game = Snake()
    game.run()

if __name__ == "__main__":
    main()