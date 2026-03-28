#ifndef WORLD
#define WORLD

#include <vector>
#include <queue>

#include "vector2.hpp"
#include "config.hpp"
#include "entity.hpp"
#include "map.hpp"

using namespace std;

class World {

    priority_queue<Entity*> entities;
    priority_queue<Entity*> next_turn_entities;

    Vector2 world_size;

    Map *map;
    Renderer *renderer;


    public:

    static World *instance;

    World();


    ~World();


    static Renderer* get_renderer();


    static Map* get_map();


    void perform_turn();


    void draw_world();


    void add_new_entity(Entity *entity);


    void queue_to_next(Entity *entity);

    private:

    void next_queue();


    void create_entities();

};

#endif