// no co, typowy uczeń kierunku humanistycznego 
// jak się znudzi to zamiast się poruszać zacznie lekturę czytać

#include "animal.hpp"
#include "config.hpp"

class Human : public Animal{
    int ability_cooldown;

    public:

    Human(Vector2 position, int ability_cooldown = 0);


    void action() override;


    void collision(Entity *other_entity) override;

};