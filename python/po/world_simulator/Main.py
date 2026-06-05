import sys
from po.world_simulator.World import World
from po.world_simulator.Config import Config

class Main:
    @staticmethod
    def main():
        world = World(Config.HEX_ENABLED)

        # mainloop
        while True:
            world.drawWorld()
            if not world.performTurn():
                break

        world.dispose()
        sys.exit(0)

if __name__ == "__main__":
    Main.main()