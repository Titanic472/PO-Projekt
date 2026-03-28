#include "fox.hpp"
#include "world.hpp"

Entity* Fox::clone(Vector2 position){
    return new Fox(position);
}


void Fox::action(){
    Map* map = World::get_map();
    Vector2 move_direction = map->get_possible_move_direction(position);
    Entity* collision_target = map->get_entity_at(position + move_direction);

    if(
        collision_target == nullptr
        || collision_target->get_power() <= this->get_power()
    )
        Animal::action();
}


void Fox::collision(Entity *other_entity){
    if(dynamic_cast<Fox*>(other_entity)){
        Entity::reproduce();
    }
    else
        Entity::collision(other_entity);
}