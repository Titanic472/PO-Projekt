package po.world_simulator;

import java.awt.Color;

public class Config {
    public static final int MAP_SIZE_X = 20;
    public static final int MAP_SIZE_Y = 10;
    public static final int STATUS_WIDTH = 25; // Jako % szerokości ekranu

    public static final int GRASS_AMOUNT = 10;
    public static final int MILKWEED_AMOUNT = 8;
    public static final int GUARANA_AMOUNT = 10;
    public static final int WOLFBERRIES_AMOUNT = 2;
    public static final int SOSNOWSKI_HOGWEED_AMOUNT = 4;

    public static final int WOLF_AMOUNT = 2;
    public static final int SHEEP_AMOUNT = 5;
    public static final int FOX_AMOUNT = 5;
    public static final int TURTLE_AMOUNT = 5;
    public static final int ANTELOPE_AMOUNT = 5;

    public static final int PLANTS_SPREAD_CHANCE = 5;

    public static final char QUIT = 'q';
    public static final int LEFT = 255 + 68;
    public static final int RIGHT = 255 + 67;
    public static final int UP = 255 + 65;
    public static final int DOWN = 255 + 66;
    public static final char ABILITY = 'e';
    public static final char NEW_TURN = 'n';
    public static final char SAVE = 's';
    public static final char LOAD = 'l';

    // Opcje renderera / GUI
    public static final int WINDOW_WIDTH = 1200;
    public static final int WINDOW_HEIGHT = 800;
    public static final Color BG_COLOR = new Color(240, 240, 240);
    public static final Color GRID_BG_COLOR = Color.WHITE;
    public static final Color BORDER_COLOR = Color.LIGHT_GRAY;
    public static final int BORDER_THICKNESS = 1;
    public static final Color TEXT_COLOR = Color.BLACK;
    public static final int BLOCK_FONT_SIZE = 24;
}
