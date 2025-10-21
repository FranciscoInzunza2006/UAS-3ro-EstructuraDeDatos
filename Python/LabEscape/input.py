from enum import IntEnum

import keyboard


class Controls(IntEnum):
    ONE = 2
    TWO = 3
    THREE = 4
    FOUR = 5
    RIGHT_KEY = 77
    LEFT_KEY = 75
    UP_KEY = 72
    DOWN_KEY = 80

def getInput() -> int:
    while True:
        event = keyboard.read_event()
        if event.event_type == keyboard.KEY_DOWN:
            key: int = event.scan_code
            if key in Controls:
                return key
            else:
                print(f"Key: {event.name}, ScanCode: {event.scan_code}")