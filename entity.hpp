#include <iostream>

#include "vector2.hpp"
#include "renderer.hpp"
#include "world.hpp"

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


    ~Entity(){}


    bool operator<(const Entity &other) const;


    virtual void action() = 0;


    virtual void draw();


    Vector2 get_position() const;


    bool is_alive();

    protected:

    virtual void collision(Entity &other_entity) = 0;


    int get_power() const;


    int set_power(int power);


    int get_initiative() const;


    void kill();

};