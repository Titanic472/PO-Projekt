#include "animal.hpp"
#include "world.hpp"

void Animal::action(){
    Map* map = World::get_map();
    Vector2 move_direction = map->get_possible_move_direction(position);

    move(move_direction);
    age += 1;
}


void Animal::move(Vector2 move_direction){
    Map* map = World::get_map();
    Entity* collision_target = map->get_entity_at(position + move_direction);

    if(collision_target != nullptr){
        collision_target->collision(this);

        if(!this->is_alive()){
            return;
        }
    }

    if(map->get_entity_at(position + move_direction) == nullptr){
        map->move(position, position + move_direction);
        position += move_direction;
    }
}