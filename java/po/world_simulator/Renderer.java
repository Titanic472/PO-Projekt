package po.world_simulator;

import javax.swing.*;
import javax.swing.border.LineBorder;

import po.world_simulator.entities.animals.Human;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;

public class Renderer {
    protected JFrame frame;
    protected JPanel mapPanel;
    protected JPanel statusPanel;

    protected JLabel[][] gridLabels;

    protected JButton btnSave;
    protected JButton btnLoad;

    protected JLabel lblNextAction;
    protected JLabel lblCooldown;
    protected JLabel lblEntities;
    protected JTextArea logArea;

    protected LinkedList<String> logMessages = new LinkedList<>();

    public Renderer(Vector2 mapSize) {
        frame = new JFrame("World Simulator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(Config.WINDOW_WIDTH, Config.WINDOW_HEIGHT);
        frame.setLayout(new BorderLayout());

        // --- GLOBAL KEY LISTENER ---
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() {
            @Override
            public boolean dispatchKeyEvent(KeyEvent e) {
                if (e.getID() == KeyEvent.KEY_PRESSED) {
                    InputManager im = World.getInputManager();
                    if (im == null) return false;

                    int code = e.getKeyCode();
                    if (code == KeyEvent.VK_LEFT)
                        im.pushInput(Config.LEFT);
                    else if (code == KeyEvent.VK_RIGHT)
                        im.pushInput(Config.RIGHT);
                    else if (code == KeyEvent.VK_UP)
                        im.pushInput(Config.UP);
                    else if (code == KeyEvent.VK_DOWN)
                        im.pushInput(Config.DOWN);
                    else if (code == KeyEvent.VK_E)
                        im.pushInput(Config.ABILITY);
                    else if (code == KeyEvent.VK_N)
                        im.pushInput(Config.NEW_TURN);
                    else if (code == KeyEvent.VK_S)
                        im.pushInput(Config.SAVE);
                    else if (code == KeyEvent.VK_L)
                        im.pushInput(Config.LOAD);
                    else if (code == KeyEvent.VK_Q)
                        im.pushInput(Config.QUIT);
                    renderInfoWindow();
                }
                return false;
            }
        });

        // --- MAP PANEL ---
        mapPanel = new JPanel(new GridLayout(mapSize.y, mapSize.x));
        mapPanel.setBackground(Config.BG_COLOR);
        gridLabels = new JLabel[mapSize.y][mapSize.x];

        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                JLabel cell = new JLabel("", SwingConstants.CENTER);
                cell.setOpaque(true);
                cell.setBackground(Config.DEFAULT_GRID_BG_COLOR);
                cell.setBorder(new LineBorder(Config.BORDER_COLOR, Config.BORDER_THICKNESS));
                cell.setForeground(Config.TEXT_COLOR);
                cell.setFont(new Font("Monospaced", Font.BOLD, Config.BLOCK_FONT_SIZE));

                final int cx = x;
                final int cy = y;
                cell.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        showAddEntityDialog(new Vector2(cx, cy));
                    }
                });

                gridLabels[y][x] = cell;
                mapPanel.add(cell);
            }
        }

        // --- STATUS PANEL ---
        statusPanel = new JPanel(new BorderLayout());

        int statusWidth = (Config.WINDOW_WIDTH * Config.STATUS_WIDTH) / 100;
        statusPanel.setPreferredSize(new Dimension(statusWidth, Config.WINDOW_HEIGHT));
        statusPanel.setBorder(new LineBorder(Color.BLACK, 2));

        // Górna sekcja statusu
        JPanel topStatusPanel = new JPanel();
        topStatusPanel.setLayout(new BoxLayout(topStatusPanel, BoxLayout.Y_AXIS));

        // Przyciski (B1 i B2)
        JPanel buttonsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        btnSave = new JButton("Save");
        btnLoad = new JButton("Load");
        btnSave.setFocusable(false); // Unikamy zabierania focusu fizycznej klawiaturze
        btnLoad.setFocusable(false);
        buttonsPanel.add(btnSave);
        buttonsPanel.add(btnLoad);

        // Informacje / Tekst
        lblNextAction = new JLabel("next action: ");
        lblCooldown = new JLabel("ability cooldown: ");
        lblEntities = new JLabel("entities: ");

        lblNextAction.setAlignmentX(Component.CENTER_ALIGNMENT);
        lblCooldown.setAlignmentX(Component.CENTER_ALIGNMENT);
        lblEntities.setAlignmentX(Component.CENTER_ALIGNMENT);

        topStatusPanel.add(buttonsPanel);
        topStatusPanel.add(lblNextAction);
        topStatusPanel.add(lblCooldown);
        topStatusPanel.add(lblEntities);

        // Dolna sekcja logów
        JPanel mainLogPanel = new JPanel(new BorderLayout());
        JLabel logTitle = new JLabel("log:", SwingConstants.CENTER);
        logArea = new JTextArea();
        logArea.setEditable(false);
        logArea.setFocusable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);

        mainLogPanel.add(logTitle, BorderLayout.NORTH);
        mainLogPanel.add(scrollPane, BorderLayout.CENTER);

        statusPanel.add(topStatusPanel, BorderLayout.NORTH);
        statusPanel.add(mainLogPanel, BorderLayout.CENTER);

        frame.add(mapPanel, BorderLayout.CENTER);
        frame.add(statusPanel, BorderLayout.EAST);

        frame.setVisible(true);
    }

    // Pozwala przypisać zewnętrzną metodę, np. od InputManagera / World
    public void bind(String buttonName, Runnable action) {
        if (buttonName.equalsIgnoreCase("Save") || buttonName.equalsIgnoreCase("B1")) {
            // Czyść ewentualne stare bindy
            for (var al : btnSave.getActionListeners()) btnSave.removeActionListener(al);
            btnSave.addActionListener(e -> action.run());
        } else if (buttonName.equalsIgnoreCase("Load") || buttonName.equalsIgnoreCase("B2")) {
            for (var al : btnLoad.getActionListeners()) btnLoad.removeActionListener(al);
            btnLoad.addActionListener(e -> action.run());
        }
    }

    public void renderMap() {
        // Swing automatycznie maluje, ale może nam to odświeżyć okno, gdy zmienimy setText
        mapPanel.repaint();
    }

    public void renderInfoWindow() {
        String button_text = "next action: ";
        button_text += convertInputToText(World.getInputManager().getLastInput());
        lblNextAction.setText(button_text);

        po.world_simulator.entities.animals.Human human = Human.getInstance();

        if (human != null) {
            lblCooldown.setText("ability cooldown: " + human.getAbilityCooldown());
        } else {
            lblCooldown.setText("Human died :(");
        }

        lblEntities.setText("entities: " + World.getEntityCount());

        StringBuilder sb = new StringBuilder();
        for (String msg : logMessages) {
            sb.append(msg).append("\n");
        }
        logArea.setText(sb.toString());

        statusPanel.repaint();
    }

    public void drawCharAt(Vector2 position, char text) {
        if (position.y >= 0 && position.y < gridLabels.length &&
            position.x >= 0 && position.x < gridLabels[0].length) {
            gridLabels[position.y][position.x].setText(String.valueOf(text));
        }
    }

    public void drawMap(Vector2 mapSize) {
        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                gridLabels[y][x].setText("");
            }
        }
    }

    public void addToLog(String text) {
        logMessages.add(text);
        // Zabezpieczenie by log się nie rozrastał w nieskończoność
        if (logMessages.size() > 100) {
            logMessages.removeFirst();
        }
    }

    public void drawInfoWindow() {
        // Logikę realizuje już złączone na stałe update w renderInfoWindow() dla Swinga
    }

    public void clearLog() {
        logMessages.clear();
        logArea.setText("");
    }

    public void dispose() {
        frame.dispose();
    }


    public String convertInputToText(int input){
    switch (input){
    case Config.LEFT:
        return "LEFT";
    case Config.RIGHT:
        return "RIGHT";
    case Config.UP:
        return "UP";
    case Config.DOWN:
        return "DOWN";
    case Config.ABILITY:
        return "ABILITY";
    default:
        return "";
    }
    }

    protected void showAddEntityDialog(Vector2 position) {
        po.world_simulator.Map map = World.getMap();
        if (map != null && map.isTileOccupied(position)) {
            return;
        }

        String[] entities = {
            "Wolf", "Sheep", "Fox", "Turtle", "Antelope",
            "Grass", "Milkweed", "Guarana", "Wolfberries", "SosnowskiHogweed"
        };

        String message = "Pozycja pola: (" + position.x + ", " + position.y + ")\nWybierz obiekt do dodania:";
        String selected = (String) JOptionPane.showInputDialog(
            frame,
            message,
            "Dodaj Entity",
            JOptionPane.PLAIN_MESSAGE,
            null,
            entities,
            entities[0]
        );

        if (selected != null && !selected.isEmpty()) {
            po.world_simulator.entities.Entity newEntity = null;
            switch (selected) {
                case "Wolf": newEntity = new po.world_simulator.entities.animals.Wolf(position); break;
                case "Sheep": newEntity = new po.world_simulator.entities.animals.Sheep(position); break;
                case "Fox": newEntity = new po.world_simulator.entities.animals.Fox(position); break;
                case "Turtle": newEntity = new po.world_simulator.entities.animals.Turtle(position); break;
                case "Antelope": newEntity = new po.world_simulator.entities.animals.Antelope(position); break;
                case "Grass": newEntity = new po.world_simulator.entities.plants.Grass(position); break;
                case "Milkweed": newEntity = new po.world_simulator.entities.plants.Milkweed(position); break;
                case "Guarana": newEntity = new po.world_simulator.entities.plants.Guarana(position); break;
                case "Wolfberries": newEntity = new po.world_simulator.entities.plants.Wolfberries(position); break;
                case "SosnowskiHogweed": newEntity = new po.world_simulator.entities.plants.SosnowskiHogweed(position); break;
            }

            if (newEntity != null) {
                World.getInstance().addNewEntity(newEntity);
                addToLog("Added " + selected + " at (" + position.x + ", " + position.y + ")");
                World.getInstance().forceDrawAll();
            }
        }
    }
}
