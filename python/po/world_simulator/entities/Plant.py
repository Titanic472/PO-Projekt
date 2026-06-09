import random
from po.world_simulator.Config import Config
from .Entity import Entity

class Plant(Entity):
    def __init__(self, power, position, name, age=0):
        super().__init__(power, 0, position, name, age)


    def action(self):
        spreadRandom = int(random.random() * 100)
        if spreadRandom < Config.PLANTS_SPREAD_CHANCE:
            self.reproduce()
        self.age += 1