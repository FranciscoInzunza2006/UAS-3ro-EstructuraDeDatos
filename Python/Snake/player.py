# FIXME: Weird movement when first loading
# TODO: Body collision
from enum import Enum
from time import sleep

import pygame

from board import Board
from common import EVENT_GAME_OVER, EVENT_NEXT_LEVEL
from item_manager import ItemManager


class Player:
    SNAKE_COLOR = (0, 255, 0)
    STARTING_SEGMENTS = 5

    class DIRECTION(Enum):
        UP = 1
        DOWN = 2
        LEFT = 3
        RIGHT = 4

    class Segment:
        def __init__(self, x: int, y: int, direction):
            self.x = x
            self.y = y
            self.direction = direction
            self.next: Player.Segment | None = None


    def __init__(self, board: Board):
        # Create body segments
        self.segment_count =  self.STARTING_SEGMENTS
        board_x_center = board.width // 2
        board_y_center = board.height // 2

        self.movement_cooldown = 8
        self.movement_direction = self.DIRECTION.RIGHT
        self.ticks_for_next_move = self.movement_cooldown

        segment = None
        for s in range(self.STARTING_SEGMENTS):
            seg = self.Segment(board_x_center + s, board_y_center, self.DIRECTION.RIGHT)
            seg.next = segment
            segment = seg

        self.body: Player.Segment = segment

    def step(self, board: Board, item_manager: ItemManager):
        pressed_keys = pygame.key.get_pressed()

        if pressed_keys[pygame.K_LEFT] and self.body.direction != self.DIRECTION.RIGHT:
            self.movement_direction = self.DIRECTION.LEFT
        elif pressed_keys[pygame.K_RIGHT] and self.body.direction != self.DIRECTION.LEFT:
            self.movement_direction = self.DIRECTION.RIGHT
        elif pressed_keys[pygame.K_UP] and self.body.direction != self.DIRECTION.DOWN:
            self.movement_direction = self.DIRECTION.UP
        elif pressed_keys[pygame.K_DOWN] and self.body.direction!= self.DIRECTION.UP:
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

            self.body.x = self.body.x % board.width
            self.body.y = self.body.y % board.height
            self.body.direction = self.movement_direction

            # Collision with itself
            segment = self.body.next
            while segment is not None:
                if segment.x == self.body.x and segment.y == self.body.y:
                    pygame.event.post(EVENT_GAME_OVER)
                segment = segment.next

            # Collision with items
            for i, food in enumerate(item_manager.foods):
                if food.x == self.body.x and food.y == self.body.y:
                    item_manager.foods.pop(i)
                    self.addSegment()
                    if self.segment_count > 7:
                        pygame.event.post(EVENT_NEXT_LEVEL)

            for i, trap in enumerate(item_manager.traps):
                if trap.x == self.body.x and trap.y == self.body.y:
                    sleep(0.15)
                    item_manager.traps.pop(i)
                    self.removeSegment()
                    if self.segment_count == 0:
                        pygame.event.post(EVENT_GAME_OVER)


    def addSegment(self):
        tail = self.body
        while tail.next is not None:
            tail = tail.next

        x = tail.x
        y = tail.y
        match tail.direction:
            case self.DIRECTION.UP:
                y += 1
            case self.DIRECTION.DOWN:
                y -= 1
            case self.DIRECTION.LEFT:
                x += 1
            case self.DIRECTION.RIGHT:
                x -= 1

        tail.next = self.Segment(x, y, tail.direction)
        self.segment_count += 1

    def removeSegment(self):
        if self.body is None:
            return

        self.segment_count -= 1
        if self.body.next is None:
            self.body = None
            return

        new_tail = self.body
        while new_tail.next.next is not None:
            new_tail = new_tail.next

        new_tail.next = None

    def updateSegmentsPosition(self, segment: Segment, next: Segment):
        if next is None:
            return

        self.updateSegmentsPosition(next, next.next)

        next.x = segment.x
        next.y = segment.y
        next.direction = segment.direction

    def draw(self, surface: pygame.Surface):
        segment = self.body
        while segment is not None:
            pygame.draw.rect(surface, self.SNAKE_COLOR,
                             (segment.x * Board.CELL_SIZE, segment.y * Board.CELL_SIZE, Board.CELL_SIZE,
                              Board.CELL_SIZE))
            segment = segment.next