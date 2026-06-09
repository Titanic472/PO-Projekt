from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2

import po.world_simulator.World as world_module
import math

class CyberSheep(Animal):
    def __init__(self, position_or_data, power=10, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 10)),
                4,
                Vector2(position_or_data.get("position")),
                "Cyber Sheep",
                int(position_or_data.get("age", 0)),
                False
            )
        else:
            super().__init__(power, 4, position_or_data, "Cyber Sheep", age, False)


    def action(self):
        hogweed = world_module.World.getHogweed()
        map = world_module.World.getMap()
        distance = math.inf
        closest: world_module.SosnowskiHogweed = None
        for weed in hogweed:
            if map.distanceTo(self.position, weed.position) < distance:
                distance = map.distanceTo(self.position, weed.position)
                closest = weed

        if closest is not None:
            moveDirection = map.getMoveDirectionTowards(self.position, closest.position)
            self.move(moveDirection)
            self.age += 1
        else:
            super().action()