#include "inputHandler.h"

//Move input functions
bool isMoveInput(char ch){
	if(ch==CONTROL_RIGHT) return true;
	else if(ch==CONTROL_LEFT) return true;
	else if(ch==CONTROL_UP) return true;
	else if(ch==CONTROL_DOWN) return true;
	else return false;
}


Vector2f toMoveInput(char ch){
	Vector2f momentum = {0,0};
	if(ch==CONTROL_RIGHT) momentum.x = 1;
	else if(ch==CONTROL_LEFT) momentum.x = -1;
	else if(ch==CONTROL_UP) momentum.y = -1;
	else if(ch==CONTROL_DOWN) momentum.y = 1;
	return momentum;
}


void handleInput(char ch, Game *game){
	if(isMoveInput(ch)){
		setMomentum(game->player, toMoveInput(ch), game->player->baseSpeed);
	}

	if(isNumber(ch)){
		setGameSpeed(game, ch - CH_LOWESTNUMBER);
	}

	if(ch == CONTROL_DASH && game->player->abilityCooldown == 0){//directional speed boost
		float speedMod = game->player->maxSpeed / game->player->baseSpeed;
		setMomentum(game->player, game->player->momentum, speedMod);
		game->player->abilityCooldown = game->screen.x/game->player->maxSpeed;//ensures only one use per every direction
	}

	if(ch == CONTROL_ALBATROSS){
		handleAlbatrossTaxi(game);
	}
}