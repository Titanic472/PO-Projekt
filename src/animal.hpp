#pragma once

#include "entity.hpp"

class Animal : public Entity{
    // implement
    bool can_kill;
    

    public:

    Animal(int power, int initiative, Vector2 position, string name, bool can_kill = false);


    virtual void action() override;


    virtual void collision(Entity *other_entity) override;


    bool is_predator();


    protected:

    virtual void move(Vector2 move_direction);
    

    bool run_away();
};
