#include "plant.hpp"

class Milkweed : public Plant{
    public:

    Milkweed(Vector2 position, int age = 0) : Plant(0, position, "milkweed", "Milkweed", age) {}


    Milkweed(map<string, string> properties) : Milkweed(Vector2(properties["position"]), stoi(properties["age"])) {}


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
