/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA6 - BattleShip                                                 *
* Date: 3-12-17                                                                            *
* Description: A game of battleship played in terminal with AI opponent                    *
*******************************************************************************************/

#include "header.h"


int main(int argc, char* argv[])
{
	srand(time(NULL));

	Ship carrier = { "carrier", 'c', 5 };
	Ship battleship = { "battleship", 'b', 4 };
	Ship cruise = { "cruiser", 'r', 3 };
	Ship submarine = { "submarine", 's', 3 };
	Ship destroyer = { "destroyer", 'd', 2 };

	char player_one_ship_grid[10][10] = { 0 };
	char player_two_ship_grid[10][10] = { 0 };


	while (1)
	{
		initialize_2d_array(player_one_ship_grid, 10, 10, '-');

		place_ships_manual(player_one_ship_grid);
		//place_ships_random(player_one_ship_grid);
		print_game_board(player_one_ship_grid);
		system("pause");
		system("cls");
	}
	return 0;
}
