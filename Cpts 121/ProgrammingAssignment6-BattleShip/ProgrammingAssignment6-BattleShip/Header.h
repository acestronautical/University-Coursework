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

typedef struct ship
{
	char* ship_name;
	char ship_symbol;
	int  ship_size;
} Ship;

char* initialize_2d_array(char *array2d, int rows, int columns, char initializing_value);

void print_game_board(char ship_grid[][10]);

char* place_ships_manual(char ship_grid[][10]);

char* place_ships_random(char ship_grid[][10]);

int row_spaces_contain_only(char token, int row, int start_space, int end_space, char *grid, int num_rows, int num_columns);

int column_spaces_contain_only(char token, int column, int start_space, int end_space, char *grid, int num_rows, int num_columns);

#endif // !HEADER
