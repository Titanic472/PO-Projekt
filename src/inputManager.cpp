#include "inputManager.hpp"


void InputManager::read_next_input(){
    // last_input = getch();
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
    last_input = input;
}


int InputManager::get_last_input() const{
    return this->last_input;
}


bool InputManager::is_quit_pressed() const{
    return last_input == QUIT;
}