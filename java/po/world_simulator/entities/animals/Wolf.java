package po.world_simulator.entities.animals;

import java.util.Map;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Animal;

public class Wolf extends Animal {
    public Wolf(Vector2 position, int power, int age) {
        super(power, 5, position, "Wolf", age, true);
    }

    public Wolf(Vector2 position) {
        this(position, 9, 0);
    }

    public Wolf(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("power")),
            Integer.parseInt(entityData.get("age"))
        );
    }
}
