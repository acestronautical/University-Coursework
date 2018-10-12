/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA5                                                              *
* Date: February 27, 2017                                                                  *
* Description: A game of Yahtzee,  playable in a win32 console                             *
*******************************************************************************************/

#include "header.h"

int main(void)
{

	while (1)
	{
		//explain game
		print_game_rules();
		enter_to_continue();
		system("cls");
		print_scoring_combinations();

		//ask if want to play
		if (!want_to_play()) { break; }
		system("cls");
		how_to_play();
		enter_to_continue();
		system("cls");

		//main game loop
		play_game();

		//play again?
		enter_to_continue();
		system("cls");
		if (!want_to_play()) { break; }
	}
	printf("\nThank you\n");
	return 0;
}