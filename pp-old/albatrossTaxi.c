#include "albatrossTaxi.h"


void loadAlbatross(Game* game, Entity *albatross){
	if (albatross == NULL) {
        fprintf(stderr, "Error: albatross is not allocated!\n");
		usleep(1000000);
    }

	loadSpriteSizes(albatross, game->levelName, "albatross", "");
	
	loadSprites(albatross, game->levelName, "albatross", "");
	albatross->momentum.x = ALBATROSS_SPEED;//only for proper animation purpose
	albatross->position = game->screen; // stored out of bounds but initialized
}


void moveAlbatross(Game *game, Entity *albatross, Vector2 playerPos){
	albatross->currFrame = 0;
	while(albatross->position.x < game->mapSize.x){
		albatross->position.x += ALBATROSS_SPEED;
		Vector2 albatrossSpriteCenter = getSpriteCenterPosition(albatross);
		if(playerPos.x == POSITION_NULL){
			if(game->player->position.x <= albatrossSpriteCenter.x){
				game->player->position = game->mapSize; //throw player out of bounds to avoid drawing
			}
		}
		else{
			if(playerPos.x <= albatrossSpriteCenter.x){
				game->player->position = playerPos; //draw player after using albatross taxi
			}
		}
		drawGame(game, false);
		usleep(ALBATROSS_TICK_RATE);
	}
}


bool checkSquare(int **collisionMap, Vector2 start, Vector2 bounds){
	for(int x = 0; x < bounds.x; ++x){
		for(int y = 0; y < bounds.y; ++y){
			if(collisionMap[start.y + y][start.x + x] != COLLIDER_NONE && collisionMap[start.y + y][start.x + x] != COLLIDER_STAR){
				return false;
			}
		}
	}
	return true;
}


Vector2 findSafeZone(int **collisionMap, Vector2 mapSize){
	for(int x = SAFE_ZONE_MARGIN; x < mapSize.x - DEFAULT_SAFE_ZONE_RADIUS*2 - SAFE_ZONE_MARGIN; ++x){
		for(int y = 0; y < mapSize.y - DEFAULT_SAFE_ZONE_RADIUS*2; ++y){
			if(checkSquare(collisionMap, (Vector2){y, x}, (Vector2){DEFAULT_SAFE_ZONE_RADIUS*2, DEFAULT_SAFE_ZONE_RADIUS*2})){
				return (Vector2){y, x};
			}
		}
	}
	return (Vector2){-1, -1};
}


void handleAlbatrossTaxi(Game* game){
	Vector2 safeZone = findSafeZone(game->collisionMap, game->mapSize);
	if(safeZone.x == POSITION_NULL) return; //handle situation when safe zone is not found
	Vector2 playerSpriteSize = getSpriteSize(game->player);
	removeEntityFromCollisionMap(game->player, game->collisionMap, game->mapSize);
	
	int posOffset = (game->albatross->spriteSizes[SPRITE_RIGHT].y - playerSpriteSize.y)/2;

	game->albatross->position = (Vector2){game->player->position.y - posOffset, 0};
	moveAlbatross(game, game->albatross, (Vector2){POSITION_NULL, POSITION_NULL});

	Vector2 newPlayerPosition;
	newPlayerPosition.y = safeZone.y + DEFAULT_SAFE_ZONE_RADIUS - (playerSpriteSize.y)/2;
	newPlayerPosition.x = safeZone.x + DEFAULT_SAFE_ZONE_RADIUS - (playerSpriteSize.x)/2;

	game->albatross->position = (Vector2){newPlayerPosition.y - posOffset, 0};
	moveAlbatross(game, game->albatross, newPlayerPosition);

	game->speed = 1;
}