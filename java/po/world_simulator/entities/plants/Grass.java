package po.world_simulator.entities.plants;

import po.world_simulator.Vector2;
import po.world_simulator.entities.Plant;

public class Grass extends Plant {
    public Grass(Vector2 position, int age) {
        super(0, position, "trawa:)", "Grass", age);
    }

    public Grass(Vector2 position) {
        this(position, 0);
    }
}
