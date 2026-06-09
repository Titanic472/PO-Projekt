import os
from .Vector2 import Vector2
from .DataFormat import DataFormat
import po.world_simulator.World as world_module

class SaveParser:
    def __init__(self):
        self.reader = None
        self.writer = None
        self.fileName = ""


    def createFile(self, worldSize):
        self.fileName = "saves/" + str(worldSize) + ".save"
        try:
            os.makedirs(os.path.dirname(self.fileName), exist_ok=True) 
            self.writer = open(self.fileName, "w")
        except IOError as e:
            print(e)


    def addEntry(self, key, type_str, value):
        try:
            self.writer.write(f"{key}:{type_str}:{value};\n")
        except IOError as e:
            print(e)


    def addStringEntry(self, value):
        try:
            if value.endswith(str(DataFormat.CATEGORY_END_HEADER)):
                self.writer.write(value + "\n")
            else:
                self.writer.write(value + DataFormat.CATEGORY_END_HEADER + "\n")
        except IOError as e:
            print(e)


    def startCategory(self, categoryName):
        try:
            self.writer.write(f"{categoryName}:{DataFormat.CATEGORY_START_HEADER}\n")
        except IOError as e:
            print(e)


    def endCategory(self):
        try:
            self.writer.write(f"{DataFormat.CATEGORY_END_HEADER}\n")
        except IOError as e:
            print(e)


    def stringifyEntry(self, key, type_or_char, value=None):
        if value is None:
            return f"{key}{DataFormat.VALUE_SEPARATOR}{type_or_char}\n"
        return f"{key}{DataFormat.VALUE_SEPARATOR}{type_or_char}{DataFormat.VALUE_SEPARATOR}{value}{DataFormat.ENTRY_SEPARATOR}\n"


    def closeFile(self):
        try:
            if self.writer is not None:
                self.writer.close()
            if self.reader is not None:
                self.reader.close()
        except IOError as e:
            print(e)


    def fileExists(self, fileName):
        return os.path.exists(fileName)


    def loadFile(self, worldSize):
        self.fileName = "saves/" + str(worldSize) + ".save"
        if not self.fileExists(self.fileName):
            return False

        try:
            self.reader = open(self.fileName, "r")
            return True
        except IOError as e:
            print(e)
            return False


    def loadEntry(self, key):
        try:
            for line in self.reader:
                line = line.strip('\n')
                if not line:
                    continue

                parts = self.parseLine(line)
                if not parts or len(parts) == 0:
                    continue

                entryKey = parts[0]
                if entryKey == key:
                    if len(parts) < 2:
                        continue

                    type_str = parts[1]
                    if type_str and type_str[0] == DataFormat.CATEGORY_START_HEADER:
                        world_module.World.getRenderer().addToLog("EXPECTED ENTRY BUT CATEGORY START FOUND: " + key)
                        return None
                    if len(parts) < 3:
                        continue
                    value = parts[2]
                    return self.loadField(type_str, value)

            world_module.World.getRenderer().addToLog("ENTRY: \"" + key + "\" NOT FOUND IN FILE")
        except IOError as e:
            print(e)
        return None


    def jumpToCategory(self, categoryName):
        try:
            for line in self.reader:
                line = line.strip('\n')
                if not line:
                    continue

                parts = self.parseLine(line)
                if not parts or len(parts) == 0:
                    continue

                entryKey = parts[0]
                if entryKey == categoryName:
                    type_str = parts[1] if len(parts) > 1 else ""
                    if not type_str or type_str[0] != DataFormat.CATEGORY_START_HEADER:
                        world_module.World.getRenderer().addToLog("EXPECTED CATEGORY START BUT ENTRY FOUND: " + categoryName)
                        return False
                    return True
        except IOError as e:
            print(e)
        return False


    def loadEntryMultiline(self, entryData):
        try:
            line = self.reader.readline()
            if not line or not line.strip() or line[0] == DataFormat.CATEGORY_END_HEADER:
                return False
            else:
                line = line.strip('\n')
                parts = self.parseLine(line)
                if len(parts) > 0:
                    entryData["type"] = parts[0]

                rest = parts[1] if len(parts) > 1 else ""
                if not rest or rest[0] != DataFormat.CATEGORY_START_HEADER:
                    return False

            while True:
                line = self.reader.readline()
                if not line:
                    break
                if not line.strip() or line[0] == DataFormat.CATEGORY_END_HEADER:
                    break
                line = line.strip('\n')
                parts = self.parseLine(line)
                if len(parts) >= 3:
                    key = parts[0]
                    # skip type (parts[1]) for multiline loading
                    value = parts[2]
                    entryData[key] = value
            return True
        except IOError as e:
            print(e)
        return False


    def parseLine(self, line):
        line = line.replace(DataFormat.ENTRY_SEPARATOR, "")
        return line.split(DataFormat.VALUE_SEPARATOR)


    def loadField(self, type_str, value):
        if type_str == DataFormat.TYPE_INT:
            return int(value)
        elif type_str == DataFormat.TYPE_FLOAT:
            return float(value)
        elif type_str == DataFormat.TYPE_STRING:
            if value.startswith('"') and value.endswith('"'):
                return value[1:-1]
            return value
        elif type_str == DataFormat.TYPE_VECTOR2:
            return Vector2(value)
        elif type_str == DataFormat.TYPE_BOOLEAN:
            return value.lower() == "true"
        else:
            world_module.World.getRenderer().addToLog("UNKNOWN TYPE: " + type_str)
            return None
