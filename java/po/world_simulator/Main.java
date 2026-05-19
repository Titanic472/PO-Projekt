package po.world_simulator;

public class Main {
    public static void main(String[] args) {
        World world = new World(Config.HEX_ENABLED);

        // mainloop
        do {
            world.drawWorld();
        } while (world.performTurn());

        world.dispose();

        System.exit(0);
    }
}
