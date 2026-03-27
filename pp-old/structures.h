#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <ncurses.h>
#include <time.h>
#include "defines.h"

typedef struct {
	int start;
	int end;
} Range;


typedef struct {
	int y;
	int x;
} Vector2;

typedef struct {
	float y;
	float x;
} Vector2f;

typedef struct {
    char* key;
    char type;
    char* value;
    int isHeader;
} fileEntry;

typedef struct {
    int pointsPerHealth;
    int pointsPerTime;
    int pointsPerScore;
} ScoreWeights;

typedef struct {
    Vector2 position;
	Vector2f momentum;//y momentum is reversed because y starts at screen top
    Vector2f excessMomentum;
    Vector2 spriteSizes[4];

    int collider;
    char **sprites[4];

    int abilityCooldown;
    int health;
    int baseHealth;
    float baseSpeed;
    float maxSpeed;
    
    int color;
    int animationFrames;
    int currFrame;
} Entity;

typedef struct {
    Vector2 screen;
    
	WINDOW *mainGameWindow;
    WINDOW *mainGameWindowContent;
	WINDOW *statusWindow;
    WINDOW *healthWindow;
	WINDOW *timeWindow;
    
    Vector2 mapSize;
    int **collisionMap;

    Entity *player;
    Entity *albatross;
    
    
    Entity **stars;
    int currentStars;
    int starSpawnChance;
    
    Entity **hunters;
    int currentHunters;
    int hunterSpawnChance;
    int maxHunters;
    float hunterLifeIncrease;
    float hunterCountIncrease;
    int hunterDamagePerLife;

	int score;
    int targetScore;
	int level;
    char levelName[32];
	bool isGameOver;
    int speed;
    time_t startTime;
    int timePassed;
    int ticksPassed;
    int levelTime;

    char playerName[PLAYER_NAME_MAX_LENGTH];

    int fogStart;
    int fogFOV; //maximum player view distance within the fog
    float fogSpreadRate; // spread rate is calculated per second
} Game;

#endif