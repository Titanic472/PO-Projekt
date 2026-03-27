#ifndef DEFINES_H
#define DEFINES_H

#define HORIZONTAL_MARGIN 5
#define VERTICAL_MARGIN 3
#define MIN_STATUS_SIZE 7 // Minimum height for the status window
#define MIN_SCREEN_HEIGHT 30
#define MIN_SCREEN_WIDTH 60
#define MAX_LEVELS 5 // can be changed if more levels are added, but remember to update CH_HIGHESTNUMBER for bigger input availability

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define TICK_RATE 250000 // Microseconds per game tick
#define ALBATROSS_TICK_RATE 45000 // Microseconds per albatross animation tick
#define CINEMATIC_TICK_RATE 200000 // Microseconds per animation tick

#define SPRITE_RIGHT 0
#define SPRITE_LEFT 1
#define SPRITE_UP 2
#define SPRITE_DOWN 3

#define CONTROL_RIGHT 'd'
#define CONTROL_LEFT 'a'
#define CONTROL_UP 'w'
#define CONTROL_DOWN 's'
#define CONTROL_DASH ' '
#define CONTROL_ALBATROSS 't'
#define QUIT 27

#define CH_LOWESTNUMBER '1'
#define CH_HIGHESTNUMBER '5'

#define COLLIDER_NONE 0
#define COLLIDER_PLAYER 1
#define COLLIDER_STAR 2
#define COLLIDER_HUNTER 3
#define COLLIDER_WALL 4

#define STAR_RANDOM_OFFSET 4 //chance for star to randomly move left or right instead of falling straight
#define HUNTER_MAX_HEALTH 9 //numbers bigger than 9 won't be displayed properly
#define HUNTER_DASH_DURATION 10 //hunter always checks intersection on full path - big numbers can cause lag
#define HUNTER_DASH_WAIT_BEFORE_START 3 //hunter always waits 1 turn, then number of turns defined here

#define DEFAULT_SAFE_ZONE_RADIUS 7 //safe zone for albatross taxi
#define SAFE_ZONE_MARGIN 5
#define ALBATROSS_SPEED 2 
#define POSITION_NULL -1 //null but in vectors

#define YELLOW 1
#define GRAY 2
#define RED 3
#define MAGENTA 4
#define BLUE 5
#define GREEN 6
#define WHITE 7
#define FOG 8 //white background with whiter text

#define LINE_MAX_SIZE 256
#define CATEGORY_NO_HEADER 0
#define CATEGORY_START_HEADER 1
#define CATEGORY_END_HEADER 2
#define RANKINGS_FILENAME "rankings.top1"
#define RANKINGS_PLAYERS_CATEGORY "topPlayers"
#define RANKINGS_SCORES_CATEGORY "topScores"
#define RANKINGS_PLAYER_AMOUNT 10
#define PLAYER_NAME_MAX_LENGTH 32 // always 1 less because of '\0'
#define HEALTHBAR_SIZE 10

#define HUNTERS_PER_SCORE_MULTIPLIER 20
#define HUNTERS_SPAWN_PER_SCORE_MULTIPLIER 20

#endif