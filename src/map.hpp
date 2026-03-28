#pragma once

#include <vector>

#include "entity.hpp"
#include "vector2.hpp"

using namespace std;

class Map{
    vector<vector<Entity*>> map;
    Vector2 size;

    public:

    //full init
    Map(Vector2 map_size);


    Entity* get_entity_at(Vector2 position);


    void place_entity_at(Vector2 position, Entity* entity);


    bool is_tile_occupied(Vector2 position) const;


    Vector2 get_possible_moves(Vector2 position, bool only_free_tiles = false) const;


    void move(Vector2 from, Vector2 to);


    private:

    vector<Vector2> get_neighbours(Vector2 position, bool only_free_tiles = false) const;
};