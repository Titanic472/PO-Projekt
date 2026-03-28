#include "animal.hpp"

class Wolf : public Animal{
    public:

    Wolf(Vector2 position) : Animal(9, 5, position, "Wolf"){}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
