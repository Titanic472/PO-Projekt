#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "mapsManagement.h"
#include "collisionHandler.h"
#include <ncurses.h>
#include <unistd.h>
#include "functions.h"

int checkCollision(Entity *entity, int **collisionMap, Vector2 mapSize, int offsetMultiplier);

Vector2 findSafeZone(int **collisionMap, Vector2 mapSize);

bool handlePlayerCollision(Game *game, Entity *entity, int collisionType);

bool handleStarCollision(Game *game, Entity *entity, int collisionType, int starID, bool* isAlive);

bool handleHunterCollision(Game *game, Entity *star, int collisionType, int starID, bool* isAlive);

void writeCollision(Entity *entity, int **collisionMap, Vector2 mapSize, int colliderID);

void removeEntityFromCollisionMap(Entity *entity, int **collisionMap, Vector2 mapSize);

#endif