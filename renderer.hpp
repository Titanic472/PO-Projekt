#include <ncurses.h>
#include "vector2.hpp"
#include "map.hpp"

class Renderer{
    Vector2 screen_size;
    public:

    // init curses
    Renderer();

    // destroy curses
    ~Renderer();


    void draw_char_at(Vector2 position, char text) const;


    void draw_map(Map *map);

};