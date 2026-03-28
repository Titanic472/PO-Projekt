#include "sosnowskiHogweed.hpp"
#include "world.hpp"
#include "animal.hpp"


Entity* SosnowskiHogweed::clone(Vector2 position){
    return new SosnowskiHogweed(position);
}


void SosnowskiHogweed::collision(Entity *other_entity){
    other_entity->kill();
    this->kill();
}


void SosnowskiHogweed::action() {
    vector<Entity*> entities = World::get_map()->get_entities_around(position);

    while(!entities.empty()){
        Entity* entity = entities.back();
        if(dynamic_cast<Animal*>(entity))
            entity->kill();
        entities.pop_back();
    }

    Plant::action();

}