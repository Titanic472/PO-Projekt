package po.world_simulator;

import javax.swing.*;
import javax.swing.border.LineBorder;

import po.world_simulator.entities.animals.Human;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;

public class Renderer {
    private JFrame frame;
    private JPanel mapPanel;
    private JPanel statusPanel;

    private JLabel[][] gridLabels;

    private JButton btnSave;
    private JButton btnLoad;

    private JLabel lblNextAction;
    private JLabel lblCooldown;
    private JLabel lblEntities;
    private JTextArea logArea;

    private LinkedList<String> logMessages = new LinkedList<>();

    public Renderer(Vector2 mapSize) {
        frame = new JFrame("World Simulator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(Config.WINDOW_WIDTH, Config.WINDOW_HEIGHT);
        frame.setLayout(new BorderLayout());

        // --- MAP PANEL ---
        mapPanel = new JPanel(new GridLayout(mapSize.y, mapSize.x));
        mapPanel.setBackground(Config.BG_COLOR);
        gridLabels = new JLabel[mapSize.y][mapSize.x];

        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                JLabel cell = new JLabel("", SwingConstants.CENTER);
                cell.setOpaque(true);
                cell.setBackground(Config.GRID_BG_COLOR);
                cell.setBorder(new LineBorder(Config.BORDER_COLOR, Config.BORDER_THICKNESS));
                cell.setForeground(Config.TEXT_COLOR);
                cell.setFont(new Font("Monospaced", Font.BOLD, Config.BLOCK_FONT_SIZE));

                final int cx = x;
                final int cy = y;
                cell.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        // TODO: Kliknięcie i otwieranie okna dialogowego do dodawania obiektów w przyszłości
                        System.out.println("Kliknięto koordynaty gry x: " + cx + ", y: " + cy);
                    }
                });

                gridLabels[y][x] = cell;
                mapPanel.add(cell);
            }
        }

        // --- STATUS PANEL ---
        statusPanel = new JPanel();
        statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.Y_AXIS));

        // Ustalenie stałej szerokości na bazie % i STATUS_WIDTH
        int statusWidth = (Config.WINDOW_WIDTH * Config.STATUS_WIDTH) / 100;
        statusPanel.setPreferredSize(new Dimension(statusWidth, Config.WINDOW_HEIGHT));
        statusPanel.setBorder(new LineBorder(Color.BLACK, 2));

        // Przyciski (B1 i B2)
        JPanel buttonsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        btnSave = new JButton("Save / B1");
        btnLoad = new JButton("Load / B2");
        buttonsPanel.add(btnSave);
        buttonsPanel.add(btnLoad);

        // Informacje / Tekst
        lblNextAction = new JLabel("next action: ");
        lblCooldown = new JLabel("ability cooldown: ");
        lblEntities = new JLabel("entities: ");

        // Pole logu (lista akcji)
        logArea = new JTextArea();
        logArea.setEditable(false);
        logArea.setFocusable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);

        lblNextAction.setAlignmentX(Component.CENTER_ALIGNMENT);
        lblCooldown.setAlignmentX(Component.CENTER_ALIGNMENT);
        lblEntities.setAlignmentX(Component.CENTER_ALIGNMENT);

        statusPanel.add(buttonsPanel);
        statusPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        statusPanel.add(lblNextAction);
        statusPanel.add(lblCooldown);
        statusPanel.add(lblEntities);
        statusPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        statusPanel.add(new JLabel("log:"));
        statusPanel.add(scrollPane);

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
}
