#include "vector2.hpp"

class Entity{
    int id;
    int power;
    int initiative;
    Vector2 position;

    public:

    Entity();


    ~Entity();


    void action();


    void collision(Entity other_entity);


    void draw();


    int get_power();


    int set_power();


    int get_initiative();


    void kill();
};