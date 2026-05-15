package po.world_simulator;

public class Main {
    public static void main(String[] args) {
        World world = new World();

        // Podpinamy przyciski zapisu i odczytu GUI pod metody logiki świata
        World.getRenderer().bind("Save", () -> world.save());
        World.getRenderer().bind("Load", () -> world.load());

        // Główna pętla gry (odpowiednik C++)
        do {
            world.drawWorld();
        } while (world.performTurn());

        // Sprzątanie po wyjściu z pętli (gdy np. wciśnięto Config.QUIT)
        world.dispose();

        // Zamykamy proces Javy
        System.exit(0);
    }
}
