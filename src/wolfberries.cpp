#include "wolfberries.hpp"


Entity* Wolfberries::clone(Vector2 position){
    return new Wolfberries(position);
}


void Wolfberries::collision(Entity *other_entity){
    other_entity->kill();
    this->kill();
}