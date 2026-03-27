#include "interface.h"

void createWindow(WINDOW **win, int height, int width, int starty, int startx){
	*win = newwin(height, width, starty, startx);
	box(*win, 0 , 0);
	wrefresh(*win);
}


void putTextAtCenter(WINDOW *win, int offsetY, const char *text){
	int len = strlen(text);
	mvwprintw(win, getmaxy(win)/2 + offsetY, (getmaxx(win) - len) / 2, "%s", text);
}


void drawStatusWindows(Game *game){
	if(game->statusWindow == NULL){
		createWindow(&game->statusWindow, MIN_STATUS_SIZE, 
					game->screen.x/3 - HORIZONTAL_MARGIN*2, getmaxy(game->mainGameWindow)+VERTICAL_MARGIN, HORIZONTAL_MARGIN);
	}
	else{
		box(game->statusWindow, 0 , 0);
		wrefresh(game->statusWindow);
	}

	if(game->healthWindow == NULL){
		createWindow(&game->healthWindow, MIN_STATUS_SIZE, 
					game->screen.x/3 - HORIZONTAL_MARGIN*2, getmaxy(game->mainGameWindow)+VERTICAL_MARGIN, HORIZONTAL_MARGIN + game->screen.x/3.0);
	}
	else{
		box(game->healthWindow, 0 , 0);
		wrefresh(game->healthWindow);
	}

	if(game->timeWindow == NULL){
		createWindow(&game->timeWindow, MIN_STATUS_SIZE, 
					game->screen.x/3 - HORIZONTAL_MARGIN*2, getmaxy(game->mainGameWindow)+VERTICAL_MARGIN, HORIZONTAL_MARGIN + game->screen.x/3.0*2);
	}
	else{
		box(game->timeWindow, 0 , 0);
		wrefresh(game->timeWindow);
	}
}


void drawWindows(Game *game){
	if(game->mainGameWindow == NULL){
		createWindow(&game->mainGameWindow, game->screen.y - VERTICAL_MARGIN - MIN_STATUS_SIZE, game->screen.x - HORIZONTAL_MARGIN*2, VERTICAL_MARGIN, HORIZONTAL_MARGIN);
	}
	else{
		//if(game->ticksPassed <= 1){//to enable other render type uncomment this if :)
		box(game->mainGameWindow, 0 , 0);
		wrefresh(game->mainGameWindow);
		//}
	}

    if(game->mainGameWindowContent == NULL){
		createWindow(&game->mainGameWindowContent, game->screen.y - VERTICAL_MARGIN - MIN_STATUS_SIZE-2, game->screen.x - HORIZONTAL_MARGIN*2 - 2, VERTICAL_MARGIN+1, HORIZONTAL_MARGIN+1);
	}
	else{
		wrefresh(game->mainGameWindowContent);
	}

	drawStatusWindows(game);
}


void drawEntity(Entity *entity, WINDOW * window, Vector2 mapSize){
	if (entity == NULL) {
        fprintf(stderr, "Error: trying to draw Empty Entity!!!\n");
        return;
    }
	if(entity->position.x >= mapSize.x || entity->position.y >= mapSize.y) return; //if entity is fully out of bounds it won't be drawn
	 

	int moveDirection = getDirectionSpriteID(entity->momentum), pos = 0;
	for(int y = entity->position.y; y < entity->position.y + entity->spriteSizes[moveDirection].y; ++y){
		for(int x = entity->position.x; x < entity->position.x + entity->spriteSizes[moveDirection].x; ++x, ++pos){
			if(y >= mapSize.y || y < 0 || x >= mapSize.x || x < 0) continue; // handle drawing entities that are partially out of bounds
			if(entity->sprites[moveDirection][entity->currFrame][pos] == ' ') continue; //don't draw empty spaces
			if(entity->sprites[moveDirection][entity->currFrame][pos] == 'H'){//'H' is used as place to display health 
				mvwprintw(window, y, x, "%c", MIN(entity->health, HUNTER_MAX_HEALTH) + '0');
				//mvwprintw(window, y, x, "%c", entity->position.y%10 + '0');//for location debug
			}
			else{
				mvwprintw(window, y, x, "%c",entity->sprites[moveDirection][entity->currFrame][pos]);
			}
		}	
	}	
}


void drawHealthBar(Game *game){
	char buf[64];

	char healthBar[13];
	healthBar[0] = '[';
	for(int i = 1; i<11; ++i){
		if(((float)game->player->health/game->player->baseHealth)*HEALTHBAR_SIZE + 1 > i) healthBar[i] = '#';//edit
		else healthBar[i] = ' ';
	}
	healthBar[11] = ']';
	healthBar[12] = '\0';
	wattron(game->healthWindow, COLOR_PAIR(RED));
	snprintf(buf, sizeof(buf), "%s", healthBar);
	putTextAtCenter(game->healthWindow, 0, buf);
	wattroff(game->healthWindow, COLOR_PAIR(RED));

	snprintf(buf, sizeof(buf), "HEALTH:");
    putTextAtCenter(game->healthWindow, -1, buf);
}


void drawStatus(Game *game){
	char buf[64];

	snprintf(buf, sizeof(buf), "PLAYER: %s\n ", game->playerName);
    putTextAtCenter(game->statusWindow, -1, buf);

	snprintf(buf, sizeof(buf), "STARS: %d/%d", game->score, game->targetScore);
	putTextAtCenter(game->statusWindow, 1, buf);

	werase(game->timeWindow);
	snprintf(buf, sizeof(buf), "TIME: %d\n ", game->levelTime - (int)(time(NULL) - game->startTime));
    putTextAtCenter(game->timeWindow, 1, buf);

	snprintf(buf, sizeof(buf), "LEVEL: %d", game->level);
    putTextAtCenter(game->timeWindow, -1, buf);

	werase(game->healthWindow);
	snprintf(buf, sizeof(buf), "ABILITY COOLDOWN: %d\n ", game->player->abilityCooldown);
    putTextAtCenter(game->healthWindow, 1, buf);

	drawHealthBar(game);
}


void nextAnimationFrame(Entity *entity){
	entity->currFrame = (entity->currFrame + 1)%entity->animationFrames;
}

void drawPlayer(Game *game, bool animate){
	if(animate) nextAnimationFrame(game->player);
	wattron(game->mainGameWindowContent, COLOR_PAIR(game->player->color));
	drawEntity(game->player, game->mainGameWindowContent, game->mapSize);
	wattroff(game->mainGameWindowContent, COLOR_PAIR(game->player->color));
}


void drawStars(Game *game, bool animate){
	for(int i = 0; i<game->currentStars; ++i){
		if(game->stars[i] == NULL){
			fprintf(stderr, "NULL Star Entity: i:%d maxEntities:%d", i, game->currentStars);
			usleep(10000000);
			continue;
		}
		if(animate) nextAnimationFrame(game->stars[i]);
		wattron(game->mainGameWindowContent, COLOR_PAIR(game->stars[i]->color));
		drawEntity(game->stars[i], game->mainGameWindowContent, game->mapSize);
		wattroff(game->mainGameWindowContent, COLOR_PAIR(game->stars[i]->color));
	}
}


void drawHunters(Game *game, bool animate){
	for(int i = 0; i<game->currentHunters; ++i){
		if(game->hunters[i] == NULL){
			fprintf(stderr, "NULL Hunter Entity: i:%d maxEntities:%d", i, game->currentHunters);
			usleep(10000000);
			continue;
		}
		if(animate) nextAnimationFrame(game->hunters[i]);
		wattron(game->mainGameWindowContent, COLOR_PAIR(game->hunters[i]->color));
		drawEntity(game->hunters[i], game->mainGameWindowContent, game->mapSize);
		wattroff(game->mainGameWindowContent, COLOR_PAIR(game->hunters[i]->color));
	}
}


bool checkFogSpawnCondition(Game *game, Vector2 position, int fogDistance){
	Vector2 playerPosCenter = getSpriteCenterPosition(game->player);
	Vector2 albatrossPosCenter = getSpriteCenterPosition(game->albatross);
	bool condition = abs(position.x - playerPosCenter.x)/2 >= fogDistance || abs(position.y - playerPosCenter.y) >= fogDistance;
	condition = condition  || (playerPosCenter.x >= game->mapSize.x || playerPosCenter.y >= game->mapSize.y);
	bool condition2 = (abs(position.x - albatrossPosCenter.x)/2 >= fogDistance || abs(position.y - albatrossPosCenter.y) >= fogDistance);
	condition2 = condition2 || (albatrossPosCenter.x >= game->mapSize.x || albatrossPosCenter.y >= game->mapSize.y);
	
	return condition && condition2;
}


void drawAlbatross(Game *game){
	nextAnimationFrame(game->albatross);
	drawEntity(game->albatross, game->mainGameWindowContent, game->mapSize);
}

void drawFog(Game *game){
	if(game->ticksPassed < game->fogStart || game->fogStart <= -1) return;
	int far = MAX(game->mapSize.x/2, game->mapSize.y); //maximum distance for fog to start showing
	int fogDistance = MAX(game->fogFOV, far-(game->ticksPassed - game->fogStart + 1)*game->fogSpreadRate);
	wattron(game->mainGameWindowContent, COLOR_PAIR(FOG));
	for(int x = 0; x < game->mapSize.x; ++x){
		for(int y = 0; y < game->mapSize.y; ++y){
			if(checkFogSpawnCondition(game, (Vector2){y, x}, fogDistance)){
				mvwprintw(game->mainGameWindowContent, y, x, "&");
			}
		}
	}
	wattroff(game->mainGameWindowContent, COLOR_PAIR(FOG));
}


void drawGame(Game *game, bool animate){
	werase(game->mainGameWindowContent);
	drawStatus(game);
	
	drawPlayer(game, animate);
	
	drawStars(game, animate);

	drawHunters(game, animate);

	drawAlbatross(game);//albatross is always animated

	drawFog(game);
	
	//drawMap(game);
    drawWindows(game);

	//doupdate();
}


void levelSelectionScreen(Game *game){
	putTextAtCenter(stdscr, -7, "Select Level:\n");
	for(int i = 1; i <= MAX_LEVELS; ++i){
		char buf[32];
		

		snprintf(buf, sizeof(buf), "%d.lvl", i);
		if(!checkFileExists(buf)) {
			snprintf(buf, sizeof(buf), "%d. ERR NOT LOADED\n", i);
		}
		else{
			char* level_name;
			loadEntry(&level_name, buf, "name", "level", "");
			snprintf(buf, sizeof(buf), "%d. %s\n", i, level_name);
			free(level_name);
		}
		
		putTextAtCenter(stdscr, -7 + i*2, buf);
	}
	int ch = getch();
	while(!isNumber(ch)){
		ch = getch();
	}
	game->level = ch - CH_LOWESTNUMBER + 1;
	char buf[32];
	snprintf(buf, sizeof(buf), "%d.lvl", game->level);
	//copy level name to game
	strcpy(game->levelName, buf);

	clear();
}

void startScreen(Game *game){
	
	putTextAtCenter(stdscr, -1, "Type player name and click Enter to start (\", : and ; will be ignored)");
	putTextAtCenter(stdscr, 1, "Name: ");
	char ch = ' ';
	int i = 0;
	for(; i < PLAYER_NAME_MAX_LENGTH - 1 && ch != '\n'; ++i){
		ch = getch();
		if(ch == ';' || ch == ':' || ch == '"' || ch =='\n'){
			--i;
			continue;
		}
		else{
			game->playerName[i] = ch;
		}	
	}
	game->playerName[i] = '\0';
	refresh();
	clear();
	noecho(); // Don't echo input characters
	levelSelectionScreen(game);
}


void tutorial(){
	char buf[64];
	putTextAtCenter(stdscr, -7, "In every level goal is to collect stars within given time");

	putTextAtCenter(stdscr, -5, "Controls:");

	snprintf(buf, sizeof(buf), "RIGHT: %c\n ", CONTROL_RIGHT);
	putTextAtCenter(stdscr, -3, buf);
	snprintf(buf, sizeof(buf), "LEFT: %c\n ", CONTROL_LEFT);
	putTextAtCenter(stdscr, -2, buf);
	snprintf(buf, sizeof(buf), "UP: %c\n ", CONTROL_UP);
	putTextAtCenter(stdscr, -1, buf);
	snprintf(buf, sizeof(buf), "DOWN: %c\n ", CONTROL_DOWN);
	putTextAtCenter(stdscr, 0, buf);
	if(CONTROL_DASH == ' '){
		snprintf(buf, sizeof(buf), "DASH: SPACE\n ");
	}
	else{
		snprintf(buf, sizeof(buf), "DASH: %c\n ", CONTROL_DASH);
	}
	putTextAtCenter(stdscr, 1, buf);
	snprintf(buf, sizeof(buf), "ALBATROSS TAXI: %c\n ", CONTROL_ALBATROSS);
	putTextAtCenter(stdscr, 2, buf);

	putTextAtCenter(stdscr, 4, "Dash allows you to move faster, but use it wisely as it has cooldown");
	putTextAtCenter(stdscr, 6, "Albatross taxi teleports you to a safe zone, but time keeps running when it's in use");
	putTextAtCenter(stdscr, 8, "Click any button to return to menu...");
	
	getch();
	clear();
}


void drawMainMenu(){
	putTextAtCenter(stdscr, -5, "Welcome to Swallow The Stars!");
	putTextAtCenter(stdscr, -3, "Use numbers (1-3) to navidate Menu");
	putTextAtCenter(stdscr, -1, "1. Start Game");
	putTextAtCenter(stdscr, 1, "2. Tutorial");
	putTextAtCenter(stdscr, 3, "3. Quit");
}


bool mainMenu(Game *game){
	drawMainMenu();
	int ch = getch();
	if(ch == QUIT) return false;

	while(ch != '1'){
		clear();
		if(ch == '2') tutorial();
		if(ch == '3') return false;
		
		drawMainMenu();
		ch = getch();
	}

	clear();
	return true;
}


void printScores(Game *game, bool isDefeat){
	int rank[RANKINGS_PLAYER_AMOUNT];
	char players[RANKINGS_PLAYER_AMOUNT][PLAYER_NAME_MAX_LENGTH];
	char buf[64];
	int score = calculateScore(game, isDefeat);
	char* temp;
	for(int i = 0; i<RANKINGS_PLAYER_AMOUNT; ++i){
		snprintf(buf, sizeof(buf), "%d", i);
		loadEntry(&rank[i], RANKINGS_FILENAME, buf, RANKINGS_SCORES_CATEGORY, "");
		loadEntry(&temp, RANKINGS_FILENAME, buf, RANKINGS_PLAYERS_CATEGORY, "");
		strncpy(players[i], temp, sizeof(players[i]));
		free(temp);
	}
	if(score > rank[9]){
		rank[9] = score;
		strncpy(players[9], game->playerName, sizeof(players[9]));
		for(int i = RANKINGS_PLAYER_AMOUNT - 2; i>=0; --i){
			if(score > rank[i]){
				rank[i+1] = rank[i];
				rank[i] = score;
				strcpy(players[i+1], players[i]);
                strcpy(players[i], game->playerName);
			}
			else break;
		}
	}
	
	snprintf(buf, sizeof(buf), "Score: %d", score);
	putTextAtCenter(stdscr, -4, buf);

	for(int i = 0; i<RANKINGS_PLAYER_AMOUNT; ++i){
		snprintf(buf, sizeof(buf), "%s: %d", players[i], rank[i]);
		putTextAtCenter(stdscr, -2+i, buf);
	}
	exportRankData(rank, players);
}


void cinematicFade(Game *game){
	for(int k = 0; k < MIN(game->mapSize.x, game->mapSize.y)/2 + 1; ++k){
		for(int x = k; x < game->mapSize.x - k; ++x){
			mvwprintw(game->mainGameWindowContent, k, x, "#");
			mvwprintw(game->mainGameWindowContent, game->mapSize.y - k - 1, game->mapSize.x - x, "#");
			wrefresh(game->mainGameWindowContent);
			usleep(CINEMATIC_TICK_RATE/(game->mapSize.x - k));
		}

		for(int y = k; y < game->mapSize.y - k; ++y){
			mvwprintw(game->mainGameWindowContent, game->mapSize.y- y, k, "#");
			mvwprintw(game->mainGameWindowContent, y, game->mapSize.x - k - 1, "#");
			wrefresh(game->mainGameWindowContent);
			usleep(CINEMATIC_TICK_RATE/(game->mapSize.y - k));
		}
	}
	clear();
}


void defeatScreen(Game *game){
	cinematicFade(game);

	putTextAtCenter(stdscr, -8, "Game Over!");

	putTextAtCenter(stdscr, -7, "Maybe next time you will have more luck");

	putTextAtCenter(stdscr, 9, "press Esc to quit...");

	printScores(game, true);
	refresh();
	while(getch() != QUIT);
}


void winScreen(Game *game){
	cinematicFade(game);

	putTextAtCenter(stdscr, -7, "You Won!");
	putTextAtCenter(stdscr, 9, "press Esc to quit...");
	
	printScores(game, false);
	
	refresh();
	while(getch() != QUIT);
}


void drawMap(Game *game){//DEBUG purpose only
	for(int y = 0; y < game->mapSize.y; y++) {
		for(int x = 0; x < game->mapSize.x; x++) {
			if(game->collisionMap[y][x] != COLLIDER_NONE)mvwprintw(game->mainGameWindowContent, y, x, "%c", game->collisionMap[y][x] + '0');
		}
	}
}
