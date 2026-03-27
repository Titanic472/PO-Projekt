#include "collisionHandler.h"

void reflectX(Entity *entity){
	entity->momentum.x *= -1;
	entity->excessMomentum.x *= -1;
}


void reflectY(Entity *entity){
	entity->momentum.y *= -1;
	entity->excessMomentum.y *= -1;
}


void bounce(Game *game, Entity *entity){
	Vector2 entitySpriteSize = getSpriteSize(entity);
	if(entity->position.x - (int)MAX(entity->momentum.x-1, 1) <= 0 || entity->position.x + entitySpriteSize.x + (int)MAX(entity->momentum.x-1, 1) >= game->mapSize.x){
		reflectX(entity);
	}
	if(entity->position.y - (int)MAX(entity->momentum.y-1, 1) <= 0 || entity->position.y + entitySpriteSize.y + (int)MAX(entity->momentum.y-1, 1) >= game->mapSize.y){
		reflectY(entity);
	}
}


Vector2 getMovementOffset(Entity *entity, int offsetMultiplier){
	Vector2 offset;

	if(offsetMultiplier == 0){
		offset = (Vector2){0,0};
	}
	else{
		offset.y = (int)entity->momentum.y*offsetMultiplier + (int)entity->excessMomentum.y;
		offset.x = (int)entity->momentum.x*offsetMultiplier + (int)entity->excessMomentum.x;
	}	

	return offset;
}


int checkCollision(Entity *entity, int **collisionMap, Vector2 mapSize, int offsetMultiplier){
	Vector2 offset = getMovementOffset(entity, offsetMultiplier);

	Vector2 entitySpriteSize = getSpriteSize(entity);
	int collision = COLLIDER_NONE;

	for(int y = entity->position.y + offset.y; y < entity->position.y + entitySpriteSize.y + offset.y; ++y){
		for(int x = entity->position.x + offset.x; x < entity->position.x + entitySpriteSize.x + offset.x; ++x){
			if(y >= mapSize.y || y < 0 || x >= mapSize.x || x < 0){
				collision = COLLIDER_WALL;
				return collision;
			}

			if(collisionMap[y][x] != COLLIDER_NONE){
				collision = collisionMap[y][x];
				continue;
			}
		}	
	}
	return collision;
}


bool handlePlayerCollision(Game *game, Entity *player, int collisionType){
	if(collisionType == COLLIDER_WALL) {//skip move when touching wall
		bounce(game, player);
		return false; 
	}
	if(collisionType == COLLIDER_STAR) { //star side handles collision with player
		return true;
	}
	if(collisionType == COLLIDER_HUNTER){ //hunter side handles collision with player
		return true;
	}

	return false;//undefined case
}


bool handleStarCollision(Game *game, Entity *star, int collisionType, int starID, bool* isAlive){
	if(collisionType==COLLIDER_WALL) {
		removeStar(game, starID);
		*isAlive = false;
		return false; // delete star when touching the wall
	}
	if(collisionType == COLLIDER_PLAYER){
		collectStar(game, starID);
		*isAlive = false;
		return false;
	}
	if(collisionType == COLLIDER_HUNTER){
		return true;
	}

	return false;//undefined case
}


bool handleHunterCollision(Game *game, Entity *hunter, int collisionType, int hunterID, bool* isAlive){
	if(collisionType == COLLIDER_WALL) {
		hunter->health -= 1;
		if(hunter->health==0){
			removeHunter(game, hunterID);
			*isAlive = false;
			return false;
		}
		else{
			bounce(game, hunter);
		}	
		return false;
	}
	if(collisionType == COLLIDER_PLAYER){
		game->player->health -= game->hunterDamagePerLife * hunter->health;
		removeHunter(game, hunterID);
		*isAlive = false;
		return false;
	}
	if(collisionType == COLLIDER_HUNTER){
		hunter->health -= 1;
		if(hunter->health==0){
			removeHunter(game, hunterID);
			*isAlive = false;
			return false;
		}
		else{
			reflectX(hunter);
		}
		return false;
	}
	if(collisionType == COLLIDER_STAR){
		return true;
	}

	return false;//undefined case
}


void writeCollision(Entity *entity, int **collisionMap, Vector2 mapSize, int colliderID){
	Vector2 entitySpriteSize = getSpriteSize(entity);

	for(int y = entity->position.y; y < entity->position.y + entitySpriteSize.y; ++y){
		for(int x = entity->position.x; x < entity->position.x + entitySpriteSize.x; ++x){
			if(y >= mapSize.y || y < 0 || x >= mapSize.x || x < 0){
				fprintf(stderr, "Error: WRITING COLLISION OUT OF BOUNDS!!! x:%d y:%d\n", x, y);
				usleep(10000000);
				continue; 
			}

			collisionMap[y][x] = colliderID;
		}	
	}
}


void removeEntityFromCollisionMap(Entity *entity, int **collisionMap, Vector2 mapSize){
	Vector2 entitySpriteSize = getSpriteSize(entity);

	for(int y = entity->position.y; y < entity->position.y + entitySpriteSize.y; ++y){
		for(int x = entity->position.x; x < entity->position.x + entitySpriteSize.x; ++x){
			if(y >= mapSize.y || y < 0 || x >= mapSize.x || x < 0){
				fprintf(stderr, "Error: REMOVING COLLISION OUT OF BOUNDS!!! x:%d y:%d maxx:%d maxy:%d\n", x, y, mapSize.x, mapSize.y);
				usleep(10000000);
				continue; 
			}
			if(collisionMap[y][x] == entity->collider) collisionMap[y][x] = COLLIDER_NONE;
		}	
	}
}