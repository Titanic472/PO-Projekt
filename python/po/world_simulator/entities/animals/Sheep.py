from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2

class Sheep(Animal):
    def __init__(self, position_or_data, power=4, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 4)),
                4,
                Vector2(position_or_data.get("position")),
                "Sheep",
                int(position_or_data.get("age", 0)),
                False
            )
        else:
            super().__init__(power, 4, position_or_data, "Sheep", age, False)