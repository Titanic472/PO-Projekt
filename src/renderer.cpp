#include "renderer.hpp"
#include "world.hpp"

// init curses
Renderer::Renderer(Vector2 map_size){
    setlocale(LC_ALL, "");

    // Start curses mode
    initscr();

    // Disable line buffering
    cbreak();

    curs_set(FALSE);

    keypad(stdscr, TRUE);

    getmaxyx(stdscr, screen_size.y, screen_size.x);

    status_window_width = (screen_size.x * STATUS_WIDTH) / 100;
    int main_window_width = screen_size.x - status_window_width;

    cell_size = Vector2(main_window_width / map_size.x, screen_size.y / map_size.y);

    status_window_width = screen_size.x - (cell_size.x * (map_size.x + 1));
    screen_size = Vector2(cell_size.x * map_size.x + 1, cell_size.y * map_size.y + 1);

    create_window(&main_window, screen_size.y, screen_size.x, 0, 0);
    create_window(&info_window, screen_size.y, status_window_width, 0, screen_size.x);
}

// destroy curses
Renderer::~Renderer(){
    endwin();
}


void Renderer::render_map(){
    wrefresh(main_window);
}


void Renderer::render_info_window(){
    wrefresh(info_window);
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


void Renderer::create_window(WINDOW **win, int height, int width, int starty, int startx){
	*win = newwin(height, width, starty, startx);
	wrefresh(*win);
}


void Renderer::add_to_log(string text){
    // limit log size to match window height
    if(log_messages.size() > (unsigned int)screen_size.y){ 
        return;
    }
    log_messages.push_back(text);
}


void Renderer::draw_info_window(){
    werase(info_window);
    box(info_window, 0 , 0);

    int max_width = status_window_width - 2; // leave space for borders
    if (max_width <= 0) return;

    int y = 1;

    // Button pressed section
    string btn_text = "button pressed: ";
    btn_text += convert_input_to_text(World::get_instance()->get_input_manager()->get_last_input());
    mvwprintw(info_window, y++, 1, "%s", btn_text.substr(0, max_width).c_str());
    
    y++; // empty line

    // Ability cooldown section
    string cd_text = "ability cooldown: <int>";
    mvwprintw(info_window, y++, 1, "%s", cd_text.substr(0, max_width).c_str());
    
    y++; // empty line

    // entities count section
    string entities_text = "entities: <int>";
    mvwprintw(info_window, y++, 1, "%s", entities_text.substr(0, max_width).c_str());

    y++; // empty line

    // Log section limit by screen height
    for(const string& message : log_messages){
        if (y >= screen_size.y - 1) {
            break;
        }
        mvwprintw(info_window, y++, 1, "%s", message.substr(0, max_width).c_str());
    }
}


void Renderer::clear_log(){
    log_messages.clear();
}


string Renderer::convert_input_to_text(int input){
    switch (input)
    {
    case LEFT:
        return "LEFT";
    case RIGHT:
        return "RIGHT";
    case UP:
        return "UP";
    case DOWN:
        return "DOWN";
    case ABILITY:
        return "ABILITY";
    default:
        return "";
    }
}