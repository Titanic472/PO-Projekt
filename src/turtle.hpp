#include "animal.hpp"

class Turtle : public Animal{
    public:

    Turtle(Vector2 position, int power = 2, int age = 0) : Animal(power, 1, position, "Turtle", "Turtle", age, true) {}


    Turtle(map<string, string> properties) : Turtle(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"])) {}


    void collision(Entity *other_entity) override;


    private:

    Entity* clone(Vector2 position) override;


    void move(Vector2 move_direction);
};
