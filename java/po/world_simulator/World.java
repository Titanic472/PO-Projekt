package po.world_simulator;

import java.util.PriorityQueue;

public class World {
    private Human human;
    // [AI] C++ std::priority_queue jest max-heap, domyślna w Javie to min-heap.
    // [AI] By odzwierciedlić najwyższą inicjatywę na szczycie, musimy upewnić się, że compareTo jest odpowiednio zaimplementowane albo użyć Collections.reverseOrder()
    private PriorityQueue<Entity> entities;
    private PriorityQueue<Entity> nextTurnEntities;

    private Vector2 worldSize;

    private Map map;
    private Renderer renderer;
    private InputManager inputManager;

    private static World instance;

    public World() {
        // ... (Zgodnie z implementacją)
        instance = this;
        // Inicjalizacja max-heap, by odpowiadało dzialaniu `priority_queue` z C++ z operatorem `<` zwracającym mniejszy = true
        // Comparator C++: return *a < *b; -> jeśli a ma mniejszą incjatywę, "b" ma wyższy priorytet. W Javie z odwróconym porzadkiem (descending) będzie dobrze
        entities = new PriorityQueue<>(java.util.Collections.reverseOrder());
        nextTurnEntities = new PriorityQueue<>(java.util.Collections.reverseOrder());
    }

    public static Renderer getRenderer() {
        return instance.renderer;
    }

    public static Map getMap() {
        return instance.map;
    }

    public static InputManager getInputManager() {
        return instance.inputManager;
    }

    public static World getInstance() {
        return instance;
    }

    public static Human getHuman() {
        return instance.human;
    }

    public static int getEntityCount() {
        return instance.entities.size() + instance.nextTurnEntities.size();
    }

    public boolean performTurn() {
        // [AI] Kod tury: pobranie kolejki, wykonanie .action() i usuwanie martwych
        return true;
    }

    public void drawWorld() {
        // delegate to map
    }

    public void addNewEntity(Entity entity) {
        nextTurnEntities.add(entity);
        map.placeEntityAt(entity.getPosition(), entity);
    }

    // Ręczne ubijanie kolejek by pomóc Garbage Collectorowi lub zlikwidować wiszące zasoby.
    private void clearEntities() {
        while (!entities.isEmpty()) {
            Entity e = entities.poll();
            if (e != null) e.dispose(); // [AI] Ręczne wywołanie destruktora/dispose'a.
        }
        while (!nextTurnEntities.isEmpty()) {
            Entity e = nextTurnEntities.poll();
            if (e != null) e.dispose();
        }
    }
}
