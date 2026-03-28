#ifndef ALBATROSS_TAXI_H
#define ALBATROSS_TAXI_H

#include <ncurses.h>
#include <unistd.h>
#include "interface.h"
#include "collisionHandler.h"
#include "entityManager.h"
#include "structures.h"

void loadAlbatross(Game* game, Entity *albatross);

void handleAlbatrossTaxi(Game* game);

#endif