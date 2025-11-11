# FIXME: Weird movement when first loading
# TODO: Body collision
from enum import Enum

import pygame

from board import Board


class Player:
    SNAKE_COLOR = (0, 255, 0)
    STARTING_SEGMENTS = 5

    class Segment:
        def __init__(self, x: int, y: int):
            self.x = x
            self.y = y
            self.next: Segment | None = None

    class DIRECTION(Enum):
        UP = 1
        DOWN = 2
        LEFT = 3
        RIGHT = 4

    def __init__(self, board: Board):
        # Create body segments
        board_x_center = board.width // 2
        board_y_center = board.height // 2

        self.movement_cooldown = 8
        self.movement_direction = self.DIRECTION.RIGHT
        self.ticks_for_next_move = self.movement_cooldown

        segment = None
        for s in range(self.STARTING_SEGMENTS):
            seg = Segment(board_x_center - s, board_y_center)
            seg.next = segment
            segment = seg

        self.body: Segment = segment

    def step(self, board: Board, food, traps):
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

            self._updateSegmentsPosition(self.body, self.body.next)

            match self.movement_direction:
                case self.DIRECTION.UP:
                    self.body.y -= 1
                case self.DIRECTION.DOWN:
                    self.body.y += 1
                case self.DIRECTION.LEFT:
                    self.body.x -= 1
                case self.DIRECTION.RIGHT:
                    self.body.x += 1

            self.body.x = self.body.x % board.width
            self.body.y = self.body.y % board.height

        body_x = self.body.x
        body_y = self.body.y
        for trap in traps:
            if trap.x == body_x and trap.y == body_y:
                pass


    def _updateSegmentsPosition(self, segment: Segment, next: Segment):
        if next is None:
            return

        self._updateSegmentsPosition(next, next.next)

        next.x = segment.x
        next.y = segment.y

    def draw(self, surface: pygame.Surface):
        segment = self.body
        while segment is not None:
            pygame.draw.rect(surface, self.SNAKE_COLOR,
                             (segment.x * Board.CELL_SIZE, segment.y * Board.CELL_SIZE, Board.CELL_SIZE,
                              Board.CELL_SIZE))
            segment = segment.next