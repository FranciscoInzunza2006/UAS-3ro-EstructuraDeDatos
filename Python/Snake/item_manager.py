import random

import pygame
from pygame import surface

from board import Board
from common import RED, BLACK, BOARD_WIDTH, BOARD_HEIGHT, CELL_SIZE


class Food:
    sprite = pygame.image.load('assets/food.png')
    sprite_rect = sprite.get_rect()

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        surface.blit(self.sprite, (self.x * CELL_SIZE, self.y * CELL_SIZE))


class Trap:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
        self.life = 300

    def step(self):
        if self.life >= 0:
            self.life -= 1

    def draw(self, surface: pygame.Surface):
        pygame.draw.rect(surface, BLACK,
                         (self.x * Board.CELL_SIZE, self.y * Board.CELL_SIZE, Board.CELL_SIZE,
                          Board.CELL_SIZE))


class ItemManager:
    def __init__(self):
        self.foods: list[Food] = []
        self.traps: list[Trap] = []

        self.trap_spawn_cooldown = 60

    def step(self, level):
        x = random.randint(0, BOARD_WIDTH - 1)
        y = random.randint(0, BOARD_HEIGHT - 1)
        if len(self.foods) == 0:
            for trap in self.traps:
                if trap.x == x and trap.y == y:
                    return
            self.foods.append(Food(x, y))
            return

        if len(self.traps) < level - 1:
            self.trap_spawn_cooldown -= 1
            if self.trap_spawn_cooldown == 0:
                self.trap_spawn_cooldown = 60
                self.traps.append(Trap(x, y))
        else:
            self.trap_spawn_cooldown = 60

    def draw(self, surface: pygame.Surface):
        for trap in self.traps:
            trap.draw(surface)

        for food in self.foods:
            food.draw(surface)
