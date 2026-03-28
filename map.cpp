#include "map.hpp"


Map::Map(Vector2 map_size){
    size = map_size;
    map = new Entity**[size.x];

    for(int x = 0; x < size.x; ++x){
        map[x] = new Entity*[size.y];
    }

    for(int x = 0; x < size.x; ++x){
        for(int y = 0; y < size.y; ++y){
            map[x][y] = nullptr;
        }
    }
}


Map::~Map(){
    for(int x = 0; x < size.x; ++x){
        delete map[x];
    }
    delete map;
}


Entity* Map::get_entity_at(Vector2 position){
    return map[position.x][position.y];
}


bool Map::is_tile_occupied(Vector2 position) const{
    return map[position.x][position.y] != nullptr;
}


Vector2 Map::get_possible_moves(Vector2 position, bool only_free_tiles = false) const{
    vector<Vector2> possible_moves = get_neighbours(position, only_free_tiles);

    if(possible_moves.empty())
        return Vector2(0, 0);
    else
        return possible_moves[rand() % possible_moves.size()];
}


void Map::move(Vector2 from, Vector2 to){
    swap(map[to.x][to.y], map[from.x][from.y]);
}



vector<Vector2> Map::get_neighbours(Vector2 position, bool only_free_tiles = false) const{
    vector<Vector2> tiles;

    for(int x = position.x - 1; x <= position.x + 1; ++x){
        for(int y = position.y - 1; y <= position.y + 1; ++y){

            if (
                position.x < 0
                || position.y < 0
                || position.x >= size.x
                || position.y >= size.y
                || (position.x == x && position.y == y)
            )
                continue;

            if (only_free_tiles && map[x][y] == nullptr || !only_free_tiles)
                tiles.push_back(Vector2(x, y));
        }
    }

    return tiles;
}