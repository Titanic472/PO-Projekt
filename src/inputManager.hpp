#include <iostream>
#include <ncurses.h>

#include "config.hpp"

using namespace std;

class InputManager{
    int last_input = ' ';

    public:

    void read_next_input();


    int get_last_input() const;


    bool is_quit_pressed() const;
};