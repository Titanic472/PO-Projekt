#include "entity.hpp"


Entity::Entity(int power, int initiative, Vector2 position){
    this->power = power;
    this->initiative = initiative;
    this->position = position;
}


bool Entity::operator<(const Entity &other) const{
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


int Entity::set_power(int power){
    this->power = power;
}


int Entity::get_initiative() const{
    return this->initiative;
}


void Entity::kill(){
    is_dead = true;
}


bool Entity::is_alive(){
    return not this->is_dead;
}