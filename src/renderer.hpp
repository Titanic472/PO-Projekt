#pragma once

#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include "vector2.hpp"

using namespace std;

class Renderer{
    Vector2 screen_size;

    WINDOW *main_window;
    static Renderer *instance;

    public:

    // init curses
    Renderer(Vector2 map_size);

    // destroy curses
    ~Renderer();


    static Renderer* get_instance();


    void draw_char_at(Vector2 position, char text) const;


    void draw_map(Vector2 map_size);

    private:

    void createWindow(WINDOW **win, int height, int width, int starty, int startx);

};
