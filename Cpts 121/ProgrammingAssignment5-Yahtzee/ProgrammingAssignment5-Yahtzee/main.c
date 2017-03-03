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
	//Declare variables
	char five_dice[5] = { 3, 2, 2, 3, 3 };
	char hold_dice[5] = { 0, 0, 0, 0, 0 };

	//score indexes are as follows
	// 0  ,   1 ,   2   ,  3   ,   4  ,   5 ,    6   ,    7  ,   8   ,   9    ,   10   ,   11  ,   12   ,   13 ,  14
	//ones, twos, threes, fours, fives, sixs, threeof, fourof, fullhs, smallst, largest, chance, yahtzee, bonus, total
	char scores[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char potential_scores[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//set global randomness seed variable to time
	srand((unsigned)time(NULL));

	/*for (int i = 0; i < 3; i++)
	{
		randomize_dice(five_dice, 5, hold_dice, 5);
		print_dice(five_dice, 5);
		if (i < 2)
		{
			hold_which_dice(hold_dice, 5);
		}
	}*/
	enter_to_continue();
	potential_scoring(five_dice, 5, potential_scores, 15);
	print_score_card(potential_scores, 15);

	return 0;
}