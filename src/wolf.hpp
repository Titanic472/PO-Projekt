#include "animal.hpp"

class Wolf : public Animal{
    public:

    Wolf(Vector2 position, int power = 9, int age = 0) : Animal(power, 5, position, "Wolf", "Wolf", age, true){}


    Wolf(map<string, string> properties) : Wolf(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"])) {}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
