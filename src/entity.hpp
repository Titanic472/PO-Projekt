#pragma once

#include <iostream>

#include "vector2.hpp"
#include "renderer.hpp"

using namespace std;

class Entity{
    bool is_dead;
    int power;
    int initiative;

    protected:

    string name;
    Vector2 position;

    public:

    Entity(int power, int initiative, Vector2 position);


    virtual ~Entity() = 0;


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    void draw();


    Vector2 get_position() const;


    bool is_alive();

    protected:

    virtual void collision(Entity &other_entity) = 0;


    int get_power() const;


    void set_power(int power);


    int get_initiative() const;


    void kill();

};