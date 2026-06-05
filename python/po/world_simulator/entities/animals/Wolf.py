from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2

class Wolf(Animal):
    # [AI] Merged constructors.
    def __init__(self, position_or_data, power=9, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 0)),
                5,
                Vector2(position_or_data.get("position")),
                "Wolf",
                int(position_or_data.get("age", 0)),
                True
            )
        else:
            super().__init__(power, 5, position_or_data, "Wolf", age, True)