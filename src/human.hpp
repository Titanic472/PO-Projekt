#pragma once

#include "animal.hpp"
#include "config.hpp"

class Human : public Animal{
    int ability_cooldown;

    public:

    Human(Vector2 position, int power = 5, int age = 0, int ability_cooldown = 0)
        : Animal(power, 4, position, "Human", "Human", age, true), ability_cooldown(ability_cooldown){}


    Human(map<string, string> properties) : Human(Vector2(properties["position"]), stoi(properties["power"]), stoi(properties["age"]), stoi(properties["ability_cooldown"])){}


    ~Human();


    void action() override;


    void kill() override;


    void collision(Entity *other_entity) override;


    int get_ability_cooldown() const;


    string save_as_string(SaveParser &parser) const override;


    private:

    Entity* clone(Vector2 position) override;
};