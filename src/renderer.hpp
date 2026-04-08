#pragma once

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <locale.h>

#include "vector2.hpp"

using namespace std;

class Renderer{
    Vector2 screen_size;
    Vector2 cell_size;
    vector<string> log_messages;

    WINDOW *main_window;
    WINDOW *info_window;

    int status_window_width;

    public:

    // init curses
    Renderer(Vector2 map_size);

    // destroy curses
    ~Renderer();


    void render();


    void draw_char_at(Vector2 position, char text) const;


    void draw_map(Vector2 map_size);


    void add_to_log(string text);


    void draw_info_window();

    private:

    void create_window(WINDOW **win, int height, int width, int starty, int startx);


    string convert_input_to_text(int input);
};
