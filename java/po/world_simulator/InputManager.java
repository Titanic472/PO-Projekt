package po.world_simulator;

import java.util.concurrent.LinkedBlockingQueue;

public class InputManager {
    private int lastInput = 0;
    private boolean newTurnPressed = false;
    private LinkedBlockingQueue<Integer> inputQueue = new LinkedBlockingQueue<>();

    public InputManager() {
    }

    public void pushInput(int input) {
        inputQueue.offer(input);
    }

    public void readNextInput() {
        newTurnPressed = false;
        try {
            // [AI] Blokowanie głównego wątku pętli aż GUI dorzuci klawisz do kolejki
            int input = inputQueue.take();

            if (input == Config.NEW_TURN) {
                newTurnPressed = true;
                return;
            }
            lastInput = input;
        } catch (InterruptedException e) {
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
