#include "antelope.hpp"
#include "world.hpp"

Entity* Antelope::clone(Vector2 position){
    return new Antelope(position);
}


void Antelope::move(Vector2 move_direction){
    // 2 tile move
    move_direction *= 2;
    if(not World::get_map()->is_tile_out_of_bounds(position + move_direction))
        Animal::move(move_direction);
}


//make run away
void Antelope::collision(Entity *other_entity){
    if(dynamic_cast<Antelope*>(other_entity)){
        Entity::reproduce();
    }
    else {
        //run away to nearby free tile with 50% chance to avoid confrontation
        if(rand() % 2 == 0){
            Vector2 escape_direction = World::get_map()->get_possible_move_direction(this->position, true);
            if(escape_direction != Vector2::ZERO){
                Animal::move(escape_direction);
                return;
            }
        }
        Entity::collision(other_entity);
    }
}


