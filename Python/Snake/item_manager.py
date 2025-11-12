import math
import random

import pygame

from common import BOARD_WIDTH, BOARD_HEIGHT, TILE_SIZE_PX


def imageThingy(sprite, rate, x, y):
    scale = math.floor(math.sin(pygame.time.get_ticks() * rate) * 2)
    new_size = TILE_SIZE_PX + scale
    scaled_sprite = pygame.transform.smoothscale(sprite, (new_size, new_size))

    offset = scale // 2
    return scaled_sprite, (x - offset, y - offset)


class Food:
    sprite = pygame.image.load('assets/food.png')

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        thingy = imageThingy(Food.sprite, 0.005, self.x * TILE_SIZE_PX, self.y * TILE_SIZE_PX)
        surface.blit(thingy[0], thingy[1])


class Trap:
    sprite = pygame.image.load('assets/trap.png')

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
        self.life = 300

    def step(self):
        if self.life >= 0:
            self.life -= 1

    def draw(self, surface: pygame.Surface):
        thingy = imageThingy(Trap.sprite, 0.01, self.x * TILE_SIZE_PX, self.y * TILE_SIZE_PX)
        surface.blit(thingy[0], thingy[1])


class ItemManager:
    def __init__(self, level):
        self.foods: list[Food] = []
        self.traps: list[Trap] = []

        total_traps = min(level, 25)
        for i in range(total_traps):
            x = random.randint(0, BOARD_WIDTH - 1)
            y = random.randint(0, BOARD_HEIGHT - 1)
            self.traps.append(Trap(x, y))

    def step(self):
        x = random.randint(0, BOARD_WIDTH - 1)
        y = random.randint(0, BOARD_HEIGHT - 1)
        if len(self.foods) == 0:
            for trap in self.traps:
                if trap.x == x and trap.y == y:
                    return
            self.foods.append(Food(x, y))

    def draw(self, surface: pygame.Surface):
        for trap in self.traps:
            trap.draw(surface)

        for food in self.foods:
            food.draw(surface)
