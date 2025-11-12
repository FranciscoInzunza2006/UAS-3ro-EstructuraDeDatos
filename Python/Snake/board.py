import pygame

from common import TILE_SIZE_PX


class Board:
    def __init__(self, width, height):
        #self.width = width
        #self.height = height

        self.background = pygame.Surface((width * TILE_SIZE_PX, height * TILE_SIZE_PX))

        # Pre-Render the whole background
        self.background.fill((170, 215, 81))
        for y in range(height):
            i = y % 2
            for x in range(width):
                if i % 2 == 0:
                    pygame.draw.rect(self.background, (162, 209, 73),
                                     (x * TILE_SIZE_PX, y * TILE_SIZE_PX, TILE_SIZE_PX, TILE_SIZE_PX))

                i += 1

    def draw(self, surface: pygame.Surface):
        surface.blit(self.background, self.background.get_rect())
