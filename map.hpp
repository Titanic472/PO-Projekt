#include <vector>

#include "entity.hpp"


class Map{
    Entity*** map;

    public:

    //full init
    Map(Vector2 map_size);


    ~Map();


    bool is_tile_occupied(Vector2 position) const;


    Vector2 get_tile_around(Vector2 position) const;


    Vector2 get_free_tile_around(Vector2 position) const;


    private:

    vector<Vector2> get_neighbours(Vector2 position, bool only_free = false);
};