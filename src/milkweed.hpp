#include "plant.hpp"

class Milkweed : public Plant{
    public:

    Milkweed(Vector2 position) : Plant(0, position, "milkweed"){}


    void action() override;

    private:

    Entity* clone(Vector2 position) override;
};
