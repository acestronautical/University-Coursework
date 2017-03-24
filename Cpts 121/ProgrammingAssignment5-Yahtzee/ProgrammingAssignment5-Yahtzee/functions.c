/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA5                                                              *
* Date: February 27, 2017                                                                  *
* Description: A game of Yahtzee,  playable in a win32 console                             *
*******************************************************************************************/

#include "header.h"

//Prints out the rules of the game of yahtzee.
void print_game_rules(void)
{
	
printf(" __   __  _______  __   __  _______  _______  _______  _______ \n"
	   "|  | |  ||   _   ||  | |  ||       ||       ||       ||       |\n"
	   "|  |_|  ||  |_|  ||  |_|  ||_     _||____   ||    ___||    ___|\n"
	   "|       ||       ||       |  |   |   ____|  ||   |___ |   |___ \n"
	   "|_     _||       ||       |  |   |  | ______||    ___||    ___|\n"
	   "  |   |  |   _   ||   _   |  |   |  | |_____ |   |___ |   |___ \n"
	   "  |___|  |__| |__||__| |__|  |___|  |_______||_______||_______|\n\n");

printf("The Yahtzee goal is pretty straightforward:\n"
	   "You're trying for 12 different combinations of the five dice\n"
	   "You get a certain number of points for each combination you roll\n"
	   "Each combination has a slot on the score card\n"
	   "the goal is to fill each slot with the maximum number of points.\n\n");
}

//Prints out a chart of scoring combinations for yahtzee
void print_scoring_combinations(void)
{
	printf(""
		"The possible scoring combinations are\n\n"

		"Upper Section:\n"
		"Aces->   The sum of dice with the number 1\n"
		"Twos->   The sum of dice with the number 2\n"
		"Threes-> The sum of dice with the number 3\n"
		"Fours->  The sum of dice with the number 4\n"
		"Fives->  The sum of dice with the number 5\n"
		"Sixes->  The sum of dice with the number 6\n\n"

		"Lower Section :\n"
		"Three Of A Kind-> Sum of dice\n"
		"Four  Of A Kind-> Sum of dice\n"
		"A Full House->    25 points\n"
		"Small Straight->  30 points\n"
		"Large Straight->  40 points\n"
		"Yahtzee->         50 points\n"
		"Chance->          Sum of dice\n");
}

//prompts if the user wants to play and outputs a boolean
int want_to_play()
{
	char userchoice = 0;
	int userbool = 1;
	printf("\nWould you like to play Yahtzee?\n");
	scanf("%c", &userchoice);
	eat_input_buffer();

	if (userchoice == 'n' || userchoice == 'N' || userchoice == '0')
	{
		userbool = 0;
	}

	return userbool;
}

//pulls character out of the input buffer until newline or EOF
void eat_input_buffer(void)
{
	char alpha;
	while ((alpha = getchar()) != '\n' && alpha != EOF);
}

//instructs user on controls etc..
void how_to_play()
{
	printf(
		"How to Play:\n\n");
	GREEN_TEXT;
	printf(
		"Player one will roll first\n");
	BLUE_TEXT;
	printf(
		"Player Two will roll second\n\n");
	WHITE_TEXT;
	printf(
		"When choosing which dice to re-roll\n"
		"Enter 'y' to keep or 'hold' a given die\n"
		"Or enter 'n' to reroll or 'not hold' that die\n"
		"when done rolling press enter to continue\n\n"

		"After rolling, your dice for the round and\n"
		"Your score card will appear on screen\n\n"

		"Scores shown in red are potention scores for this round\n"
		"Scores in white are from previous rounds and cannot be changed\n\n"

		"Play proceeds until both players have filled their scorecards\n"
		"At which point a winner will be announced, or no winner if a tie\n\n"

		"Ready?\n"
		"Let's Begin!\n"
	);
}

//yahtzee game code game
int play_game()
{
	//set global randomness seed variable to time
	srand((unsigned)time(NULL));

	//score indices are as follows for player_one_score and player_two_scores
	// 0  ,   1 ,   2   ,  3   ,   4  ,   5 ,    6   ,    7  ,   8   ,   9    ,   10   ,   11  ,   12   ,   13 ,  14  ,  15
	//ones, twos, threes, fours, fives, sixs, threeof, fourof, fullhs, smallst, largest, chance, yahtzee, bonus, total, extra yahtzee
	int player_one_scores[15] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1 };
	int player_two_scores[15] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1 };

	//score indices are as follows for potential_scores
	// 0  ,   1 ,   2   ,  3   ,   4  ,   5 ,    6   ,    7  ,   8   ,   9    ,   10   ,   11  ,   12     
	//ones, twos, threes, fours, fives, sixs, threeof, fourof, fullhs, smallst, largest, chance, yahtzee
	int potential_scores[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//five_dice will hold rolled dice values 1-6
	//hold_dice will hold true false values 
	int five_dice[5] = { 0, 0, 0, 0, 0 };
	int hold_dice[5] = { 0, 0, 0, 0, 0 };

	int selection[2] = { 0, 0 };
	int playing = 1;

	while (playing)
	{
		playing = 0;

		if (!score_card_full(player_one_scores, 15))
		{
			GREEN_TEXT;
			printf("Player One Rolls\n");
			WHITE_TEXT;
			printf("\n('y' to hold | 'n' to reroll)\n");
			player_rolls(five_dice, 5, hold_dice, 5);
			enter_to_continue();
			system("cls");
			GREEN_TEXT;
			printf(" Player One Potential Scoring This Round\n");
			WHITE_TEXT;
			print_dice(five_dice, 5);
			printf(" Possible scores shown in red | Previously entered scores in white\n");
			potential_scoring(five_dice, 5, potential_scores, 13);
			compare_and_remove_scores(player_one_scores, 15, potential_scores, 13);
			print_score_card(player_one_scores, 15, potential_scores, 13);
			select_score(potential_scores, 13, selection, 2);
			player_one_scores[(int)(selection[0])] = selection[1];
			enter_to_continue();
			system("cls");
			playing = 1;
		}


		if (!score_card_full(player_two_scores, 15))
		{
			BLUE_TEXT;
			printf("Player Two Rolls\n");
			WHITE_TEXT;
			printf("\n('y' to hold | 'n' to reroll)\n");
			player_rolls(five_dice, 5, hold_dice, 5);
			enter_to_continue();
			system("cls");
			BLUE_TEXT;
			printf(" Player Two Potential Scoring This Round\n");
			WHITE_TEXT;
			print_dice(five_dice, 5);
			printf(" Possible scores shown in red | Previously entered scores in white\n");
			potential_scoring(five_dice, 5, potential_scores, 13);
			compare_and_remove_scores(player_two_scores, 15, potential_scores, 13);
			print_score_card(player_two_scores, 15, potential_scores, 13);
			select_score(potential_scores, 13, selection, 2);
			player_two_scores[(int)(selection[0])] = selection[1];
			enter_to_continue();
			system("cls");
			playing = 1;
		}

	}
	potential_scores[12] = -1;

	score_bonus_and_total(player_one_scores, 15);
	printf("Player One ScoreCard\n");
	print_score_card(player_one_scores, 15, potential_scores, 13);
	enter_to_continue();
	system("cls");

	score_bonus_and_total(player_two_scores, 15);
	printf("Player Two ScoreCard\n");
	print_score_card(player_two_scores, 15, potential_scores, 13);
	enter_to_continue();
	system("cls");

	if (player_one_scores[14] == player_two_scores[14])
	{
		printf("\n\n\n\nNO ONE WINS!!!!!!!!!!!!\n\n");
	}
	else if (player_one_scores[14] > player_two_scores[14])
	{
		printf("\n\n\n\nPLAYER ONE WINS!!!!!!!!!!!!\n\n");
	}
	else
	{
		printf("\n\n\n\nPLAYER TWO WINS!!!!!!!!!!!!\n\n");
	}

	return 0;
}

//rolls a single die and outputs a random 1-6
int roll_die(void)
{
	int roll = 0;
	roll = (rand() % 6) + 1;
	return roll;
}

//gets characters until one of them is newline
void enter_to_continue(void)
{
	RED_TEXT;
	printf("\n\npress enter\n");
	WHITE_TEXT;
	while (getchar() != '\n');
}

//enters a random value from 1-6 in all elements of passed array for which parralel hold array is false
void randomize_dice(int *dice, int sizeof_dice, int *hold_dice, int sizeof_hold_dice)
{
	if (sizeof_dice == sizeof_hold_dice) {
		for (int i = 0; i < sizeof_dice; i++)
		{
			if (!hold_dice[i])
			{
				dice[i] = roll_die();
			}
		}
	}
	else
	{
		printf("error incorrect arguments");
	}
}

//uses getche() prompt to propagate all elements of hold array with boolean values
//0 or 'n' or 'N' are false all others are true
void hold_which_dice(int *hold_dice, int sizeof_hold_dice)
{
	for (int i = 0; i < sizeof_hold_dice; i++)
	{
		printf("  hold? ");
		hold_dice[i] = _getche();
		printf("  ");

		if (hold_dice[i] == 'n' || hold_dice[i] == 'N')
		{
			hold_dice[i] = 0;
		}
	}
}

//roll dice, prompt which to hold, reroll non held dice, prompt which to hold, reroll non held dice, reset hold dice array to 0's
void player_rolls(int *dice, int sizeof_dice, int *hold_dice, int sizeof_hold_dice)
{
	for (int i = 0; i < 3; i++)
	{
		randomize_dice(dice, sizeof_dice, hold_dice, sizeof_hold_dice);
		print_dice(dice, sizeof_dice);
		if (i < 2)
		{
			hold_which_dice(hold_dice, sizeof_hold_dice);
		}
	}
	for (int i = 0; i < sizeof_hold_dice; i++)
	{
		hold_dice[i] = 0;
	}
}

//prints any number of 6 sided dice values from an array horizontally with ascii art 
void print_dice(int *dice, int sizeof_dice)
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

//iterates through all possible scorings and saves the values into potential_scores
void potential_scoring(int *dice, int sizeof_dice, int *potential_scores, int sizeof_potential_scores)
{
	//potential score array indexes are as follows
	// 0  ,   1 ,   2   ,  3   ,   4  ,   5 ,    6   ,    7  ,   8   ,   9    ,   10   ,   11  ,   12   
	//ones, twos, threes, fours, fives, sixs, threeof, fourof, fullhs, smallst, largest, chance, yahtzee
	int score;
	int ofakind, i, c, n, inarow;

	for (int count = 0; count < sizeof_potential_scores; count++)
	{
		ofakind = 0, inarow = 0, score = 0, i = 0, c = 0, n = 0;

		switch (count)
		{
		case 0: //ones
		case 1: //twos
		case 2: //threes
		case 3: //fours
		case 4: //fives
		case 5: //sixs
			//case 1-5 have same scoring algorithm
			potential_scores[count] = sum_of_target((count + 1), dice, 5);
			break;
		case 6: //three of a kind
			for (c = 0; c <= 3; c++)
			{
				for (n = 0; n < 5; n++)
				{
					if (dice[n] == dice[c])
					{
						ofakind += 1;
					}

					if (ofakind >= 3)
					{
						score = sum_of_array(dice, 5);
						break;
					}
				}
				ofakind = 0;
			}
			potential_scores[count] = score;
			break;
		case 7: //four of a kind
			for (c = 0; c <= 3; c++)
			{
				for (n = 0; n < 5; n++)
				{
					if (dice[n] == dice[c])
					{
						ofakind += 1;
					}

					if (ofakind >= 4)
					{
						score = sum_of_array(dice, 5);
						break;
					}
				}
				ofakind = 0;
			}
			potential_scores[count] = score;
			break;
		case 8: //full house
			for (c = 0; c <= sizeof_dice; c++)
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
				score = 25;
			}
			potential_scores[count] = score;
			break;
		case 9: //small straight
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
					score = 30;
					break;
				}
				else
				{
					inarow = 0;
				}
			}
			potential_scores[count] = score;
			break;
		case 10: //large straight
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
					score = 40;
					break;
				}
				else
				{
					inarow = 0;
				}
			}
			potential_scores[count] = score;
			break;
		case 11://chance
			score = sum_of_array(dice, 5);
			potential_scores[count] = score;
			break;
		case 12://yahtzee
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
				score = 50;
			}
			potential_scores[count] = score;
			break;
		default: //default case should never trigger
			printf("something went wrong\n check your array size\n");
			break;
		}
	}
}

//compares scores already entered on scorecard with potential scores for round
//removes scores from potential scores for round if they have already been scored
//special case for yahtzee to allow multiple yahtzee's to score
void compare_and_remove_scores(int *scores, int size_scores, int *potential_scores, int sizeof_potential_scores)
{
	//if more than one yahtzee is sitting on the scorecard move the extra points into the bonus score as per yahtzee rules
	if (scores[sizeof_potential_scores - 1] > 50)
	{
		scores[sizeof_potential_scores - 1] -= 50;
		if (scores[sizeof_potential_scores] == -1)
		{
			//case to correct for addition with -1
			//i'm using -1 in my score arrays to represent empty
			scores[sizeof_potential_scores] += 51;
		}
		else
		{
			scores[sizeof_potential_scores] += 50;
		}
	}

	//if score exists on scorecard signify it as no possible on potential scores by changing value to -1
	for (int i = 0; i < sizeof_potential_scores - 1; i++)
	{
		if (scores[i] != -1)
		{
			potential_scores[i] = -1;
		}
	}

	//special cases for scoring multiple yahtzee's
	if (potential_scores[sizeof_potential_scores - 1] == 0 && scores[sizeof_potential_scores - 1] == -1)
	{
		potential_scores[sizeof_potential_scores - 1] = 0;
	}
	else if (potential_scores[sizeof_potential_scores - 1] == 0 && scores[sizeof_potential_scores - 1] == 0)
	{
		potential_scores[sizeof_potential_scores - 1] = -1;
	}
	else if (potential_scores[sizeof_potential_scores - 1] == 50 && scores[sizeof_potential_scores - 1] != -1)
	{
		potential_scores[sizeof_potential_scores - 1] += scores[sizeof_potential_scores - 1];
	}
	else if (potential_scores[sizeof_potential_scores - 1] == 50 && scores[sizeof_potential_scores - 1] == -1)
	{
		potential_scores[sizeof_potential_scores - 1] = 50;
	}

}

//prompts  user to select the letter next to the score they want to use
//maps 'A'-'M' && 'a'-'m' to 0-12 array indices with switch case
//re prompts if value in potential scores for selection if -1
void select_score(int *potential_scores, int sizeof_potential_scores, int *selection, int sizeof_selection)

{
	selection[0] = -1;
	selection[1] = -1;
	int choice = 'z';
	if (sizeof_selection == 2 && sizeof_potential_scores == 13)
	{
		while (selection[1] == -1)
		{
			printf("What box would you like to score?\n(Select A-M)\n");
			scanf(" %c", &choice);

			switch (choice)
			{
			case 'a':
			case 'A':
				selection[0] = 0;
				selection[1] = potential_scores[0];
				break;
			case 'b':
			case 'B':
				selection[0] = 1;
				selection[1] = potential_scores[1];
				break;
			case 'c':
			case 'C':
				selection[0] = 2;
				selection[1] = potential_scores[2];
				break;
			case 'd':
			case 'D':
				selection[0] = 3;
				selection[1] = potential_scores[3];
				break;
			case 'e':
			case 'E':
				selection[0] = 4;
				selection[1] = potential_scores[4];
				break;
			case 'f':
			case 'F':
				selection[0] = 5;
				selection[1] = potential_scores[5];
				break;
			case 'g':
			case 'G':
				selection[0] = 6;
				selection[1] = potential_scores[6];
				break;
			case 'h':
			case 'H':
				selection[0] = 7;
				selection[1] = potential_scores[7];
				break;
			case 'i':
			case 'I':
				selection[0] = 8;
				selection[1] = potential_scores[8];
				break;
			case 'j':
			case 'J':
				selection[0] = 9;
				selection[1] = potential_scores[9];
				break;
			case 'k':
			case 'K':
				selection[0] = 10;
				selection[1] = potential_scores[10];
				break;
			case 'l':
			case 'L':
				selection[0] = 11;
				selection[1] = potential_scores[11];
				break;
			case 'm':
			case 'M':
				selection[0] = 12;
				selection[1] = potential_scores[12];
				break;
			default:
				printf("invalid selection\n");
				break;
			}
		}
	}
}

//uses macro defined SetConsoleTextAttribute to switch text from red to white
//logically prints enterable scores red and previously entered scores white using ternary expressions
void print_score_card(int *scores, int sizeof_scores, int *potential_scores, int sizeof_potential_scores)
{
	int n = 0;

	printf("  ----------------------------------------------------------------\n");
	printf(" |A.ONE's   |B.TWO's   |C.THREE's |D.FOUR's  |E.FIVE's  |F.SIX's  |\n");
	printf(" |          |          |          |          |          |         |\n");
	printf(" |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("    |\n");
	printf("  --------------------------------------------------------------- \n");
	printf(" |G.THREE   |H.FOUR    |I.FULL    |J.SMALL   |K.LARGE   |         |\n");
	printf(" |  KIND    |  KIND    |  HOUS    |  STR8    |  STR8    |         |\n");
	printf(" |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |         |\n");
	printf("  ---------------------------------------------------------------- \n");
	printf(" |L.CHANCE  |M.YAHTZEE |          |          |  BONUS   |  TOTAL  |\n");
	printf(" |          |          |          |          |          |         |\n");
	printf(" |   ");
	(scores[n] == -1) ? RED_TEXT,  printf("%02d", potential_scores[n]), WHITE_TEXT: printf("%02d", scores[n]);
	n++;
	printf("     |   ");
	(scores[n] < potential_scores[n]) ? RED_TEXT,  printf("%03d", potential_scores[n]), WHITE_TEXT: printf("%03d", scores[n]);
	n++;
	printf("    |          |          |   ");
	(scores[n] == -1 ) ? printf("%c%c%c", ' ', ' ', ' ') : printf("%03d", scores[n]);
	n++;
	printf("    |   ");
	(scores[n] == -1 ) ? printf("%c%c%c", ' ', ' ', ' ') : printf("%03d", scores[n]);
	n++;
	printf("   |\n");
	printf("  ----------------------------------------------------------------\n");

}

//iterates through an array and adds all elements of the array, returns the sum
int sum_of_array(int *dice, int sizeof_dice)
{
	int sum = 0, i = 0;
	for (i = 0; i < sizeof_dice; i++)
	{
		sum += dice[i];
	}

	return sum;
}

//looks for target value in given array and sums up all matching elements, returns the sum EX: add all ones in an array
int sum_of_target(int target, int *array, int sizeof_array)
{
	int i;
	int return_value = 0;
	for (i = 0; i < sizeof_array; i++)
	{
		if (array[i] == target)
			return_value += target;
	}
	return return_value;
}

//checks if all elements of the score card array are not -1
// -1 signifies emptiness in this program
int score_card_full(int *scores, int sizeof_scores)
{
	int return_value = 1;
	int i;

	for (i = 0; i < sizeof_scores - 2; i++)
	{
		if (scores[i] == -1)
		{
			return_value = 0;
			break;
		}
	}

	return return_value;
}

//calculates bonus and total score and puts them into end of array
void score_bonus_and_total(int *scores, int sizeof_scores)
{
	int total_upper_section = 0;
	scores[sizeof_scores - 2] = 0;

	for (int i = 0; i < sizeof_scores - 9; i++)
	{
		total_upper_section += scores[i];
	}

	if (total_upper_section >= 63)
	{
		if (scores[sizeof_scores - 2] == -1)
		{
			scores[sizeof_scores - 2] == 35;
		}
		else if (scores[sizeof_scores - 2] > -1)
		{
			scores[sizeof_scores - 2] += 35;
		}
	}

	scores[sizeof_scores - 1] = sum_of_array(scores, 14);
}
