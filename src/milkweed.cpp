#include "milkweed.hpp"


void Milkweed::action() {
    // three reproduce attempts
    for(int i = 0; i < 2; ++i){
        if(rand() % 100 < PLANTS_SPREAD_CHANCE){
            Entity::reproduce();
        }
    }

    // third reproduce attempt is located in plant action code
    Plant::action();

}

Entity* Milkweed::clone(Vector2 position){
    return new Milkweed(position);
}