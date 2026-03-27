#ifndef INIT_H
#define INIT_H

#include <ncurses.h>
#include "albatrossTaxi.h"
#include "entityManager.h"
#include "fileParser.h"
#include "moveHandler.h"

bool initGame(Game *game);

bool initCurses(Game *game);

#endif