package po.world_simulator.entities;

import po.world_simulator.Entity;
import po.world_simulator.Vector2;
import po.world_simulator.World;

public abstract class Animal extends Entity {
    private boolean canKill;

    public Animal(int power, int initiative, Vector2 position, String name, String datatype, int age, boolean canKill) {
        super(power, initiative, position, name, datatype, age);
        this.canKill = canKill;
    }

    public Animal(int power, int initiative, Vector2 position, String name, String datatype) {
        this(power, initiative, position, name, datatype, 0, false);
    }

    @Override
    public void action() {
        // [AI] Wywoływane akcje - do implementacji wg konkretnej logiki c++ (losowy kierunek itp)
        Vector2 moveDirection = World.getMap().getPossibleMoveDirection(this.position, false);
        if (!moveDirection.equals(Vector2.ZERO)) {
            move(moveDirection);
        }
        this.age += 1;
    }

    @Override
    public void collision(Entity otherEntity) {
        super.collision(otherEntity);
    }

    public boolean isPredator() {
        return canKill;
    }

    protected void move(Vector2 moveDirection) {
        Vector2 targetPos = this.position.add(moveDirection);

        if (World.getMap().isTileOccupied(targetPos)) {
            Entity occupant = World.getMap().getEntityAt(targetPos);
            // Jeżeli ten sam gatunek to rozmnażanie
            if (occupant.getName().equals(this.getName())) {
                this.reproduce();
            } else {
                this.collision(occupant);
                if (this.isAlive()) {
                    World.getMap().move(this.position, targetPos);
                    this.position = targetPos;
                }
            }
        } else {
            World.getMap().move(this.position, targetPos);
            this.position = targetPos;
        }
    }

    protected boolean runAway() {
        Vector2 moveDir = World.getMap().getPossibleMoveDirection(this.position, true);
        if (!moveDir.equals(Vector2.ZERO)) {
            Vector2 targetPos = this.position.add(moveDir);
            World.getMap().move(this.position, targetPos);
            this.position = targetPos;
            World.getRenderer().addToLog(this.getName() + " ran away.");
            return true;
        }
        return false; // nie udało się uciec
    }
}
