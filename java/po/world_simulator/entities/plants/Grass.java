package po.world_simulator.entities.plants;

import java.util.Map;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Plant;

public class Grass extends Plant {
    public Grass(Vector2 position, int age) {
        super(0, position, "trawa:)", age);
    }

    public Grass(Vector2 position) {
        this(position, 0);
    }

    public Grass(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("age"))
        );
    }
}
