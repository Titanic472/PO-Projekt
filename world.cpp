#include "world.hpp"


World::World(){
    this->map = new Map(world_size);
    this->renderer = new Renderer();

    if(instance == nullptr){
        delete instance;
    }

    instance = this;

    create_entities();
}


World::~World(){
    delete map;
    delete renderer;
}


Renderer* World::get_renderer(){
    return World::instance->renderer;
}


Map* World::get_map(){
    return World::instance->map;
}


void World::perform_turn(){
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        if (entity->is_alive()){
            entity->action();
        }

        queue_to_next_turn(entity);
    }

    prepare_next_turn();
}


void World::draw_world(){
    renderer->draw_map();


}


void World::add_new_entity(Entity *entity){
    if(map->is_tile_occupied(entity->get_position())){
        delete entity;
    }
    else{
        queue_to_next_turn(entity);
    }
}


void World::queue_to_next_turn(Entity *entity){
    if(entity->is_alive()){
        next_turn_entities.push(entity);
    }
    else{
        delete entity;
    }
}


void World::prepare_next_turn(){
    entities = move(next_turn_entities);
}