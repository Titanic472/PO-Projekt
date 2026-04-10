#include "animal.hpp"

class Sheep : public Animal{
    public:

    Sheep(Vector2 position) : Animal(4, 4, position, "Sheep", "Sheep"){}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
