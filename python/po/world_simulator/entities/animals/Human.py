from po.world_simulator.entities.Animal import Animal
from po.world_simulator.Vector2 import Vector2
from po.world_simulator.Config import Config
from po.world_simulator.DataFormat import DataFormat
import po.world_simulator.World as world_module

class Human(Animal):
    instance = None

    def __init__(self, position_or_data, power=5, age=0, abilityCooldown=0):
        if isinstance(position_or_data, dict):
            super().__init__(
                int(position_or_data.get("power", 5)),
                4,
                Vector2(position_or_data.get("position")),
                "Human",
                int(position_or_data.get("age", 0)),
                True
            )
            self.abilityCooldown = int(position_or_data.get("abilityCooldown", 0))
        else:
            super().__init__(power, 4, position_or_data, "Human", age, True)
            self.abilityCooldown = abilityCooldown

        if Human.instance is not None:
            Human.instance.dispose()

        Human.instance = self


    @staticmethod
    def getInstance():
        return Human.instance


    def dispose(self):
        if Human.instance == self:
            Human.instance = None
        super().dispose()


    def action(self):
        if self.abilityCooldown > 0:
            self.abilityCooldown -= 1

        moveDirection = Vector2.ZERO
        lastInput = world_module.World.getInputManager().getLastInput()

        if lastInput == Config.LEFT:
            moveDirection = Vector2(-1, 0)
        elif lastInput == Config.RIGHT:
            moveDirection = Vector2(1, 0)
        elif lastInput == Config.UP:
            moveDirection = Vector2(0, -1)
        elif lastInput == Config.DOWN:
            moveDirection = Vector2(0, 1)
        elif lastInput == Config.ABILITY:
            if self.abilityCooldown == 0:
                self.abilityCooldown = 10

        if not world_module.World.getMap().isTileOutOfBounds(self.position.add(moveDirection)) and moveDirection != Vector2.ZERO:
            self.move(moveDirection)

        # if(age == 90) cout << "moje plecy!";
        self.age += 1


    def collision(self, otherEntity):
        # ability handle before turn if collision happened
        if world_module.World.getInputManager().getLastInput() == Config.ABILITY and self.abilityCooldown == 0:
            self.abilityCooldown = 11

        if self.abilityCooldown > 5:
            if otherEntity.getPower() >= self.getPower():
                self.runAway()
            return

        super().collision(otherEntity)


    def getAbilityCooldown(self):
        return self.abilityCooldown


    def kill(self):
        if self.abilityCooldown > 5:
            return
        world_module.World.getRenderer().addToLog("Human died at age " + str(self.age))
        super().kill()


    def saveAsString(self, parser):
        data = super().saveAsString(parser)
        data += parser.stringifyEntry("abilityCooldown", DataFormat.TYPE_INT, str(self.abilityCooldown))
        return data