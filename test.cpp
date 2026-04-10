// C++ Program to illustrate how we can serialize and
// deserialize an object
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Serializable {
private:
    string name;
    int age;

public:
    Serializable(){};
    // Constructor to initialize the data members
    Serializable(const string& name, int age)
        : name(name)
        , age(age)
    {
    }

    // Getter methods for the class
    string getName() const { return name; }
    int getAge() const { return age; }

    //  Function for Serialization
    void serialize(ofstream& file) const
    {
        // Write the length of the string
        size_t len = name.size();
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        // Write the actual string characters
        file.write(name.c_str(), len);
        // Write the age
        file.write(reinterpret_cast<const char*>(&age), sizeof(age));
    }

    //  Function for Deserialization
    static Serializable deserialize(ifstream& file)
    {
        Serializable obj;
        size_t len;
        // Read string length
        if (file.read(reinterpret_cast<char*>(&len), sizeof(len))) {
            // Read string characters
            char* buffer = new char[len + 1];
            file.read(buffer, len);
            buffer[len] = '\0';
            obj.name = buffer;
            delete[] buffer;

            // Read age
            file.read(reinterpret_cast<char*>(&obj.age), sizeof(obj.age));
        }
        return obj;
    }
};

int main()
{
    // Serialize multiple objects
    ofstream outFile("data.bin", ios::binary);
    if(outFile.is_open()) {
        Serializable obj1("Alice", 25);
        Serializable obj2("Bob", 30);
        obj1.serialize(outFile);
        obj2.serialize(outFile);
        outFile.close();
        cout << "Objects serialized successfully.\n";
    }

    // Deserialize multiple objects
    ifstream inFile("data.bin", ios::binary);
    if(inFile.is_open()) {
        cout << "Deserialized Objects:\n";
        while(inFile.peek() != EOF) {
            Serializable restored = Serializable::deserialize(inFile);
            if(inFile) {
                cout << "Name: " << restored.getName() << ", Age: " << restored.getAge() << endl;
            }
        }
        inFile.close();
    }

    return 0;
}