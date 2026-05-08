package po.world_simulator;

import java.util.Map;

public abstract class Entity implements Comparable<Entity> {
    private boolean isDead = false;
    private int power;
    private int initiative;
    private String name;
    private String datatype;

    protected Vector2 position;
    protected int age;

    public Entity(int power, int initiative, Vector2 position, String name, String datatype, int age) {
        this.power = power;
        this.initiative = initiative;
        this.name = name;
        this.datatype = datatype;
        this.position = position;
        this.age = age;
    }

    public Entity(int power, int initiative, Vector2 position, String name, String datatype) {
        this(power, initiative, position, name, datatype, 0);
    }

    // [AI] Ręczne usuwanie / sprzątanie by odciążyć powiązania
    public void dispose() {
    }

    @Override
    public int compareTo(Entity other) {
        if (this.initiative == other.initiative) {
            return Integer.compare(this.age, other.age);
        }
        return Integer.compare(this.initiative, other.initiative);
    }

    public abstract void action();

    public void draw() {
        World.getRenderer().drawCharAt(this.position, this.name.charAt(0));
    }

    public Vector2 getPosition() {
        return this.position;
    }

    public boolean isAlive() {
        return !this.isDead;
    }

    public void kill() {
        this.isDead = true;
        World.getMap().removeEntityAt(this.position);
    }

    public void setPower(int power) {
        this.power = power;
    }

    public int getPower() {
        return this.power;
    }

    public String getName() {
        return this.name;
    }

    public void collision(Entity otherEntity) {
        if (this.power <= otherEntity.getPower()) {
            World.getRenderer().addToLog(this.name + " collided with " + otherEntity.name + " and died");
            this.kill();
        } else {
            World.getRenderer().addToLog(this.name + " collided with " + otherEntity.name + " and won");
            otherEntity.kill();
        }
    }

    public String saveAsString(SaveParser parser) {
        // [AI] Wykorzystanie parsera zapisu, wymaga dopasowania do jawnego przekazywania argumentów w Javie
        String data = "";
        data += parser.stringifyEntry(datatype, DataFormat.CATEGORY_START_HEADER);
        data += parser.stringifyEntry("position", DataFormat.TYPE_VECTOR2, this.position.toString());
        data += parser.stringifyEntry("age", DataFormat.TYPE_INT, String.valueOf(this.age));
        data += parser.stringifyEntry("power", DataFormat.TYPE_INT, String.valueOf(this.power));
        return data;
    }

    protected void reproduce() {
        Vector2 direction = World.getMap().getPossibleMoveDirection(this.position, true);

        if (!World.getMap().isTileOccupied(this.position.add(direction))) {
            World.getRenderer().addToLog(this.name + " reproduced");
            World.getInstance().addNewEntity(clone(this.position.add(direction)));
        }
    }


    protected abstract Entity clone(Vector2 position);
}
