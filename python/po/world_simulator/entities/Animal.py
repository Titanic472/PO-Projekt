from .Entity import Entity
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module

class Animal(Entity):
    def __init__(self, power, initiative, position, name, age=0, canKill=False):
        super().__init__(power, initiative, position, name, age)
        self.canKill = canKill

    def action(self):
        moveDirection = world_module.World.getMap().getPossibleMoveDirection(self.position, False)
        if moveDirection != Vector2.ZERO:
            self.move(moveDirection)
        self.age += 1

    def collision(self, otherEntity):
        if type(self) == type(otherEntity):
            self.reproduce()
            return

        if isinstance(otherEntity, Animal):
            enemy = otherEntity
            if self.getPower() <= enemy.getPower() and not enemy.isPredator():
                self.runAway()
                return

        super().collision(otherEntity)

    def isPredator(self):
        return self.canKill

    def move(self, moveDirection):
        game_map = world_module.World.getMap()
        targetPos = self.position.add(moveDirection)
        collisionTarget = game_map.getEntityAt(targetPos)

        if collisionTarget is not None:
            collisionTarget.collision(self)

            if not self.isAlive():
                return

        if game_map.getEntityAt(targetPos) is None:
            game_map.move(self.position, targetPos)
            self.position = targetPos

    def runAway(self):
        game_map = world_module.World.getMap()
        direction = game_map.getPossibleMoveDirection(self.position, True)

        if direction != Vector2.ZERO:
            self.move(direction)
            return True
        return False