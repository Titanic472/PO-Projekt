#include "guarana.hpp"


Entity* Guarana::clone(Vector2 position){
    return new Guarana(position);
}


void Guarana::collision(Entity *other_entity){
    other_entity->set_power(other_entity->get_power() + 3);
    Entity::collision(other_entity);
}