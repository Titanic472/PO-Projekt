package po.world_simulator.entities.animals;

import java.util.Map;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Animal;


public class Sheep extends Animal {
    public Sheep(Vector2 position, int power, int age) {
        super(power, 4, position, "Sheep", age, false);
    }

    public Sheep(Vector2 position) {
        this(position, 4, 0);
    }

    public Sheep(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("power")),
            Integer.parseInt(entityData.get("age"))
        );
    }
}
