#include "plant.hpp"

class Guarana : public Plant{
    public:

    Guarana(Vector2 position, int age = 0) : Plant(0, position, "guarana", "Guarana"){}


    Guarana(map<string, string> properties) : Guarana(Vector2(properties["position"]), stoi(properties["age"])){}


    void collision(Entity *other_entity) override;

    private:

    Entity* clone(Vector2 position) override;
};
