#include "renderer.hpp"

Renderer* Renderer::instance = nullptr;

// init curses
Renderer::Renderer(Vector2 map_size){
    if(instance == nullptr){
        delete instance;
    }

    instance = this;

    setlocale(LC_ALL, "");

    // Start curses mode
    initscr();

    // Disable line buffering
    cbreak();

    curs_set(FALSE);

    getmaxyx(stdscr, screen_size.y, screen_size.x);

    screen_size = Vector2(screen_size.x / map_size.x * map_size.x + 1, screen_size.y / map_size.y * map_size.x + 1);

    createWindow(&main_window, screen_size.y, screen_size.x, 0, 0);

}

// destroy curses
Renderer::~Renderer(){

    endwin();
}


Renderer* Renderer::get_instance(){
    return Renderer::instance;
}


void Renderer::draw_char_at(Vector2 position, char text) const{

}


void Renderer::draw_map(Vector2 map_size){
    Vector2 cell_size = Vector2(screen_size.x / map_size.x, screen_size.y / map_size.y);

    box(main_window, 0 , 0);

    for(int y = 1; y < screen_size.y - 1; ++y){
        string line = "";
        for(int x = 1; x < screen_size.x - 1; ++x){
            if(x % cell_size.x == 0 && y % cell_size.y == 0)
                line += "┼";
            else if(x % cell_size.x == 0)
                line += "│";
            else if(y % cell_size.y == 0)
                line += "─";
            else
                line += ' ';
        }
        mvwprintw(main_window, y, 1, "%s", line.c_str());
    }

    wrefresh(main_window);
}


void Renderer::createWindow(WINDOW **win, int height, int width, int starty, int startx){
	*win = newwin(height, width, starty, startx);
	wrefresh(*win);
}