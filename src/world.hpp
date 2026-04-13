#pragma once

#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <meta>

#include "vector2.hpp"
#include "config.hpp"
#include "renderer.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "inputManager.hpp"
#include "saveParser.hpp"

#include "grass.hpp"
#include "milkweed.hpp"
#include "guarana.hpp"
#include "wolfberries.hpp"
#include "sosnowskiHogweed.hpp"

#include "wolf.hpp"
#include "sheep.hpp"
#include "fox.hpp"
#include "turtle.hpp"
#include "antelope.hpp"

#include "human.hpp"

using namespace std;

class World {

    Human *human;
    priority_queue<Entity*, vector<Entity*>, CompareEntityPtr> entities;
    priority_queue<Entity*, vector<Entity*>, CompareEntityPtr> next_turn_entities;

    Vector2 world_size;

    Map *map;
    Renderer *renderer;
    InputManager *input_manager;

    static World *instance;

    public:

    World();


    ~World();


    static Renderer* get_renderer();


    static Map* get_map();


    static InputManager* get_input_manager();


    static World* get_instance();


    static Human** get_human();


    static int get_entitity_count();


    // returns if turn was performed successfully and application should continue executing
    bool perform_turn();


    void draw_world();


    void add_new_entity(Entity *entity);


    private:

    void save();


    void load();


    void queue_to_next(Entity *entity);


    void next_queue();


    void create_entities();


    template<typename T>
    void randomize_entities(int percent, int world_area);


    void clear_entities();


    template <typename... Types>
    void load_entity(std::map<string, string> entity_data);
};