#include <vector>

#include "entity.hpp"


class Map{
    Entity*** map;
    Vector2 size;

    public:

    //full init
    Map(Vector2 map_size);


    ~Map();


    Entity* get_entity_at(Vector2 position);


    bool is_tile_occupied(Vector2 position) const;


    Vector2 get_possible_moves(Vector2 position, bool only_free_tiles = false) const;


    void move(Vector2 from, Vector2 to);


    private:

    vector<Vector2> get_neighbours(Vector2 position, bool only_free_tiles = false) const;
};