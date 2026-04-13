#include "world.hpp"

World* World::instance = nullptr;

World::World(){
    // TODO change later, bad code
    world_size = Vector2(MAP_SIZE_X, MAP_SIZE_Y);

    this->map = new Map(world_size);
    this->renderer = new Renderer(world_size);
    this->input_manager = new InputManager();

    if(instance != nullptr){
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

    clear_entities();
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


Human** World::get_human(){
    return &World::instance->human;
}


int World::get_entitity_count(){
    return World::instance->entities.size();
}


bool World::perform_turn(){
    do{
        input_manager->read_next_input();

        if(input_manager->is_quit_pressed())
            return false;

        if(input_manager->get_last_input() == SAVE){
            save();
        }
        else if(input_manager->get_last_input() == LOAD){
            load();
            // skip turn after loading
            return true;
        }

        // redraw info window to show pressed input
        renderer->draw_info_window();
        renderer->render_info_window();
    }
    while (!input_manager->is_new_turn_pressed());

    renderer->clear_log();

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
    renderer->draw_info_window();
    renderer->render_info_window();

    renderer->draw_map(world_size);

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        entity->draw();

        queue_to_next(entity);
    }

    renderer->render_map();

    next_queue();
}


void World::save(){
    SaveParser parser;

    parser.create_file(world_size);

    parser.add_entry("world_size", DataFormat::TYPE_VECTOR2, world_size.to_string());

    parser.start_category("entities");

    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        if(entity->is_alive()){
            parser.add_string_entry(entity->save_as_string());
        }

        queue_to_next(entity);
    }

    next_queue();

    parser.end_category();

    parser.close_file();

    renderer->clear_log();
    renderer->add_to_log("game saved!");
}


void World::load(){
    renderer->clear_log();

    SaveParser parser;

    if(!parser.load_file(world_size)){
        renderer->add_to_log("no save file found!");
        return;
    }

    parser.loadEntry(&world_size, "world_size");

    // clear previous world
    delete map;
    map = new Map(world_size);
    clear_entities();

    // load entities
    if(!parser.jump_to_category("entities")){
        renderer->add_to_log("incorrect save file format");
        return;
    }

    std::map<string, string> entity_data;

    while(parser.load_entry_multiline(&entity_data)){
        load_entity<
            Grass, Milkweed, Guarana, Wolfberries, SosnowskiHogweed,
            Wolf, Sheep, Fox, Turtle, Antelope, Human
            >(entity_data);
        entity_data.clear();
    }

    next_queue();
    renderer->add_to_log("game loaded!");
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
    human = new Human(world_size * 0.5);
    add_new_entity(human);

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


void World::clear_entities(){
    while (!entities.empty()){
        Entity *entity = entities.top();
        entities.pop();

        delete entity;
    }
}

template <typename... Types>
void World::load_entity(std::map<string, string> entity_data){
    // C++26 features to make it easier
    std::unique_ptr<Entity> result = nullptr;

    // 'template for' expands the loop at compile-time for each type
    template for (constexpr auto type_meta : { ^Types... }) {
        // std::meta::name_of gets the class name (e.g., "Player") at compile-time,
        // converting it to a string view to compare with our runtime 'name'.
        if (entity_data["type"] == std::meta::name_of(type_meta)) {
            // [:type_meta:] behaves exactly as the specific type in this iteration
            result = std::make_unique<[:type_meta:]>(entity_data);
            if(entity_data["type"] == "Human"){
                human = static_cast<Human*>(result);
            }
        }
    }

    return result;
}