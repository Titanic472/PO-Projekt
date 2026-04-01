#include "inputManager.hpp"


void InputManager::read_next_input(){
    // last_input = getch();
    cin >> last_input;
}


int InputManager::get_last_input() const{
    return this->last_input;
}


bool InputManager::is_quit_pressed() const{
    return last_input == QUIT;
}