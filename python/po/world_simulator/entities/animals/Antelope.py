import random
from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module

class Antelope(Animal):
    # [AI] Merged constructors using parameter types.
    def __init__(self, position_or_data, power=4, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 0)),
                4,
                Vector2(position_or_data.get("position")),
                "Antelope",
                int(position_or_data.get("age", 0)),
                False
            )
        else:
            super().__init__(power, 4, position_or_data, "Antelope", age, False)

    def move(self, moveDirection):
        # 2 tile move
        moveDirection.multiplySelf(2)

        if not world_module.World.getMap().isTileOutOfBounds(self.position.add(moveDirection)):
            super().move(moveDirection)

    def collision(self, otherEntity):
        if type(self) != type(otherEntity):
            if random.random() < 0.5:
                if self.runAway():
                    return
        super().collision(otherEntity)
