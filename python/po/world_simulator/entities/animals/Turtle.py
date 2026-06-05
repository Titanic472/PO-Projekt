import random
from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2

class Turtle(Animal):
    # [AI] Merged constructors.
    def __init__(self, position_or_data, power=2, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 0)),
                1,
                Vector2(position_or_data.get("position")),
                "Turtle",
                int(position_or_data.get("age", 0)),
                False
            )
        else:
            super().__init__(power, 1, position_or_data, "Turtle", age, False)

    def collision(self, otherEntity):
        if type(self) != type(otherEntity):
            if otherEntity.getPower() < 5:
                return
        super().collision(otherEntity)

    def move(self, moveDirection):
        if random.random() < 0.25:
            super().move(moveDirection)