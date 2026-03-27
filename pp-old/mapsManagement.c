#ifndef MAPS_H
#define MAPS_H

#include "mapsManagement.h"


void allocateMaps(Game *game){
	game->mapSize.y = getmaxy(game->mainGameWindowContent);
	game->mapSize.x = getmaxx(game->mainGameWindowContent);
	//allocate maps only if they are null with sizes of Content window

	if(game->collisionMap == NULL){
		game->collisionMap = malloc(sizeof(int*) * game->mapSize.y);
		for(int i = 0; i < game->mapSize.y; i++) {
			game->collisionMap[i] = malloc(sizeof(int) * game->mapSize.x);
		}
	}
}


void freeMaps(Game *game){
	if(game->collisionMap != NULL){
		for(int i = 0; i < game->mapSize.y; i++) {
			free(game->collisionMap[i]);
		}
		free(game->collisionMap);
		game->collisionMap = NULL;
	}
}


void resetMaps(Game *game){
	//if maps are null allocate them
	if(game->collisionMap == NULL) allocateMaps(game);

	for(int i = 0; i < game->mapSize.y; i++) {
		memset(game->collisionMap[i], COLLIDER_NONE, sizeof(int) * game->mapSize.x); // Reset to no collision
	}
}

#endif