package po.world_simulator.entities.plants;

import java.util.Map;

import po.world_simulator.Config;
import po.world_simulator.Vector2;
import po.world_simulator.entities.Plant;

public class Milkweed extends Plant {
    public Milkweed(Vector2 position, int age) {
        super(0, position, "milkweed", age);
    }

    public Milkweed(Vector2 position) {
        this(position, 0);
    }

    public Milkweed(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("age"))
        );
    }

    @Override
    public void action() {
        // three reproduce attempts
        for (int i = 0; i < 2; i++) {
            if (Math.random() * 100 < Config.PLANTS_SPREAD_CHANCE) {
                this.reproduce();
            }
        }

        // third reproduce attempt is located in plant action code
        super.action();
    }
}
