#include "plant.hpp"

class Guarana : public Plant{
    public:

    Guarana(Vector2 position) : Plant(0, position, "guarana", "Guarana"){}

    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
