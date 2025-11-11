import pygame


class Food:
    def __init__(self, x:int, y: int):
        self.x = x
        self.y = y

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        pass

class Trap:
    def __init__(self, x:int, y: int):
        self.x = x
        self.y = y
        self.life = 300

    def step(self):
        if self.life >= 0:
            self.life -= 1

    def draw(self, surface: pygame.Surface):
        if self.life >= 0:
            pass

class ItemManager:
    def __init__(self):
        pass

    def step(self):
        pass

    def draw(self, surface: pygame.Surface):
        pass