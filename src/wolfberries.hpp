#include "plant.hpp"

class Wolfberries : public Plant{
    public:

    Wolfberries(Vector2 position) : Plant(99, position, "wolfberries"){}

    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
