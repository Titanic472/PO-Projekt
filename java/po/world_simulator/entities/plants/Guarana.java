package po.world_simulator.entities.plants;

import po.world_simulator.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.entities.Plant;

public class Guarana extends Plant {
    public Guarana(Vector2 position, int age) {
        super(0, position, "guarana", age);
    }

    public Guarana(Vector2 position) {
        this(position, 0);
    }

    @Override
    public void collision(Entity otherEntity) {
        otherEntity.setPower(otherEntity.getPower() + 3);
        super.collision(otherEntity);
    }
}
