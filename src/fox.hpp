#pragma once

#include "animal.hpp"

class Fox : public Animal{
    public:

    Fox(Vector2 position) : Animal(3, 7, position, "Fox"){}


    void collision(Entity *other_entity) override;


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
