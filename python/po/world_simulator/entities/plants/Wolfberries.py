from po.world_simulator.entities.Plant import Plant
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module

class Wolfberries(Plant):
    def __init__(self, position_or_data, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(99, Vector2(position_or_data.get("position")), "wolfberries", int(position_or_data.get("age", 0)))
        else:
            super().__init__(99, position_or_data, "wolfberries", age)


    def collision(self, otherEntity):
        otherEntity.kill()
        self.kill()
        world_module.World.getRenderer().addToLog(self.getName() + " tried to kill " + otherEntity.getName() + " and died")
