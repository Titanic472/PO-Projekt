from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module

class Fox(Animal):
    def __init__(self, position_or_data, power=3, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 3)),
                7,
                Vector2(position_or_data.get("position")),
                "Fox",
                int(position_or_data.get("age", 0)),
                True
            )
        else:
            super().__init__(power, 7, position_or_data, "Fox", age, True)


    def action(self):
        game_map = world_module.World.getMap()
        moveDirection = game_map.getPossibleMoveDirection(self.position, False)

        collisionTarget = game_map.getEntityAt(self.position.add(moveDirection))

        if collisionTarget is None or collisionTarget.getPower() <= self.getPower():
            super().action()
            return

        self.age += 1