#pragma once

#include <iostream>
#include <string>

#include "vector2.hpp"

using namespace std;

class Entity{
    bool is_dead = false;
    int power;
    int initiative;
    string name;
    string datatype;

    protected:

    Vector2 position;
    int age = 0;

    public:

    Entity(int power, int initiative, Vector2 position, string name, string datatype);


    virtual ~Entity() = default;


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    void draw();


    Vector2 get_position() const;


    bool is_alive();


    virtual void kill();


    void set_power(int power);


    int get_power() const;


    virtual void collision(Entity *other_entity);


    virtual string save_as_string() const;


    protected:

    virtual void reproduce();


    int get_initiative() const;


    virtual Entity* clone(Vector2 position) = 0;

};


struct CompareEntityPtr {
    bool operator()(const Entity* a, const Entity* b) const;
};