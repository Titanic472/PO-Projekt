#pragma once

#include <vector>
#include <queue>

#include "vector2.hpp"
#include "config.hpp"
#include "renderer.hpp"
#include "entity.hpp"
#include "map.hpp"

using namespace std;

class World {

    priority_queue<Entity*> entities;
    priority_queue<Entity*> next_turn_entities;

    Vector2 world_size;

    Map *map;
    Renderer *renderer;

    static World *instance;

    public:

    World();


    ~World();


    // static Renderer* get_renderer();


    static Map* get_map();


    static World* get_instance();


    void perform_turn();


    void draw_world();


    void add_new_entity(Entity *entity);


    private:

    void queue_to_next(Entity *entity);


    void next_queue();


    void create_entities();

};