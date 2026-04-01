#include "human.hpp"
#include "world.hpp"


Human::Human(Vector2 position, int ability_cooldown) :
    Animal(5, 4, position, "Jan Dolski", false){
        
    this->ability_cooldown = ability_cooldown;
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
        ability_cooldown = 10;
        // Handle ability usage
        break;
    default:
        break;
    }

    if(not World::get_map()->is_tile_out_of_bounds(position + move_direction))
        move(move_direction);
    
    // if(age == 90) cout << "moje plecy!";
    age += 1;
}