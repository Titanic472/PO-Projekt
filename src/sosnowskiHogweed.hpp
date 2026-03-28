#pragma once

#include "plant.hpp"

class SosnowskiHogweed : public Plant{
    public:

    SosnowskiHogweed(Vector2 position) : Plant(10, position, "sosnowski hogweed"){}


    void collision(Entity *other_entity) override;


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
