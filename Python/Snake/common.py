import pygame

# Custom events
MAIN_MENU = pygame.USEREVENT + 1
GAME_START = pygame.USEREVENT + 2
GAME_OVER = pygame.USEREVENT + 3
FOOD_EATEN = pygame.USEREVENT + 4

EVENT_MAIN_MENU = pygame.event.Event(MAIN_MENU)
EVENT_GAME_START = pygame.event.Event(GAME_START)
EVENT_GAME_OVER = pygame.event.Event(GAME_OVER)

# Board dimensions
BOARD_WIDTH = 17
BOARD_HEIGHT = 15

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)