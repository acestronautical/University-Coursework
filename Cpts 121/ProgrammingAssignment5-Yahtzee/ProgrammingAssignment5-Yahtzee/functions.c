/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA5                                                              *
* Date: February 27, 2017                                                                  *
* Description: A game of Yahtzee,  playable in a win32 console                             *
*******************************************************************************************/

#include "header.h"

int roll_die(void)
{
	int roll = 0;
	roll = (rand() % 6) + 1;
	return roll;
}

void enter_to_continue(void)
{
	while (getchar() != '\n');
}

void randomize_dice(char *dice, int sizeof_dice, char *hold_dice, int sizeof_hold_dice)
{
	if (sizeof_dice == sizeof_hold_dice) {
		for (int i = 0; i < sizeof_dice; i++)
		{
			if (hold_dice[i] == 0 || hold_dice[i] == 'n' || hold_dice[i] == 'N')
			{
				dice[i] = roll_die();
			}
		}
	}
	else
	{
		printf("error randomize dice incorrect arguments");
	}
}

void hold_which_dice(char *hold_dice, int sizeof_hold_dice)
{

	for (int i = 0; i < sizeof_hold_dice; i++)
	{
		printf("  hold? ");
		hold_dice[i] = getche();
		printf("  ");
	}

}

void print_dice(char *dice, int sizeof_dice)
{

	int count;

	printf("\n");
	for (count = 0; count < sizeof_dice; count++)
	{
		printf(" --------- ");
	}

	printf("\n");

	for (count = 0; count < sizeof_dice; count++)
	{
		switch (dice[count])
		{
		case 1:
			printf(" |       | ");
			break;
		case 2:
			printf(" | o     | ");
			break;
		case 3:
			printf(" | o     | ");
			break;
		case 4:
			printf(" | o   o | ");
			break;
		case 5:
			printf(" | o   o | ");
			break;
		case 6:
			printf(" | o   o | ");
			break;
		default:
			break;
		}
	}

	printf("\n");

	for (count = 0; count < sizeof_dice; count++)
	{
		switch (dice[count])
		{
		case 1:
			printf(" |   o   | ");
			break;
		case 2:
			printf(" |       | ");
			break;
		case 3:
			printf(" |   o   | ");
			break;
		case 4:
			printf(" |       | ");
			break;
		case 5:
			printf(" |   o   | ");
			break;
		case 6:
			printf(" | o   o | ");
			break;
		default:
			break;
		}
	}

	printf("\n");

	for (count = 0; count < sizeof_dice; count++)
	{
		switch (dice[count])
		{
		case 1:
			printf(" |       | ");
			break;
		case 2:
			printf(" |     o | ");
			break;
		case 3:
			printf(" |     o | ");
			break;
		case 4:
			printf(" | o   o | ");
			break;
		case 5:
			printf(" | o   o | ");
			break;
		case 6:
			printf(" | o   o | ");
			break;
		default:
			break;
		}
	}

	printf("\n");

	for (count = 0; count < sizeof_dice; count++)
	{
		printf(" --------- ");
	}

	printf("\n");

}

void potential_scoring(char *dice, int sizeof_dice, char *potential_scores, int sizeof_potential_scores)
{
	//score indexes are as follows
	// 0  ,   1 ,   2   ,  3   ,   4  ,   5 ,    6   ,    7  ,   8   ,   9    ,   10   ,   11  ,   12   ,   13 ,  14
	//ones, twos, threes, fours, fives, sixs, threeof, fourof, fullhs, smallst, largest, chance, yahtzee, bonus, total
	char score;
	int ofakind, i, c, n, inarow;

	for (int count = 0; count < sizeof_potential_scores; count++)
	{
		ofakind = 0;
		inarow = 0;
		score = 0;
		i = 0;
		c = 0;
		n = 0;

		switch (count)
		{
		case 0: //ones
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 1)
					score += 1;
			}
			potential_scores[count] = score;
			break;
		case 1: //twos
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 2)
					score += 2;
			}
			potential_scores[count] = score;
			break;
		case 2: //threes
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 3)
					score += 3;
			}
			potential_scores[count] = score;
			break;
		case 3: //fours
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 4)
					score += 4;
			}
			potential_scores[count] = score;
			break;
		case 4: //fives
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 5)
					score += 5;
			}
			potential_scores[count] = score;
			break;
		case 5: //sixs
			for (i = 0; i < sizeof_dice; i++)
			{
				if (dice[i] == 6)
					score += 6;
			}
			potential_scores[count] = score;
			break;
		case 6: //threeof
			for (c = 1; c <= 6; c++)
			{
				for (n = 0; n < 5; n++)
				{
					if (dice[n] == c)
					{
						ofakind += 1;
					}
				}
				if (ofakind >= 3)
				{
					score = sum_of_dice(dice, 5);
					break;
				}
				else
				{
					ofakind = 0;
				}
			}
			potential_scores[count] = score;
			break;
		case 7: //fourof
			for (c = 1; c <= 6; c++)
			{
				for (n = 0; n < 5; n++)
				{
					if (dice[n] == c)
					{
						ofakind += 1;
					}
				}
				if (ofakind >= 4)
				{
					score = sum_of_dice(dice, 5);
					break;
				}
				else
				{
					ofakind = 0;
				}
			}
			potential_scores[count] = score;
			break;
		case 8: //fullhouse
			for (c = 1; c <= 6; c++)
			{
				for (i = 1; i < sizeof_dice; i++)
				{
					if (dice[((i + c) % sizeof_dice)] == dice[c])
					{
						ofakind += 1;
						break;
					}
				}
			}
			if (ofakind >= 5) 
			{
				potential_scores[count] = 25;
			}
			break;
		case 9: //smallst
			inarow = 0;
			for (c = 1; c <= 3; c++)
			{
				for (i = c; i < (c + 4) ; i++)
				{
					for (n = 0; n < 5; n++)
					{
						if (dice[n] == i)
						{
							inarow += 1;
							break;
						}
					}
				}
				if (inarow >= 4)
				{
					potential_scores[count] = 30;
					break;
				}
				else
				{
					inarow = 0;
				}
			}
			break;
		case 10: //largest
			inarow = 0;
			for (c = 1; c <= 2; c++)
			{
				for (i = c; i < (c + 5); i++)
				{
					for (n = 0; n < 5; n++)
					{
						if (dice[n] == i)
						{
							inarow += 1;
							break;
						}
					}
				}
				if (inarow >= 5)
				{
					potential_scores[count] = 40;
					break;
				}
				else
				{
					inarow = 0;
				}
			}
			break;
		case 11:
			for (i = 0; i < 5; i++)
			{
				score += dice[i];
			}
			potential_scores[count] = score;
			break;
		case 12:
			ofakind = 1;
			for (i = 0; i < sizeof_dice - 1; i++)
			{
				if (dice[i] == dice[i + 1])
				{
					ofakind += 1;
				}
			}
			if (ofakind == 5)
			{
				potential_scores[count] = 50;
			}
			break;
		case 13:
			break;
		case 14:
			break;
		default:
			break;
		}
	}
}

void print_score_card(char *scores, int sizeof_scores)
{
	if (sizeof_scores == 15) {
		printf("  ------------------------------------------------------------\n");
		printf(" | ONE's  |  TWO's  |  THREE's  |  FOUR's  |  FIVE's  |  SIX's|\n");
		printf(" |        |         |           |          |          |       |\n");
		printf(" |   %02d   |   %02d    |   %02d      |   %02d     |   %02d     |   %02d  |\n", scores[0], scores[1], scores[2], scores[3], scores[4], scores[5]);
		printf("  ------------------------------------------------------------\n");
		printf(" | THREE  |  FOUR   |  FULL     |  SMALL   |  LARGE   |       |\n");
		printf(" | KIND   |  KIND   |  HOUS     |  STR8    |  STR8    |       |\n");
		printf(" |   %02d   |   %02d    |   %02d      |   %02d     |   %02d     |       |\n", scores[6], scores[7], scores[8], scores[9], scores[10]);
		printf("  ------------------------------------------------------------\n");
		printf(" | CHANCE |  YAHTZEE|  BONUS    |  TOTAL   |          |       |\n");
		printf(" |        |         |           |          |          |       |\n");
		printf(" |   %02d   |   %02d    |   %02d      |   %02d     |          |       |\n", scores[11], scores[12], scores[13], scores[14]);
		printf("  ------------------------------------------------------------\n");
	}
	else
	{
		printf("error score_card incorrect arguments");
	}

}

char sum_of_dice(char *dice, int sizeof_dice)
{
	int sum = 0, i = 0;
	for (i = 0; i < sizeof_dice; i++)
	{
		sum += dice[i];
	}

	return sum;
}