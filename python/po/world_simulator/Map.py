import random
from .Vector2 import Vector2
import math

class Map:
    def __init__(self, mapSize, hexMode):
        self.size = mapSize
        self.hexMode = hexMode
        if hexMode:
            self.tileNeighbours = [
                [
                    Vector2(-1, -1), Vector2(0, -1),
                    Vector2(-1, 0), Vector2(1, 0),
                    Vector2(-1, 1),  Vector2(0, 1)
                ],
                [
                    Vector2(0, -1), Vector2(1, -1),
                    Vector2(-1, 0), Vector2(1, 0),
                    Vector2(0, 1),  Vector2(1, 1)
                ]
            ]
        else:
            self.tileNeighbours = [
                [
                    Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1),
                    Vector2(-1, 0),                  Vector2(1, 0),
                    Vector2(-1, 1),  Vector2(0, 1),  Vector2(1, 1)
                ],
                [
                    Vector2(-1, -1), Vector2(0, -1), Vector2(1, -1),
                    Vector2(-1, 0),                  Vector2(1, 0),
                    Vector2(-1, 1),  Vector2(0, 1),  Vector2(1, 1)
                ]
            ]

        self.map = [[None for _ in range(self.size.y)] for _ in range(self.size.x)]


    def getEntityAt(self, position):
        if self.isTileOutOfBounds(position):
            return None
        return self.map[position.x][position.y]


    def placeEntityAt(self, position, entity):
        if not self.isTileOutOfBounds(position):
            self.map[position.x][position.y] = entity


    def removeEntityAt(self, position):
        if not self.isTileOutOfBounds(position):
            self.map[position.x][position.y] = None


    def isTileOccupied(self, position):
        return not self.isTileOutOfBounds(position) and self.map[position.x][position.y] is not None


    def isTileOutOfBounds(self, position):
        return position.x < 0 or position.y < 0 or position.x >= self.size.x or position.y >= self.size.y


    def getPossibleMoveDirection(self, position, onlyFreeTiles):
        possibleMoves = self.getNeighbours(position, onlyFreeTiles, False)

        if not possibleMoves:
            return Vector2.ZERO
        else:
            movePosition = possibleMoves[int(random.random() * len(possibleMoves))]
            return Vector2(movePosition.x - position.x, movePosition.y - position.y)


    def getEntitiesAround(self, position):
        possibleMoves = self.getNeighbours(position, False, True)
        entities = []

        for pos in possibleMoves:
            entities.append(self.map[pos.x][pos.y])
        return entities


    def move(self, from_pos, to_pos):
        temp = self.map[to_pos.x][to_pos.y]
        self.map[to_pos.x][to_pos.y] = self.map[from_pos.x][from_pos.y]
        self.map[from_pos.x][from_pos.y] = temp


    def getNeighbours(self, position, onlyFreeTiles, onlyOccupiedTiles):
        tiles = []

        for direction in self.tileNeighbours[position.y % 2]:
            neighbour = position.add(direction)
            
            if self.isTileOutOfBounds(neighbour):
                continue

            occupant = self.map[neighbour.x][neighbour.y]
            if (
                (onlyFreeTiles and occupant is None)
                or (not onlyFreeTiles and not onlyOccupiedTiles)
                or (onlyOccupiedTiles and occupant is not None)
            ):
                tiles.append(neighbour)
                
        return tiles

    # calculate total moves needed to get from from_pos to to_pos, assuming no obstacles
    def distanceTo(self, from_pos, to_pos):
        if not self.hexMode:
            return max(abs(from_pos.x - to_pos.x), abs(from_pos.y - to_pos.y))
        else:
            dx = from_pos.x - to_pos.x
            dy = abs(from_pos.y - to_pos.y)
            if from_pos.y % 2 == 0:
                return dy + max(0, abs(dx) - (dy + 1 * math.copysign(1, dx)) // 2)
            else:
                return dy + max(0, abs(dx) - dy // 2)


    def getMoveDirectionTowards(self, from_pos, to_pos):
        if not self.hexMode:
            dx = to_pos.x - from_pos.x
            dy = to_pos.y - from_pos.y
            move_x = 0 if dx == 0 else (1 if dx > 0 else -1)
            move_y = 0 if dy == 0 else (1 if dy > 0 else -1)
            return Vector2(move_x, move_y)
        else:
            # Hex grid movement logic
            best_direction = Vector2.ZERO
            min_distance = math.inf

            for direction in self.tileNeighbours[from_pos.y % 2]:
                new_position = from_pos.add(direction)
                distance = self.distanceTo(new_position, to_pos)
                if distance < min_distance and not self.isTileOutOfBounds(new_position):
                    min_distance = distance
                    best_direction = direction

            return best_direction