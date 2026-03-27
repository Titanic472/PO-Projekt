#ifndef MOVE_HANDLER_H
#define MOVE_HANDLER_H

#include "mapsManagement.h"
#include "collisionHandler.h"
#include <ncurses.h>

void setMomentum(Entity *entity, Vector2f momentum, float speedMod);

void moveEntity(Entity *entity);

void handlePlayerMove(Game *game);

void handleStarMove(Game *game, Entity *star, int starID);

void handleHunterMove(Game *game, Entity *hunter, int hunterID);

void handleMove(Game *game);

#endif