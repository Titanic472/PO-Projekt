package po.world_simulator;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class RendererHex extends Renderer {

    private HexPanel hexMapPanel;
    private char[][] hexGrid;

    public RendererHex(Vector2 mapSize) {
        super(mapSize);

        // Usuwamy stary prostokątny panel mapy utworzony w super()
        frame.remove(mapPanel);

        // Inicjalizujemy własną siatkę znaków
        hexGrid = new char[mapSize.y][mapSize.x];
        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                hexGrid[y][x] = ' ';
            }
        }

        hexMapPanel = new HexPanel(mapSize);
        frame.add(hexMapPanel, BorderLayout.CENTER);

        // Odświeżamy ramkę po zmianach panelu
        frame.revalidate();
        frame.repaint();
    }

    @Override
    public void drawCharAt(Vector2 position, char text) {
        if (position.y >= 0 && position.y < hexGrid.length &&
            position.x >= 0 && position.x < hexGrid[0].length) {
            hexGrid[position.y][position.x] = text;
        }
    }

    @Override
    public void drawMap(Vector2 mapSize) {
        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                hexGrid[y][x] = ' ';
            }
        }
    }

    @Override
    public void renderMap() {
        // Swing zawoła paintComponent dla panelu heksagonalnego
        hexMapPanel.repaint();
    }

    // Niestandardowy panel rysujący sześciokąty
    private class HexPanel extends JPanel {
        private Vector2 mapSize;
        private Polygon[][] hexagons;

        public HexPanel(Vector2 mapSize) {
            this.mapSize = mapSize;
            this.hexagons = new Polygon[mapSize.y][mapSize.x];
            setBackground(Config.BG_COLOR);

            // Obsługa kliknięć na heksagony
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    for (int y = 0; y < mapSize.y; y++) {
                        for (int x = 0; x < mapSize.x; x++) {
                            if (hexagons[y][x] != null && hexagons[y][x].contains(e.getPoint())) {
                                showAddEntityDialog(new Vector2(x, y));
                            }
                        }
                    }
                }
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D g2d = (Graphics2D) g;

            // Antialiasing, żeby krawędzie były gładkie
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int width = getWidth();
            int height = getHeight();

            if (width <= 0 || height <= 0) return;

            // Obliczenia proporcji dla sześciokąta spiczastego na górze (pointy-topped)
            double cols = mapSize.x + 0.5;
            double rows = (mapSize.y * 0.75) + 0.25;

            double maxW = width / cols;
            double maxH = height / rows;

            // Zależność: widthHex = sqrt(3) * size, heightHex = 2 * size
            double sizeW = maxW / Math.sqrt(3);
            double sizeH = maxH / 2.0;

            // Wybieramy mniejszy rozmiar i dopasowujemy padding (95%) by nie dotykał krawędzi
            double size = Math.min(sizeW, sizeH) * 0.95;

            double hexWidth = Math.sqrt(3) * size;
            double hexHeight = 2.0 * size;

            // Wyśrodkowanie siatki wewnątrz dostępnego panelu
            double offsetX = (width - ((mapSize.x + 0.5) * hexWidth)) / 2.0;
            double offsetY = (height - ((mapSize.y * 0.75 + 0.25) * hexHeight)) / 2.0;

            // Dostosowanie wcięć dla obramowań heksagonów (by pismo wpisywało się wewnątrz)
            int fontSize = Math.max(10, (int)(size * 0.8));
            g2d.setFont(new Font("Monospaced", Font.BOLD, fontSize));
            FontMetrics fm = g2d.getFontMetrics();

            for (int y = 0; y < mapSize.y; y++) {
                for (int x = 0; x < mapSize.x; x++) {
                    // Wzorzec "odd-r": nieparzyste rzędy są przesunięte w prawo
                    double cx = offsetX + x * hexWidth + (y % 2 != 0 ? hexWidth / 2.0 : 0) + hexWidth / 2.0;
                    double cy = offsetY + y * (hexHeight * 0.75) + hexHeight / 2.0;

                    Polygon hex = createHexagon(cx, cy, size);
                    hexagons[y][x] = hex;

                    // Tło komórki
                    g2d.setColor(Config.DEFAULT_GRID_BG_COLOR);
                    g2d.fillPolygon(hex);

                    // Obramowanie
                    g2d.setColor(Config.BORDER_COLOR);
                    g2d.setStroke(new BasicStroke(Config.BORDER_THICKNESS));
                    g2d.drawPolygon(hex);

                    // Rysowanie zjawisk na hexie (znak obiektu lub ' ')
                    char c = hexGrid[y][x];
                    if (c != ' ' && c != '\0') {
                        g2d.setColor(Config.TEXT_COLOR);
                        String s = String.valueOf(c);
                        int textW = fm.stringWidth(s);
                        int textH = fm.getAscent() - fm.getDescent();
                        g2d.drawString(s, (int)(cx - textW / 2.0), (int)(cy + textH / 2.0));
                    }
                }
            }
        }

        private Polygon createHexagon(double x, double y, double size) {
            Polygon polygon = new Polygon();
            for (int i = 0; i < 6; i++) {
                // Kąt startowy -30 stopni dla sześciokąta "spiczastego" (pointy-topped)
                double angle_deg = 60 * i - 30;
                double angle_rad = Math.PI / 180 * angle_deg;
                int px = (int) Math.round(x + size * Math.cos(angle_rad));
                int py = (int) Math.round(y + size * Math.sin(angle_rad));
                polygon.addPoint(px, py);
            }
            return polygon;
        }
    }
}