#pragma once

#include "entity.hpp"

class Animal : public Entity{
    bool can_kill;


    public:

    Animal(int power, int initiative, Vector2 position, string name, string datatype, int age = 0, bool can_kill = false)
        : Entity(power, initiative, position, name, datatype, age), can_kill(can_kill){};


    virtual void action() override;


    virtual void collision(Entity *other_entity) override;


    bool is_predator();


    protected:

    virtual void move(Vector2 move_direction);


    bool run_away();
};
