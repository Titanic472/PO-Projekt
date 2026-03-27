#include <unistd.h>     // Unix standard (usleep for timing)
#include <ncurses.h>    // Text-based UI library
#include <locale.h>
#include <time.h>
#include "structures.h"
#include "moveHandler.h"
#include "entityManager.h"
#include "init.h"
#include "inputHandler.h"


void mainloop(Game *game){
	drawWindows(game);
	resetMaps(game);
	// Main game loop
	int ch = 0;
	while(!game->isGameOver && ch != QUIT){
		ch = getch();

		handleInput(ch, game);

		handleMove(game);

		spawnEntities(game);
		
        drawGame(game, true);
		if(game->player->abilityCooldown>0) --game->player->abilityCooldown;
		usleep(TICK_RATE/(game->speed));
		game->timePassed = MIN((int)(time(NULL) - game->startTime), game->levelTime);
		++game->ticksPassed;
		if(game->player->health <= 0 || (game->levelTime - game->timePassed) <= 0 || game->score >= game->targetScore) game->isGameOver = true;
	}
	if(game->isGameOver){
		if(game->player->health <= 0 || game->score < game->targetScore){
			defeatScreen(game);
		}
		else{
			winScreen(game);
		}
	}

	clearStructures(game);

	endwin();
}


int main(){
	setlocale(LC_ALL, "");
	Game game;
	
	if(!initCurses(&game)){
		endwin();
		fprintf(stderr, "Failed to initialize ncurses. Probably terminal size is smaller than minimum size\n");
		return EXIT_FAILURE;
	}
	else{
		if(!mainMenu(&game)) {
			endwin();
			return 0; //main menu returns true if player started game
		}
		startScreen(&game);
		
	}

	if(!initGame(&game)){
		endwin();
		fprintf(stderr, "Failed to initialize the game.\n");
		return EXIT_FAILURE;
	}
	timeout(10); // Non-blocking input
	mainloop(&game);

	return 0;
}