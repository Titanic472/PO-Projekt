#include "grass.hpp"


Entity* clone(Vector2 position){
    return new Grass(position);
}