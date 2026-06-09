import queue
from .Config import Config

class InputManager:
    def __init__(self):
        self.lastInput = 0
        self.newTurnPressed = False
        self.inputQueue = queue.Queue()


    def pushInput(self, input_val):
        self.inputQueue.put(input_val)


    def readNextInput(self):
        self.newTurnPressed = False

        if self.inputQueue.empty():
            return

        input_val = self.inputQueue.get(block=False)
        
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
