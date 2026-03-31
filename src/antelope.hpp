#pragma once

#include "animal.hpp"

class Antelope : public Animal{
    public:

    Antelope(Vector2 position) : Animal(4, 4, position, "Antelope"){}


    void collision(Entity *other_entity) override;


    private:

    void move(Vector2 move_direction) override;


    Entity* clone(Vector2 position) override;
};
