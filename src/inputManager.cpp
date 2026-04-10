#include "inputManager.hpp"


void InputManager::read_next_input(){
    new_turn_pressed = false;
    char input;
    cin >> input;
    if(input == 27){
        cin >> input;
        if(input == 79){
            cin >> input;
            last_input = input + 255;
            return;
        }
    }
    if(input == NEW_TURN){
        new_turn_pressed = true;
        return;
    }
    
    last_input = input;
}


int InputManager::get_last_input() const{
    return this->last_input;
}


bool InputManager::is_quit_pressed() const{
    return last_input == QUIT;
}


bool InputManager::is_new_turn_pressed() const{
    return new_turn_pressed;
}