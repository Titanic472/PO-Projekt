#pragma once

#include "entity.hpp"

class Animal : public Entity{
    public:

    Animal(int power, int initiative, Vector2 position, string name):
        Entity(power, initiative, position, name){}


    virtual void action() override;


    protected:

    virtual void move(Vector2 move_direction);
};
