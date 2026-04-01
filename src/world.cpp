#include "world.hpp"

World* World::instance = nullptr;

World::World(){
    //TODO change later, bad code
    world_size = Vector2(MAP_SIZE_X, MAP_SIZE_Y);

    this->map = new Map(world_size);
    this->renderer = new Renderer(world_size);
    this->input_manager = new InputManager();

    if(instance == nullptr){
        delete instance;
    }

    instance = this;

    create_entities();
}


World::~World(){
    delete map;
    delete renderer;
    delete input_manager;

    cout << "exited with " << entities.size() << " entities\n";
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        delete entity;
    }
}


Renderer* World::get_renderer(){
    return World::instance->renderer;
}


Map* World::get_map(){
    return World::instance->map;
}


InputManager* World::get_input_manager(){
    return World::instance->input_manager;
}


World* World::get_instance(){
    return World::instance;
}


bool World::perform_turn(){
    input_manager->read_next_input();

    if(input_manager->is_quit_pressed())
        return false;

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        if (entity->is_alive()){
            entity->action();
        }

        queue_to_next(entity);
    }

    next_queue();
    return true;
}


void World::draw_world(){
    renderer->draw_map(world_size);

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        entity->draw();

        queue_to_next(entity);
    }

    // cout << input_manager->get_last_input();

    renderer->render();

    next_queue();
}


void World::add_new_entity(Entity *entity){
    if(map->is_tile_occupied(entity->get_position())){
        // convert entity into kebap
        delete entity;
    }
    else{
        // add entity to world
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


void World::create_entities(){
    int world_area = world_size.x * world_size.y;
    add_new_entity(new Human(world_size * 0.5));

    randomize_entities<Grass>(world_area, GRASS_AMOUNT);
    randomize_entities<Milkweed>(world_area, MILKWEED_AMOUNT);
    randomize_entities<Guarana>(world_area, GUARANA_AMOUNT);
    randomize_entities<Wolfberries>(world_area, WOLFBERRIES_AMOUNT);
    randomize_entities<SosnowskiHogweed>(world_area, SOSNOWSKI_HOGWEED_AMOUNT);
    randomize_entities<Wolf>(world_area, WOLF_AMOUNT);
    randomize_entities<Sheep>(world_area, SHEEP_AMOUNT);
    randomize_entities<Fox>(world_area, FOX_AMOUNT);
    randomize_entities<Turtle>(world_area, TURTLE_AMOUNT);
    randomize_entities<Antelope>(world_area, ANTELOPE_AMOUNT);

    next_queue();
}

template<typename T>
void World::randomize_entities(int world_area, int percent){
    int amount = world_area * percent / 100;
    for(int i = 0; i < amount; ++i){
        add_new_entity(new T(Vector2(rand() % world_size.x, rand() % world_size.y)));
    }
}