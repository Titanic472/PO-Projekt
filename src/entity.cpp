#include "entity.hpp"
#include "renderer.hpp"
#include "world.hpp"


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


string Entity::get_name() const{
    return this->name;
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


string Entity::save_as_string(SaveParser &parser) const{
    string data;

    data += parser.stringify_entry(datatype, DataFormat::CATEGORY_START_HEADER);
    data += parser.stringify_entry("position", DataFormat::TYPE_VECTOR2, this->position.to_string());
    data += parser.stringify_entry("age", DataFormat::TYPE_INT, to_string(this->age));
    data += parser.stringify_entry("power", DataFormat::TYPE_INT, to_string(this->power));

    return data;
}


void Entity::reproduce(){
    Vector2 direction = World::get_map()->get_possible_move_direction(this->position, true);

    if(not World::get_map()->is_tile_occupied(this->position + direction)){
        World::get_renderer()->add_to_log(this->name + " reproduced");
        World::get_instance()->add_new_entity(clone(this->position + direction));
    }

}


bool CompareEntityPtr::operator()(const Entity* a, const Entity* b) const{
    return *a < *b;
}