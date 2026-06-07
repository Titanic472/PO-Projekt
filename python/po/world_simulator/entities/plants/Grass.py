from po.world_simulator.entities.Plant import Plant
from po.world_simulator.Vector2 import Vector2

class Grass(Plant):
    def __init__(self, position_or_data, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(0, Vector2(position_or_data.get("position")), "trawa:)", int(position_or_data.get("age", 0)))
        else:
            super().__init__(0, position_or_data, "trawa:)", age)