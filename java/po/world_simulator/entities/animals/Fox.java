package po.world_simulator.entities.animals;

import po.world_simulator.Entity;
import po.world_simulator.Map;
import po.world_simulator.Vector2;
import po.world_simulator.World;
import po.world_simulator.entities.Animal;

public class Fox extends Animal {
    public Fox(Vector2 position, int power, int age) {
        super(power, 7, position, "Fox", age, true);
    }

    public Fox(Vector2 position) {
        this(position, 3, 0);
    }

    @Override
    public void action() {
        Map map = World.getMap();
        Vector2 moveDirection = map.getPossibleMoveDirection(this.position, false);

        Entity collisionTarget = map.getEntityAt(this.position.add(moveDirection));

        if (collisionTarget == null || collisionTarget.getPower() <= this.getPower()) {
            super.action();
            return;
        }

        this.age += 1;
    }
}
