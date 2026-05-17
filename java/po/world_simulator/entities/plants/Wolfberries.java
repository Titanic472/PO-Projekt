package po.world_simulator.entities.plants;

import po.world_simulator.entities.Entity;

import java.util.Map;

import po.world_simulator.Vector2;
import po.world_simulator.World;
import po.world_simulator.entities.Plant;

public class Wolfberries extends Plant {
    public Wolfberries(Vector2 position, int age) {
        super(99, position, "wolfberries", age);
    }

    public Wolfberries(Vector2 position) {
        this(position, 0);
    }

    public Wolfberries(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("age"))
        );
    }

    @Override
    public void collision(Entity otherEntity) {
        otherEntity.kill();
        this.kill();
        World.getRenderer().addToLog(this.getName() + " tried to kill " + otherEntity.getName() + " and died");
    }
}
