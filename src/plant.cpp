#include "plant.hpp"

void Plant::action() {
    if(rand() % 100 < PLANTS_SPREAD_CHANCE){
        Entity::reproduce();
    }
}