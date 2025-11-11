import pygame

from board import Board
from common import RED, BLACK


class Food:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        pygame.draw.rect(surface, RED,
                         (self.x * Board.CELL_SIZE, self.y * Board.CELL_SIZE, Board.CELL_SIZE,
                          Board.CELL_SIZE))


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

    def step(self, board):
        if len(self.foods) == 0:
            self.foods.append(Food(5, 3))

        if len(self.traps) == 0:
            self.traps.append(Trap(5, 10))

        #for trap in self.traps:
            #self.traps.append(Food(3, 1))

    def draw(self, surface: pygame.Surface):
        for food in self.foods:
            food.draw(surface)

        for trap in self.traps:
            trap.draw(surface)
