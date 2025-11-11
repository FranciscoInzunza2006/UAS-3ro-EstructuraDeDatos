import pygame

from common import WHITE


class Board:
    CELL_SIZE = 32

    def __init__(self, width, height):
        self.width = width
        self.height = height

        self.background = pygame.Surface((self.width * self.CELL_SIZE, self.height * self.CELL_SIZE))

        # Pre-Render the whole background
        self.background.fill((170, 215, 81))
        for y in range(self.height):
            i = y % 2
            for x in range(self.width):
                if i % 2 == 0:
                    pygame.draw.rect(self.background, (162, 209, 73),
                                     (x * self.CELL_SIZE, y * self.CELL_SIZE, self.CELL_SIZE, self.CELL_SIZE))

                i += 1

    def draw(self, surface: pygame.Surface):
        surface.blit(self.background, self.background.get_rect())