#include "turtle.hpp"


Entity* Turtle::clone(Vector2 position){
    return new Turtle(position);
}


void Turtle::collision(Entity *other_entity){
    if(dynamic_cast<Turtle*>(other_entity)){
        Entity::reproduce();
    }
    // ignore attacks from entites with less than 5 power
    else if(other_entity->get_power() >= 5)
        Entity::collision(other_entity);
}


void Turtle::move(Vector2 move_direction){
    if(rand() % 4 == 0)
        Animal::move(move_direction);
}

