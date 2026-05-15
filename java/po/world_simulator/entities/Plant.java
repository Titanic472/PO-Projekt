package po.world_simulator.entities;

import po.world_simulator.entities.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.Config;
import po.world_simulator.World;

public abstract class Plant extends Entity {

    public Plant(int power, Vector2 position, String name, int age) {
        super(power, 0, position, name, age);
    }

    public Plant(int power, Vector2 position, String name) {
        this(power, position, name, 0);
    }

    @Override
    public void action() {
        int spreadRandom = (int) (Math.random() * 100);
        if (spreadRandom < Config.PLANTS_SPREAD_CHANCE) {
            this.reproduce();
        }
        this.age += 1;
    }
}
