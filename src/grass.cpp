#include "grass.hpp"


Entity* Grass::clone(Vector2 position){
    return new Grass(position);
}