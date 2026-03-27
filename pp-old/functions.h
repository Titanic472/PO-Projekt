#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include "structures.h"
#include "defines.h"
#include "fileParser.h"
#include "mapsManagement.h"

int getDirectionSpriteID(Vector2f momentum);

Vector2 getSpriteSize(Entity *entity);

Vector2 getSpriteCenterPosition(Entity *entity);

bool isNumber(char ch);

void setGameSpeed(Game *game, int speed);

void removeStar(Game *game, int starID);

void removeHunter(Game *game, int hunterID);

void clearStructures(Game *game);

void collectStar(Game *game, int starID);

int calculateScore(Game *game, bool isDefeat);

#endif