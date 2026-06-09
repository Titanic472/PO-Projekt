import heapq
import random
import importlib
import sys

from .Vector2 import Vector2
from .Config import Config
from .Map import Map as WorldMap
from .InputManager import InputManager
from .SaveParser import SaveParser
from .DataFormat import DataFormat

from po.world_simulator.entities.animals.Human import Human
from po.world_simulator.entities.plants.Grass import Grass
from po.world_simulator.entities.plants.Milkweed import Milkweed
from po.world_simulator.entities.plants.Guarana import Guarana
from po.world_simulator.entities.plants.Wolfberries import Wolfberries
from po.world_simulator.entities.plants.SosnowskiHogweed import SosnowskiHogweed
from po.world_simulator.entities.animals.Wolf import Wolf
from po.world_simulator.entities.animals.Sheep import Sheep
from po.world_simulator.entities.animals.Fox import Fox
from po.world_simulator.entities.animals.Turtle import Turtle
from po.world_simulator.entities.animals.Antelope import Antelope
from po.world_simulator.entities.animals.CyberSheep import CyberSheep

class World:
    instance = None

    def __init__(self, hexMode):
        self.worldSize = Vector2(Config.MAP_SIZE_X, Config.MAP_SIZE_Y)
        self.isHexMode = hexMode

        self.map = WorldMap(self.worldSize, hexMode)
        self.renderer = None
        self.loadRenderer()
        self.inputManager = InputManager()

        if World.instance is not None:
            World.instance.dispose()

        World.instance = self

        # Using list for PriorityQueue. Will use heapq module for ops.
        self.entities = []
        self.hogweed: list[SosnowskiHogweed] = []
        self.nextTurnEntities = []

        self.createEntities()


    def dispose(self):
        self.clearEntities()
       self.renderer.dispose()
        if World.instance == self:
            World.instance = None


    @staticmethod
    def getRenderer():
        return World.instance.renderer


    @staticmethod
    def getMap():
        return World.instance.map


    @staticmethod
    def getInputManager():
        return World.instance.inputManager


    @staticmethod
    def getInstance():
        return World.instance


    @staticmethod
    def getEntityCount():
        return len(World.instance.entities)


    @staticmethod
    def getHogweed() -> list[SosnowskiHogweed]:
        return World.instance.hogweed


    def loadRenderer(self):
        if self.renderer is not None:
            self.renderer.dispose()

        if self.isHexMode:
            from .RendererHex import RendererHex
            self.renderer = RendererHex(self.worldSize)
        else:
            from .Renderer import Renderer
            self.renderer = Renderer(self.worldSize)

        # bind buttons
        self.renderer.bind("Save", lambda: World.getInputManager().pushInput(Config.SAVE))
        self.renderer.bind("Load", lambda: World.getInputManager().pushInput(Config.LOAD))


    def performTurn(self):
        while True:
            self.inputManager.readNextInput()

            if self.inputManager.isQuitPressed():
                return False

            if self.inputManager.getLastInput() == Config.SAVE:
                self.save()
                self.inputManager.clearLastInput()
                return True
            elif self.inputManager.getLastInput() == Config.LOAD:
                self.load()
                self.inputManager.clearLastInput()
                # skip turn after loading
                return True

            # redraw info window to show pressed input
            self.renderer.drawInfoWindow()
            self.renderer.renderInfoWindow()

            if self.inputManager.isNewTurnPressed():
                break

        self.renderer.clearLog()

        while self.entities:
            entity = heapq.heappop(self.entities)

            if entity.isAlive():
                entity.action()

            self.queueToNext(entity)

        self.nextQueue()
        return True

    def drawWorld(self):
        self.renderer.drawMap(self.worldSize)

        while self.entities:
            entity = heapq.heappop(self.entities)

            if entity.isAlive() and self.renderer:
                entity.draw()

            self.queueToNext(entity)

        self.renderer.renderMap()

        self.nextQueue()

        self.renderer.drawInfoWindow()
        self.renderer.renderInfoWindow()


    def forceDrawAll(self):
        # force push all entities that were already added
        self.nextQueue()

        # draw world with all entities added
        self.drawWorld()


    def save(self):
        parser = SaveParser()

        parser.createFile(self.worldSize)

        parser.addEntry("world_size", DataFormat.TYPE_VECTOR2, str(self.worldSize))
        parser.addEntry("hex_mode", DataFormat.TYPE_BOOLEAN, str(self.isHexMode).lower())

        parser.startCategory("entities")

        while self.entities:
            entity = heapq.heappop(self.entities)

            if entity.isAlive():
                parser.addStringEntry(entity.saveAsString(parser))

            self.queueToNext(entity)

        self.nextQueue()

        parser.endCategory()

        parser.closeFile()

        self.renderer.clearLog()
        self.renderer.addToLog("game saved!")


    def load(self):
        self.renderer.clearLog()

        parser = SaveParser()

        if not parser.loadFile(self.worldSize):
            self.renderer.addToLog("no save file found!")
            return

        self.worldSize = parser.loadEntry("world_size")
        hexMode = parser.loadEntry("hex_mode")

        # clear previous world
        self.map = WorldMap(self.worldSize, self.isHexMode)
        # reload renderer if save contains different grid mode
        if hexMode != self.isHexMode:
            self.isHexMode = hexMode
            self.loadRenderer()

        self.clearEntities()

        # load entities
        if not parser.jumpToCategory("entities"):
            self.renderer.addToLog("incorrect save file format")
            return

        entityData = {}

        while parser.loadEntryMultiline(entityData):
            self.loadEntity(entityData)
            entityData.clear()

        self.nextQueue()
        iself.renderer.addToLog("game loaded!")


    def addNewEntity(self, entity):
        if self.map.isTileOccupied(entity.getPosition()):
            # convert entity into kebap
            entity.dispose()
        else:
            # add entity to world
            self.map.placeEntityAt(entity.getPosition(), entity)
            self.queueToNext(entity)


    def queueToNext(self, entity):
        if entity.isAlive():
            self.nextTurnEntities.append(entity)
        else:
            entity.dispose()


    def nextQueue(self):
        self.hogweed.clear()
        for entity in self.nextTurnEntities:
            heapq.heappush(self.entities, entity)
            if isinstance(entity, SosnowskiHogweed):
                self.hogweed.append(entity)
        self.nextTurnEntities.clear()


    def createEntities(self):
        worldArea = self.worldSize.x * self.worldSize.y

        self.addNewEntity(Human(self.worldSize.multiply(0.5)))

        self.randomizeEntities(Grass, worldArea, Config.GRASS_AMOUNT)
        self.randomizeEntities(Milkweed, worldArea, Config.MILKWEED_AMOUNT)
        self.randomizeEntities(Guarana, worldArea, Config.GUARANA_AMOUNT)
        self.randomizeEntities(Wolfberries, worldArea, Config.WOLFBERRIES_AMOUNT)
        self.randomizeEntities(SosnowskiHogweed, worldArea, Config.SOSNOWSKI_HOGWEED_AMOUNT)
        self.randomizeEntities(Wolf, worldArea, Config.WOLF_AMOUNT)
        self.randomizeEntities(Sheep, worldArea, Config.SHEEP_AMOUNT)
        self.randomizeEntities(Fox, worldArea, Config.FOX_AMOUNT)
        self.randomizeEntities(Turtle, worldArea, Config.TURTLE_AMOUNT)
        self.randomizeEntities(Antelope, worldArea, Config.ANTELOPE_AMOUNT)
        self.randomizeEntities(CyberSheep, worldArea, Config.CYBER_SHEEP_AMOUNT)

        self.nextQueue()


    def randomizeEntities(self, constructor, worldArea, percent):
        amount = int(worldArea * percent / 100)
        for _ in range(amount):
            self.addNewEntity(constructor(Vector2(random.randint(0, self.worldSize.x - 1), random.randint(0, self.worldSize.y - 1))))


    def loadEntity(self, entityData):
        type_str = entityData.get("type")

        packages = [
            "po.world_simulator.entities.animals",
            "po.world_simulator.entities.plants"
        ]

        for pkg in packages:
            try:
                module = importlib.import_module(f"{pkg}.{type_str}")
                clazz = getattr(module, type_str)
                
                entity = clazz(entityData)
                self.addNewEntity(entity)
                return
            except Exception:
                pass

        self.renderer.addToLog("UNKNOWN ENTITY TYPE: " + str(type_str))


    def clearEntities(self):
        while self.entities:
            entity = heapq.heappop(self.entities)
            if entity is not None:
                entity.dispose()

        while self.nextTurnEntities:
            entity = self.nextTurnEntities.pop(0)
            if entity is not None:
                entity.dispose()