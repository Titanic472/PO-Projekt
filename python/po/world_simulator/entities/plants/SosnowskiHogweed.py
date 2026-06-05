from po.world_simulator.entities.Plant import Plant
from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module

class SosnowskiHogweed(Plant):
    # [AI] Merged constructors.
    def __init__(self, position_or_data, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(10, Vector2(position_or_data.get("position")), "sosnowski hogweed", int(position_or_data.get("age", 0)))
        else:
            super().__init__(10, position_or_data, "sosnowski hogweed", age)

    def action(self):
        entities = world_module.World.getMap().getEntitiesAround(self.position)

        for entity in entities:
            if isinstance(entity, Animal):
                entity.kill()
                world_module.World.getRenderer().addToLog(self.getName() + " killed " + entity.getName())

        super().action()

    def collision(self, otherEntity):
        otherEntity.kill()
        self.kill()
        world_module.World.getRenderer().addToLog(self.getName() + " killed " + otherEntity.getName() + " and died")
