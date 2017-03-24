/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA6 - BattleShip                                                 *
* Date: 3-12-17                                                                            *
* Description: A game of battleship played in terminal with AI opponent                    *
*******************************************************************************************/

#include "header.h"

char* initialize_2d_array(char *array2d, int rows, int columns, char initializing_value)
{
	int idx = 0;
	for (idx; idx < (columns*rows); idx++) {
		array2d[idx] = initializing_value;
	}
	return array2d;
}

void print_game_board(char ship_grid[][10])
{
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (int idx = 0; idx < 10; idx++)
	{
		printf("%c ", ('A' + idx));
		for (int idy = 0; idy < 10; idy++)
		{
			printf("%c ", ship_grid[idx][idy]);
		}
		printf("\n");
	}
}

char* place_ships_manual(char ship_grid[][10])
{
	char ship_name[5][11] = { "carrier" , "battleship" , "cruiser" , "submarine" , "destroyer" };
	char ship_symbol[5] = { 'c', 'b', 'r', 's', 'd' };
	int  ship_size[5] = { 5, 4, 3, 3, 2 };
	
	int success;
	int idx = 0, idy;
	int row, column;
	int ship_start = -1, ship_end = -1;
	int input;

	while (idx < 5)
	{
		input = 0, ship_start = -1, ship_end = -1, row = -1, column = -1, idy = 0, success = 0;

		print_game_board(ship_grid);

		printf("\nEnter the row or column where you would you like to place your %s:\n", ship_name[idx]);

		input = _getche();
		printf("\n");
		if (input >= '0' && input <= '9') // ascii 0 - 9
			column = (input - 48);
		else if (input >= 'A' && input <= 'J')// ascii A - J
			row = (input - 65);
		else if (input >= 'a' && input <= 'j')//ascii a - j
			row = (input - 97);
		else
		{
			printf("Let's try that again\n");
			continue;
		}

		printf("Enter the first and last of the %d spaces in this ", ship_size[idx]);
		if (row == -1)
			printf("column");
		else
			printf("row");
		printf(" where you would like your %s:\n", ship_name[idx]);

		while (idy < 3 && !success)
		{
			idy++;

			printf("[ ");
			ship_start = _getche();
			printf(" - ");
			ship_end = _getche();
			printf(" ]\n");

			if (ship_start > ship_end)
			{
				input = ship_start;
				ship_start = ship_end;
				ship_end = input;
			}

			if (row == -1)
			{
				if ((ship_start >= 'A' && ship_start <= 'J') && (ship_end >= 'A' && ship_end <= 'J'))// ascii A - J
					ship_start = (ship_start - 65), 
					ship_end = (ship_end - 65);
				else if ((ship_start >= 'a' && ship_start <= 'j') && (ship_end >= 'a' && ship_end <= 'j'))//ascii a - j
					ship_start = (ship_start - 97),
					ship_end = (ship_end - 97) ;
				else
				{
					printf("Invalid entry, Let's try again\n");
					continue;
				}

				if ((ship_end - ship_start + 1) != ship_size[idx])
				{
					printf("Sorry, that's not the right length, try again\n");
					continue;
				}

				if (!column_spaces_contain_only('-', column, ship_start, (ship_start + ship_size[idx]), ship_grid, 10, 10))
				{
					printf("There is already a ship in some of these spaces! Try again\n");
					continue;
				}

				for (int i = ship_start; i < ship_start + ship_size[idx]; i++)
				{
					ship_grid[i][column] = ship_symbol[idx];
				}
			}

			else if (column == -1)
			{
				if ((ship_start >= '0' && ship_start <= '9') && (ship_start >= '0' && ship_start <= '9'))// ascii 0 - 9
					ship_start = (ship_start - 48),
					ship_end = (ship_end - 48);
				else
				{
					printf("Invalid entry, Let's try again\n");
					continue;
				}

				if ((ship_end - ship_start + 1) != ship_size[idx])
				{
					printf("Sorry, that's not the right length, try again\n");
					continue;
				}


				if(!row_spaces_contain_only('-', row, ship_start, (ship_start + ship_size[idx]) ,ship_grid, 10, 10))
				{
					printf("There is already a ship in some of these spaces! Try again\n");
					continue;
				}


				for (int i = ship_start; i < ship_start + ship_size[idx]; i++)
				{
					ship_grid[row][i] = ship_symbol[idx];
				}
			}

			success = 1;
		}

		if (!success)
		{
			printf("You seem to be having trouble placing your ship in this ");
			if (row == -1)
				printf("column");
			else
				printf("row");

			printf(", it may be that this ");
			
			if (row == -1)
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

	return ship_grid;
}

char* place_ships_random(char ship_grid[][10])
{
	char ship_symbol[5] = { 'c', 'b', 'r', 's', 'd' };
	int  ship_size[5] = { 5, 4, 3, 3, 2 };
	int row, column, vertical;
	int idx = 0;

	while (idx < 5)
	{

		vertical = rand() % 2;

		if (vertical)
		{
			do {
				row = rand() % (ship_size[idx] + 1);
				column = rand() % 10;
			} while (!column_spaces_contain_only('-', column, row, (row + ship_size[idx]), ship_grid, 10, 10));

			for (int i = 0; i < ship_size[idx]; i++)
			{
				ship_grid[row + i][column] = ship_symbol[idx];
			}
		}
		else
		{
			do{
				row = rand() % 10;
				column = rand() % (ship_size[idx] + 1);
			} while (!row_spaces_contain_only('-', row, column, (column + ship_size[idx]), ship_grid, 10, 10));

			for (int i = 0; i < ship_size[idx]; i++)
			{
				ship_grid[row][column + i] = ship_symbol[idx];

			}
		}
		idx++;
	}
	
	return  ship_grid;
}

int row_spaces_contain_only(char token, int row, int start_space, int end_space, char *grid, int num_rows, int num_columns)
{
	int bool = 1;
	char* space = (grid + (row * num_columns));

	for (int i = start_space; i < end_space; i++)
	{
		if (*(space + i) != token)
		{
			bool = 0;
			break;
		}
	}
	return bool;
}

int column_spaces_contain_only(char token, int column, int start_space, int end_space, char *grid, int num_rows, int num_columns)
{
	int bool = 1;
	char* space = (grid + (column));

	for (int i = start_space; i < end_space; i++)
	{
		if (*(space + (i * num_columns)) != token)
		{
			bool = 0;
			break;
		}
	}
	return bool;
}