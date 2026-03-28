#include "entityManager.h"


void loadSpriteSizes(Entity *entity, char* fileName, char* fileKey, char* subCat){
	loadEntry(&entity->spriteSizes[SPRITE_RIGHT].x, fileName, "sprite_right_x", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_RIGHT].y, fileName, "sprite_right_y", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_LEFT].x, fileName, "sprite_left_x", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_LEFT].y, fileName, "sprite_left_y", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_UP].x, fileName, "sprite_up_x", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_UP].y, fileName, "sprite_up_y", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_DOWN].x, fileName, "sprite_down_x", fileKey, subCat);
	loadEntry(&entity->spriteSizes[SPRITE_DOWN].y, fileName, "sprite_down_y", fileKey, subCat);
}


void loadAnimationSprites(Entity *entity, char* fileName, char* baseKey, char* fileKey, char* subCat, int index){
	char buf[LINE_MAX_SIZE];
	entity->sprites[index] = malloc(sizeof(char**)*entity->animationFrames);
	for(int i = 0; i < entity->animationFrames; ++i){
		if(i == 0){
			loadEntry(&entity->sprites[index][i], fileName, baseKey, fileKey, subCat);
		}
		else{
			snprintf(buf, sizeof(buf), "%s_%d", baseKey, i);
			loadEntry(&entity->sprites[index][i], fileName, buf, fileKey, subCat);
		}
		
	}
}

void loadSprites(Entity *entity, char* fileName, char* fileKey, char* subCat){//to do with many sprites later
	loadEntry(&entity->animationFrames, fileName, "animationFrames", fileKey, subCat);

	loadAnimationSprites(entity, fileName, "sprite_right", fileKey, subCat, SPRITE_RIGHT);
	loadAnimationSprites(entity, fileName, "sprite_left", fileKey, subCat, SPRITE_LEFT);
	loadAnimationSprites(entity, fileName, "sprite_up", fileKey, subCat, SPRITE_UP);
	loadAnimationSprites(entity, fileName, "sprite_down", fileKey, subCat, SPRITE_DOWN);

	entity->currFrame = 0;

	// loadEntry(&entity->sprites[SPRITE_RIGHT], fileName, "sprite_right", fileKey, subCat);
	// loadEntry(&entity->sprites[SPRITE_LEFT], fileName, "sprite_left", fileKey, subCat);
	// loadEntry(&entity->sprites[SPRITE_UP], fileName, "sprite_up", fileKey, subCat);
	// loadEntry(&entity->sprites[SPRITE_DOWN], fileName, "sprite_down", fileKey, subCat);
}


void loadColor(Entity *entity, char* fileName, char* fileKey, char* subCat){
	char* colorName;
	loadEntry(&colorName, fileName, "color", fileKey, subCat);
	if(strcmp(colorName, "YELLOW") == 0){
		entity->color = YELLOW;
	}
	else if(strcmp(colorName, "GRAY") == 0){
		entity->color = GRAY;
	}
	else if(strcmp(colorName, "RED") == 0){
		entity->color = RED;
	}
	else if(strcmp(colorName, "MAGENTA") == 0){
		entity->color = MAGENTA;
	}
	else if(strcmp(colorName, "BLUE") == 0){
		entity->color = BLUE;
	}
	else if(strcmp(colorName, "GREEN") == 0){
		entity->color = GREEN;
	}
	else{
		entity->color = WHITE;
	}

	free(colorName);
}


void loadEntity(Entity *entity, char* fileName, char* fileKey, bool oneFromMany){
	char subcategory[32];
	if(oneFromMany){
		
		int count;
		loadEntry(&count, fileName, "count", fileKey, "");
		if(count <= 0){
			fprintf(stderr, "ENTITY COUNT ERROR INT MULTIPLE LOAD: %d ENTITIES", count);
			return;
		}
		snprintf(subcategory, sizeof(subcategory), "%d", rand() % count + 1);
		
	}
	else{
		subcategory[0] = '\0';
	}
	
	loadEntry(&entity->health, fileName, "health", fileKey, subcategory);
	loadEntry(&entity->baseSpeed, fileName, "baseSpeed", fileKey, subcategory);
	loadEntry(&entity->maxSpeed, fileName, "maxSpeed", fileKey, subcategory);
	entity->baseHealth = entity->health;

	loadSpriteSizes(entity, fileName, fileKey, subcategory);

	loadSprites(entity, fileName, fileKey, subcategory);

	loadColor(entity, fileName, fileKey, subcategory);
}


void createStar(Game *game){
	game->currentStars += 1;
	game->stars = (Entity**)realloc(game->stars, sizeof(Entity*) * (game->currentStars));
	game->stars[game->currentStars - 1] = malloc(sizeof(Entity));
	Entity *newStar = game->stars[game->currentStars - 1];
	
	newStar->position = (Vector2){0, rand() % game->mapSize.x};
	newStar->momentum = (Vector2f){-newStar->baseSpeed, 0};
	newStar->collider = COLLIDER_STAR;

	loadEntity(newStar, game->levelName, "star", false);
}


//Range end is biggest value, start is the smallest value of possible diagonal movement range within given distance
void castMaxDiagonalBounds(Vector2 position, Vector2 *pos){
	int x = pos->x;
	int diff = abs(position.x - x);
	Range posBounds = (Range){position.y - diff, position.y + diff};
	if(posBounds.end < pos->y) pos->y = posBounds.end;
	if(posBounds.start > pos->y) pos->y = posBounds.start;
}


bool createHunter(Game *game){
	game->currentHunters += 1;
	game->hunters = (Entity**)realloc(game->hunters, sizeof(Entity*) * (game->currentHunters));
	game->hunters[game->currentHunters - 1] = malloc(sizeof(Entity));
	Entity *newHunter = game->hunters[game->currentHunters - 1];

	loadEntity(newHunter, game->levelName, "hunters", true);
	newHunter->health = MIN(HUNTER_MAX_HEALTH, (int)(game->timePassed * game->hunterLifeIncrease) + newHunter->health);

	int dir = rand() % 2;//0 - left, 1 - right

	Vector2 pos;

	newHunter->momentum.x = newHunter->baseSpeed;
	if(dir == 0){
		pos.y = rand() % (game->mapSize.y - newHunter->spriteSizes[SPRITE_LEFT].y);
		pos.x = game->mapSize.x - newHunter->spriteSizes[SPRITE_LEFT].x;
		newHunter->momentum.x *= -1;
	}
	else{
		pos.y = rand() % (game->mapSize.y - newHunter->spriteSizes[SPRITE_RIGHT].y);
		pos.x = 0;
	}
	
	castMaxDiagonalBounds(game->player->position, &pos);

	//normalize position for max diagonal movement
	newHunter->position = pos;
	newHunter->momentum.y = (float)(game->player->position.y - pos.y)/abs(game->player->position.x - pos.x);
	
	newHunter->collider = COLLIDER_HUNTER;
	newHunter->abilityCooldown = -1;

	return true;
}


void spawnEntities(Game *game){
	if(rand()%game->starSpawnChance == 0){
		createStar(game);
	}
	if(rand()%game->hunterSpawnChance == 0 && game->maxHunters + (int)(game->timePassed * game->hunterCountIncrease) > game->currentHunters){
		createHunter(game);
	}
}