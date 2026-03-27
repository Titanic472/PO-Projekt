#include "moveHandler.h"


void modifyMomentum(Vector2f *momentum, float speedMod){
	momentum->x *= speedMod;
	momentum->y *= speedMod;
}


void setMomentum(Entity *entity, Vector2f momentum, float speedMod){
	modifyMomentum(&momentum, speedMod);
	entity->momentum = momentum;
	entity->excessMomentum = (Vector2f){0,0};
}


void moveEntity(Entity *entity){
	entity->position.y += (int)entity->momentum.y + (int)entity->excessMomentum.y;
	entity->position.x += (int)entity->momentum.x + (int)entity->excessMomentum.x;
	entity->excessMomentum.y += entity->momentum.y - (int)entity->momentum.y - (int)entity->excessMomentum.y;
	entity->excessMomentum.x += entity->momentum.x - (int)entity->momentum.x - (int)entity->excessMomentum.x;
}


void handlePlayerMove(Game *game){
    removeEntityFromCollisionMap(game->player, game->collisionMap, game->mapSize);
	int collision = checkCollision(game->player, game->collisionMap, game->mapSize, 1);
	bool move = true;
	if(collision != COLLIDER_NONE){
		move = handlePlayerCollision(game, game->player, collision);
	}
	if(move) moveEntity(game->player);
	writeCollision(game->player, game->collisionMap, game->mapSize, COLLIDER_PLAYER);
}


void randomizeMomentum(Game *game, Entity *star){
	if(star->excessMomentum.x!=0){
		if(rand() % STAR_RANDOM_OFFSET == 0 && star->position.x < game->mapSize.x-1){
			star->momentum.x = star->baseSpeed;
		}
		else if(rand() % STAR_RANDOM_OFFSET == 0 && star->position.x > 0){
			star->momentum.x = -star->baseSpeed;
		}
		else star->momentum.x = 0;
	}
}


void handleStarMove(Game *game, Entity *star, int starID){
	randomizeMomentum(game, star);
	bool isAlive = true;

	removeEntityFromCollisionMap(star, game->collisionMap, game->mapSize);
	int collision = checkCollision(star, game->collisionMap, game->mapSize, 0);
	if(collision == COLLIDER_PLAYER){
		handleStarCollision(game, star, collision, starID, &isAlive);//handle collision removes star and increases score
		return;
	}
	collision = checkCollision(star, game->collisionMap, game->mapSize, 1);
	bool move = true;
	if(collision != COLLIDER_NONE){
		move = handleStarCollision(game, star, collision, starID, &isAlive);
	}
	if(move) {//move is also false when star is removed
		moveEntity(star);
	}
	if(isAlive) writeCollision(star, game->collisionMap, game->mapSize, COLLIDER_STAR);
}


bool handleDashAbility(Game *game, Entity *hunter){
	if(hunter->abilityCooldown == -1){
		float speedMod = hunter->maxSpeed / hunter->baseSpeed;

		modifyMomentum(&hunter->momentum, speedMod);

		for(int i = 1; i <= HUNTER_DASH_DURATION; ++i){
			if(checkCollision(hunter, game->collisionMap, game->mapSize, i) == COLLIDER_PLAYER){
				hunter->abilityCooldown = HUNTER_DASH_DURATION + 1 + HUNTER_DASH_WAIT_BEFORE_START;
				return false;
			}
		}
		modifyMomentum(&hunter->momentum, 1/speedMod);
		return true;
	}
	else if(hunter->abilityCooldown == 0){
		float speedMod = hunter->baseSpeed / hunter->maxSpeed;

		modifyMomentum(&hunter->momentum, speedMod);
		hunter->abilityCooldown = -1;//set cooldown to "ability can be used again"
		return false;
	}
	else{
		hunter->abilityCooldown -= 1;
		if(hunter->abilityCooldown <= HUNTER_DASH_DURATION + 1) return true;
		else return false;
	}
}


void handleHunterMove(Game *game, Entity *hunter, int hunterID){
	bool isAlive = true;

	removeEntityFromCollisionMap(hunter, game->collisionMap, game->mapSize);
	int collision = checkCollision(hunter, game->collisionMap, game->mapSize, 0);
	if(collision == COLLIDER_PLAYER){
		handleHunterCollision(game, hunter, collision, hunterID, &isAlive);
		return;
	}
	collision = checkCollision(hunter, game->collisionMap, game->mapSize, 1);
	bool move = true;
	if(collision != COLLIDER_NONE){
		move = handleHunterCollision(game, hunter, collision, hunterID, &isAlive);
	}
	else{
		move = handleDashAbility(game, hunter);
	}
	if(move) {//move is also false when hunter is removed
		moveEntity(hunter);
	}
	if(isAlive) writeCollision(hunter, game->collisionMap, game->mapSize, COLLIDER_HUNTER);
}


void handleMove(Game *game){
	
	//player move
	handlePlayerMove(game);

	//stars move
	for(int i = 0; i<game->currentStars; ++i){
		handleStarMove(game, game->stars[i], i);
	}

	//enemy move
	for(int i = 0; i<game->currentHunters; ++i){
		handleHunterMove(game, game->hunters[i], i);
	}
}