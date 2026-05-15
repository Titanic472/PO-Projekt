package po.world_simulator.entities.animals;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Animal;

public class Wolf extends Animal {
    public Wolf(Vector2 position, int power, int age) {
        super(power, 5, position, "Wolf", age, true);
    }

    public Wolf(Vector2 position) {
        this(position, 9, 0);
    }
}
