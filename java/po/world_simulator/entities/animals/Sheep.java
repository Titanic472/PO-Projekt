package po.world_simulator.entities.animals;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Animal;

public class Sheep extends Animal {
    public Sheep(Vector2 position, int power, int age) {
        super(power, 4, position, "Sheep", age, false);
    }

    public Sheep(Vector2 position) {
        this(position, 4, 0);
    }
}
