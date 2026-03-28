#pragma once

#include <iostream>

#include "vector2.hpp"

using namespace std;

class Entity{
    bool is_dead = false;
    int power;
    int initiative;
    string name;

    protected:

    Vector2 position;
    int age = 0;

    public:

    Entity(int power, int initiative, Vector2 position, string name);


    virtual ~Entity() = default;


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    void draw();


    Vector2 get_position() const;


    bool is_alive();


    void kill();


    void set_power(int power);


    int get_power() const;


    virtual void collision(Entity *other_entity);


    protected:

    virtual void reproduce();


    int get_initiative() const;


    virtual Entity* clone(Vector2 position) = 0;

};