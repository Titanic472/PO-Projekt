from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2

class CyberSheep(Animal):
    def __init__(self, position_or_data, power=10, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 0)),
                4,
                Vector2(position_or_data.get("position")),
                "Cyber Sheep",
                int(position_or_data.get("age", 0)),
                False
            )
        else:
            super().__init__(power, 4, position_or_data, "Cyber Sheep", age, False)