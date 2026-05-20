package po.world_simulator.entities.animals;

import java.util.Map;
import po.world_simulator.Config;
import po.world_simulator.DataFormat;
import po.world_simulator.SaveParser;
import po.world_simulator.Vector2;
import po.world_simulator.World;
import po.world_simulator.entities.Animal;
import po.world_simulator.entities.Entity;

public class Human extends Animal {
    private int abilityCooldown;
    private static Human instance;

    public Human(Vector2 position, int power, int age, int abilityCooldown) {
        super(power, 4, position, "Human", age, true);
        this.abilityCooldown = abilityCooldown;

        if (instance != null)
            instance.dispose();

        instance = this;
    }

    public Human(Vector2 position) {
        this(position, 5, 0, 0);
    }

    public Human(Map<String, String> entityData){
        this(
            new Vector2(entityData.get("position")),
            Integer.parseInt(entityData.get("power")),
            Integer.parseInt(entityData.get("age")),
            Integer.parseInt(entityData.get("abilityCooldown"))
        );
    }

    public static Human getInstance() {
        return instance;
    }

    @Override
    public void dispose() {
        if (instance == this)
            instance = null;
        super.dispose();
    }

    @Override
    public void action() {
        if (abilityCooldown > 0)
            abilityCooldown--;

        Vector2 moveDirection = Vector2.ZERO;
        int lastInput = World.getInputManager().getLastInput();

        switch (lastInput) {
            case Config.LEFT:
                moveDirection = new Vector2(-1, 0);
                break;
            case Config.RIGHT:
                moveDirection = new Vector2(1, 0);
                break;
            case Config.UP:
                moveDirection = new Vector2(0, -1);
                break;
            case Config.DOWN:
                moveDirection = new Vector2(0, 1);
                break;
            case Config.ABILITY:
                if (abilityCooldown == 0)
                    abilityCooldown = 10;
                break;
        }

        if (!World.getMap().isTileOutOfBounds(this.position.add(moveDirection)) && !moveDirection.equals(Vector2.ZERO))
            move(moveDirection);

        // if(age == 90) cout << "moje plecy!";
        this.age += 1;
    }

    @Override
    public void collision(Entity otherEntity) {
        // ability handle before turn if collision happened
        if (World.getInputManager().getLastInput() == Config.ABILITY && abilityCooldown == 0)
            abilityCooldown = 11;

        if (abilityCooldown > 5) {
            if (otherEntity.getPower() >= this.getPower())
                this.runAway();
            return;
        }

        super.collision(otherEntity);
    }

    public int getAbilityCooldown() {
        return abilityCooldown;
    }

    @Override
    public void kill() {
        if (abilityCooldown > 5)
            return;
        World.getRenderer().addToLog("Human died at age " + this.age);
        super.kill();
    }

    @Override
    public String saveAsString(SaveParser parser) {
        String data = super.saveAsString(parser);
        data += parser.stringifyEntry("abilityCooldown", DataFormat.TYPE_INT, String.valueOf(this.abilityCooldown));
        return data;
    }
}
