#pragma once

#include "entity.hpp"
#include "config.hpp"

class Plant : public Entity{
    public:

    Plant(int power, Vector2 position, string name) : Entity(power, 0, position, name){}


    ~Plant(){}


    virtual void action() override;
};
