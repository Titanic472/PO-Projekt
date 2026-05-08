package po.world_simulator;

import po.world_simulator.entities.Animal;

public class Human extends Animal {
    public Human(Vector2 position) {
        super(5, 4, position, "Human", "human", 0, true);
    }

    @Override
    public Entity clone(Vector2 position) {
        return new Human(position); // lub zablokować klonowanie ludzia
    }
}
