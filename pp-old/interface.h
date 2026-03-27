#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "structures.h"
#include "defines.h"
#include "functions.h"
#include "fileParser.h"

void createWindow(WINDOW **win, int height, int width, int starty, int startx);

void putTextAtCenter(WINDOW *win, int offsetY, const char *text);

void drawStatusWindows(Game *game);

void drawWindows(Game *game);

void drawEntity(Entity *entity, WINDOW * window, Vector2 mapSize);

void drawStatus(Game *game);

void drawGame(Game *game, bool animate);

bool mainMenu(Game *game);

void startScreen(Game *game);

void printScores(Game *game, bool isDefeat);

void defeatScreen(Game *game);

void winScreen(Game *game);

void drawMap(Game *game);

#endif