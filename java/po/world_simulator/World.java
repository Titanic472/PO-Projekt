package po.world_simulator;

import java.util.PriorityQueue;
import java.util.HashMap;
import java.util.Random;
import java.util.Map as JavaMap;
import java.util.function.Function;

import po.world_simulator.entities.plants.*;
import po.world_simulator.entities.animals.*;

public class World {
    // [AI] C++ std::priority_queue jest max-heap, domyślna w Javie to min-heap.
    // [AI] By odzwierciedlić najwyższą inicjatywę na szczycie, musimy upewnić się, że compareTo jest odpowiednio zaimplementowane albo użyć Collections.reverseOrder()
    private PriorityQueue<Entity> entities;
    private PriorityQueue<Entity> nextTurnEntities;

    private Vector2 worldSize;

    private Map map;
    private Renderer renderer;
    private InputManager inputManager;

    private static World instance;
    private Random random = new Random();

    public World() {
        worldSize = new Vector2(Config.MAP_SIZE_X, Config.MAP_SIZE_Y);

        this.map = new Map(worldSize);
        this.renderer = new Renderer(worldSize);
        this.inputManager = new InputManager();

        if (instance != null) {
            instance.dispose();
        }

        instance = this;

        entities = new PriorityQueue<>(java.util.Collections.reverseOrder());
        nextTurnEntities = new PriorityQueue<>(java.util.Collections.reverseOrder());

        createEntities();
    }

    public void dispose() {
        clearEntities();
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

    public static int getEntityCount() {
        return instance.entities.size();
    }

    public boolean performTurn() {
        do {
            inputManager.readNextInput();

            if (inputManager.isQuitPressed())
                return false;

            if (inputManager.getLastInput() == Config.SAVE) {
                save();
                inputManager.clearLastInput();
                // skip turn after saving
                return true;
            } else if (inputManager.getLastInput() == Config.LOAD) {
                load();
                inputManager.clearLastInput();
                // skip turn after loading
                return true;
            }

            // redraw info window to show pressed input
            renderer.drawInfoWindow();
            renderer.renderInfoWindow();
        }
        while (!inputManager.isNewTurnPressed());

        renderer.clearLog();

        while (!entities.isEmpty()) {
            Entity entity = entities.poll();

            if (entity.isAlive())
                entity.action();

            queueToNext(entity);
        }

        nextQueue();
        return true;
    }

    public void drawWorld() {
        renderer.drawMap(worldSize);

        while (!entities.isEmpty()) {
            Entity entity = entities.poll();

            if (entity.isAlive()) entity.draw();

            queueToNext(entity);
        }

        renderer.renderMap();

        nextQueue();

        renderer.drawInfoWindow();
        renderer.renderInfoWindow();
    }

    public void save() {
        SaveParser parser = new SaveParser();

        parser.createFile(worldSize);

        parser.addEntry("world_size", DataFormat.TYPE_VECTOR2, worldSize.toString());

        parser.startCategory("entities");

        while (!entities.isEmpty()) {
            Entity entity = entities.poll();

            if (entity.isAlive()) parser.addStringEntry(entity.saveAsString(parser));

            queueToNext(entity);
        }

        nextQueue();

        parser.endCategory();

        parser.closeFile();

        renderer.clearLog();
        renderer.addToLog("game saved!");
    }

    public void load() {
        renderer.clearLog();

        SaveParser parser = new SaveParser();

        if (!parser.loadFile(worldSize)) {
            renderer.addToLog("no save file found!");
            return;
        }

        worldSize = parser.loadEntryVector2("world_size");

        // clear previous world
        map = new Map(worldSize);
        clearEntities();

        // load entities
        if (!parser.jumpToCategory("entities")) {
            renderer.addToLog("incorrect save file format");
            return;
        }

        JavaMap<String, String> entityData = new HashMap<>();

        while (parser.loadEntryMultiline(entityData)) {
            loadEntity(entityData);
            entityData.clear();
        }

        nextQueue();
        renderer.addToLog("game loaded!");
    }

    public void addNewEntity(Entity entity) {
        if (map.isTileOccupied(entity.getPosition())) {
            // convert entity into kebap
            entity.dispose();
        } else {
            // add entity to world
            map.placeEntityAt(entity.getPosition(), entity);
            queueToNext(entity);
        }
    }

    private void queueToNext(Entity entity) {
        if (entity.isAlive())
            nextTurnEntities.add(entity);
        else
            entity.dispose();
    }

    private void nextQueue() {
        entities.addAll(nextTurnEntities);
        nextTurnEntities.clear();
    }

    private void createEntities() {
        int worldArea = worldSize.x * worldSize.y;

        addNewEntity(new Human(worldSize.multiply(0.5f)));

        randomizeEntities(Grass::new, worldArea, Config.GRASS_AMOUNT);
        randomizeEntities(Milkweed::new, worldArea, Config.MILKWEED_AMOUNT);
        randomizeEntities(Guarana::new, worldArea, Config.GUARANA_AMOUNT);
        randomizeEntities(Wolfberries::new, worldArea, Config.WOLFBERRIES_AMOUNT);
        randomizeEntities(SosnowskiHogweed::new, worldArea, Config.SOSNOWSKI_HOGWEED_AMOUNT);
        randomizeEntities(Wolf::new, worldArea, Config.WOLF_AMOUNT);
        randomizeEntities(Sheep::new, worldArea, Config.SHEEP_AMOUNT);
        randomizeEntities(Fox::new, worldArea, Config.FOX_AMOUNT);
        randomizeEntities(Turtle::new, worldArea, Config.TURTLE_AMOUNT);
        randomizeEntities(Antelope::new, worldArea, Config.ANTELOPE_AMOUNT);

        nextQueue();
    }

    private void randomizeEntities(Function<Vector2, Entity> constructor, int worldArea, int percent) {
        int amount = worldArea * percent / 100;
        for (int i = 0; i < amount; ++i) {
            addNewEntity(constructor.apply(new Vector2(random.nextInt(worldSize.x), random.nextInt(worldSize.y))));
        }
    }

    public void loadEntity(JavaMap<String, String> entityData) {
        String type = entityData.get("type");

        // Szukamy klasy po jej nazwie względem konkretnego pakietu
        String[] packages = {
            "po.world_simulator.entities.animals.",
            "po.world_simulator.entities.plants."
        };

        for (String pkg : packages) {
            try {
                Class<?> clazz = Class.forName(pkg + type);
                Entity entity = (Entity) clazz.getDeclaredConstructor(JavaMap.class).newInstance(entityData);
                addNewEntity(entity);
                return;
            } catch (Exception ignored) {
                // Wyjątek oznacza, że klasy tu nie ma, kontynuujemy z kolejnym pakietem
            }
        }

        renderer.addToLog("UNKNOWN ENTITY TYPE: " + type);
    }

    // Ręczne ubijanie kolejek by pomóc Garbage Collectorowi lub zlikwidować wiszące zasoby.
    private void clearEntities() {
        while (!entities.isEmpty()) {
            Entity entity = entities.poll();
            if (entity != null) entity.dispose();
        }
        while (!nextTurnEntities.isEmpty()) {
            Entity entity = nextTurnEntities.poll();
            if (entity != null) entity.dispose();
        }
    }
}
