import queue
from .Config import Config

class InputManager:
    def __init__(self):
        self.lastInput = 0
        self.newTurnPressed = False
        self.inputQueue = queue.Queue() # [AI] Replaced LinkedBlockingQueue with queue.Queue

    def pushInput(self, input_val):
        self.inputQueue.put(input_val) # [AI] replaced offer with put

    def readNextInput(self):
        self.newTurnPressed = False
        # [AI] Removed try-catch since queue.get is thread-safe and blocking
        input_val = self.inputQueue.get()

        if input_val == Config.NEW_TURN:
            self.newTurnPressed = True
            return
        self.lastInput = input_val

    def getLastInput(self):
        return self.lastInput

    def clearLastInput(self):
        self.lastInput = 0

    def isQuitPressed(self):
        return self.lastInput == Config.QUIT

    def isNewTurnPressed(self):
        return self.newTurnPressed
