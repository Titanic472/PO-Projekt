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


void Antelope::collision(Entity *other_entity){
    if(dynamic_cast<Antelope*>(other_entity)){
        Entity::reproduce();
    }
    else {
        if(rand() % 2 == 0){
            if(this->run_away())
                return;
        }
        Animal::collision(other_entity);
    }
}


