#include "map.hpp"


Map::Map(Vector2 map_size){
    size = map_size;

    map.resize(size.x, std::vector<Entity*>(size.y, nullptr));
}


Entity* Map::get_entity_at(Vector2 position){
    return map[position.x][position.y];
}


void Map::remove_entity_at(Vector2 position){
    map[position.x][position.y] = nullptr;
}


void Map::place_entity_at(Vector2 position, Entity* entity){
    map[position.x][position.y] = entity;
}


bool Map::is_tile_occupied(Vector2 position) const{
    return map[position.x][position.y] != nullptr;
}


Vector2 Map::get_possible_move_direction(Vector2 position, bool only_free_tiles) const{
    vector<Vector2> possible_moves = get_neighbours(position, only_free_tiles);

    if(possible_moves.empty())
        return Vector2::ZERO;
    else{
        Vector2 move_position = possible_moves[rand() % possible_moves.size()];
        return Vector2(move_position.x - position.x, move_position.y - position.y);
    }
}


vector<Entity*> Map::get_entities_around(Vector2 position){
    vector<Vector2> possible_moves = get_neighbours(position, false, true);

    vector<Entity*> entities;

    while(!possible_moves.empty()){
        Vector2 pos = possible_moves.back();
        possible_moves.pop_back();
        entities.push_back(map[pos.x][pos.y]);
    }

    return entities;
}


void Map::move(Vector2 from, Vector2 to){
    swap(map[to.x][to.y], map[from.x][from.y]);
}



vector<Vector2> Map::get_neighbours(Vector2 position, bool only_free_tiles, bool only_occupied_tiles) const{
    vector<Vector2> tiles;


    for(int x = position.x - 1; x <= position.x + 1; ++x){
        for(int y = position.y - 1; y <= position.y + 1; ++y){

            if (
                x < 0
                || y < 0
                || x >= size.x
                || y >= size.y
                || (position.x == x && position.y == y)
            )
                continue;

            if (
                (only_free_tiles && map[x][y] == nullptr)
                || (!only_free_tiles && !only_occupied_tiles)
                || (only_occupied_tiles && map[x][y] != nullptr)
            )
                tiles.push_back(Vector2(x, y));

        }
    }

    return tiles;
}