#include <iostream>
#include <time.h>
#include <unistd.h>

#include "world.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    World *world = new World();

    world->draw_world();
    //create input manager

    char a = ' ';
    while(a != 'q'){
        cin >> a;
        if (a == 'n'){
            world->perform_turn();
            world->draw_world();
        }

    }

    // world->draw_world();
    // usleep(10000000);

    delete world;
    return 0;
}