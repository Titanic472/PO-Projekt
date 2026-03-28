#pragma once

#include <iostream>

#include "vector2.hpp"
#include "renderer.hpp"
#include "world.hpp"

using namespace std;

class Entity{
    int age = 0;
    bool is_dead;
    int power;
    int initiative;

    protected:

    string name;
    Vector2 position;

    public:

    Entity(int power, int initiative, Vector2 position, string name);


    virtual ~Entity() = 0;


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    void draw();


    Vector2 get_position() const;


    bool is_alive();


    protected:

    virtual void reproduce();


    void set_power(int power);


    int get_initiative() const;


    void kill();


    int get_power() const;


    virtual void collision(Entity *other_entity);


    virtual Entity* clone(Vector2 position) = 0;

};