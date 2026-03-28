#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include "structures.h"

bool checkFileExists(char* fileName);

void loadEntry(void* field, char* fileName, char* key, char* category, char* subcategory);

void exportRankData(int rank[RANKINGS_PLAYER_AMOUNT], char players[RANKINGS_PLAYER_AMOUNT][32]);

#endif