package po.world_simulator.entities.animals;

import po.world_simulator.entities.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.World;
import po.world_simulator.entities.Animal;

public class Antelope extends Animal {
    public Antelope(Vector2 position, int power, int age) {
        super(power, 4, position, "Antelope", age, false);
    }

    public Antelope(Vector2 position) {
        this(position, 4, 0);
    }

    @Override
    protected void move(Vector2 moveDirection) {
        // 2 tile move
        moveDirection.multiplySelf(2);

        if (!World.getMap().isTileOutOfBounds(this.position.add(moveDirection))) {
            super.move(moveDirection);
        }
    }

    @Override
    public void collision(Entity otherEntity) {
        if (!this.getClass().equals(otherEntity.getClass())) {
            if (Math.random() < 0.5) {
                if (this.runAway()) {
                    return;
                }
            }
        }
        super.collision(otherEntity);
    }
}
