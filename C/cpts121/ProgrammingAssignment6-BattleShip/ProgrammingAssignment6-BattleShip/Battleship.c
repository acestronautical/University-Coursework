/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA6 - BattleShip                                                 *
* Date: 3-12-17                                                                            *
* Description: A game of battleship played in terminal with AI opponent                    *
*******************************************************************************************/

#include "header.h"

//Explains the rules of battleship and looks pretty
void welcome_screen()
{	puts("");
	puts(" _______  _______  _______  _______  ___      _______  __  ");
	puts("|  _    ||   _   ||       ||       ||   |    |       ||  | ");
	puts("| |_|   ||  |_|  ||_     _||_     _||   |    |    ___||  | ");
	puts("|       ||       |  |   |    |   |  |   |    |   |___ |  | ");
	puts("|  _   | |       |  |   |    |   |  |   |___ |    ___||__| ");
	puts("| |_|   ||   _   |  |   |    |   |  |       ||   |___  __  ");
	puts("|_______||__| |__|  |___|    |___|  |_______||_______||__| ");
	puts(" _______  __   __  ___   _______  _______    __   __   __  ");
	puts("|       ||  | |  ||   | |       ||       |  |  | |  | |  | ");
	puts("|  _____||  |_|  ||   | |    _  ||  _____|  |  | |  | |  | ");
	puts("| |_____ |       ||   | |   |_| || |_____   |  | |  | |  | ");
	puts("|_____  ||       ||   | |    ___||_____  |  |__| |__| |__| ");
	puts(" _____| ||   _   ||   | |   |     _____| |   __   __   __  ");
	puts("|_______||__| |__||___| |___|    |_______|  |__| |__| |__| ");
	puts("");
	puts("Pitting Human VS Robot, Battle ships will determine who is superior");
	puts("It is up to you, Human, to save our species!");
	puts("");
	puts("You and the Robot will take turns firing a shot to attack enemy ships");
	puts("On your turn, call out a letter and a number of a row and column on the grid");
	puts("Depending on what your opponents board contains it will be either a");
	puts("\"miss\" if there are no ships there, or \"hit\" if the space contained a ship");
	puts("Spaces where you have shot will be marked with an \"M\" for miss or \"*\" for hit");
	puts("When a either one of your own ships or an opponents ship has been sunk");
	puts("it will be announced, and entered into the log.");
	puts("");
	puts("Victory: The first player to sink all opposing ships wins.");
	puts("");	}

//generates a random true or false value and says who won the coin flip
bool coin_flip()
{	bool human_turn = (rand() % 2);
	puts("Flip a coin to see who  goes first!");
	if (human_turn)
		puts("human wins the coin flip, human goes first\n");
	else
		puts("robot wins the coin flip, robot goes first\n");
	return human_turn;	}

//initializes a two dimensional array of any dimensions 
//with a given token, done in only two lines
void initialize_2d_array(char *array2d, int rows, int columns, char initializing_value)
{	for (int idx = 0; idx < (rows*columns); idx++)
		array2d[idx] = initializing_value;	}

//displays the given battleship game board with a boolean to toggle whether to show ships
void print_game_board(char ship_grid[][COLUMNS], bool show_ships)
{	GREEN_TEXT;
	printf(" ");
	for (int i = 0; i < COLUMNS; i++)
	{
		printf(" %d", i);
	}
	printf("\n");

	for (int idx = 0; idx < ROWS; idx++)
	{
		printf("%c ", ('A' + idx));
		for (int idy = 0; idy < COLUMNS; idy++)
		{
			if (show_ships)
			{
				switch (ship_grid[idx][idy]) {
				case HIT:   RED_TEXT; printf("%c ", HIT); GREEN_TEXT;                      break;
				case MISS:  BLUE_TEXT; printf("%c ", MISS); GREEN_TEXT;                    break;
				case WATER: BLUE_TEXT;  printf("%c ", WATER); GREEN_TEXT;                  break;
				default:    WHITE_TEXT;  printf("%c ", ship_grid[idx][idy]); GREEN_TEXT;   break;
				}
			}
			else
			{
				switch (ship_grid[idx][idy]) {
				case HIT:   RED_TEXT; printf("%c ", HIT);     GREEN_TEXT;  break;
				case MISS:  BLUE_TEXT; printf("%c ", MISS);   GREEN_TEXT;  break;
				default:    BLUE_TEXT;  printf("%c ", WATER); GREEN_TEXT;  break;
				}
			}
		}
		printf("\n");
	}
}

//places all ships in the armada either manually of randomly based on a boolean
char* place_ships(char ship_grid[][COLUMNS], Ship armada[ARMADA_SIZE], bool random)
{	if (random)
		random_placement(ship_grid, armada);
	else 
		manual_placement(ship_grid, armada);
	return ship_grid;	}

//used by place ships when random boolean is true
void manual_placement(char ship_grid[][COLUMNS], Ship armada[ARMADA_SIZE])
{
	int idx = 0;
	while (idx < 5)
	{
		int input = 0, ship_start = NOT_ENTERED, ship_end = NOT_ENTERED, row = NOT_ENTERED, column = NOT_ENTERED, idy = 0;
		bool success = FALSE, open_ocean = TRUE;

		print_game_board(ship_grid, TRUE);

		printf("\nEnter the row or column where you would you like to place your %s:\n", *armada[idx].name);
		input = _getche(); printf("\n");

		if (input >= '0' && input <= '9') // ascii 0 - 9
			column = (input - 48);
		else if (input >= 'A' && input <= 'J')// ascii A - J
			row = (input - 65);
		else if (input >= 'a' && input <= 'j')//ascii a - j
			row = (input - 97);
		else
		{
			printf("Let's try that again\n"); continue;
		}

		printf("Enter the first and last of the %d spaces in this ", armada[idx].size);
		if (row == NOT_ENTERED)
			printf("column");
		else
			printf("row");
		printf(" where you would like your %s:\n", *armada[idx].name);

		while (idy < 2 && !success)
		{
			idy++;
			open_ocean = TRUE;

			printf("[ ");
			printf("%c - ", ship_start = _getch());
			printf("%c ]\n", ship_end = _getch());

			if (ship_start > ship_end)
			{	input = ship_start;
				ship_start = ship_end;
				ship_end = input;	}

			if (row == NOT_ENTERED)
			{
				if ((ship_start >= 'A' && ship_start <= 'J') && (ship_end >= 'A' && ship_end <= 'J'))// ascii A - J
					ship_start = (ship_start - 65), ship_end = (ship_end - 65);
				else if ((ship_start >= 'a' && ship_start <= 'j') && (ship_end >= 'a' && ship_end <= 'j'))//ascii a - j
					ship_start = (ship_start - 97), ship_end = (ship_end - 97);
				else
				{
					printf("Invalid entry, Let's try again\n");
					continue;
				}
			}
			else if (column == NOT_ENTERED)
			{
				if ((ship_start >= '0' && ship_start <= '9') && (ship_start >= '0' && ship_start <= '9'))// ascii 0 - 9
					ship_start = (ship_start - 48),	ship_end = (ship_end - 48);
				else
				{
					printf("Invalid entry, Let's try again\n");
					continue;
				}
			}

			if ((ship_end - ship_start + 1) != armada[idx].size)
			{	printf("Sorry, that's not the right length, try again\n");
				continue;	}


			if (row == NOT_ENTERED) {

				for (int i = ship_start; i < ship_end + 1; i++)
				{
					if (ship_grid[i][column] != WATER)
					{	open_ocean = FALSE; break;	}
				}

				if (!open_ocean)
				{	printf("There is already a ship in some of these spaces! Try again\n"); continue;	}

				for (int i = ship_start; i < ship_start + armada[idx].size; i++)
					ship_grid[i][column] = armada[idx].symbol;
			}
			else if (column == NOT_ENTERED) {

				for (int i = ship_start; i < ship_end + 1; i++)
				{
					if (ship_grid[row][i] != WATER)
					{	open_ocean = FALSE; break;	}
				}

				if (!open_ocean)
				{	printf("There is already a ship in some of these spaces! Try again\n"); continue;	}

				for (int i = ship_start; i < ship_start + armada[idx].size; i++)
					ship_grid[row][i] = armada[idx].symbol;
			}
			success = TRUE;
		}

		if (!success)
		{
			printf("You seem to be having trouble placing your ship in this ");
			if (row == NOT_ENTERED)
				printf("column");
			else
				printf("row");
			printf(", it may be that this ");
			if (row == NOT_ENTERED)
				printf("column");
			else
				printf("row");
			printf(" is full. You may select a new row or column\n");
			system("pause");
			system("cls");
			continue;
		}

		system("cls");
		idx++;
	}
}

//used by place ships when random boolean is false
void random_placement(char ship_grid[][COLUMNS], Ship armada[ARMADA_SIZE])
{
	int idx = 0, vertical, row, column;
	bool open_ocean;
	while (idx < 5)
	{
		vertical = rand() % 2;
		if (vertical) //vertical -> down
		{
			do {
				open_ocean = TRUE;
				row = rand() % (armada[idx].size + 1);
				column = rand() % COLUMNS;
				for (int i = row; i < armada[idx].size + row; i++)
				{
					if (ship_grid[i][column] != WATER)
					{	open_ocean = FALSE; break;	}
				}
			} while (!open_ocean);

			for (int i = 0; i < armada[idx].size; i++)
				ship_grid[row + i][column] = armada[idx].symbol;
		}
		else //horizontal -> right
		{
			do {
				open_ocean = TRUE;
				row = rand() % ROWS;
				column = rand() % (armada[idx].size + 1);
				for (int i = column; i < armada[idx].size + column; i++)
				{
					if (ship_grid[row][i] != WATER)
					{	open_ocean = FALSE; break;	}
				}
			} while (!open_ocean);

			for (int i = 0; i < armada[idx].size; i++)
				ship_grid[row][column + i] = armada[idx].symbol;
		}
		idx++;
	}
}

//shoots at the given board either as human or AI and returns a shot struct which contains
//the coordinates of the shot, name of shooter as string, and a char of what was hit
Shot shoot_at(char ship_grid[][COLUMNS], bool human)
{	char input = NOT_ENTERED, column = NOT_ENTERED, row = NOT_ENTERED;
	bool valid_shot = FALSE, kill_shot = !(rand() % 7);
	Shot this_shot;
		while (!valid_shot)
		{
			if (human) { //human shooter
				row = NOT_ENTERED, column = NOT_ENTERED;
				*this_shot.shooter = "Human";
				puts("Enter the row and column where you would like to shoot");

				for (int i = 0; i < 2; i++) {
					if(i == 0) printf("[ ");
					printf("%c ", input = _getch());
					if (input >= '0' && input <= '9') // ascii 0 - 9
						column = (input - 48), this_shot.column = input;
					else if (input >= 'A' && input <= 'J')// ascii A - J
						row = (input - 65), this_shot.row = input;
					else if (input >= 'a' && input <= 'j')//ascii a - j
						row = (input - 97), this_shot.row = input - 32;
					else
					{
						printf("Let's try that again\n"); i = -1; continue;
					}
					if(i== 1) printf("]");
				}

				if (row == NOT_ENTERED || column == NOT_ENTERED)
				{
					puts("Please enter a row and a column"); continue;
				}

				if (ship_grid[row][column] == HIT || ship_grid[row][column] == MISS)
				{
					puts("You've already shot there!"); continue;
				}
				else if (ship_grid[row][column] == WATER)
				{
					puts("That's a Miss!"); this_shot.hit_what = WATER; ship_grid[row][column] = MISS;
				}
				else
				{
					puts("That's a Hit!"); this_shot.hit_what = ship_grid[row][column]; ship_grid[row][column] = HIT;
				}
			}
			else //robot shooter
			{
				*this_shot.shooter = "Robot";
				if (kill_shot) {
					for (int i = 0; i < ROWS && row == NOT_ENTERED; i++) {
						for (int j = 0; j < COLUMNS && row == NOT_ENTERED; j++) {
							if (ship_grid[i][j] != WATER && ship_grid[i][j] != HIT && ship_grid[i][j] != MISS)
								row = i, column = j;
						}
					}
				}
				else
					row = rand() % ROWS, column = rand() % COLUMNS;

				this_shot.row = row + 65;
				this_shot.column = column + 48;

				if (ship_grid[row][column] == HIT || ship_grid[row][column] == MISS)
					continue;
				
				if (ship_grid[row][column] == WATER)
				{
					this_shot.hit_what = WATER;  ship_grid[row][column] = MISS;
				}
				else
				{
					this_shot.hit_what = ship_grid[row][column]; ship_grid[row][column] = HIT;
				}

				printf("Robot shoots at [ %c  %c ]\nRobot", this_shot.row, this_shot.column);
				if (this_shot.hit_what == WATER)
					puts(" Misses!");
				else
					puts(" Hits!");
			}
			valid_shot = TRUE;
		}
	return this_shot;
}

//logs the current shot to the battleship log file
void log_shot(Shot shot_to_log, Stats these_stats, FILE* log_file)
{
	fprintf(log_file, "%s: %c,%c", *shot_to_log.shooter, shot_to_log.row, shot_to_log.column);
	if (shot_to_log.hit_what == WATER)
		fprintf(log_file, " \"Miss\" \n");
	else
	{
		fprintf(log_file, " \"Hit\" ");
		fprintf(log_file, "%s\n", sunk_something_string(shot_to_log, these_stats));
	}
}

//updates player stats and returns the updated stats
Stats update_stats(Shot current_shot, Stats these_stats)
{
	switch (current_shot.hit_what)
	{
	case 'c':
		these_stats.enemy_carrier_hp -= 1;
		these_stats.hits += 1;
		break;
	case 'b':
		these_stats.enemy_battleship_hp -= 1;
		these_stats.hits += 1;
		break;
	case 'r':
		these_stats.enemy_cruiser_hp -= 1;
		these_stats.hits += 1;
		break;
	case 's':
		these_stats.enemy_submarine_hp -= 1;
		these_stats.hits += 1;
		break;
	case 'd':
		these_stats.enemy_destroyer_hp -= 1;
		these_stats.hits += 1;
		break;
	case WATER:
		these_stats.misses += 1;
	default:
		break;
	}
	if (these_stats.hits == 17)
		these_stats.won = TRUE;

	return these_stats;
}

//returns a string of which ship was just sunk, or empty string if no ship was sunk
char* sunk_something_string(Shot this_shot, Stats these_stats)
{
	if (these_stats.enemy_carrier_hp == 0 && this_shot.hit_what == 'c')
		return "Enemy Carrier Sunk";
	else if (these_stats.enemy_battleship_hp == 0 && this_shot.hit_what == 'b')
		return "Enemy Battleship Sunk";
	else if (these_stats.enemy_cruiser_hp == 0 && this_shot.hit_what == 'r')
		return "Enemy Cruiser Sunk";
	else if (these_stats.enemy_submarine_hp == 0 && this_shot.hit_what == 's')
		return "Enemy Submarine Sunk";
	else if (these_stats.enemy_destroyer_hp == 0 && this_shot.hit_what == 'd')
		return "Enemy Destroyer Sunk";
	else
		return "";
}

//outputs players stats to screen
void stats_to_screen(Stats these_stats)
{
	printf("%s Stats:\n", *these_stats.player_name);
	printf("Total Hits: %d\n", these_stats.hits);
	printf("Total Misses: %d\n", these_stats.misses);
	printf("Total Shots: %d\n", these_stats.misses + these_stats.hits);
	printf("Hit vs Miss Percentage: %.0lf%%\n", 100 * ((double)these_stats.hits / these_stats.misses));
}

//output players stats to log file
void stats_to_file(FILE* log_file, Stats these_stats)
{
	fprintf( log_file ,"\n%s Stats:\n", *these_stats.player_name);
	fprintf( log_file ,"Total Hits: %d\n", these_stats.hits);
	fprintf( log_file ,"Total Misses: %d\n", these_stats.misses);
	fprintf( log_file ,"Total Shots: %d\n", these_stats.misses + these_stats.hits);
	fprintf( log_file ,"Hit vs Miss Percentage: %.0lf%%\n", 100 * ((double)these_stats.hits / these_stats.misses));
	fprintf( log_file ,"%s", *these_stats.player_name);
	these_stats.won ? fprintf(log_file, " Won!\n") : fprintf(log_file, " Lost!\n");
}