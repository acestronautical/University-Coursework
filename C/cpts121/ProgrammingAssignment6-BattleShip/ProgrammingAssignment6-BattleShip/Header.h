/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA6 - BattleShip                                                 *
* Date: 3-12-17                                                                            *
* Description: A game of battleship played in terminal with AI opponent                    *
*******************************************************************************************/

#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <wincon.h>
#include <stdbool.h>
#include <string.h>

#define BLUE_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)
#define RED_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define GREEN_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define WHITE_TEXT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

#define WATER '~'
#define HIT '*'
#define MISS 'm'

#define RANDOM TRUE
#define MANUAL FALSE

#define ARMADA_SIZE 5

#define HUMAN  TRUE
#define ROBOT FALSE

#define ROWS 10
#define COLUMNS 10

#define NOT_ENTERED -1

typedef struct shot
{
	char* shooter[10];
	char row;
	char column;
	char hit_what;
} Shot;

typedef  struct stats {
	char* player_name[10];
	int hits;
	int misses;
	bool won;
	int enemy_carrier_hp;
	int enemy_battleship_hp;
	int enemy_cruiser_hp;
	int enemy_submarine_hp;
	int enemy_destroyer_hp;
}Stats;

typedef struct ship {
	char* name[11];
	char symbol;
	int  size;
}Ship;

//Explains the rules of battleship and looks pretty
void welcome_screen();

//generates a random true or false value and says who won the coin flip
bool coin_flip();

//initializes a two dimensional array of any dimensions with a given token
void initialize_2d_array(char *array2d, int rows, int columns, char initializing_value);

//displays the given battleship game board with a boolean to toggle whether to show ships
void print_game_board(char ship_grid[][COLUMNS], bool show_ships);

//places all ships in the armada either manually of randomly based on a boolean
char* place_ships(char ship_grid[][COLUMNS],Ship armada[ARMADA_SIZE], bool random);

//used by place ships when random boolean is true, places  ships randomly
void random_placement(char ship_grid[][COLUMNS], Ship armada[ARMADA_SIZE]);

//used by place ships when random boolean is false, prompts user for ship placement
void manual_placement(char ship_grid[][COLUMNS], Ship armada[ARMADA_SIZE]);

//shoots at the given board and returns a shot struct which contains
//the coordinates of the shot, name of shooter as string, and char of what was hit
Shot shoot_at(char ship_grid[][COLUMNS], bool human);

//logs the current shot to the battleship log file
void log_shot(Shot shot_to_log, Stats these_stats, FILE* log_file);

//updates player stats and returns the updated stats
Stats update_stats(Shot current_shot, Stats these_stats);

//returns a string of which ship was just sunk, or empty string if no ship was sunk
char* sunk_something_string(Shot this_shot, Stats these_stats);

//outputs players stats to screen
void stats_to_screen(Stats these_stats);

//output players stats to log file
void stats_to_file(FILE* log_file, Stats these_stats);

#endif // !HEADER
