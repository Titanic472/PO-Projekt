#pragma once

#include "plant.hpp"

class Wolfberries : public Plant{
    public:

    Wolfberries(Vector2 position, int age = 0) : Plant(99, position, "wolfberries", "Wolfberries", age){}


    Wolfberries(map<string, string> properties) : Wolfberries(Vector2(properties["position"]), stoi(properties["age"])) {}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
