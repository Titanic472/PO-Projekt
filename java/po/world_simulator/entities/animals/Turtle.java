package po.world_simulator.entities.animals;

import po.world_simulator.entities.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.entities.Animal;

public class Turtle extends Animal {
    public Turtle(Vector2 position, int power, int age) {
        super(power, 1, position, "Turtle", age, false);
    }

    public Turtle(Vector2 position) {
        this(position, 2, 0);
    }

    @Override
    public void collision(Entity otherEntity) {
        if (!this.getClass().equals(otherEntity.getClass())) {
            if (otherEntity.getPower() < 5) {
                return;
            }
        }
        super.collision(otherEntity);
    }

    @Override
    protected void move(Vector2 moveDirection) {
        if (Math.random() < 0.25) {
            super.move(moveDirection);
        }
    }
}
