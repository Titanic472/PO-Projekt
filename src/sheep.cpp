#include "sheep.hpp"


Entity* Sheep::clone(Vector2 position){
    return new Sheep(position);
}


void Sheep::collision(Entity *other_entity){
    if(dynamic_cast<Sheep*>(other_entity)){
        Entity::reproduce();
    }
    else
        Entity::collision(other_entity);
}