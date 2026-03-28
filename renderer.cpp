#include "renderer.hpp"


// init curses
Renderer::Renderer(){
    // Start curses mode
    initscr();

    // Disable line buffering
    cbreak();

    curs_set(FALSE);

    getmaxyx(stdscr, screen_size.x, screen_size.y);

    std::cout << screen_size.x << " " << screen_size.y;
}

// destroy curses
Renderer::~Renderer(){
    endwin();
}


void Renderer::draw_char_at(Vector2 position, char text) const{

}


void Renderer::draw_map(Map *map){

}