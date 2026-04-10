#pragma once

#include "animal.hpp"
#include "config.hpp"

class Human : public Animal{
    int ability_cooldown;

    public:

    Human(Vector2 position, int ability_cooldown = 0);

    ~Human();

    void action() override;


    void kill() override;


    void collision(Entity *other_entity) override;


    int get_ability_cooldown() const;


    string save_as_string() const override;


    private:

    Entity* clone(Vector2 position) override;
};