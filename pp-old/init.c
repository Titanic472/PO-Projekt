#include "init.h"

void initPlayer(Game *game, Entity *player, char* file){
	if (player == NULL) {
        fprintf(stderr, "Error: player is not allocated!\n");
		usleep(1000000);
    }

	loadEntity(player, file, "player", false);

	player->position.y = 2;
	player->position.x = game->screen.x/2;
	setMomentum(player, (Vector2f){1,0}, player->baseSpeed);
	
	player->collider = COLLIDER_PLAYER;
	player->abilityCooldown = 10;
}


bool screnSizeLoad(Game *game, char* file, char *category){
	Vector2 screenSize;
	loadEntry(&screenSize.y, file, "screenY", category, "");
	loadEntry(&screenSize.x, file, "screenX", category, "");
	if(screenSize.y != 0 && screenSize.x != 0){
		if(screenSize.y< MIN_SCREEN_HEIGHT || screenSize.x < MIN_SCREEN_WIDTH){
			fprintf(stderr, "Configured screen size is smaller than preferred min:%d x %d current:%d x %d\n", MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT, screenSize.x, screenSize.y);
			usleep(10000000);
			return false;
		}
		else{
			while(game->screen.y < screenSize.y || game->screen.x < screenSize.x){
				clear();
				mvwprintw(stdscr, 0, 0, "Current terminal size is too small!");
				mvwprintw(stdscr, 1, 0, "Current size: %d rows and %d columns", game->screen.y, game->screen.x);
				mvwprintw(stdscr, 2, 0, "Resize to at least %d x %d", screenSize.y, screenSize.x);
				refresh();
				usleep(1000000);
				getmaxyx(stdscr,game->screen.y,game->screen.x);
			}
		}
		game->screen = screenSize;
	}
	clear();
	return true;
}

bool loadGameData(Game *game, char* file, char *category){

    loadEntry(&game->targetScore, file, "targetScore", category, "");
	loadEntry(&game->levelTime, file, "time", category, "");

    loadEntry(&game->hunterSpawnChance, file, "hunterSpawnChance", category, "");
	loadEntry(&game->maxHunters, file, "maxHunterCount", category, "");
	loadEntry(&game->hunterLifeIncrease, file, "hunterLifeIncrease", category, "");
	loadEntry(&game->hunterCountIncrease, file, "hunterCountIncrease", category, "");
	loadEntry(&game->hunterDamagePerLife, file, "hunterDamagePerLife", category, "");

    loadEntry(&game->starSpawnChance, file, "starSpawnChance", category, "");

	loadEntry(&game->fogStart, file, "fogStart", category, "");
	loadEntry(&game->fogSpreadRate, file, "fogSpreadRate", category, "");
	loadEntry(&game->fogFOV, file, "fogFOV", category, "");

    int seed;
    loadEntry(&seed, file, "seed", category, "");
    if(seed == 0) srand(time(NULL));
    else srand(seed);
	return screnSizeLoad(game, file, category);
}


bool initGame(Game *game){
    if(!loadGameData(game, game->levelName, "game")) return false;
	game->score = 0;
	
	game->speed = 1;
	game->isGameOver = false;

	game->mainGameWindow = NULL;
    game->statusWindow = NULL;
	game->healthWindow = NULL;
	game->timeWindow = NULL;
	game->mainGameWindowContent = NULL;

	game->player = malloc(sizeof(Entity));
	game->albatross = malloc(sizeof(Entity));

	game->currentStars = 0;

	game->currentHunters = 0;

	game->startTime = time(NULL);
	game->ticksPassed = 0;

	initPlayer(game, game->player, game->levelName);
	loadAlbatross(game, game->albatross);
	return true;
}

bool initCurses(Game *game){
	initscr();// Start curses mode
	//keypad(stdscr, TRUE);//for arrow keys
	cbreak(); // Disable line buffering
	curs_set(FALSE);
	getmaxyx(stdscr,game->screen.y,game->screen.x);
	if(game->screen.y< MIN_SCREEN_HEIGHT || game->screen.x < MIN_SCREEN_WIDTH){
		fprintf(stderr, "screen height is smaller than preferred min:%d current:%d\n", MIN_SCREEN_HEIGHT, game->screen.y);
		return false;
	}

	start_color();
	init_pair(GRAY, 8, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(FOG, 15, COLOR_WHITE);
	return true;
}