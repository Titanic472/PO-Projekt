package po.world_simulator.entities;

import po.world_simulator.Entity;
import po.world_simulator.Map;
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
        if (this.getClass().equals(otherEntity.getClass())) {
            this.reproduce();
            return;
        }

        if (otherEntity instanceof Animal) {
            Animal enemy = (Animal) otherEntity;
            if (this.getPower() <= enemy.getPower() && !enemy.isPredator()) {
                this.runAway();
                return;
            }
        }
        super.collision(otherEntity);
    }

    public boolean isPredator() {
        return canKill;
    }

    protected void move(Vector2 moveDirection) {
        Map map = World.getMap();
        Vector2 targetPos = this.position.add(moveDirection);
        Entity collisionTarget = map.getEntityAt(targetPos);

        if (collisionTarget != null) {
            collisionTarget.collision(this);

            if (!this.isAlive()) {
                return;
            }
        }

        if (map.getEntityAt(targetPos) == null) {
            map.move(this.position, targetPos);
            this.position = targetPos;
        }
    }

    protected boolean runAway() {
        Map map = World.getMap();
        Vector2 direction = map.getPossibleMoveDirection(this.position, true);

        if (!moveDir.equals(Vector2.ZERO)) {
            move(direction);
            return true;
        }
        return false;
    }
}
