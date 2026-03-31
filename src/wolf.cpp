#include "wolf.hpp"


Entity* Wolf::clone(Vector2 position){
    return new Wolf(position);
}


void Wolf::collision(Entity *other_entity){
    if(dynamic_cast<Wolf*>(other_entity)){
        Entity::reproduce();
    }
    else
        Animal::collision(other_entity);
}