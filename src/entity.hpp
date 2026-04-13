#pragma once

#include <iostream>
#include <string>
#include <map>

#include "vector2.hpp"
#include "saveParser.hpp"

using namespace std;

class Entity{
    bool is_dead = false;
    int power;
    int initiative;
    string name;
    string datatype;

    protected:

    Vector2 position;
    int age;

    public:

    Entity(int power, int initiative, Vector2 position, string name, string datatype, int age = 0)
        : power(power), initiative(initiative), name(name), datatype(datatype), position(position), age(age){};


    virtual ~Entity() = default;


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    void draw();


    Vector2 get_position() const;


    bool is_alive();


    virtual void kill();


    void set_power(int power);


    int get_power() const;


    string get_name() const;


    virtual void collision(Entity *other_entity);


    virtual string save_as_string(SaveParser &parser) const;


    protected:

    virtual void reproduce();


    int get_initiative() const;


    virtual Entity* clone(Vector2 position) = 0;

};


struct CompareEntityPtr {
    bool operator()(const Entity* a, const Entity* b) const;
};