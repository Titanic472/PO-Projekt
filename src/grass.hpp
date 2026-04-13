#include "plant.hpp"

class Grass : public Plant{
    public:

    Grass(Vector2 position, int age = 0) : Plant(0, position, "trawa:)", "Grass", age) {}


    Grass(map<string, string> properties) : Grass(Vector2(properties["position"]), stoi(properties["age"])) {}


    private:

    Entity* clone(Vector2 position) override;
};
