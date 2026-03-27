#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "structures.h"
#include "fileParser.h"
#include <stdlib.h>

void loadSpriteSizes(Entity *entity, char* fileName, char* fileKey, char* subCat);

void loadSprites(Entity *entity, char* fileName, char* fileKey, char* subCat);

void loadEntity(Entity *entity, char* fileName, char* fileKey, bool oneFromMany);

void spawnEntities(Game *game);

#endif