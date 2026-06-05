import functools
from po.world_simulator.DataFormat import DataFormat
import po.world_simulator.World as world_module

@functools.total_ordering # [AI] total_ordering allows comparison decorators
class Entity:
    def __init__(self, power, initiative, position, name, age=0):
        self.isDead = False
        self.power = power
        self.initiative = initiative
        self.name = name
        self.position = position
        self.age = age

    def dispose(self):
        pass

    def __lt__(self, other):
        # [AI] Python heapq uses min-heap. So we want largest element to pop first. Thus we define `__lt__` such that larger element is "less".
        if self.initiative == other.initiative:
            return self.age > other.age
        return self.initiative > other.initiative

    def __eq__(self, other):
        if not isinstance(other, Entity):
            return False
        return (self.initiative, self.age) == (other.initiative, other.age)

    def action(self):
        pass

    def draw(self):
        world_module.World.getRenderer().drawCharAt(self.position, self.name[0])

    def getPosition(self):
        return self.position

    def isAlive(self):
        return not self.isDead

    def kill(self):
        self.isDead = True
        world_module.World.getMap().removeEntityAt(self.position)

    def setPower(self, power):
        self.power = power

    def getPower(self):
        return self.power

    def getName(self):
        return self.name

    def collision(self, otherEntity):
        if self.power <= otherEntity.getPower():
            world_module.World.getRenderer().addToLog(f"{self.name} collided with {otherEntity.name} and died")
            self.kill()
        else:
            world_module.World.getRenderer().addToLog(f"{self.name} collided with {otherEntity.name} and won")
            otherEntity.kill()

    def saveAsString(self, parser):
        data = ""
        # [AI] using type(self).__name__ to get simple class name
        data += parser.stringifyEntry(type(self).__name__, DataFormat.CATEGORY_START_HEADER)
        data += parser.stringifyEntry("position", DataFormat.TYPE_VECTOR2, str(self.position))
        data += parser.stringifyEntry("age", DataFormat.TYPE_INT, str(self.age))
        data += parser.stringifyEntry("power", DataFormat.TYPE_INT, str(self.power))
        return data

    def reproduce(self):
        direction = world_module.World.getMap().getPossibleMoveDirection(self.position, True)

        if not world_module.World.getMap().isTileOccupied(self.position.add(direction)):
            world_module.World.getRenderer().addToLog(f"{self.name} reproduced at {self.getPosition()}")
            world_module.World.getInstance().addNewEntity(self.clone(self.position.add(direction)))

    def clone(self, position):
        try:
            return type(self)(position=position) # [AI] creating new object of same type
        except Exception as e:
            print(e)
            return None