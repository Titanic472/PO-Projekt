package po.world_simulator;

import java.util.Scanner;

public class InputManager {
    private int lastInput = 0;
    private boolean newTurnPressed = false;
    private Scanner scanner;

    public InputManager() {
        scanner = new Scanner(System.in);
    }

    public void readNextInput() {
        newTurnPressed = false;
        // [AI] Blokujące wczytywanie bajtów dla zachowania zgodności z buforowaniem strzałek znaków sterujących zdefiniowanych w C++
        try {
            int input = System.in.read();
            if (input == 27) {
                int next1 = System.in.read();
                if (next1 == 79 || next1 == 91) {
                    int next2 = System.in.read();
                    lastInput = next2 + 255;
                    return;
                }
            }

            if (input == Config.NEW_TURN) {
                newTurnPressed = true;
                return;
            }
            lastInput = input;
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public int getLastInput() {
        return this.lastInput;
    }

    public void clearLastInput() {
        this.lastInput = 0;
    }

    public boolean isQuitPressed() {
        return lastInput == Config.QUIT;
    }

    public boolean isNewTurnPressed() {
        return newTurnPressed;
    }
}
