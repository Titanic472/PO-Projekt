package po.world_simulator.entities.plants;

import po.world_simulator.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.World;
import po.world_simulator.entities.Animal;
import po.world_simulator.entities.Plant;

import java.util.List;

public class SosnowskiHogweed extends Plant {
    public SosnowskiHogweed(Vector2 position, int age) {
        super(10, position, "sosnowski hogweed", "SosnowskiHogweed", age);
    }

    public SosnowskiHogweed(Vector2 position) {
        this(position, 0);
    }

    @Override
    public void action() {
        List<Entity> entities = World.getMap().getEntitiesAround(this.position);

        for (Entity entity : entities) {
            if (entity instanceof Animal) {
                entity.kill();
                World.getRenderer().addToLog(this.getName() + " killed " + entity.getName());
            }
        }

        super.action();
    }

    @Override
    public void collision(Entity otherEntity) {
        otherEntity.kill();
        this.kill();
        World.getRenderer().addToLog(this.getName() + " killed " + otherEntity.getName() + " and died");
    }
}
