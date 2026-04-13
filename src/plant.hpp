#pragma once

#include "entity.hpp"
#include "config.hpp"

class Plant : public Entity{
    public:

    Plant(int power, Vector2 position, string name, string datatype, int age = 0) : Entity(power, 0, position, name, datatype, age){}


    ~Plant(){}


    virtual void action() override;
};
