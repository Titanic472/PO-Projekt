#include "functions.h"

//all input handler functions are located in this functions file 
int getDirectionSpriteID(Vector2f momentum){
	if(momentum.x>0) return SPRITE_RIGHT;
	else if(momentum.x<0) return SPRITE_LEFT;
	else if(momentum.y<0) return SPRITE_UP;
	else return SPRITE_DOWN;
}


Vector2 getSpriteSize(Entity *entity){
	int moveDirection = getDirectionSpriteID(entity->momentum);
	return (Vector2){entity->spriteSizes[moveDirection].y, entity->spriteSizes[moveDirection].x};
}


Vector2 getSpriteCenterPosition(Entity *entity){
	Vector2 sizes = getSpriteSize(entity);
	return (Vector2){entity->position.y + sizes.y/2, entity->position.x + sizes.x/2}; 
}


bool isNumber(char ch){
	if(ch >= CH_LOWESTNUMBER && ch <= CH_HIGHESTNUMBER) return true;
	return false;
}


void setGameSpeed(Game *game, int speed){
	game->speed = speed + 1;
}


void removeEntity(Entity *entity){
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < entity->animationFrames; ++j){
			free(entity->sprites[i][j]);
		}
		free(entity->sprites[i]);
	}
	free(entity);
}


void rearrangeEntityArray(Entity *array[], int arraySize, int start){
	for(int i = start; i<arraySize - 1; ++i){
		array[i] = array[i+1];
	}
}


void removeStar(Game *game, int starID){//merge later
	removeEntity(game->stars[starID]);
	rearrangeEntityArray(game->stars, game->currentStars, starID);
	game->currentStars -= 1;
	game->stars = (Entity**)realloc(game->stars, sizeof(Entity*) * (game->currentStars));
}


void removeHunter(Game *game, int hunterID){//merge later
	removeEntity(game->hunters[hunterID]);
	rearrangeEntityArray(game->hunters, game->currentHunters, hunterID);
	game->currentHunters -= 1;
	game->hunters = (Entity**)realloc(game->hunters, sizeof(Entity*) * (game->currentHunters));
}


void clearStructures(Game *game){
	removeEntity(game->player);
	removeEntity(game->albatross);
	freeMaps(game);
	for(int i = 0; i<game->currentStars; ++i){
		removeEntity(game->stars[i]);
	}
	for(int i = 0; i<game->currentHunters; ++i){
		removeEntity(game->hunters[i]);
	}
	free(game->stars);
	free(game->hunters);
}


void collectStar(Game *game, int starID){
	game->score += 1;
	removeStar(game, starID);
}


ScoreWeights loadScoreWeights(Game *game){
	ScoreWeights weights;
	loadEntry(&weights.pointsPerHealth, game->levelName, "pointsPerHealth", "scoreWeights", "");
	loadEntry(&weights.pointsPerTime, game->levelName, "pointsPerTime", "scoreWeights", "");
	loadEntry(&weights.pointsPerScore, game->levelName, "pointsPerScore", "scoreWeights", "");
	return weights;
}


int calculateScore(Game *game, bool isDefeat){
	ScoreWeights weights = loadScoreWeights(game);
	int score = 0;
	if(isDefeat){
		score = game->score * weights.pointsPerScore / game->targetScore;
		score = score*(float)((game->maxHunters + game->hunterCountIncrease*game->timePassed)/HUNTERS_PER_SCORE_MULTIPLIER);
	}
	else{
		int timeLeft = game->levelTime - game->timePassed;
		score += weights.pointsPerScore;
		score += game->player->health * weights.pointsPerHealth / game->player->baseHealth;
		score += timeLeft * weights.pointsPerTime / game->levelTime;
		score = score*(float)((game->maxHunters + game->hunterCountIncrease*game->levelTime)/HUNTERS_PER_SCORE_MULTIPLIER);
	}
	score = (float)score*HUNTERS_SPAWN_PER_SCORE_MULTIPLIER/game->hunterSpawnChance;
	return score;
}