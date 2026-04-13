#pragma once

#include "plant.hpp"

class SosnowskiHogweed : public Plant{
    public:

    SosnowskiHogweed(Vector2 position, int age = 0) : Plant(10, position, "sosnowski hogweed", "SosnowskiHogweed", age) {}


    SosnowskiHogweed(map<string, string> properties) : SosnowskiHogweed(Vector2(properties["position"]), stoi(properties["age"])) {}


    void collision(Entity *other_entity) override;


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
