#include "renderer.hpp"
#include "world.hpp"

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

    cell_size = Vector2(screen_size.x / map_size.x, screen_size.y / map_size.y);

    screen_size = Vector2(cell_size.x * map_size.x + 1, cell_size.y * map_size.y + 1);

    createWindow(&main_window, screen_size.y, screen_size.x, 0, 0);

}

// destroy curses
Renderer::~Renderer(){
    endwin();
}


void Renderer::render(){
    wrefresh(main_window);
}

void Renderer::draw_char_at(Vector2 position, char text) const{
    Vector2 screen_position = Vector2(position.x * cell_size.x, position.y * cell_size.y);
    screen_position += Vector2(cell_size.x / 2, cell_size.y / 2);
    mvwprintw(main_window, screen_position.y, screen_position.x, "%c", text);
}


void Renderer::draw_map(Vector2 map_size){
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
}


void Renderer::createWindow(WINDOW **win, int height, int width, int starty, int startx){
	*win = newwin(height, width, starty, startx);
	wrefresh(*win);
}