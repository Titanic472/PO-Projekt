// #include <ncurses.h>

class Renderer{
    public:
    //TODO

    // init curses
    Renderer();

    // destroy curses
    ~Renderer();


    void draw_char_at(Vector2 position, char text) const;


    void draw_map(Map *map);

};