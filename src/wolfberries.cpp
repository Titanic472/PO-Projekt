#include "wolfberries.hpp"
#include "world.hpp"


Entity* Wolfberries::clone(Vector2 position){
    return new Wolfberries(position);
}


void Wolfberries::collision(Entity *other_entity){
    other_entity->kill();
    this->kill();
    World::get_renderer()->add_to_log(this->get_name() + " tried to kill " + other_entity->get_name() + " and died");
}