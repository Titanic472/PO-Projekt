#include "animal.hpp"

class Sheep : public Animal{
    public:

    Sheep(Vector2 position, int power = 4, int age = 0) : Animal(power, 4, position, "Sheep", "Sheep", age, true){}


    Sheep(map<string, string> properties) : Sheep(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"])) {}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
