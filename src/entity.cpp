#include "entity.hpp"


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
    Renderer::get_instance()->draw_char_at(this->position, this->name[0]);
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
    World::get_map()->remove_at(position);
}


bool Entity::is_alive(){
    return not this->is_dead;
}


void Entity::collision(Entity *other_entity){
    if(this->power <= other_entity->get_power())
        this->kill();
    else
        other_entity->kill();
}


void Entity::reproduce(){
    Vector2 position = World::get_map()->get_possible_moves(position, true);
    World::get_instance()->add_new_entity(clone(position));
}