#include "entity.hpp"
#include "renderer.hpp"
#include "world.hpp"


Entity::Entity(int power, int initiative, Vector2 position, string name){
    this->power = power;
    this->initiative = initiative;
    this->position = position;
    this->name = name;
}


bool Entity::operator<(const Entity &other) const{
    if(this->initiative == other.initiative){
        return this->age < other.age;
    }
    return this->initiative < other.initiative;
}


void Entity::draw(){
    World::get_renderer()->draw_char_at(this->position, this->name[0]);
}


Vector2 Entity::get_position() const{
    return this->position;
}


int Entity::get_power() const{
    return this->power;
}


void Entity::set_power(int power){
    this->power = power;
}


int Entity::get_initiative() const{
    return this->initiative;
}


void Entity::kill(){
    is_dead = true;
    World::get_map()->remove_entity_at(this->position);
}


bool Entity::is_alive(){
    return !this->is_dead;
}


void Entity::collision(Entity *other_entity){
    if(this->power <= other_entity->get_power()){
        World::get_renderer()->add_to_log(this->name + " collided with " + other_entity->name + " and died");
        this->kill();
    }
    else{
        World::get_renderer()->add_to_log(this->name + " collided with " + other_entity->name + " and won");
        other_entity->kill();
    }
        
}


void Entity::reproduce(){
    Vector2 direction = World::get_map()->get_possible_move_direction(this->position, true);

    if(not World::get_map()->is_tile_occupied(this->position + direction)){
        World::get_renderer()->add_to_log(this->name + " reproduced");
        World::get_instance()->add_new_entity(clone(this->position + direction));
    }
    
}