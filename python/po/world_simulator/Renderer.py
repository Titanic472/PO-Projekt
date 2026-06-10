import tkinter as tk
from tkinter import simpledialog
import collections

from po.world_simulator.Config import Config
from po.world_simulator.Vector2 import Vector2
import po.world_simulator.World as world_module
from po.world_simulator.entities.animals.Human import Human

# Helper function to convert custom Color class to tkinter hex colors
def get_hex_color(color):
    return f"#{color.r:02x}{color.g:02x}{color.b:02x}"

class Renderer:
    def __init__(self, mapSize):
        self.frame = tk.Tk()
        self.frame.title("World Simulator")
        self.frame.geometry(f"{Config.WINDOW_WIDTH}x{Config.WINDOW_HEIGHT}")
        self.frame.protocol("WM_DELETE_WINDOW", self.on_close)

        self.logMessages = collections.deque()
        self.mapSize = mapSize

        # --- GLOBAL KEY LISTENER ---
        self.frame.bind("<KeyPress>", self.dispatchKeyEvent)

        # main container
        self.main_container = tk.Frame(self.frame)
        self.main_container.pack(fill=tk.BOTH, expand=True)

        # --- MAP PANEL ---
        self.mapPanel = tk.Frame(self.main_container, bg=get_hex_color(Config.BG_COLOR))
        self.mapPanel.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.gridLabels = [[None for _ in range(mapSize.x)] for _ in range(mapSize.y)]

        # Tkinter grid configuration to make cells expand equally
        for y in range(mapSize.y):
            self.mapPanel.rowconfigure(y, weight=1)
        for x in range(mapSize.x):
            self.mapPanel.columnconfigure(x, weight=1)

        for y in range(mapSize.y):
            for x in range(mapSize.x):
                # Using frame for different border thickness
                border_frame = tk.Frame(self.mapPanel, bg=get_hex_color(Config.BORDER_COLOR), bd=Config.BORDER_THICKNESS)
                border_frame.grid(row=y, column=x, sticky="nsew")

                cell = tk.Label(border_frame, text="", bg=get_hex_color(Config.DEFAULT_GRID_BG_COLOR),
                                fg=get_hex_color(Config.TEXT_COLOR), font=("Courier", Config.BLOCK_FONT_SIZE, "bold"))
                cell.pack(fill=tk.BOTH, expand=True)

                cell.bind("<Button-1>", lambda e, cx=x, cy=y: self.showAddEntityDialog(Vector2(cx, cy)))

                self.gridLabels[y][x] = cell

        # --- STATUS PANEL ---
        statusWidth = int((Config.WINDOW_WIDTH * Config.STATUS_WIDTH) / 100)
        self.statusPanel = tk.Frame(self.main_container, width=statusWidth, highlightbackground="black", highlightthickness=2)
        self.statusPanel.pack(side=tk.RIGHT, fill=tk.Y)
        self.statusPanel.pack_propagate(False) # Prevent shrinking

        # upper status panel
        topStatusPanel = tk.Frame(self.statusPanel)
        topStatusPanel.pack(side=tk.TOP, fill=tk.X, pady=10)

        # buttons
        buttonsPanel = tk.Frame(topStatusPanel)
        buttonsPanel.pack(pady=5)

        # Buttons, disabling strict focus so key events still propagate to root
        self.btnSave = tk.Button(buttonsPanel, text="Save", takefocus=False)
        self.btnSave.pack(side=tk.LEFT, padx=5)
        self.btnLoad = tk.Button(buttonsPanel, text="Load", takefocus=False)
        self.btnLoad.pack(side=tk.LEFT, padx=5)

        # info
        self.lblNextAction = tk.Label(topStatusPanel, text="next action: ")
        self.lblNextAction.pack()
        self.lblCooldown = tk.Label(topStatusPanel, text="ability cooldown: ")
        self.lblCooldown.pack()
        self.lblEntities = tk.Label(topStatusPanel, text="entities: ")
        self.lblEntities.pack()

        # log area
        mainLogPanel = tk.Frame(self.statusPanel)
        mainLogPanel.pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)

        logTitle = tk.Label(mainLogPanel, text="log:")
        logTitle.pack(side=tk.TOP)

        self.logArea = tk.Text(mainLogPanel, state=tk.DISABLED, takefocus=False)
        scrollPane = tk.Scrollbar(mainLogPanel, command=self.logArea.yview)
        self.logArea.configure(yscrollcommand=scrollPane.set)

        self.logArea.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollPane.pack(side=tk.RIGHT, fill=tk.Y)

        # Keep the window responsive for setup but wait for manual update calls during simulation
        self.frame.update()


    def on_close(self):
        # Quit cleanly when clicking X
        im = world_module.World.getInputManager()
        if im is not None:
            im.pushInput(Config.QUIT) # Config.QUIT


    def dispatchKeyEvent(self, e):
        im = world_module.World.getInputManager()
        if im is None:
            return "break"

        keysym = e.keysym.upper()
        # Map tkinter keysyms to our input setup
        
        im.pushInput(keysym.lower())

        return "break"


    def bind(self, buttonName, action):
        if buttonName.lower() == "save" or buttonName.lower() == "b1":
            self.btnSave.config(command=action)
        elif buttonName.lower() == "load" or buttonName.lower() == "b2":
            self.btnLoad.config(command=action)


    def renderMap(self):
        self.frame.update()


    def renderInfoWindow(self):
        button_text = "next action: "
        button_text += self.convertInputToText(world_module.World.getInputManager().getLastInput())
        self.lblNextAction.config(text=button_text)

        human = Human.getInstance()

        if human is not None:
            self.lblCooldown.config(text=f"ability cooldown: {human.getAbilityCooldown()}")
        else:
            self.lblCooldown.config(text="Human died :(")

        self.lblEntities.config(text=f"entities: {world_module.World.getEntityCount()}")

        sb = ""
        for msg in self.logMessages:
            sb += msg + "\n"

        self.logArea.config(state=tk.NORMAL)
        self.logArea.delete(1.0, tk.END)
        self.logArea.insert(tk.END, sb)
        self.logArea.config(state=tk.DISABLED)
        # self.logArea.yview(tk.END) # autoscroll optionally

        self.frame.update()


    def drawCharAt(self, position, text):
        if 0 <= position.y < len(self.gridLabels) and 0 <= position.x < len(self.gridLabels[0]):
            self.gridLabels[position.y][position.x].config(text=str(text))


    def drawMap(self, mapSize):
        for y in range(mapSize.y):
            for x in range(mapSize.x):
                self.gridLabels[y][x].config(text=" ")


    def addToLog(self, text):
        if len(self.logMessages) <= Config.MAX_LOG_MESSAGES:
            self.logMessages.append(text)


    def drawInfoWindow(self):
        pass


    def clearLog(self):
        self.logMessages.clear()
        self.logArea.config(state=tk.NORMAL)
        self.logArea.delete(1.0, tk.END)
        self.logArea.config(state=tk.DISABLED)


    def dispose(self):
        self.frame.destroy()


    def convertInputToText(self, input_val):
        if input_val == Config.LEFT:
            return "LEFT"
        elif input_val == Config.RIGHT:
            return "RIGHT"
        elif input_val == Config.UP:
            return "UP"
        elif input_val == Config.DOWN:
            return "DOWN"
        elif input_val == Config.ABILITY:
            return "ABILITY"
        return ""


    def showAddEntityDialog(self, position):
        game_map = world_module.World.getMap()
        if game_map is not None and game_map.isTileOccupied(position):
            return

        entities_list = [
            "Wolf", "Sheep", "Fox", "Turtle", "Antelope",
            "Grass", "Milkweed", "Guarana", "Wolfberries", "SosnowskiHogweed", "CyberSheep"
        ]

        # Using custom dialog with OptionMenu to select entity
        dialog = tk.Toplevel(self.frame)
        dialog.title("Add Entity")
        dialog.transient(self.frame)
        dialog.grab_set()

        tk.Label(dialog, text=f"Position: ({position.x}, {position.y})\nChoose entity to add:").pack(pady=10, padx=20)

        selected_entity = tk.StringVar(dialog)
        selected_entity.set(entities_list[0])

        tk.OptionMenu(dialog, selected_entity, *entities_list).pack(pady=5, padx=20)

        result = [None]

        def on_ok():
            result[0] = selected_entity.get()
            dialog.destroy()

        def on_cancel():
            dialog.destroy()

        btn_frame = tk.Frame(dialog)
        btn_frame.pack(pady=10)
        tk.Button(btn_frame, text="OK", command=on_ok, width=10).pack(side=tk.LEFT, padx=5)
        tk.Button(btn_frame, text="Cancel", command=on_cancel, width=10).pack(side=tk.LEFT, padx=5)

        # Center the dialog relative to the main window
        dialog.update_idletasks()
        x = self.frame.winfo_x() + (self.frame.winfo_width() // 2) - (dialog.winfo_width() // 2)
        y = self.frame.winfo_y() + (self.frame.winfo_height() // 2) - (dialog.winfo_height() // 2)
        dialog.geometry(f"+{x}+{y}")

        self.frame.wait_window(dialog)
        selected = result[0]

        # Validate selected string
        if selected and selected in entities_list:
            newEntity = None
            try:
                # Same strategy as World string loader
                if selected in ["Wolf", "Sheep", "Fox", "Turtle", "Antelope", "Human", "CyberSheep"]:
                    import importlib
                    module = importlib.import_module(f"po.world_simulator.entities.animals.{selected}")
                    clazz = getattr(module, selected)
                else:
                    import importlib
                    module = importlib.import_module(f"po.world_simulator.entities.plants.{selected}")
                    clazz = getattr(module, selected)

                newEntity = clazz(position)
            except Exception as e:
                print("Failed to create entity directly from dialog:", e)

            if newEntity is not None:
                world_module.World.getInstance().addNewEntity(newEntity)
                self.addToLog(f"Added {selected} at ({position.x}, {position.y})")
                world_module.World.getInstance().forceDrawAll()
