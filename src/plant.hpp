#pragma once

#include "entity.hpp"

class Plant : public Entity{
    protected:

    public:

    Plant(int power, Vector2 position, string name) : Entity(power, 0, position, name){}


    virtual void action() override;
};
