package po.world_simulator;

import java.io.*;
import java.util.Map;

public class SaveParser {
    private BufferedReader reader;
    private BufferedWriter writer;
    private String fileName;

    public void createFile(Vector2 worldSize) {
        fileName = "saves/" + worldSize.toString() + ".save";
        try {
            File f = new File(fileName);
            f.getParentFile().mkdirs();
            writer = new BufferedWriter(new FileWriter(f, false));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addEntry(String key, String type, String value) {
        try {
            writer.write(key + ":" + type + ":" + value + ";\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addStringEntry(String value) {
        try {
            if (value.endsWith(String.valueOf(DataFormat.CATEGORY_END_HEADER))) {
                writer.write(value + "\n");
            } else {
                writer.write(value + DataFormat.CATEGORY_END_HEADER + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void startCategory(String categoryName) {
        try {
            writer.write(categoryName + ":" + DataFormat.CATEGORY_START_HEADER + "\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void endCategory() {
        try {
            writer.write(DataFormat.CATEGORY_END_HEADER + "\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String stringifyEntry(String key, String type, String value) {
        return key + DataFormat.VALUE_SEPARATOR + type + DataFormat.VALUE_SEPARATOR + value + DataFormat.ENTRY_SEPARATOR + "\n";
    }

    public String stringifyEntry(String key, char type) {
        return key + DataFormat.VALUE_SEPARATOR + type + "\n";
    }

    public void closeFile() {
        try {
            if (writer != null)
                writer.close();
            if (reader != null)
                reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private boolean fileExists(String fileName) {
        return new File(fileName).exists();
    }

    public boolean loadFile(Vector2 worldSize) {
        this.fileName = "saves/" + worldSize.toString() + ".save";
        if (!fileExists(fileName)) {
            return false;
        }

        try {
            reader = new BufferedReader(new FileReader(fileName));
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public Object loadEntry(String key) {
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.isEmpty())
                    continue;

                String[] parts = parseLine(line);
                if (parts == null || parts.length == 0)
                    continue;

                String entryKey = parts[0];
                if (entryKey.equals(key)) {
                    if (parts.length < 2)
                        continue;

                    String type = parts[1];
                    if (type.charAt(0) == DataFormat.CATEGORY_START_HEADER) {
                        World.getRenderer().addToLog("EXPECTED ENTRY BUT CATEGORY START FOUND: " + key);
                        return null;
                    }
                    if (parts.length < 3)
                        continue;
                    String value = parts[2];
                    return loadField(type, value);
                }
            }
            World.getRenderer().addToLog("ENTRY: \"" + key + "\" NOT FOUND IN FILE");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean jumpToCategory(String categoryName) {
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.isEmpty())
                    continue;

                String[] parts = parseLine(line);
                if (parts == null || parts.length == 0)
                    continue;

                String entryKey = parts[0];
                if (entryKey.equals(categoryName)) {
                    String type = parts.length > 1 ? parts[1] : "";
                    if (type.isEmpty() || type.charAt(0) != DataFormat.CATEGORY_START_HEADER) {
                        World.getRenderer().addToLog("EXPECTED CATEGORY START BUT ENTRY FOUND: " + categoryName);
                        return false;
                    }
                    return true;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean loadEntryMultiline(Map<String, String> entryData) {
        try {
            String line = reader.readLine();
            if (line == null || line.trim().isEmpty() || line.charAt(0) == DataFormat.CATEGORY_END_HEADER) {
                return false;
            }
            else {
                String[] parts = parseLine(line);
                if (parts.length > 0) {
                    entryData.put("type", parts[0]);
                }

                String rest = parts.length > 1 ? parts[1] : "";
                if (rest.isEmpty() || rest.charAt(0) != DataFormat.CATEGORY_START_HEADER) {
                    return false;
                }
            }

            while ((line = reader.readLine()) != null && !line.trim().isEmpty() && line.charAt(0) != DataFormat.CATEGORY_END_HEADER) {
                String[] parts = parseLine(line);
                if (parts.length >= 3) {
                    String key = parts[0];
                    // skip type (parts[1]) for multilenie loading
                    String value = parts[2];
                    entryData.put(key, value);
                }
            }
            return true;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    private String[] parseLine(String line) {
        line = line.replace(DataFormat.ENTRY_SEPARATOR, "");
        return line.split(DataFormat.VALUE_SEPARATOR);
    }

    private Object loadField(String type, String value) {
        switch (type) {
            case DataFormat.TYPE_INT:
                return Integer.parseInt(value);
            case DataFormat.TYPE_FLOAT:
                return Float.parseFloat(value);
            case DataFormat.TYPE_STRING:
                if (value.startsWith("\"") && value.endsWith("\"")) {
                    return value.substring(1, value.length() - 1);
                }
                return value;
            case DataFormat.TYPE_VECTOR2:
                return new Vector2(value);
            case DataFormat.TYPE_BOOLEAN:
                return Boolean.parseBoolean(value);
            default:
                World.getRenderer().addToLog("UNKNOWN TYPE: " + type);
                return null;
        }
    }
}
