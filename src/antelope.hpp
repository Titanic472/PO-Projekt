#pragma once

#include "animal.hpp"

class Antelope : public Animal{
    public:

    Antelope(Vector2 position, int power = 4, int age = 0) : Animal(power, 4, position, "Antelope", "Antelope", age){}


    Antelope(map<string, string> properties) : Antelope(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"])){}


    void collision(Entity *other_entity) override;


    private:

    void move(Vector2 move_direction) override;


    Entity* clone(Vector2 position) override;
};
