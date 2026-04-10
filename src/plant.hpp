#pragma once

#include "entity.hpp"
#include "config.hpp"

class Plant : public Entity{
    public:

    Plant(int power, Vector2 position, string name, string datatype) : Entity(power, 0, position, name, datatype){}


    ~Plant(){}


    virtual void action() override;
};
