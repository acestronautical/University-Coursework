/*******************************************************************************************
* Programmer: Ace Cassidy 011481306                                                        *
* Class: CptS 121, Spring  2017; Lab Section 9                                             *
* Programming Assignment: PA4                                                              *
* Date: February 13, 2017                                                                  *
* Description: A game of craps,  playable in a win32 console                               *
*******************************************************************************************/

#include"Craps.h"

//Prints out the rules of the game of "craps".
void print_game_rules(void) 
{
	printf("   ___\n");
	printf("  / __\\ __ __ _ _ __  ___\n");
	printf(" / / | '__/ _` | '_ \\/ __|\n");
	printf("/ /__| | | (_| | |_) \\__ \\\n");
	printf("\\____/_|  \\__,_| .__/|___/\n");
	printf("               |_|\n");


	printf("Welcome to Jim's Fabulous Back Alley Craps\n"
		"\n"
		"NO FIGHTING\n"
		"NO GUNS\n"
		"NO DOGS\n"
		"\n"
		"The Rules:\n"
		"A player rolls two dice. Each die has six faces.\n"
		"These faces contain 1, 2, 3, 4, 5, and 6 spots.\n"
		"After the dice have come to rest, the sum of the two dice is calculated.\n"
		"If the sum is 7 or 11 on the first throw, the player wins.\n"
		"If the sum is 2, 3, or 12 on the first throw, the player loses.\n"
		"If the sum is 4, 5, 6, 8, 9, or 10 on the first throw,\n"
		"then this sum becomes the player's \"point\"\n"
		"To win, you must continue rolling the dice until you \"make your point.\"\n"
		"The player loses by rolling a 7 before making the point.\n\n");
}



//Prompts the player for an initial bank balance from which wagering will be added or subtracted.
//The player entered bank balance(in dollars, i.e.$100.00) is returned.
double get_bank_balance(void) 
{
	double bank_balance = 0;
	while (bank_balance == 0) {
		printf("\nHow many chips do you want to buy?\n$");
		scanf(" %lf", &bank_balance);
	}
	return bank_balance;
}

//Prompts the player for a wager on a particular roll.The wager is returned.
double get_wager_amount(void) {
	double wager_amount = 0;
	scanf(" %lf", &wager_amount);

	return wager_amount;
}

//banters about how much you're wagering
void wager_banter(double wager_amount) 
{
	if (wager_amount >= 90)
	{
		printf("Looks like we got some big spenders here!\n");
	}
	else if (wager_amount >= 60)
	{
		printf("That's a nice healthy bet\n");
	}
	else if (wager_amount >= 20)
	{
		printf("Who's going to lose their beer vouchers this time?\n");
	}
	else
	{
		printf("Say goodbye to your lunch money!\n");
	}
}

//Checks to see if the wager is within the limits of the player's available balance. 
//If the wager exceeds the player's allowable balance, then 0 is returned; otherwise 1 is returned.
int check_wager_amount(double wager, double balance) 
{
	if (wager > balance || wager <= 0)
	{
		return 0;
	}

	return 1;
}

//pulls character out of the input buffer until newline or EOF
void eat_input_buffer(void)
{
	char alpha;
	while ((alpha = getchar()) != '\n' && alpha != EOF);
}

//Rolls one die.This function should randomly generate a value between 1 and 6, inclusively.Returns the value of the die.
int roll_die(void)
{
	int roll = 0;
	roll = (rand() % 6) + 1;
	return roll;
}


//Sums together the values of the two dice and returns the result.Note: this result may become the player's point in future rolls.
int calculate_sum_dice(int die1_value, int die2_value)
{
	int sum = die1_value + die2_value;
	return sum;
}


//Determines the result of the first dice roll.If the sum is 7 or 11 on the roll, the player wins and 1 is returned.
//If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses(i.e.the "house" wins) and 0 is returned.
//If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point" and -1 is returned.
int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice == 7 || sum_dice == 11) //equivalence has higher precedence than OR so no extra parens are needed
	{
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3  || sum_dice == 12)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


//Determines the result of any successive roll after the first roll.
//If the sum of the roll is the point_value, then 1 is returned.
//If the sum of the roll is a 7, then 0 is returned.Otherwise, -1 is returned.
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == point_value)
	{
		return 1;
	}
	else if (sum_dice == 7)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


//If add_or_subtract is 1, then the wager amount is added to the bank_balance.
//If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance.
//Otherwise, the bank_balance remains the same.The bank_balance result is returned.
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	double new_bank_balance = bank_balance;

	if (add_or_subtract == 1)
	{
		new_bank_balance = bank_balance + wager_amount;
	}
	else if (add_or_subtract == 0)
	{
		new_bank_balance = bank_balance - wager_amount;
	}

	return new_bank_balance;
}


//banters based on win or loss
void win_loss_banter(int win_loss_neither)
{
	if (win_loss_neither == 1)
	{
		printf("You win\n"
			"Rake it in\n");
	}
	else if (win_loss_neither == 0)
	{
		printf("You lose\n"
			"That just means you'll win next time\n");
	}
	else
	{
		printf("What are you doing boy?\n");
	}
}

//banters based on how many rolls have passed
void number_rolls_banter(int number_rolls) 
{
	if (number_rolls == 2)
	{
		printf("Time for round two!\n");
	}
	else if (number_rolls == 5)
	{
		printf("Now we're getting into the swing of things\n");
	}
	else if (number_rolls == 7)
	{
		printf("Back and forth the money goes!\n");
	}
	else if (number_rolls == 13)
	{
		printf("You boys are some real professional gamblers!\n");
	}
}

//Prints an appropriate message dependent on the number of rolls taken so far by the player, the current balance, and 
//whether or not the player just won his roll.The parameter win_loss_neither indicates the result of the previous roll.
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
	win_loss_banter(win_loss_neither);
	printf("\n");
	bank_balance_banter(initial_bank_balance, current_bank_balance);

	number_rolls_banter(number_rolls);
	printf("\n");
}

//prints ascii art
void print_dice_art(void)
{
	
	printf("  ____\n");
	printf(" /\\' .\\    _____\n");
	printf("/: \\___\\  / .  /\\\n");
	printf("\\' / . / /____/..\\\n");
	printf(" \\/___/  \\'  '\\  /\n");
	printf("          \\'__'\\/\n\n");


}

//prints ascii goodbye letters
void print_goodbye(void)
{
	printf("                       _ _\n");
	printf("  __ _  ___   ___   __| | |__  _   _  ___\n");
	printf(" / _` |/ _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\\n");
	printf("| (_| | (_) | (_) | (_| | |_) | |_| |  __/\n");
	printf(" \\__, |\\___/ \\___/ \\__,_|_.__/ \\__, |\\___|\n");
	printf(" |___/                         |___/\n");
}

//makes a press enter to continue prompt
void enter_to_continue(void)
{
	while(getchar() != '\n'); //I cannot tell a lie, I got this line from stack exchange. It's very nice though.
}


//banters based on your bank balance
void bank_balance_banter(double initial_bank_balance, double current_bank_balance)
{
	double net = current_bank_balance - initial_bank_balance;

	if (net > 0)
	{
		if (net >= 200)
		{
			printf("You're rich\n");
		}
		else if (net >= 70)
		{
			printf("You're hot now!\n");
		}
		else if (net >= 50)
		{
			printf("Daddy just got a new pair of shoes\n");
		}
		else if (net >= 2)
		{
			printf("Bet big while your luck is holding\n");
		}
		else
		{
			printf("Pretty much broke even on that one\n");
		}
	}

	if (net < 0)
	{
		if (net <= -99)
		{
			printf("You can gamble here as much as you want\n");
		}
		else if (net <= -49)
		{
			printf("You're luck is going to change soon\n");
		}
		else if (net <= -29)
		{
			printf("You'll get it back\n");
		}
		else if (net <= -9)
		{
			printf("Spend money to make money my friend\n");
		}
		else
		{
			printf("Broke even on that one\n");
		}
	}
}
