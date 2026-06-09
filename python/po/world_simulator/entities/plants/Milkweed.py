import random
from po.world_simulator.entities.Plant import Plant
from po.world_simulator.Vector2 import Vector2
from po.world_simulator.Config import Config

class Milkweed(Plant):
    def __init__(self, position_or_data, age=0):
        if isinstance(position_or_data, dict):
            super().__init__(0, Vector2(position_or_data.get("position")), "milkweed", int(position_or_data.get("age", 0)))
        else:
            super().__init__(0, position_or_data, "milkweed", age)


    def action(self):
        # three reproduce attempts
        for _ in range(2):
            if random.random() * 100 < Config.PLANTS_SPREAD_CHANCE:
                self.reproduce()

        # third reproduce attempt is located in plant action code
        super().action()