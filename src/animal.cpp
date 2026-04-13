#include "animal.hpp"
#include "world.hpp"


void Animal::action(){
    Map* map = World::get_map();
    Vector2 move_direction = map->get_possible_move_direction(position);

    move(move_direction);
    age += 1;
}


void Animal::collision(Entity *other_entity) {
    if(dynamic_cast<Animal*>(other_entity)){
        Animal* enemy = dynamic_cast<Animal*>(other_entity);
        if(this->get_power() <= enemy->get_power() && not enemy->is_predator()){
            this->run_away();
            return;
        }
        // else if(this->get_power() > enemy->get_power() && not this->is_predator())
        //     return;
    }
    Entity::collision(other_entity);
}


bool Animal::is_predator(){
    return this->can_kill;
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


bool Animal::run_away(){
    Vector2 direction = World::get_map()->get_possible_move_direction(this->position, true);
    if(direction != Vector2::ZERO){
        this->move(direction);
        return true;
    }
    else
        return false;
}