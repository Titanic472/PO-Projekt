class Color: # [AI] Simple color class to replace java.awt.Color
    def __init__(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b

class Config:
    MAP_SIZE_X = 5
    MAP_SIZE_Y = 5
    STATUS_WIDTH = 25

    HEX_ENABLED = False

    GRASS_AMOUNT = 10
    MILKWEED_AMOUNT = 8
    GUARANA_AMOUNT = 10
    WOLFBERRIES_AMOUNT = 2
    SOSNOWSKI_HOGWEED_AMOUNT = 4

    WOLF_AMOUNT = 2
    SHEEP_AMOUNT = 5
    FOX_AMOUNT = 5
    TURTLE_AMOUNT = 5
    ANTELOPE_AMOUNT = 5

    PLANTS_SPREAD_CHANCE = 5

    QUIT = 'q'
    LEFT = 255 + 68
    RIGHT = 255 + 67
    UP = 255 + 65
    DOWN = 255 + 66
    ABILITY = 'e'
    NEW_TURN = 'n'
    SAVE = 's'
    LOAD = 'l'

    # renderer config
    MAX_LOG_MESSAGES = 100
    WINDOW_WIDTH = 1200
    WINDOW_HEIGHT = 800
    BG_COLOR = Color(240, 240, 240)
    DEFAULT_GRID_BG_COLOR = Color(0, 0, 0) # [AI] Replaced Color.black with RGB
    BORDER_COLOR = Color(192, 192, 192) # [AI] Replaced Color.LIGHT_GRAY
    BORDER_THICKNESS = 4
    TEXT_COLOR = Color(255, 255, 255) # [AI] Replaced Color.WHITE
    BLOCK_FONT_SIZE = 24
