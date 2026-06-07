class Color:
    def __init__(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b

class Config:
    MAP_SIZE_X = 20
    MAP_SIZE_Y = 20
    STATUS_WIDTH = 25

    HEX_ENABLED = True

    GRASS_AMOUNT = 0
    MILKWEED_AMOUNT = 0
    GUARANA_AMOUNT = 0
    WOLFBERRIES_AMOUNT = 0
    SOSNOWSKI_HOGWEED_AMOUNT = 100

    WOLF_AMOUNT = 0
    SHEEP_AMOUNT = 0
    FOX_AMOUNT = 0
    TURTLE_AMOUNT = 0
    ANTELOPE_AMOUNT = 0
    CYBER_SHEEP_AMOUNT = 1

    PLANTS_SPREAD_CHANCE = 5

    QUIT = ord('q')
    LEFT = 255 + 68
    RIGHT = 255 + 67
    UP = 255 + 65
    DOWN = 255 + 66
    ABILITY = ord('e')
    NEW_TURN = ord('n')
    SAVE = ord('s')
    LOAD = ord('l')

    # renderer config
    MAX_LOG_MESSAGES = 100
    WINDOW_WIDTH = 1200
    WINDOW_HEIGHT = 800
    BG_COLOR = Color(240, 240, 240)
    DEFAULT_GRID_BG_COLOR = Color(0, 0, 0)
    BORDER_COLOR = Color(192, 192, 192)
    BORDER_THICKNESS = 2
    TEXT_COLOR = Color(255, 255, 255)
    BLOCK_FONT_SIZE = 18
