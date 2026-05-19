package po.world_simulator;

import java.util.ArrayList;
import java.util.List;
import po.world_simulator.entities.Entity;

public class Map {

    private final Vector2[][] tileNeighbours;

    private final Entity[][] map;
    private final Vector2 size;

    public Map(Vector2 mapSize, boolean hexMode) {
        this.size = mapSize;
        if(hexMode){
            this.tileNeighbours = new Vector2[][]{
                {
                    new Vector2(-1, -1), new Vector2(0, -1),
                    new Vector2(-1, 0), new Vector2(1, 0),
                    new Vector2(-1, 1),  new Vector2(0, 1)
                },
                {
                    new Vector2(0, -1), new Vector2(1, -1),
                    new Vector2(-1, 0), new Vector2(1, 0),
                    new Vector2(0, 1),  new Vector2(1, 1)
                }
            };
        }
        else{
            this.tileNeighbours = new Vector2[][]{
                {
                    new Vector2(-1, -1), new Vector2(0, -1), new Vector2(1, -1),
                    new Vector2(-1, 0),                      new Vector2(1, 0),
                    new Vector2(-1, 1),  new Vector2(0, 1),  new Vector2(1, 1)
                },
                {
                    new Vector2(-1, -1), new Vector2(0, -1), new Vector2(1, -1),
                    new Vector2(-1, 0),                      new Vector2(1, 0),
                    new Vector2(-1, 1),  new Vector2(0, 1),  new Vector2(1, 1)
                }
            };
        }
        // W Javie używamy tablic 2D (lub list), inicjalizują się na null domyślnie
        this.map = new Entity[size.x][size.y];
    }

    public Entity getEntityAt(Vector2 position) {
        if (isTileOutOfBounds(position)) return null;
        return map[position.x][position.y];
    }

    public void placeEntityAt(Vector2 position, Entity entity) {
        if (!isTileOutOfBounds(position)) {
            map[position.x][position.y] = entity;
        }
    }

    public void removeEntityAt(Vector2 position) {
        if (!isTileOutOfBounds(position)) {
            map[position.x][position.y] = null;
        }
    }

    public boolean isTileOccupied(Vector2 position) {
        return !isTileOutOfBounds(position) && map[position.x][position.y] != null;
    }

    public boolean isTileOutOfBounds(Vector2 position) {
        return position.x < 0 || position.y < 0
            || position.x >= size.x || position.y >= size.y;
    }

    public Vector2 getPossibleMoveDirection(Vector2 position, boolean onlyFreeTiles) {
        List<Vector2> possibleMoves = getNeighbours(position, onlyFreeTiles, false);

        if (possibleMoves.isEmpty()) {
            return Vector2.ZERO;
        } else {
            Vector2 movePosition = possibleMoves.get((int) (Math.random() * possibleMoves.size()));
            return new Vector2(movePosition.x - position.x, movePosition.y - position.y);
        }
    }

    public List<Entity> getEntitiesAround(Vector2 position) {
        List<Vector2> possibleMoves = getNeighbours(position, false, true);
        List<Entity> entities = new ArrayList<>();

        for (Vector2 pos : possibleMoves) {
            entities.add(map[pos.x][pos.y]);
        }
        return entities;
    }

    public void move(Vector2 from, Vector2 to) {
        Entity temp = map[to.x][to.y];
        map[to.x][to.y] = map[from.x][from.y];
        map[from.x][from.y] = temp;
    }

    private List<Vector2> getNeighbours(Vector2 position, boolean onlyFreeTiles, boolean onlyOccupiedTiles) {
        List<Vector2> tiles = new ArrayList<>();

        for (Vector2 direction : tileNeighbours[position.y % 2]) {
            Vector2 neighbour = position.add(direction);
            if (isTileOutOfBounds(neighbour)) continue;

            Entity occupant = map[neighbour.x][neighbour.y];
            if (
                    (onlyFreeTiles && occupant == null)
                    || (!onlyFreeTiles && !onlyOccupiedTiles)
                    || (onlyOccupiedTiles && occupant != null)
            )
                tiles.add(neighbour);
        }
        return tiles;
    }
}