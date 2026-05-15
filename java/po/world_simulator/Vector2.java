package po.world_simulator;

public class Vector2 {
    public int x;
    public int y;

    public static final Vector2 ZERO = new Vector2(0, 0);

    public Vector2(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Vector2() {
        this.x = 0;
        this.y = 0;
    }

    public Vector2(String str) {
        int pos = str.indexOf('_');
        this.x = Integer.parseInt(str.substring(0, pos));
        this.y = Integer.parseInt(str.substring(pos + 1));
    }

    @Override
    public String toString() {
        return x + "_" + y;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Vector2 vector2 = (Vector2) obj;
        return x == vector2.x && y == vector2.y;
    }

    public Vector2 add(Vector2 other) {
        return new Vector2(this.x + other.x, this.y + other.y);
    }

    public void addSelf(Vector2 other) {
        this.x += other.x;
        this.y += other.y;
    }

    public Vector2 multiply(float scale) {
        return new Vector2((int)(this.x * scale), (int)(this.y * scale));
    }

    public void multiplySelf(int scale) {
        this.x *= scale;
        this.y *= scale;
    }
}
