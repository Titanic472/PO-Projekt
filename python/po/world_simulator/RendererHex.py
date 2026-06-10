import tkinter as tk
import math

from po.world_simulator.Renderer import Renderer, get_hex_color
from po.world_simulator.Vector2 import Vector2
from po.world_simulator.Config import Config
import po.world_simulator.World as world_module

class RendererHex(Renderer):
    def __init__(self, mapSize):
        super().__init__(mapSize)

        # Remove grid layout map panel from original renderer and replace with canvas
        self.mapPanel.destroy()

        self.hexGrid = [[' ' for _ in range(mapSize.x)] for _ in range(mapSize.y)]

        self.hexMapCanvas = tk.Canvas(self.main_container, bg=get_hex_color(Config.BG_COLOR), highlightthickness=0)
        self.hexMapCanvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # Bind resize and click events
        self.hexMapCanvas.bind("<Configure>", self.on_resize)
        self.hexMapCanvas.bind("<Button-1>", self.on_click)

        self.hexagons_memory = [[None for _ in range(mapSize.x)] for _ in range(mapSize.y)] # Memory for bounding box detection

        self.frame.update()


    def drawCharAt(self, position, text):
        if 0 <= position.y < len(self.hexGrid) and 0 <= position.x < len(self.hexGrid[0]):
            self.hexGrid[position.y][position.x] = text


    def drawMap(self, mapSize_obj):
        for y in range(self.mapSize.y):
            for x in range(self.mapSize.x):
                self.hexGrid[y][x] = ' '


    def renderMap(self):
        self.draw_hexes()
        self.frame.update()


    def on_resize(self, event):
        self.draw_hexes()


    def on_click(self, event):
        clicked_pos = None
        min_dist = float('inf')

        for y in range(self.mapSize.y):
            for x in range(self.mapSize.x):
                center = self.hexagons_memory[y][x]
                if center:
                    dist = math.hypot(center[0] - event.x, center[1] - event.y)
                    if dist < min_dist and dist < center[2]: # size
                        min_dist = dist
                        clicked_pos = Vector2(x, y)

        if clicked_pos is not None:
            self.showAddEntityDialog(clicked_pos)


    def draw_hexes(self):
        self.hexMapCanvas.delete("all")

        width = self.hexMapCanvas.winfo_width()
        height = self.hexMapCanvas.winfo_height()

        if width <= 1 or height <= 1:
            return

        # calculate proportions
        cols = self.mapSize.x + 0.5
        rows = (self.mapSize.y * 0.75) + 0.25

        maxW = width / cols
        maxH = height / rows

        # widthHex = sqrt(3) * size, heightHex = 2 * size
        sizeW = maxW / math.sqrt(3)
        sizeH = maxH / 2.0

        size = min(sizeW, sizeH) * 0.95

        hexWidth = math.sqrt(3) * size
        hexHeight = 2.0 * size

        offsetX = (width - ((self.mapSize.x + 0.5) * hexWidth)) / 2.0
        offsetY = (height - ((self.mapSize.y * 0.75 + 0.25) * hexHeight)) / 2.0

        fontSize = max(10, int(size * 0.8))

        for y in range(self.mapSize.y):
            for x in range(self.mapSize.x):
                # uneven rows are moved right
                cx = offsetX + x * hexWidth + (hexWidth / 2.0 if y % 2 != 0 else 0) + hexWidth / 2.0
                cy = offsetY + y * (hexHeight * 0.75) + hexHeight / 2.0

                polygon_points = self.createHexagon(cx, cy, size)

                # store cx, cy and size for click detection
                self.hexagons_memory[y][x] = (cx, cy, size)

                # background
                self.hexMapCanvas.create_polygon(polygon_points, fill=get_hex_color(Config.DEFAULT_GRID_BG_COLOR),
                                                 outline=get_hex_color(Config.BORDER_COLOR), width=Config.BORDER_THICKNESS)

                # Draw objects on hex
                c = self.hexGrid[y][x]
                if c != ' ' and c != '\0':
                    self.hexMapCanvas.create_text(cx, cy, text=c, fill=get_hex_color(Config.TEXT_COLOR),
                                                  font=("Courier", fontSize, "bold"))


    def createHexagon(self, x, y, size):
        points = []
        for i in range(6):
            # calculate polygon positions based on angle
            angle_deg = 60 * i - 30
            angle_rad = math.pi / 180 * angle_deg
            px = int(round(x + size * math.cos(angle_rad)))
            py = int(round(y + size * math.sin(angle_rad)))
            points.extend([px, py])
        return points
