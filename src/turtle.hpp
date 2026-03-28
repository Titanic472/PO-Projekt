#include "animal.hpp"

class Turtle : public Animal{
    public:

    Turtle(Vector2 position) : Animal(2, 1, position, "Turtle"){}


    void collision(Entity *other_entity) override;


    private:

    Entity* clone(Vector2 position) override;


    void move(Vector2 move_direction);
};
