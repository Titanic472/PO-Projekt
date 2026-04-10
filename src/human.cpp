#include "human.hpp"
#include "world.hpp"


Human::Human(Vector2 position, int ability_cooldown) :
    Animal(5, 4, position, "Human", "Human", true){

    this->ability_cooldown = ability_cooldown;
}

Human::~Human(){
    World::get_renderer()->add_to_log("Human died at age " + to_string(age));
    *(World::get_human()) = nullptr;
}


Entity* Human::clone(Vector2 position){
    return new Human(position, ability_cooldown);
}


void Human::action(){
    if(ability_cooldown > 0)
        --ability_cooldown;

    Vector2 move_direction = Vector2::ZERO;

    switch(World::get_input_manager()->get_last_input()){
    case LEFT:
        move_direction = Vector2(-1, 0);
        break;
    case RIGHT:
        move_direction = Vector2(1, 0);
        break;
    case UP:
        move_direction = Vector2(0, -1);
        break;
    case DOWN:
        move_direction = Vector2(0, 1);
        break;
    case ABILITY:
        if(ability_cooldown == 0)
            ability_cooldown = 10;
        // Handle ability in other's collision
        break;
    default:
        break;
    }

    if(
        not World::get_map()->is_tile_out_of_bounds(position + move_direction)
        && move_direction != Vector2::ZERO
    )
        move(move_direction);

    // if(age == 90) cout << "moje plecy!";
    age += 1;
}


void Human::collision(Entity *other_entity){
    //ability handle before turn if collision happened
    if(
        World::get_input_manager()->get_last_input() == ABILITY
        && ability_cooldown == 0
    )
        ability_cooldown = 11;

    if(ability_cooldown > 5){
        if(other_entity->get_power() >= this->get_power())
            this->run_away();
        return;
    }

    Animal::collision(other_entity);

}


int Human::get_ability_cooldown() const{
    return ability_cooldown;
}


void Human::kill(){
    if(ability_cooldown > 5)
        return;
    Entity::kill();
}


string Human::save_as_string() const{
    string data = Entity::save_as_string();
    data = data + "ability_cooldown:" + DataFormat::TYPE_INT + ":" + to_string(this->ability_cooldown) + ";\n";
    return data;
}