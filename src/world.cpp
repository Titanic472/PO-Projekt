#include "world.hpp"

World* World::instance = nullptr;

World::World(){
    //TODO change later, bad code
    world_size = Vector2(MAP_SIZE_X, MAP_SIZE_Y);

    this->map = new Map(world_size);
    this->renderer = new Renderer(world_size);

    if(instance == nullptr){
        delete instance;
    }

    instance = this;

    // create_entities();
}


World::~World(){
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        delete entity;
    }

    delete map;
    delete renderer;
}


// Renderer* World::get_renderer(){
//     return World::instance->renderer;
// }


Map* World::get_map(){
    return World::instance->map;
}


World* World::get_instance(){
    return World::instance;
}


void World::perform_turn(){
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        if (entity->is_alive()){
            entity->action();
        }

        queue_to_next(entity);
    }

    next_queue();
}


void World::draw_world(){
    renderer->draw_map(world_size);

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        entity->draw();

        queue_to_next(entity);
    }
}


void World::add_new_entity(Entity *entity){
    if(map->is_tile_occupied(entity->get_position())){
        delete entity;
    }
    else{
        map->place_entity_at(entity->get_position(), entity);
        queue_to_next(entity);
    }
}


void World::queue_to_next(Entity *entity){
    if(entity->is_alive()){
        next_turn_entities.push(entity);
    }
    else{
        delete entity;
    }
}


void World::next_queue(){
    entities = move(next_turn_entities);
}


// void World::create_entities(){

// }