#pragma once

#include "animal.hpp"

class Fox : public Animal{
    public:

    Fox(Vector2 position, int power = 3, int age = 0) : Animal(power, 7, position, "Fox", "Fox", age, true){}


    Fox(map<string, string> properties) : Fox(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"])){}


    void collision(Entity *other_entity) override;


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
