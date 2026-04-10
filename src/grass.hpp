#include "plant.hpp"

class Grass : public Plant{
    public:

    Grass(Vector2 position) : Plant(0, position, "trawa:)", "Grass") {}


    private:

    Entity* clone(Vector2 position) override;
};
